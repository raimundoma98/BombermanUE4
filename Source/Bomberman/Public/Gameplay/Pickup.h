// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Pickup.generated.h"

UCLASS(Abstract)
class BOMBERMAN_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
  void Activate(APlayerCharacter* Player);
  virtual void Activate_Implementation(APlayerCharacter* Player);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
  UFUNCTION()
    void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
