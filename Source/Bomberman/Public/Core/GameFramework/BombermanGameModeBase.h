// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameModeBase.generated.h"

class APlayerCharacter;
class ABombermanCameraActor;
class AMapGenerator;

DECLARE_MULTICAST_DELEGATE(FOnPlayerDeath)

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
  TWeakObjectPtr<APlayerCharacter> Player1;
  TWeakObjectPtr<APlayerCharacter> Player2;

public:
  virtual void StartPlay() override;

  void CheckEndGame();

  UFUNCTION(BlueprintCallable)
    float GetCountDownDuration() const;

  UFUNCTION(BlueprintCallable)
    float GetTimeRemaining() const;

protected:
  virtual void BeginPlay() override;

  UFUNCTION(BlueprintImplementableEvent)
  void EndGame(const FString& ResultText, FLinearColor TextColor);

private:
  UFUNCTION()
    void CountDownFinished();

  UFUNCTION()
    void PlayerDeath();
};
