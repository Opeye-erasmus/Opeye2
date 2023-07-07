// Fill out your copyright notice in the Description page of Project Settings.

#include "GazePointAPIConnectionHandler.h"

UGazePointAPIConnectionHandler::UGazePointAPIConnectionHandler()
{
}

bool UGazePointAPIConnectionHandler::ConnectToGazeAPI(const FString& IP, int32 Port)
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();

	bool bIsValid;
	Addr->SetIp(*IP, bIsValid);
	Addr->SetPort(Port);

	if (!bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid IP address."));
		return false;
	}

	Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("GazeTCPConnection"), false);

	if (Socket->Connect(*Addr))
	{
		UE_LOG(LogTemp, Log, TEXT("Connected to Gazepoint API."));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to Gazepoint API."));
		return false;
	}
}

bool UGazePointAPIConnectionHandler::ReceiveGazeData(FVector2D& GazeCoordinates)
{
	TArray<uint8> ReceivedData;
	if (ReceiveData(ReceivedData))
	{
		FString ReceivedString = FString(ReceivedData.Num(), (TCHAR*)ReceivedData.GetData());
		// Parse ReceivedString and extract gaze coordinates, then set GazeCoordinates.
		return true;
	}
	else
	{
		return false;
	}
}

bool UGazePointAPIConnectionHandler::ReceiveData(TArray<uint8>& Data)
{
	if (!Socket) return false;

	uint32 Size;
	while (Socket->HasPendingData(Size))
	{
		Data.SetNumUninitialized(FMath::Min(Size, 65507u));
		int32 Read = 0;
		Socket->Recv(Data.GetData(), Data.Num(), Read);

		if (Read > 0)
		{
			return true;
		}
	}

	return false;
}


UGazePointAPIConnectionHandler::~UGazePointAPIConnectionHandler()
{
}

