// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "LuckyMagazine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUCKOFTHEDRAW_API ULuckyMagazine : public UActorComponent
{
	GENERATED_BODY()

public:	
	//Sets default values for this component's properties
	ULuckyMagazine();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float barrelIndex = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Reload();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	float maxAmmo = 6;
};
