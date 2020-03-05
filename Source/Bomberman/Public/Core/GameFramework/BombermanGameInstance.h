// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BombermanGameInstance.generated.h"

class ABombermanGameModeBase;

DECLARE_EVENT_OneParam(ABombermanGameModeBase, FOnPlayerWins, uint8)

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UBombermanGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
  UBombermanGameInstance();

  FOnPlayerWins OnPlayerWins;

private:
  int32 Player1Score;
  int32 Player2Score;

public:
  virtual void Init() override;
  
  UFUNCTION(BlueprintCallable)
    int32 GetPlayer1Score() const;

  UFUNCTION(BlueprintCallable)
    int32 GetPlayer2Score() const;

private:
  UFUNCTION()
    void AddScoreToPlayer(uint8 PlayerId);
};
