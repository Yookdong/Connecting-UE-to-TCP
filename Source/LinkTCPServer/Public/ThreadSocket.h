// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// 해당 패킷의 사이즈를 1바이트씩 나열하겠다는 의미이다.
// 이는 메모리의 낭비를 막기 위함이고, 개발 환경이 달라도 크기를 맞추기 위함인데
// 관련 설명은 https://she11.tistory.com/109 확인 바람
#pragma pack(push, 1) 
struct MyData
{
	int MyServer;
	int PlayerNum;
	int16 ServerPort;
	char IP[16];
};
#pragma pack(pop)

/**
 * 
 */
class LINKTCPSERVER_API ThreadSocket : public FRunnable
{
private:
	FString Messag;
	TSharedPtr<FInternetAddr> DediServerAddress;
	class FSocket* DediServerSocket;
	class FRunnableThread* DediThread;

	bool bRunThread;
	bool bOneDediTCPInfo;

public:
	ThreadSocket();
	~ThreadSocket();

	bool Init() override; // BeginPlay 와 생성자의 역할을 한다. 스레드가 실행 될 때 호출이 되는 함수이다.
	virtual uint32 Run() override; // 데이터 보내는 함수
	virtual void Stop() override; // 스레드 중지 함수
};
