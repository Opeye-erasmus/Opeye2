// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "GazePointAPIConnectionHandler.generated.h"
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class OPEYE2_API UGazePointAPIConnectionHandler : public UObject
{
	GENERATED_BODY()
public:
	UGazePointAPIConnectionHandler();
	~UGazePointAPIConnectionHandler();
	UFUNCTION(BlueprintCallable, Category = "Gaze TCP Connection")
	bool ConnectToGazeAPI(const FString& IP, int32 Port);

	UFUNCTION(BlueprintCallable, Category = "Gaze TCP Connection")
	bool ReceiveGazeData(FVector2D& GazeCoordinates);
private:
	FSocket* Socket;
	bool ReceiveData(TArray<uint8>& Data);
};
