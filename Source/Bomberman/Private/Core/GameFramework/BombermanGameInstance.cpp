// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanGameInstance.h"
#include "Kismet/GameplayStatics.h"

UBombermanGameInstance::UBombermanGameInstance() {
  Player1Score = 0;
  Player2Score = 0;
}

void UBombermanGameInstance::Init() {
  Super::Init();

  OnPlayerWins.AddUObject(this, &UBombermanGameInstance::AddScoreToPlayer);
}

int32 UBombermanGameInstance::GetPlayer1Score() const {
  return Player1Score;
}

int32 UBombermanGameInstance::GetPlayer2Score() const {
  return Player2Score;
}

void UBombermanGameInstance::AddScoreToPlayer(uint8 PlayerId) {
  if (PlayerId == 0) {
    ++Player1Score;
  }
  else {
    ++Player2Score;
  }
}
