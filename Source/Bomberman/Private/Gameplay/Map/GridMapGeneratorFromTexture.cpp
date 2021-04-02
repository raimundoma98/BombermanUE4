// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Map/GridMapGeneratorFromTexture.h"
#include "Gameplay/Map/GridMap.h"
#include "Gameplay/Map/GridMapTileData.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/TextureUtilsLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGridMapGeneratorFromTexture::UGridMapGeneratorFromTexture()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bIsEditorOnly = true;
}


// Called when the game starts
void UGridMapGeneratorFromTexture::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGridMapGeneratorFromTexture::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGridMapGeneratorFromTexture::GenerateMap()
{
	if (!IsValid(MapTexture))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), 
			TEXT("UGridMapGeneratorFromTexture::GenerateMap: Invalid texture"), 
			true, true, FColor::Red);
		return;
	}

	TArray<FColor> Pixels;

	if (!UTextureUtilsLibrary::GetPixelsFromTexture(MapTexture, Pixels))
	{
		UKismetSystemLibrary::PrintString(GetWorld(),
			TEXT("UGridMapGeneratorFromTexture::GenerateMap: Could not read map texture pixels"), 
			true, true, FColor::Red);
		return;
	}

	AGridMap* GridMap = Cast<AGridMap>(GetOwner());
	
	if (!IsValid(GridMap))
	{
		UKismetSystemLibrary::PrintString(GetWorld(),
			TEXT("UGridMapGeneratorFromTexture::GenerateMap: Invalid owner, this component should be attached to an actor of type AGridMap"), 
			true, true, FColor::Red);
	}


	ClearMap();

	int32 SizeX = MapTexture->GetSizeX();
	int32 SizeY = MapTexture->GetSizeY();

	//GridMap->Initialize(SizeX, SizeY);

	float TotalMapWidth = static_cast<float>(SizeX) * TileSize.X;
	float TotalMapHeight = static_cast<float>(SizeY) * TileSize.Y;

	FVector InitialLocation = GetOwner()->GetActorLocation() -
		FVector(TotalMapWidth * 0.5f, TotalMapHeight * 0.5f, 0.0f) + 
		FVector(TileSize.X * 0.5f, TileSize.Y * 0.5f, 0.0f);
	FVector SpawnLocation = InitialLocation;
	SpawnLocation.Z += TileSize.Z * 0.5f;

	for (int32 Y = 0; Y < SizeY; ++Y)
	{
		for (int32 X = 0; X < SizeX; ++X)
		{
			FGridMapTileData* TileData = ColorToTileMap.Find(Pixels[Y * SizeX + X]);
			FVector Extent = FVector(TileSize.X * 0.5f, TileSize.Y * 0.5f, TileSize.Z * 0.5f);
			FColor Color = FColor::White;

			if (TileData != nullptr)
			{
				//GridMap->ChangeTileNavigation(X, Y, !TileData->bIsObstacle);
				Color = Pixels[Y * SizeX + X];

				AActor* NewTile = GetWorld()->SpawnActor<AActor>(TileData->TileClass, SpawnLocation, FRotator::ZeroRotator);
				if (IsValid(NewTile))
				{
					FVector TileOrigin;
					FVector TileExtent;
					NewTile->GetActorBounds(true, TileOrigin, TileExtent);
					TileExtent *= 2.0f;
					FVector TileScale = FVector(TileSize.X / TileExtent.X, TileSize.Y / TileExtent.Y, TileSize.Z / TileExtent.Z);
					NewTile->SetActorScale3D(TileScale);

					NewTile->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
					NewTile->Tags.Add(TEXT("MapTile"));
				}
			}
			
			DrawDebugBox(GetWorld(), SpawnLocation, Extent, Color, false, 10.0f);

			SpawnLocation.X += TileSize.X;
		}
		SpawnLocation.X = InitialLocation.X;
		SpawnLocation.Y += TileSize.Y;
	}

	// Change the floor size.
	if (IsValid(GridMap))
	{
		UStaticMeshComponent* Floor = GridMap->GetFloorMeshComponent();
		if (IsValid(Floor))
		{
			FVector MinBounds; 
			FVector MaxBounds; 
			Floor->GetLocalBounds(MinBounds, MaxBounds);
			
			Floor->SetRelativeScale3D(FVector(
				(TotalMapWidth * 0.5f) / MaxBounds.X,
				(TotalMapHeight * 0.5f) / MaxBounds.Y,
				Floor->GetRelativeScale3D().Z)
			);
		}
	}
}

void UGridMapGeneratorFromTexture::ClearMap()
{
	TArray<AActor*> Children;
	GetOwner()->GetAttachedActors(Children);

	for (AActor* Child : Children) 
	{
		//AActor* Child = Children.Pop();
		Child->Destroy();
	}
}
