// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GraphFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UGraphFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Charts", meta = (WorldContext = "WorldContextObject"))
		static void UpdateHeatmapData(const UObject* WorldContextObject, TArray<float> Data);
	UFUNCTION(BlueprintCallable, Category = "Charts", meta = (WorldContext = "WorldContextObject"))
		static void UpdateBoxplotData(const UObject* WorldContextObject, FVector2D Data);
	UFUNCTION(BlueprintCallable, Category = "Charts", meta = (WorldContext = "WorldContextObject"))
		static void UpdatePieData(const UObject* WorldContextObject, FVector2D Data);
	UFUNCTION(BlueprintCallable, Category = "Charts", meta = (WorldContext = "WorldContextObject"))
		static void UpdateHeatmapResolution(const UObject* WorldContextObject, int Resolution);
};
