// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BOMBERMAN_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets", 
    meta=(BindWidget))
    UButton* ResetButton;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets",
    meta = (BindWidget))
    UTextBlock* ResultText;
};
