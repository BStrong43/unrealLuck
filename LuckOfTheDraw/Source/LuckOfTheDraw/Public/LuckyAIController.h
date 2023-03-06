// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuckyEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "LuckyAIController.generated.h"

/**
 * 
 */

UCLASS()
class LUCKOFTHEDRAW_API ALuckyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALuckyAIController();

	UFUNCTION(BlueprintCallable, Category = "Lucky AI Controller")
	void SetDestToActor(AActor* inActor);

	UFUNCTION(BlueprintCallable, Category = "Lucky AI Controller")
	void SetDestination(FVector loc);

	UFUNCTION(BlueprintImplementableEvent, Category = "Lucky AI Controller")
	void ActiveTick(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent, Category = "Lucky AI Controller")
	void OnPathingTick();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lucky AI Controller")
	ALuckyEnemy* mEnemySelf;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lucky AI Controller")
	FVector mTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lucky AI Controller")
	float mTermRadius = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lucky AI Controller")
	float pathingUpdateTimer = 5;

	UPROPERTY(EditAnywhere, Category = "Lucky AI Controller")
	bool active = true;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	float mPathtime = 5;
};
