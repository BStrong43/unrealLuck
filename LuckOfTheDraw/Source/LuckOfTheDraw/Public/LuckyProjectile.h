// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "LuckyProjectile.generated.h"

UENUM(BlueprintType)
enum LuckyProjectileType : int
{
	STANDARD = 0
};

UCLASS()
class LUCKOFTHEDRAW_API ALuckyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuckyProjectile();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) UStaticMeshComponent* UMesh;
	UPROPERTY(EditAnywhere) USphereComponent* USphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Movement")
	float mSpeed = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Movement")
	float mLifeTime = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Movement")
	bool mOverridePath = false;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Projectile Movement")
	void doOverridePath(float DeltaTime);
	void doPath(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Init();
	float maxLifeTime = 360;
	float timeAlive = 0;
};
