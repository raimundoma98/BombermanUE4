// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MapGenerator.generated.h"

class AWall;

UCLASS()
class BOMBERMAN_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bGenerateMapOnBeginPlay;

protected:
  // Mesh that represents the floor of the map.
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* FloorMesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties",
    meta = (UIMin = 0.0f, ClampMin = 0.0f))
    float TileZScale;

  // Scale of the tiles of the map.
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties",
    meta = (ClampMin = 0.0f, UIMin = 0.0f))
    float TileScale;

  // Number of tiles in each axis.
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", 
    meta = (ClampMin = 4, UIMin = 4))
    int32 MapSize;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    TSubclassOf<AWall> WallBP;

  // Size of the tiles of the map.
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
    float TileSize;

private:
  TArray<FVector> AvailableStartLocations;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  void GenerateMap();
  const TArray<FVector>& GetAvailableStartLocations() const;
  float GetTileSize() const;

  UFUNCTION(CallInEditor, Category = "Debug")
    void ShowDebugGrid();
};
