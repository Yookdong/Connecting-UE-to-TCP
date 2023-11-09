// Fill out your copyright notice in the Description page of Project Settings.


#include "TCPGameInstance.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"

UTCPGameInstance::UTCPGameInstance()
{

}

void UTCPGameInstance::BeginPlay()
{
}

void UTCPGameInstance::SetData(int playernum, int portnum, FString ip)
{
    Data.PlayerNum = playernum;
    Data.PortNum = portnum;
    Data.IP = ip;

    UE_LOG(LogTemp, Error, TEXT("Singleton Port : %d"), Data.PortNum);
    UE_LOG(LogTemp, Error, TEXT("Singleton IP : %s"), *Data.IP);
}
