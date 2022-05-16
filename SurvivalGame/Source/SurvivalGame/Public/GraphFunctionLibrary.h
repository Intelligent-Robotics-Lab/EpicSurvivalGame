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
		static void NotifyServer(const UObject* WorldContextObject, TArray<float> Data);
	//void NotifyServer();
};
