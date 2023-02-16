// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "LuckyProjectile.generated.h"

UCLASS()
class LUCKOFTHEDRAW_API ALuckyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuckyProjectile();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UMesh;
	UPROPERTY(VisibleAnywhere) USphereComponent* USphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float mSpeed = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float mLifeTime = 20;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void doPath(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Init();
	float maxLifeTime = 360;
	float timeAlive = 0;
};
