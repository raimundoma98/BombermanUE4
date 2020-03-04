// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Gameplay/Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>(
    FName(TEXT("Mesh")));
  SetRootComponent(Mesh);
  Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, 
    ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
  OnActorBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::Activate_Implementation(APlayerCharacter* Player) {

}

void APickup::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {
  APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
  if (Player != NULL) {
    Activate(Player);
    Destroy();
  }
}
