// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanGameModeBase.h"
#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ABombermanGameModeBase::ABombermanGameModeBase() {

}

void ABombermanGameModeBase::BeginPlay() {
  Super::BeginPlay();
}

void ABombermanGameModeBase::StartPlay() {
  APlayerController* Controller = UGameplayStatics::CreatePlayer(GetWorld());

  Super::StartPlay();
}
