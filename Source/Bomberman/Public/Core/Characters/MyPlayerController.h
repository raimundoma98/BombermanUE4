// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
  AMyPlayerController();

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    FColor Player1Color;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    FColor Player2Color;

protected:
  UPROPERTY()
    APlayerCharacter* Player1;

  UPROPERTY()
    APlayerCharacter* Player2;

public:
  APlayerCharacter* GetPlayer1() const;
  APlayerCharacter* GetPlayer2() const;

protected:
  virtual void BeginPlay() override;
  virtual void SetupInputComponent() override;

private:
  UFUNCTION()
    void ActionPlayer1();

  UFUNCTION()
    void ActionPlayer2();

  UFUNCTION()
    void MoveForwardPlayer1(float Value);

  UFUNCTION()
    void MoveForwardPlayer2(float Value);

  UFUNCTION()
    void MoveRightPlayer1(float Value);

  UFUNCTION()
    void MoveRightPlayer2(float Value);
};
