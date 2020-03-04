// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Gameplay/Bomb.h"
#include "TimerManager.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(
    FName(TEXT("Bomb Mesh")));
  SetRootComponent(BombMesh);

  WickMesh = CreateDefaultSubobject<UStaticMeshComponent>(
    FName(TEXT("Wick Mesj")));
  WickMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
  GetWorldTimerManager().SetTimer(ExplosionTimer, this, &ABomb::Explode, 
    ExplosionCountDown, false);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::Explode() {
  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta,
    TEXT("ABomb::Explode"));

  OnExplode.ExecuteIfBound();
}
