// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Bomb.generated.h"

DECLARE_DELEGATE(FOnExplode)

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

  FOnExplode OnExplode;

  UPROPERTY(EditAnywhere, Category = "Properties")
  float ExplosionDistance;

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* BombMesh;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* WickMesh;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    float ExplosionCountDown;

private:
  FTimerHandle ExplosionTimer;

protected:
  // Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
  UFUNCTION()
    void Explode();

  void CheckBlastCollision(AActor* HitActor);
};
