// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LuckyCharacter.generated.h"

UCLASS()
class LUCKOFTHEDRAW_API ALuckyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALuckyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float mHealth = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float mSpeed = 20;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	float mDeltaTime = 0.0167;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookAtTarget();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Shoot();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();
	UFUNCTION(BlueprintCallable, Category = "Character")
	void Dash();

};
