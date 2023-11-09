// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadSocket.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"
#include "TCPGameInstance.h"
#include "Engine/GameInstance.h"

ThreadSocket::ThreadSocket()
{
	bRunThread = false;
	bOneDediTCPInfo = false;

}

ThreadSocket::~ThreadSocket()
{
	if (DediThread)
	{
		UE_LOG(LogTemp, Display, TEXT("End DediThread"));
		delete DediThread;
	}
}

bool ThreadSocket::Init()
{
	bRunThread = true;

	// TCP 소켓 생성 연결
	DediServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
	DediServerAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	FString ip = TEXT("192.168.0.53");	//tcp ip
	int32 port = 10101;	//tcp port
	FIPv4Address temporaryAddr;		//임시 저장소
	FIPv4Address::Parse(ip, temporaryAddr); //ip를 temporaryAddr에 변환해서 넣고
	DediServerAddress->SetPort(port);	//port넣음
	DediServerAddress->SetIp(temporaryAddr.Value);	//ip넣음

	if (DediServerSocket->Connect(*DediServerAddress))
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP서버 접속 성공"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP서버 접속 실패"));
	}

	UTCPGameInstance* gameinst = Cast<UTCPGameInstance>(GetGameInstance());

	return true;
}

uint32 ThreadSocket::Run()
{
	return 0;
}

void ThreadSocket::Stop()
{
}
