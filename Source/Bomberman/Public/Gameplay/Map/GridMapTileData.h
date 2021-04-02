#pragma once

#include "CoreMinimal.h"
#include "GridMapTileData.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FGridMapTileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridMapTileData")
		TSubclassOf<class AActor> TileClass;

	// Whether or not the tile is a navigation obstacle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridMapTileData")
		bool bIsObstacle;
};
