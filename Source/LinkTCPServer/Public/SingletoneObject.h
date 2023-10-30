// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataTableManager.h"
#include "SingletoneObject.generated.h"

/**
 * 
 */
UCLASS()
class LINKTCPSERVER_API USingletoneObject : public UObject
{
	GENERATED_BODY()
private:
	static USingletoneObject* Instance;
	static TSubclassOf<USingletoneObject> SingletonClass;

	FST_Data Data;
	bool bSingleton;

private:
	USingletoneObject();

public:
	static USingletoneObject* GetInstance();

	const FST_Data& GetData() { return Data; }
	void SetData(int playernum, int serverport, FString ip);

	bool GetBool() const { return bSingleton; }
	void SerBool(bool value) { bSingleton = value; }
};

USingletoneObject* USingletoneObject::Instance = NULL;	//싱글톤 초기화