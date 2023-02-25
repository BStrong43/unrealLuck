// Fill out your copyright notice in the Description page of Project Settings.


#include "LuckyAIController.h"

ALuckyAIController::ALuckyAIController()
{
	TArray<AActor*> allies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALuckyEnemy::StaticClass(), allies);

	
}

void ALuckyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ALuckyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	mSelf = Cast<ALuckyEnemy>(InPawn);
}

void ALuckyAIController::Tick(float DeltaTime)
{
	if (active)
	{

	}
}

void ALuckyAIController::doPath()
{

}

void ALuckyAIController::startShootTimer()
{
	
}

void ALuckyAIController::stopShootTimer()
{

}