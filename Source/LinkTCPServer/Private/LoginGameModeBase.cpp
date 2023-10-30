// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TCPPlayerController.h"
#include "TCPCharacter.h"
#include "LoginWidget.h"
#include "IPAddress.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "DataTableManager.h"



ALoginGameModeBase::ALoginGameModeBase()
{
	PlayerControllerClass = ATCPPlayerController::StaticClass();
	DefaultPawnClass = ATCPCharacter::StaticClass();
}

void ALoginGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	check(LoginWidgetClass);

	LoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass);
	LoginWidget->AddToViewport();

	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (IsValid(pc))
	{
		pc->SetInputMode(FInputModeUIOnly());
	}
}

void ALoginGameModeBase::StartPlay()
{
	Super::StartPlay();
}

void ALoginGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
}

void ALoginGameModeBase::TCPClientInfo()
{
	ClientSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
	ClientSocketAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	FString ip = TEXT("127.0.0.1");
	int32 portNum = 7777;
	FIPv4Address TemporaryAddr;		// 임시 저장소
	FIPv4Address::Parse(ip, TemporaryAddr); // ip를 temporaryAddr에 변환해서 넣고
	ClientSocketAddr->SetPort(portNum);	// port넣음
	ClientSocketAddr->SetIp(TemporaryAddr.Value); // ip 넣음

	if (!ClientSocket->Connect(*ClientSocketAddr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Client Connect Error"));
	}

	int myClientServer = 2;
	uint8 buffer[sizeof(int)];
	memcpy(buffer, &myClientServer, sizeof(int));
	int32 bytesSent = 0;

	if (ClientSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		ClientSocket->Send(buffer, sizeof(int), bytesSent);
	}
	
	FST_ServerData serverData;

	uint8 dbBuffer[1024] = { 0, };
	int32 bytes = 0;
	int recvBytes = 0;

	UE_LOG(LogTemp, Display, TEXT("Recv DB Data..."));

	if (ClientSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(5)))
	{
		recvBytes = ClientSocket->Recv(dbBuffer, sizeof(dbBuffer), bytes);

		if (recvBytes <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error"));
		}
		else if (ClientSocket == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Data"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("In Data"));
			memcpy(&serverData, dbBuffer, sizeof(FST_ServerData));

			UE_LOG(LogTemp, Warning, TEXT("%d"), serverData.ServerPort);
			FString str(serverData.ServerIP);
			str += ":";
			str += FString::FromInt(serverData.ServerPort);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *str);

			GetWorld()->GetFirstPlayerController()->ClientTravel(str, TRAVEL_Absolute);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No"));
	}
}