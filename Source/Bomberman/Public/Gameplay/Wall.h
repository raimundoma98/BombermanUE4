// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Wall.generated.h"

class APickup;

UCLASS()
class BOMBERMAN_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    TArray<TSubclassOf<APickup>> PickupsBP;

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    UMaterialInterface* DestructibleMaterial;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    UMaterialInterface* InDestructibleMaterial;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties",
    meta = (UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100))
    int32 SpawnPickupProbability;

private:
  bool bIsDestructible;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
  virtual void BeginDestroy() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  void Break();

  bool IsDestructible() const;
  void SetDestructible(bool Destructible);
};
