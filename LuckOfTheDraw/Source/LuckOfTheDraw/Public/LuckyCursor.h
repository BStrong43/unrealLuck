// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuckyCursor.generated.h"

UCLASS()
class LUCKOFTHEDRAW_API ALuckyCursor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuckyCursor();

	UStaticMeshComponent* UMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveX(float value);
	void MoveY(float value);
	void Move(FVector value);
	//void SetHeight(float value);

private:
	void TrackToMouse();

	float mBoundingBoxDiameter = 25;

};
