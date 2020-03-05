// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BOMBERMAN_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets",
    meta = (BindWidget))
    UProgressBar* CountDownBar;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets",
    meta = (BindWidget))
    UTextBlock* CountDownText;
};
