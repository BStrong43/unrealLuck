// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "LuckyMagazine.h"
//#include "LuckyProjectile.h"
#include "LuckyEnemy.generated.h"

class ALuckyProjectile;

UCLASS()
class LUCKOFTHEDRAW_API ALuckyEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALuckyEnemy();

	UPROPERTY(EditAnywhere) UStaticMeshComponent* UMesh;
	UPROPERTY(EditAnywhere) UCapsuleComponent* UCapsule;
	UPROPERTY(EditAnywhere) USceneComponent* UGunBarrel;
	UPROPERTY(EditAnywhere) ULuckyMagazine* UMag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float mHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	bool mIsChasing = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	APawn* mTarget;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	float TakeDamage (float dmg);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	ALuckyProjectile* Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
