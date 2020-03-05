// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Core/GameFramework/BombermanGameModeBase.h"
#include "Bomberman/Public/Core/GameFramework/BombermanGameInstance.h"
#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "Bomberman/Public/Core/Characters/MyPlayerController.h"
#include "Bomberman/Public/Gameplay/MapGenerator.h"
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

  APlayerController* Controller = UGameplayStatics::GetPlayerController(
    GetWorld(), 1);

  // Create a new player only if there is just one player in the game.
  if (Controller == NULL) {
    Controller = UGameplayStatics::CreatePlayer(GetWorld());
  }

  Super::StartPlay();

  // Move players to a valid location in the map.
  if (MapGenerator.IsValid()) {
    const TArray<FVector>& AvailableLocations =
      MapGenerator->GetAvailableStartLocations();

    if (AvailableLocations.Num() > 1) {
      if (Controller != NULL && Controller->GetPawn() != NULL) {
        FVector Location =
          AvailableLocations[FMath::RandRange(0, AvailableLocations.Num() - 1)];
        Location.Z = Controller->GetPawn()->GetActorLocation().Z;
        Controller->GetPawn()->SetActorLocation(Location);
      }

      Controller = UGameplayStatics::GetPlayerController(
        GetWorld(), 0);

      if (Controller != NULL && Controller->GetPawn() != NULL) {
        FVector Location =
          AvailableLocations[FMath::RandRange(0, AvailableLocations.Num() - 1)];
        Location.Z = Controller->GetPawn()->GetActorLocation().Z;
        Controller->GetPawn()->SetActorLocation(Location);
      }
    }
  }

  // Store references to players.
  AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(
    UGameplayStatics::GetPlayerController(GetWorld(), 0));

  if (MyPlayerController != NULL) {
    Player1 = MyPlayerController->GetPlayer1();
    Player2 = MyPlayerController->GetPlayer2();
  }
}

void ABombermanGameModeBase::CheckEndGame() {
  if ((Player1.IsValid() && Player1->IsAlive() == false) ||
    (Player2.IsValid() && Player2->IsAlive() == false)) {
    PlayerDeath();
  }
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

void ABombermanGameModeBase::PlayerDeath() {
  AMyPlayerController* Controller = Cast<AMyPlayerController>(
    UGameplayStatics::GetPlayerController(GetWorld(), 0));

  if (Controller != NULL) {
    if (Player1.IsValid() && Player2.IsValid()) {
      if (Player1->IsAlive() == false && Player2->IsAlive() == false) {
        EndGame(TEXT("Draw"), FLinearColor::White);
      }
      else {
        FString Result;
        FColor WinnerColor;
        uint8 PlayerId = 0;

        if (Player1->IsAlive()) {
          Result = Player1->GetName() + TEXT(" wins!");
          WinnerColor = Controller->Player1Color;
        }
        else {
          Result = Player2->GetName() + TEXT(" wins!");
          WinnerColor = Controller->Player2Color;
          PlayerId = 1;
        }

        UBombermanGameInstance* GameInstance = Cast<UBombermanGameInstance>(
          GetGameInstance());

        if (GameInstance != NULL) {
          GameInstance->OnPlayerWins.Broadcast(PlayerId);
        }

        EndGame(Result, FLinearColor::FromSRGBColor(WinnerColor));
      }
    }
  }
}
