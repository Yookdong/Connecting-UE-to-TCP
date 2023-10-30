// Fill out your copyright notice in the Description page of Project Settings.


#include "SingletoneObject.h"

USingletoneObject::USingletoneObject()
{
	Data.PlayerNum = 0;
}

USingletoneObject* USingletoneObject::GetInstance()
{
    if (Instance == NULL)
    {
        Instance = NewObject<USingletoneObject>();
    }
    return Instance;
}

void USingletoneObject::SetData(int playernum, int serverport, FString ip)
{
}
