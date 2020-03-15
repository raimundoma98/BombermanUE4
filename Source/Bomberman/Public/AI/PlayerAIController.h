// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "PlayerAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API APlayerAIController : public AAIController
{
	GENERATED_BODY()
	
public:
  APlayerAIController();

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBehaviorTreeComponent* BTComponent;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBlackboardComponent* BBComponent;

  UPROPERTY(VisibleAnywhere)
    UAISenseConfig_Sight* SightConfig;

protected:
  virtual void OnPossess(APawn* InPawn) override;
  virtual void OnUnPossess() override;

  UFUNCTION()
    void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
};
