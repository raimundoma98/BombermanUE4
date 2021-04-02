// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Map/GridMap.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGridMap::AGridMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		FName(TEXT("Floor Mesh")));
	SetRootComponent(FloorMesh);
}

// Called when the game starts or when spawned
void AGridMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridMap::GetNavigationMap(TArray<bool>& OutNavigationMap) const
{
	OutNavigationMap = NavigationMap;
}

void AGridMap::Initialize(int32 MapWidth, int32 MapHeight)
{
	NavigationMap.Init(true, Width * Height);
	Width = MapWidth;
	Height = MapHeight;
}

void AGridMap::ChangeTileNavigation(int32 X, int32 Y, bool bCanNavigate)
{
	if (UKismetMathLibrary::InRange_IntInt(X, 0, Width, true, false) &&
		UKismetMathLibrary::InRange_IntInt(Y, 0, Height, true, false))
	{
		NavigationMap[X + Y * Width] = bCanNavigate;
	}
}

bool AGridMap::IsTileNavigable(int32 X, int32 Y) const
{
	if (UKismetMathLibrary::InRange_IntInt(X, 0, Width, true, false) &&
			UKismetMathLibrary::InRange_IntInt(Y, 0, Height, true, false))
	{
		return NavigationMap[X + Y * Width];
	}

	return false;
}