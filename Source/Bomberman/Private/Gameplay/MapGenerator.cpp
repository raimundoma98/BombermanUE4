// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Gameplay/MapGenerator.h"
#include "Bomberman/Public/Core/GameFramework/BombermanGameModeBase.h"
#include "Bomberman/Public/Gameplay/Wall.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(
    FName(TEXT("Floor Mesh")));
  SetRootComponent(FloorMesh);

  MapSize = 4;
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

  ABombermanGameModeBase* GameMode = Cast<ABombermanGameModeBase>(
    UGameplayStatics::GetGameMode(GetWorld()));

  if (GameMode != NULL && GameMode->MapGenerator.IsValid() == false) {
    GameMode->MapGenerator = this;
  }

  FVector Min;
  FVector Max;
  FloorMesh->GetLocalBounds(Min, Max);

  TileSize = (TileScale * Max.X * 2.0f);

  DrawDebugBox(GetWorld(), GetActorLocation(),
    Max, FColor::Green, false, 
    5.0f, (uint8)'\000', 3.0f);

  if (bGenerateMapOnBeginPlay)
    GenerateMap();
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::GenerateMap() {

  FVector MapScale = FVector(MapSize * TileScale, MapSize * TileScale, 1.0f);
  FloorMesh->SetRelativeScale3D(MapScale);

  if (WallBP == NULL) {
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,
      TEXT("AMapGenerator::GenerateMap: Invalid Wall BP"));
    return;
  }

  FVector TopLeft;
  FVector Extent;
  GetActorBounds(true, TopLeft, Extent);

  float HalfTileSize = TileSize * 0.5f;

  // Calculate center position of the top-left tile.
  TopLeft = (TopLeft - Extent) +
    FVector(HalfTileSize, HalfTileSize, 0.0f);
  FVector Location = TopLeft;

  // Traverse tiles and choose randomly to spawn a wall or not.
  for (int32 i = 0; i < MapSize; ++i) {
    for (int32 j = 0; j < MapSize; ++j) {
      // Check if tile is border and spawn indestructible blocks.
      if (i == 0 || i == MapSize - 1 || j == 0 || j == MapSize - 1) {
        // Right border wall.
        AWall* Wall = GetWorld()->SpawnActor<AWall>(WallBP, Location,
          FRotator::ZeroRotator);

        Wall->SetActorScale3D(FVector(TileScale, TileScale, TileZScale));
        // TODO: Adjust Z location.
        Wall->SetDestructible(false);
      }
      else if (FMath::RandBool()) {
        // Choose randomly to spawn a wall or not.

        AWall* Wall = GetWorld()->SpawnActor<AWall>(WallBP, Location,
          FRotator::ZeroRotator);

        Wall->SetActorScale3D(FVector(TileScale, TileScale, TileZScale));
        // TODO: Adjust Z location.

        // Choose randomly if a wall is destructible or not.
        Wall->SetDestructible(FMath::RandBool());
      }
      Location.Y += TileSize;
    }
    Location.Y = TopLeft.Y;
    Location.X += TileSize;
  }
}

float AMapGenerator::GetTileSize() const {
  return TileSize;
}

void AMapGenerator::ShowDebugGrid() {
  FVector TopLeft;
  FVector Extent;
  GetActorBounds(true, TopLeft, Extent);

  float HalfTileSize = TileSize * 0.5f; 

  // Calculate center position of the top-left tile.
  TopLeft = (TopLeft - Extent) +
    FVector(HalfTileSize, HalfTileSize, 0.0f);
  
  FVector Location = TopLeft;
  Extent = FVector(HalfTileSize, HalfTileSize, 1.0f);

  for (int32 i = 0; i < MapSize; ++i) {
    for (int32 j = 0; j < MapSize; ++j) {
      DrawDebugBox(GetWorld(), Location,
        Extent, FColor::Green, false, 5.0f,
        (uint8)'\000', 3.0f);
      
      Location.Y += TileSize;
    }
    Location.Y = TopLeft.Y;
    Location.X += TileSize;
  }
}
