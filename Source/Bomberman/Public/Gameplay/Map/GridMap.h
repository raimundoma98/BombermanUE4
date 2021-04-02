// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridMap.generated.h"

class UStaticMeshComponent;

UCLASS()
class BOMBERMAN_API AGridMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMap();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GridMap")
		FORCEINLINE UStaticMeshComponent* GetFloorMeshComponent() const { return FloorMesh; }

	UFUNCTION(BlueprintCallable, Category = "GridMap")
		void GetNavigationMap(TArray<bool>& OutNavigationMap) const;

	UFUNCTION(BlueprintCallable, Category = "GridMap")
		void Initialize(int32 MapWidth, int32 MapHeight);

	UFUNCTION(BlueprintCallable, Category = "GridMap")
		void ChangeTileNavigation(int32 X, int32 Y, bool bCanNavigate);

	// Can a character move through the tile?
	UFUNCTION(BlueprintCallable, Category = "GridMap")
		bool IsTileNavigable(int32 X, int32 Y) const;

	UFUNCTION(BlueprintCallable, Category = "GridMap")
		FORCEINLINE int32 GetWidth() const { return Width; }

	UFUNCTION(BlueprintCallable, Category = "GridMap")
		FORCEINLINE int32 GetHeight() const { return Height; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Floor mesh of the map.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GridMap")
		UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter = GetWidth, Category = "GridMap")
		int32 Width;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter = GetHeight, Category = "GridMap")
		int32 Height;

	UPROPERTY(Transient)
		TArray<bool> NavigationMap;
};
