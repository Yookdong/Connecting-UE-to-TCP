// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTableManager.generated.h"

USTRUCT(BlueprintType)
struct FST_ServerData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FST_ServerData() : ServerPort(0), ServerIP("") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ServerData)
	uint8 ServerPort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ServerData)
	FString ServerIP;
};

USTRUCT(BlueprintType)
struct FST_Data : public FTableRowBase
{
	GENERATED_BODY()
public:
	FST_Data() :PlayerNum(0), PortNum(0), IP(TEXT("")) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int PlayerNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int PortNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FString IP;
};


UCLASS()
class LINKTCPSERVER_API UDataTableManager : public UDataTable
{
	GENERATED_BODY()

};
