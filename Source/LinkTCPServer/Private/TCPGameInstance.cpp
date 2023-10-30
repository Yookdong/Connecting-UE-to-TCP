// Fill out your copyright notice in the Description page of Project Settings.


#include "TCPGameInstance.h"

UTCPGameInstance::UTCPGameInstance()
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
