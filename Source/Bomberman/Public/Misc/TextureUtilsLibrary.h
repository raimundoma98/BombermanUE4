// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextureUtilsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UTextureUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		static bool GetPixelsFromTexture(class UTexture2D* Texture, TArray<FColor>& Pixels);

	UFUNCTION(BlueprintCallable)
		static bool GetPixelFromTexture(class UTexture2D* Texture, const int32 X, const int32 Y, FColor& PixelColor);
};
