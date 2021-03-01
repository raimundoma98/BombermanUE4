// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/TextureUtilsLibrary.h"
#include "Engine/Texture2D.h"

bool UTextureUtilsLibrary::GetPixelsFromTexture(UTexture2D* Texture, TArray<FColor>& Pixels)
{
	if (!IsValid(Texture)) {
		return false;
	}

	TextureCompressionSettings OldCompressionSettings = Texture->CompressionSettings;
	TextureMipGenSettings OldMipGenSettings = Texture->MipGenSettings;
	bool OldSRGB = Texture->SRGB;

	Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Texture->SRGB = false;
	Texture->UpdateResource();

	const FColor* ImageData = static_cast<const FColor*>(Texture->PlatformData->Mips[0].BulkData.LockReadOnly());

	if (ImageData == nullptr)
	{
		return false;
	}

	Pixels.SetNum(Texture->GetSizeX() * Texture->GetSizeY());

	for (int32 X = 0; X < Texture->GetSizeX(); ++X)
	{
		for (int32 Y = 0; Y < Texture->GetSizeY(); ++Y)
		{
			int32 Index = Y * Texture->GetSizeX() + X;
			Pixels[Index] = ImageData[Index];
		}
	}
	Texture->PlatformData->Mips[0].BulkData.Unlock();

	Texture->CompressionSettings = OldCompressionSettings;
	Texture->MipGenSettings = OldMipGenSettings;
	Texture->SRGB = OldSRGB;
	Texture->UpdateResource();

	return true;
}

bool UTextureUtilsLibrary::GetPixelFromTexture(UTexture2D* Texture, const int32 X, const int32 Y, FColor& PixelColor)
{
	if (!IsValid(Texture))
	{
		return false;
	}

	if (X < 0 || Y < 0 || X > Texture->GetSizeX() || Y > Texture->GetSizeY())
	{
		return false;
	}

	TextureCompressionSettings OldCompressionSettings = Texture->CompressionSettings;
	TextureMipGenSettings OldMipGenSettings = Texture->MipGenSettings;
	bool OldSRGB = Texture->SRGB;

	// Needed texture settings for reading the pixel.
	Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Texture->SRGB = false;
	Texture->UpdateResource();

	const FColor* ImageData = static_cast<const FColor*>(Texture->PlatformData->Mips[0].BulkData.LockReadOnly());

	if (ImageData == nullptr)
	{
		return false;
	}

	PixelColor = ImageData[Y * Texture->GetSizeX() + X];
	
	Texture->PlatformData->Mips[0].BulkData.Unlock();

	Texture->CompressionSettings = OldCompressionSettings;
	Texture->MipGenSettings = OldMipGenSettings;
	Texture->SRGB = OldSRGB;
	Texture->UpdateResource();

	return true;
}
