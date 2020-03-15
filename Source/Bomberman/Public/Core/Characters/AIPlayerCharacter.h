// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/PlayerCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AAIPlayerCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
  AAIPlayerCharacter();

  UPROPERTY(EditAnywhere, Category = "AI Properties")
    UBehaviorTree* BehaviorTree;
};
