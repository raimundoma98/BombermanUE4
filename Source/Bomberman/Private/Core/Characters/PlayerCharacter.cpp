// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "Bomberman/Public/Gameplay/Bomb.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  NameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Name Text"));
  NameText->SetupAttachment(RootComponent);

  bIsRemoteBomb = false;
  LastPlacedBomb = NULL;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
  NameText->SetText(FText::FromString(GetName()));
  CurrentBombs = StartBombs;
  BombBlastDistance = StartBombBlastDistance;
  bIsAlive = true;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::Action() {
  if (bIsRemoteBomb) {
    if (LastPlacedBomb.IsValid()) {
      LastPlacedBomb->Explode();
      return;
    }
  }
  
  if (CurrentBombs > 0) {
    ABomb* NewBomb = GetWorld()->SpawnActor<ABomb>(BombBP, GetActorLocation(),
      FRotator::ZeroRotator);

    if (NewBomb != NULL) {
      --CurrentBombs;
      LastPlacedBomb = NewBomb;
      NewBomb->OnExplode.BindUObject(this, &APlayerCharacter::OnBombExplode);
      NewBomb->ExplosionDistance = BombBlastDistance;
    }
  }
}

void APlayerCharacter::AddBombs(int32 Count) {
  CurrentBombs += Count;
}

void APlayerCharacter::IncreaseBombBlastDistance(int32 Increment) {
  BombBlastDistance += Increment;
}

bool APlayerCharacter::IsAlive() const {
  return bIsAlive;
}

void APlayerCharacter::Kill() {
  bIsAlive = false;
}

void APlayerCharacter::MoveForward(float Value) {
  AddMovementInput(FVector::ForwardVector, Value);
}

void APlayerCharacter::MoveRight(float Value) {
  AddMovementInput(FVector::RightVector, Value);
}

void APlayerCharacter::PickRemoteBomb(float Duration) {
  bIsRemoteBomb = true;

  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,
    TEXT("APlayerCharacter::PickRemoteBomb"));

  GetWorldTimerManager().SetTimer(DetonatorTimer, this,
    &APlayerCharacter::RemoveRemoteBomb, Duration, false);
}

void APlayerCharacter::RemoveRemoteBomb() {
  bIsRemoteBomb = false;
  GetWorldTimerManager().ClearTimer(DetonatorTimer);

  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,
    TEXT("APlayerCharacter::RemoveRemoteBomb"));
}

void APlayerCharacter::SetColor(FColor Color) {
  NameText->SetTextRenderColor(Color);
  
  GetMesh()->SetVectorParameterValueOnMaterials(FName(TEXT("Color")),
    FVector(Color.R / 255, Color.G / 255, Color.B / 255));
}

void APlayerCharacter::OnBombExplode() {
  ++CurrentBombs;
}
