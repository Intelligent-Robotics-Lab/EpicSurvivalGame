// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "GraphFunctionLibrary.h"
#include "World/SGameInstance.h"
#include "Dom/JsonObject.h"

void UGraphFunctionLibrary::NotifyServer(const UObject* WorldContextObject, TArray<float> Data)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"data\": [" + FString::SanitizeFloat(Data[0]) + ",";
            for (int i = 1; i < (Data.GetAllocatedSize()/Data.GetTypeSize()) - 1; ++i)
            {
                newString += FString::SanitizeFloat(Data[i]) + ',';
            }
            newString += FString::SanitizeFloat(Data.Last()) + "] }";
            GameInstance->WebSocket->Send(newString);
        }
    }
}
