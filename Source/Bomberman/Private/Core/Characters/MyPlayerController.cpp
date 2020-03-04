// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/Core/Characters/MyPlayerController.h"
#include "Bomberman/Public/Core/Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"

AMyPlayerController::AMyPlayerController() {

}

void AMyPlayerController::BeginPlay() {
  Super::BeginPlay();

  Player1 = Cast<APlayerCharacter>(GetPawn());

  APlayerController* Controller = UGameplayStatics::GetPlayerController(
    GetWorld(), 1);

  if (Controller != NULL) {
    Player2 = Cast<APlayerCharacter>(Controller->GetPawn());
  }
  
  // Disable split screen.
  GetLocalPlayer()->ViewportClient->SetDisableSplitscreenOverride(true);

  /*if (InputComponent != NULL) {
    // Player1 Input.
    if (Player1 != NULL) {
      InputComponent->BindAction(FName(TEXT("ActionPlayer1")),
        EInputEvent::IE_Pressed, Player1, &APlayerCharacter::Action);

      InputComponent->BindAxis(FName(TEXT("MoveForwardPlayer1")), Player1,
        &APlayerCharacter::MoveForward);

      InputComponent->BindAxis(FName(TEXT("MoveRightPlayer1")), Player1,
        &APlayerCharacter::MoveRight);
    }
    
    // Player2 Input.
    if (Player2 != NULL) {
      InputComponent->BindAction(FName(TEXT("ActionPlayer2")),
        EInputEvent::IE_Pressed, Player2, &APlayerCharacter::Action);

      InputComponent->BindAxis(FName(TEXT("MoveForwardPlayer2")), Player2,
        &APlayerCharacter::MoveForward);

      InputComponent->BindAxis(FName(TEXT("MoveRightPlayer2")), Player2,
        &APlayerCharacter::MoveRight);
    }
  }*/
}

void AMyPlayerController::SetupInputComponent() {
  Super::SetupInputComponent();

  if (InputComponent != NULL) {
    // Player1 Input.
    InputComponent->BindAction(FName(TEXT("ActionPlayer1")),
      EInputEvent::IE_Pressed, this, &AMyPlayerController::ActionPlayer1);

    InputComponent->BindAxis(FName(TEXT("MoveForwardPlayer1")), this,
      &AMyPlayerController::MoveForwardPlayer1);

    InputComponent->BindAxis(FName(TEXT("MoveRightPlayer1")), this,
      &AMyPlayerController::MoveRightPlayer1);

    // Player2 Input.
    InputComponent->BindAction(FName(TEXT("ActionPlayer2")),
      EInputEvent::IE_Pressed, this, &AMyPlayerController::ActionPlayer2);

    InputComponent->BindAxis(FName(TEXT("MoveForwardPlayer2")), this,
      &AMyPlayerController::MoveForwardPlayer2);

    InputComponent->BindAxis(FName(TEXT("MoveRightPlayer2")), this,
      &AMyPlayerController::MoveRightPlayer2);
  }
}

void AMyPlayerController::ActionPlayer1() {
  if (Player1 != NULL) {
    Player1->Action();
  }
}

void AMyPlayerController::ActionPlayer2() {
  if (Player2 != NULL) {
    Player2->Action();
  }
}

void AMyPlayerController::MoveForwardPlayer1(float Value) {
  if (Player1 != NULL) {
    Player1->MoveForward(Value);
  }
}

void AMyPlayerController::MoveForwardPlayer2(float Value) {
  if (Player2 != NULL) {
    Player2->MoveForward(Value);
  }
}

void AMyPlayerController::MoveRightPlayer1(float Value) {
  if (Player1 != NULL) {
    Player1->MoveRight(Value);
  }
}

void AMyPlayerController::MoveRightPlayer2(float Value) {
  if (Player2 != NULL) {
    Player2->MoveRight(Value);
  }
}
