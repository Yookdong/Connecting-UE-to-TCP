// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DataTableManager.h"
#include "TCPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LINKTCPSERVER_API UTCPGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FST_Data Data;

private:
	UTCPGameInstance();

public:
	const FST_Data& GetData() { return Data; }
	void SetData(int playernum, int protnum, FString ip);
};
