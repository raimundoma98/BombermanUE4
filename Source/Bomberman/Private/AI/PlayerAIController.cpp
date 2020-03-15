// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomberman/Public/AI/PlayerAIController.h"
#include "Bomberman/Public/Core/Characters/AIPlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"

APlayerAIController::APlayerAIController() {
  BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(
    FName(TEXT("Behavior Tree Component")));

  BBComponent = CreateDefaultSubobject<UBlackboardComponent>(
    FName(TEXT("Blackboard Component")));

  PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(
    FName(TEXT("Perception Component")));

  SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
  
  PerceptionComponent->ConfigureSense(*SightConfig);
  PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void APlayerAIController::OnPossess(APawn* InPawn) {
  Super::OnPossess(InPawn);

  SetPerceptionComponent(*PerceptionComponent);
  PerceptionComponent->OnPerceptionUpdated.AddDynamic(this,
    &APlayerAIController::OnPerceptionUpdated);

  AAIPlayerCharacter* AIPlayer = Cast<AAIPlayerCharacter>(InPawn);

  if (AIPlayer != NULL) {
    if (AIPlayer->BehaviorTree != NULL) {
      if (AIPlayer->BehaviorTree->BlackboardAsset != NULL) {
        BBComponent->InitializeBlackboard(
          *(AIPlayer->BehaviorTree->BlackboardAsset));
      }

      BTComponent->StartTree(*AIPlayer->BehaviorTree);
    }
  }
}

void APlayerAIController::OnUnPossess() {
  Super::OnUnPossess();

  BTComponent->StopTree();
}

void APlayerAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors) {

}
