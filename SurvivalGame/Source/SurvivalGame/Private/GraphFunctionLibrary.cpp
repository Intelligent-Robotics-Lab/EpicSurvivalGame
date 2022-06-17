// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "GraphFunctionLibrary.h"
#include "World/SGameInstance.h"
#include "Dom/JsonObject.h"

void UGraphFunctionLibrary::UpdateHeatmapData(const UObject* WorldContextObject, TArray<float> Data)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"data\": [" + FString::SanitizeFloat(Data[0]) + ",";
            for (int i = 1; i < Data.Num() - 1; ++i)
            {
                newString += FString::SanitizeFloat(Data[i]) + ',';
            }
            newString += FString::SanitizeFloat(Data.Last()) + "] }";
            GameInstance->WebSocket->Send(newString);
        }
    }
}

void UGraphFunctionLibrary::UpdateBoxplotData(const UObject* WorldContextObject, FVector2D Data)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"point\": [" + FString::SanitizeFloat(Data[0]) + "," + FString::SanitizeFloat(Data[1]) + "] }";
            GameInstance->WebSocket->Send(newString);
        }
    }
}

void UGraphFunctionLibrary::UpdateBarChartData(const UObject* WorldContextObject, float Data)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"barPoint\": " + FString::SanitizeFloat(Data) + " }";
            //GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, newString);
            GameInstance->WebSocket->Send(newString);
        }
    }
}

void UGraphFunctionLibrary::SwitchBarChartData(const UObject* WorldContextObject, TArray<float> Data)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            if (Data.Num())
            {
                FString newString = "{ \"switchBar\": [" + FString::SanitizeFloat(Data[0]) + ",";
                for (int i = 1; i < Data.Num() - 1; ++i)
                {
                    newString += FString::SanitizeFloat(Data[i]) + ',';
                }
                newString += FString::SanitizeFloat(Data.Last()) + "] }";
                //GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, newString);
                GameInstance->WebSocket->Send(newString);
            }
        }
    }
}

void UGraphFunctionLibrary::ZeroBarChartData(const UObject* WorldContextObject)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"zeroBar\": 1 }";
            //GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, newString);
            GameInstance->WebSocket->Send(newString);
        }
    }
}

void UGraphFunctionLibrary::UpdateScatterData(const UObject* WorldContextObject, FString Name, FVector2D Data)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"scatter\": { \"name\": \"" + Name + "\", \"data\": [ " + FString::SanitizeFloat(Data.X) + "," + FString::SanitizeFloat(Data.Y) + " ] } }";
            //GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, newString);
            GameInstance->WebSocket->Send(newString);
        }
    }
}

void UGraphFunctionLibrary::UpdatePieData(const UObject* WorldContextObject, float Value, FString Name)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"pieData\": [ { \"value\": " + FString::SanitizeFloat(Value) + ", \"name\": \"" + Name + "\" } ] }";
            GameInstance->WebSocket->Send(newString);
        }
    }
}

void UGraphFunctionLibrary::ChangePieVariables(const UObject* WorldContextObject, float Value, FString Name)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"pieVariable\": [ { \"value\": " + FString::SanitizeFloat(Value) + ", \"name\": \"" + Name + "\" } ] }";
            GameInstance->WebSocket->Send(newString);
        }
    }
}

void UGraphFunctionLibrary::UpdateHeatmapResolution(const UObject* WorldContextObject, int Resolution)
{
    const USGameInstance* GameInstance = Cast<USGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());

    if (GameInstance)
    {
        if (GameInstance->WebSocket->IsConnected())
        {
            FString newString = "{ \"resolution\": " + FString::FromInt(Resolution) + " }";
            GameInstance->WebSocket->Send(newString);
        }
    }
}

FVector2D UGraphFunctionLibrary::ClampToSquare(const UObject* WorldContextObject, float Length, float Angle, float WidgetSize, bool Static)
{
    float x = Length * cos(Angle * PI / 180);
    float y = Length * sin(Angle * PI / 180);

    if (Static)
    {
        float absX = abs(x);
        float absY = abs(y);
        float absMin = std::min(std::min(WidgetSize / absY, WidgetSize / absX), 1.f);
        return FVector2D(absMin * x, -absMin * y);
    }
    return FVector2D(x, -y);
}
