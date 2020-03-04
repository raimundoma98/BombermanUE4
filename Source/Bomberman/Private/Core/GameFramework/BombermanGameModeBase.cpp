// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Core/GameFramework/BombermanGameModeBase.h"
#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ABombermanGameModeBase::ABombermanGameModeBase() {

}

void ABombermanGameModeBase::BeginPlay() {
  Super::BeginPlay();

  OnPlayerDeath.AddUObject(this, &ABombermanGameModeBase::PlayerDeath);

  GetWorldTimerManager().SetTimer(CountDownTimer, this, 
    &ABombermanGameModeBase::CountDownFinished, CountDownDuration, false);
}

void ABombermanGameModeBase::StartPlay() {
  APlayerController* Controller = UGameplayStatics::CreatePlayer(GetWorld());

  Super::StartPlay();
}

void ABombermanGameModeBase::CountDownFinished() {
  // Show draw image.
  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
    TEXT("ABombermanGameModeBase::CountDownFinished"));
}

void ABombermanGameModeBase::PlayerDeath(APlayerCharacter* Player) {
  // Show player victory.
  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
    TEXT("ABombermanGameModeBase::PlayerDeath"));
}
