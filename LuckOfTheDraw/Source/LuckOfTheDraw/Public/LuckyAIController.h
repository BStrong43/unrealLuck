// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuckyEnemy.h"
#include "Kismet/GameplayStatics.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LuckyController")
	TArray<ALuckyEnemy*> mAllies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LuckyController")
	float mSpeed = 75;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LuckyController")
	float mShootTimer = 3;

	UFUNCTION(BlueprintCallable, Category = "LuckyController")
	void startShootTimer();

	UFUNCTION(BlueprintCallable, Category = "LuckyController")
	void stopShootTimer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	ALuckyEnemy* mSelf;
	bool pathActive = false;
	APawn* mTarget;
	FVector mDestination;
};
