// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "MaterialEditor/DEditorParameterValue.h"

#include "DEditorScalarParameterValue.generated.h"

USTRUCT()
struct FScalarParameterAtlasData
{
	GENERATED_BODY()
public:
	UPROPERTY(Transient)
	bool bIsUsedAsAtlasPosition=false;

	UPROPERTY(Transient)
	TSoftObjectPtr<class UCurveLinearColor> Curve;

	UPROPERTY(Transient)
	TSoftObjectPtr<class UCurveLinearColorAtlas> Atlas;
};

UCLASS(hidecategories=Object, collapsecategories, editinlinenew)
class UNREALED_API UDEditorScalarParameterValue : public UDEditorParameterValue
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, Category=DEditorScalarParameterValue)
	float ParameterValue;

	float SliderMin=0.0f;
	float SliderMax = 0.0f;

	UPROPERTY(Transient)
	FScalarParameterAtlasData AtlasData;

};

