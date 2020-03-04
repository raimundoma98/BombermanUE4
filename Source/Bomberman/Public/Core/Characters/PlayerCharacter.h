// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
#include "PlayerCharacter.generated.h"

class ABomb;

UCLASS()
class BOMBERMAN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    TSubclassOf<ABomb> BombBP;

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTextRenderComponent* NameText;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", 
    meta=(UIMin=0, ClampMin=0))
    int32 StartBombs;

  // Distance of bomb blasts in units of tiles.
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties",
    meta = (UIMin = 1, ClampMin = 1))
    int32 StartBombBlastDistance;

private:
  int32 CurrentBombs;
  int32 BombBlastDistance;

protected:
  // Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  UFUNCTION()
    void Action();

  UFUNCTION(BlueprintCallable)
    void AddBombs(int32 Count = 1);

  UFUNCTION(BlueprintCallable)
    void IncreaseBombBlastDistance(int32 Units = 1);

  void Kill();

  UFUNCTION()
    void MoveForward(float Value);

  UFUNCTION()
    void MoveRight(float Value);

  void SetColor(FColor Color);

private:
  UFUNCTION()
    void OnBombExplode();
};
