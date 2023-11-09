// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TCPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LINKTCPSERVER_API ATCPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATCPPlayerController() {};
	virtual void BeginPlay() override;
};
