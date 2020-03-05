// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Gameplay/Bomb.h"
#include "Bomberman/Public/Gameplay/Wall.h"
#include "Bomberman/Public/Gameplay/BombermanCameraActor.h"
#include "Bomberman/Public/Gameplay/MapGenerator.h"
#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "Bomberman/Public/Core/GameFramework/BombermanGameModeBase.h"
#include "kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

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
  ABombermanGameModeBase* GameMode = Cast<ABombermanGameModeBase>(
    UGameplayStatics::GetGameMode(GetWorld()));

  float TotalBlastDistance = 0.0f;

  if (GameMode != NULL) {
    if (GameMode->MainCamera.IsValid()) {
      GameMode->MainCamera->ScreenShake(ExplosionScreenShakeDuration,
        ExplosionScreenShakeMagnitude);
    }

    if (GameMode->MapGenerator.IsValid()) {
      TotalBlastDistance = GameMode->MapGenerator->GetTileSize() * 
        ExplosionDistance;
    }
  }

  GetWorldTimerManager().ClearTimer(ExplosionTimer);
  SetActorEnableCollision(false);
  OnExplode.ExecuteIfBound();

  FCollisionQueryParams Params;
  Params.AddIgnoredActor(this);
  
  FHitResult Hit;
  FVector Start = GetActorLocation();
  FVector LeftBlastEnd = Start + FVector::LeftVector * TotalBlastDistance;
  FVector RightBlastEnd = Start + FVector::RightVector * TotalBlastDistance;
  FVector ForwardBlastEnd = Start + FVector::ForwardVector * TotalBlastDistance;
  FVector BackwardBlastEnd = Start + FVector::BackwardVector * TotalBlastDistance;

  DrawDebugLine(GetWorld(), Start, LeftBlastEnd, FColor::Red, false, 3.0f,
    (uint8)'\000', 5.0f);

  DrawDebugLine(GetWorld(), Start, RightBlastEnd, FColor::Red, false, 3.0f,
    (uint8)'\000', 5.0f);

  DrawDebugLine(GetWorld(), Start, ForwardBlastEnd, FColor::Red, false, 3.0f,
    (uint8)'\000', 5.0f);

  DrawDebugLine(GetWorld(), Start, BackwardBlastEnd, FColor::Red, false, 3.0f,
    (uint8)'\000', 5.0f);

  // Left blast.
  GetWorld()->LineTraceSingleByChannel(Hit, Start, LeftBlastEnd,
    ECollisionChannel::ECC_Visibility, Params);
  CheckBlastCollision(Hit.Actor.Get());

  // Right blast.
  GetWorld()->LineTraceSingleByChannel(Hit, Start, RightBlastEnd,
    ECollisionChannel::ECC_Visibility, Params);
  CheckBlastCollision(Hit.Actor.Get());

  // Forward blast.
  GetWorld()->LineTraceSingleByChannel(Hit, Start, ForwardBlastEnd,
    ECollisionChannel::ECC_Visibility, Params);
  CheckBlastCollision(Hit.Actor.Get());

  // Backward blast.
  GetWorld()->LineTraceSingleByChannel(Hit, Start, BackwardBlastEnd,
    ECollisionChannel::ECC_Visibility, Params);
  CheckBlastCollision(Hit.Actor.Get());

  Destroy();
}

void ABomb::CheckBlastCollision(AActor* HitActor) {
  if (HitActor != NULL) {
    if (HitActor->ActorHasTag(TEXT("Bomb"))) {
      // Explode bomb.
      ABomb* Bomb = Cast<ABomb>(HitActor);
      if (Bomb != NULL) {
        Bomb->Explode();
      }
    }
    else if (HitActor->ActorHasTag(TEXT("Player"))) {
      // Kill player.
      APlayerCharacter* Player = Cast<APlayerCharacter>(HitActor);

      GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
        TEXT("ABomb::CheckBlastCollision: Kill Player"));

      if (Player != NULL)
        Player->Kill();
    }
    else if (HitActor->ActorHasTag(TEXT("Wall"))) {
      AWall* Wall = Cast<AWall>(HitActor);
      if (Wall != NULL && Wall->IsDestructible()) {
        Wall->Break();
      }
    }
    else if (HitActor->ActorHasTag(TEXT("Pickup"))) {
      HitActor->Destroy();
    }
  }
}
