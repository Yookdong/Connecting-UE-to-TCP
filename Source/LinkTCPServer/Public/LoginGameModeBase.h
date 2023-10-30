// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class LINKTCPSERVER_API ALoginGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> LoginWidgetClass;

	class ULoginWidget* LoginWidget;

	TSharedPtr<class FInternetAddr> ClientSocketAddr;

	class FSocket* ClientSocket;


public:
	ALoginGameModeBase();

	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;

	void TCPClientInfo();


};
