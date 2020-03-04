// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Gameplay/Wall.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh")));
  SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
  // Set mesh.
  SetDestructible(bIsDestructible);
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::SetDestructible(bool Destructible) {
  bIsDestructible = Destructible;

  if (bIsDestructible) {
    Mesh->SetMaterial(0, DestructibleMaterial);
  }
  else {
    Mesh->SetMaterial(0, InDestructibleMaterial);
  }
}
