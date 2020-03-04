// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "Bomberman/Public/Gameplay/Bomb.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  NameText = CreateDefaultSubobject<UTextRenderComponent>(
    FName(TEXT("Name Text")));
  NameText->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
  NameText->SetText(FText::FromString(GetName()));
  CurrentBombs = StartBombs;
  BombBlastDistance = StartBombBlastDistance;
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
  GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,
    TEXT("APlayerCharacter::Action"));

  if (CurrentBombs > 0) {
    ABomb* NewBomb = GetWorld()->SpawnActor<ABomb>(BombBP, GetActorLocation(),
      FRotator::ZeroRotator);

    if (NewBomb != NULL) {
      --CurrentBombs;
      NewBomb->OnExplode.BindUObject(this, &APlayerCharacter::OnBombExplode);
    }
  }
}

void APlayerCharacter::AddBombs(int32 Count) {
  CurrentBombs += Count;
}

void APlayerCharacter::IncreaseBombBlastDistance(int32 Increment) {
  BombBlastDistance += Increment;
}

void APlayerCharacter::MoveForward(float Value) {
  AddMovementInput(FVector::ForwardVector, Value);
}

void APlayerCharacter::MoveRight(float Value) {
  AddMovementInput(FVector::RightVector, Value);
}

void APlayerCharacter::SetColor(FColor Color) {
  NameText->SetTextRenderColor(Color);
  
  GetMesh()->SetVectorParameterValueOnMaterials(FName(TEXT("Color")),
    FVector(Color.R / 255, Color.G / 255, Color.B / 255));
}

void APlayerCharacter::OnBombExplode() {
  ++CurrentBombs;
}
