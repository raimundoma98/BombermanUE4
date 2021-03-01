// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MapGeneratorFromTexture.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN_API UMapGeneratorFromTexture : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMapGeneratorFromTexture();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, CallInEditor)
		void GenerateMap();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneratorFromTexture")
		class UTexture2D* MapTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneratorFromTexture")
		FVector2D TileSize;

	// Convert a color to a tile actor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneratorFromTexture")
		TMap<FColor, TSubclassOf<AActor>> ColorToTileMap;

	// Tile that will be spawned when a color is not found on the ColorToTileMap.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneratorFromTexture")
		TSubclassOf<AActor> DefaultTile;
};
