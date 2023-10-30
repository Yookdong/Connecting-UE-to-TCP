// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerActor.h"

// Sets default values
AServerActor::AServerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AServerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AServerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

