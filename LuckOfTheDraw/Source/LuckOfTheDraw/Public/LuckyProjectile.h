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
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UMesh;
	UPROPERTY(VisibleAnywhere) USphereComponent* USphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float mSpeed = 250;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Init();
};
