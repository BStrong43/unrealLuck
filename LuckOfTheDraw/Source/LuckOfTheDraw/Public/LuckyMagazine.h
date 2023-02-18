// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Array.h"
#include "LuckyProjectile.h"
#include "LuckyMagazine.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUCKOFTHEDRAW_API ULuckyMagazine : public UActorComponent
{
	GENERATED_BODY()

public:	
	//Sets default values for this component's properties
	ULuckyMagazine();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Reload();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
	float maxAmmo = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine")
	TArray<int> mag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Magazine")
	float barrelIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Magazine")
	LuckyProjectileType RollBarrel();//Returns chambered projectile, and increments barrelIndex
	UFUNCTION(BlueprintCallable, Category = "Magazine")
	LuckyProjectileType swapProjectile(int index, LuckyProjectileType newBullet);
	UFUNCTION(BlueprintCallable, Category = "Magazine")
	ALuckyProjectile* shootProjectile(FVector loc, FRotator rot);//Returns the projectile just fired
	UFUNCTION(BlueprintCallable, Category = "Magazine")
	void addProjectile(LuckyProjectileType newBullet);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
