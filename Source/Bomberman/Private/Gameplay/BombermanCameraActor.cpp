// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Gameplay/BombermanCameraActor.h"
#include "Bomberman/Public/Core/GameFramework/BombermanGameModeBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

ABombermanCameraActor::ABombermanCameraActor() {
  PrimaryActorTick.bCanEverTick = true;
}

void ABombermanCameraActor::BeginPlay() {
  Super::BeginPlay();

  // Set this camera as the main camera of the game.
  ABombermanGameModeBase* GameMode = Cast<ABombermanGameModeBase>(
    UGameplayStatics::GetGameMode(GetWorld()));

  if (GameMode != NULL) {
    GameMode->MainCamera = this;
  }

  if (FocusedActor.IsValid()) {
    FVector Location = FocusedActor->GetActorLocation();
    Location.Z += ZDistance;

    FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Location,
      FocusedActor->GetActorLocation());

    SetActorLocation(Location);
    SetActorRotation(Rotation);
  }

  APlayerController* Controller = 
    UGameplayStatics::GetPlayerController(GetWorld(), 0);

  if (Controller != NULL) {
    Controller->SetViewTarget(this);
    Player1 = Controller->GetPawn();
  }

  Controller =
    UGameplayStatics::GetPlayerController(GetWorld(), 1);

  if (Controller != NULL) {
    Player2 = Controller->GetPawn();
  }
}

void ABombermanCameraActor::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  if (Player1.IsValid() && Player2.IsValid()) {

    FVector Direction = Player2->GetActorLocation() -
      Player1->GetActorLocation();

    // Place the camera in the center between players.
    FVector Location = Player1->GetActorLocation() + Direction * 0.5f;
    
    float Alpha = Direction.Size() / MaxPlayersDistance;

    Location.Z = FMath::Lerp(MinZDistance, MaxZDistance, Alpha);
    SetActorLocation(Location);
  }
}
