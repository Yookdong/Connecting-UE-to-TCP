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

	bool bIsWork;

private:
	UTCPGameInstance();

public:
	// Getter
	const FST_Data& GetData() { return Data; }
	bool IsWork() const { return bIsWork; }

	// Setter
	void SetData(int playernum, int protnum, FString ip);
	void SetWork(bool value) { bIsWork = value; }
};

class LINKTCPSERVER_API SocketThread : public FRunnable
{
private:
	FST_Data MyData;
	FString Message;
	TSharedPtr<FInternetAddr> DediServerAddress;
	class FSocket* DediServerSocket;
	class FRunnableThread* thread;

	bool bRunThread;
	bool bOneDediTCPInfo;

public:
	SocketThread();
	~SocketThread();

	bool Init() override;
	virtual uint32 Run() override;	//데이터를 보내는
	virtual void Stop() override;	//스레드 중지
};
