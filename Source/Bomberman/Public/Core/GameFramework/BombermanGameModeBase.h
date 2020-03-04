// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameModeBase.generated.h"

class APlayerCharacter;
class ABombermanCameraActor;
class AMapGenerator;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDeath, APlayerCharacter*)

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABombermanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
  ABombermanGameModeBase();

  FOnPlayerDeath OnPlayerDeath;

  UPROPERTY(BlueprintReadWrite)
  TWeakObjectPtr<ABombermanCameraActor> MainCamera;

  UPROPERTY(BlueprintReadWrite)
    TWeakObjectPtr<AMapGenerator> MapGenerator;

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
    float CountDownDuration;

private:
  FTimerHandle CountDownTimer;

public:
  virtual void StartPlay() override;

protected:
  virtual void BeginPlay() override;

private:
  UFUNCTION()
    void CountDownFinished();

  UFUNCTION()
    void PlayerDeath(APlayerCharacter* Player);
};
