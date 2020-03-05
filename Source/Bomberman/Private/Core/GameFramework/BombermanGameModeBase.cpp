// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Core/GameFramework/BombermanGameModeBase.h"
#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "Bomberman/Public/Core/Characters/MyPlayerController.h"
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
  EndGame(TEXT("Draw"), FLinearColor::White);

  GetWorldTimerManager().ClearTimer(CountDownTimer);
}

float ABombermanGameModeBase::GetCountDownDuration() const {
  return CountDownDuration;
}

float ABombermanGameModeBase::GetTimeRemaining() const {
  return GetWorldTimerManager().GetTimerRemaining(CountDownTimer);
}

void ABombermanGameModeBase::PlayerDeath(APlayerCharacter* Player) {
  AMyPlayerController* Controller = Cast<AMyPlayerController>(
    UGameplayStatics::GetPlayerController(GetWorld(), 0));

  if (Controller != NULL) {
    APlayerCharacter* Player1 = Controller->GetPlayer1();
    APlayerCharacter* Player2 = Controller->GetPlayer2();
    if (Player1 != NULL && Player2 != NULL) {
      if (Player1->IsAlive() == false && Player2->IsAlive() == false) {
        EndGame(TEXT("Draw"), FLinearColor::White);
      }
      else if (Player1->IsAlive()) {
        FString Result = Player1->GetName() + TEXT(" wins!");
        EndGame(Result, FLinearColor::FromSRGBColor(Controller->Player1Color));
      }
      else {
        FString Result = Player2->GetName() + TEXT(" wins!");
        EndGame(Result, FLinearColor::FromSRGBColor(Controller->Player2Color));
      }
    }
  }
}
