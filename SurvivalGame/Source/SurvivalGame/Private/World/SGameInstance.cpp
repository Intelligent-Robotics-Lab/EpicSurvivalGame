// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "World/SGameInstance.h"
#include "WebSocketsModule.h"

void USGameInstance::Init()
{
    Super::Init();

    if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }
    WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://localhost:8080");
    WebSocket->OnConnected().AddLambda([]()
    {
        GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, "Connected");
    });
    WebSocket->OnConnectionError().AddLambda([](const FString& Error)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Error:" + Error);
    });
    WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool clean)
    {
        GEngine->AddOnScreenDebugMessage(-1, 10, clean ? FColor::Cyan : FColor::Red,  FString::SanitizeFloat(StatusCode) + Reason);
    });
    WebSocket->Connect();
}

void USGameInstance::Shutdown()
{
    if (WebSocket->IsConnected())
    {
        WebSocket->Close();
    }
    Super::Shutdown();

}
