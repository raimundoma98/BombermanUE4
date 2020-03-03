// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Wall.generated.h"

UCLASS()
class BOMBERMAN_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMesh* DestructibleMesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMesh* IndestructibleMesh;

private:
  bool bIsDestructible;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  void SetDestructible(bool Destructible);
};
