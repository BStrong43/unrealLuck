// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "LuckyMagazine.h"
#include "LEMovement.h"
//#include "LuckyProjectile.h"
#include "LuckyEnemy.generated.h"

class ALuckyProjectile;

UCLASS()
class LUCKOFTHEDRAW_API ALuckyEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALuckyEnemy();

	UPROPERTY(EditAnywhere) UStaticMeshComponent* UMesh;
	UPROPERTY(EditAnywhere) UCapsuleComponent* UCapsule;
	UPROPERTY(EditAnywhere) USceneComponent* UGunBarrel;
	UPROPERTY(EditAnywhere) ULuckyMagazine* UMag;
	//UPROPERTY(EditAnywhere) ULEMovement* UMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float mHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float mShootTimer = 5;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void startShootTimer();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void stopShootTimer();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void OnTakeDamage(AActor* DamageCauser, float damageAmount);//Event triggered when this enemy gets shot

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void OnDeath();//Event triggered when this enemy dies

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void OnShoot(ALuckyProjectile* shot);//Event triggered when this enemy shoots

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	ALuckyProjectile* Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;


private:
	float EnemyTakeDamage(float dmg);

	ALuckyProjectile* lastShot;
	bool doShootTimer = true;
	float shootTime = 5;
};
