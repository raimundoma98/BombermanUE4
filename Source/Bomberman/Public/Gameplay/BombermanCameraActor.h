// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "BombermanCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABombermanCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
public:
  ABombermanCameraActor();

  UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Properties")
    TWeakObjectPtr<AActor> FocusedActor;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    float ZDistance;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    float MaxPlayersDistance;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    float MinZDistance;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    float MaxZDistance;

private:
  TWeakObjectPtr<AActor> Player1;
  TWeakObjectPtr<AActor> Player2;

protected:
  virtual void BeginPlay() override;

public:
  virtual void Tick(float DeltaTime) override;

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void ScreenShake(float Duration, float Magnitude);
};
