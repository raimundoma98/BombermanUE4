// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MapGeneratorFromTexture.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/TextureUtilsLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMapGeneratorFromTexture::UMapGeneratorFromTexture()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bIsEditorOnly = true;
}


// Called when the game starts
void UMapGeneratorFromTexture::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UMapGeneratorFromTexture::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMapGeneratorFromTexture::GenerateMap()
{
	if (!IsValid(MapTexture))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), 
			TEXT("UMapGeneratorFromTexture::GenerateMap: Invalid texture"), true, 
			true, FColor::Red);
		return;
	}

	TArray<FColor> Pixels;

	if (!UTextureUtilsLibrary::GetPixelsFromTexture(MapTexture, Pixels))
	{
		UKismetSystemLibrary::PrintString(GetWorld(),
			TEXT("UMapGeneratorFromTexture::GenerateMap: Could not red map texture pixels"), true,
			true, FColor::Red);
		return;
	}

	int32 SizeX = MapTexture->GetSizeX();
	int32 SizeY = MapTexture->GetSizeY();

	FVector InitialLocation = GetOwner()->GetActorLocation();
	FVector SpawnLocation = InitialLocation;

	for (int32 Y = 0; Y < SizeY; ++Y)
	{
		for (int32 X = 0; X < SizeX; ++X)
		{

			TSubclassOf<AActor>* Class = ColorToTileMap.Find(Pixels[Y * SizeX + X]);
			if (Class != nullptr)
			{
				DrawDebugSphere(GetWorld(), SpawnLocation, TileSize.X * 0.5f, 12, Pixels[Y * SizeX + X], false, 10.0f);
			}
			else if (IsValid(DefaultTile))
			{
				DrawDebugSphere(GetWorld(), SpawnLocation, TileSize.X * 0.5f, 12, FColor::White, false, 10.0f);
			}

			SpawnLocation.X += TileSize.X;
		}
		SpawnLocation.X = InitialLocation.X;
		SpawnLocation.Y += TileSize.Y;
	}
}
