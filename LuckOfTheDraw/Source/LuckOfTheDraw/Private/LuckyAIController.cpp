// Fill out your copyright notice in the Description page of Project Settings.


#include "LuckyAIController.h"

ALuckyAIController::ALuckyAIController()
{
	
}

void ALuckyAIController::BeginPlay()
{
	Super::BeginPlay();
	mPathtime = pathingUpdateTimer;
}

void ALuckyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	mEnemySelf = Cast<ALuckyEnemy>(InPawn);
	UE_LOG(LogTemp, Display, TEXT("Pawn Possessed"));
}

void ALuckyAIController::Tick(float DeltaTime)
{
	if (active)
	{
		ActiveTick(DeltaTime);
		
		pathingUpdateTimer -= DeltaTime;
		if (pathingUpdateTimer <= 0)
		{
			OnPathingTick();
			pathingUpdateTimer = mPathtime;
		}
	}
}

void ALuckyAIController::SetDestination(FVector loc)
{
	mTarget = loc;
}

void ALuckyAIController::SetDestToActor(AActor* inActor)
{
	SetDestination(inActor->GetActorLocation());
}