// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Gameplay/Wall.h"
#include "Bomberman/Public/Gameplay/Pickup.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh")));
  SetRootComponent(Mesh);

  Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1,
    ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
  // Set mesh.
  SetDestructible(bIsDestructible);
}

void AWall::BeginDestroy() {
  Super::BeginDestroy();

}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::Break() {
  if (bIsDestructible) {
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,
      TEXT("AWall::Break"));

    if (SpawnPickupProbability > 0 &&
      FMath::RandRange(0, 99) < SpawnPickupProbability) {

      TSubclassOf<APickup> PickupBP = 
        PickupsBP[FMath::RandRange(0, PickupsBP.Num() - 1)];
      
      FVector Center;
      FVector Extent;
      //GetActorBounds(true, Center, Extent);

      APickup* Pickup = GetWorld()->SpawnActor<APickup>(PickupBP, 
        GetActorLocation(), FRotator::ZeroRotator);
    }

    Destroy();
  }
}

bool AWall::IsDestructible() const {
  return bIsDestructible;
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
