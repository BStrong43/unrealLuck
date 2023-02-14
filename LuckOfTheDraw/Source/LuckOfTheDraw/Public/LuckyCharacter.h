// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
	float mSpeed = 250;

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UMesh;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UGunMesh;
	UPROPERTY(VisibleAnywhere) UCameraComponent* UCamera;
	UPROPERTY(VisibleAnywhere) USpringArmComponent* UCamBoom;

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	float mDeltaTime = 0.0167;

	//incel functions for harry
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Shoot();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SpecialAction();

	//gigachad functions harry will never see hahahahaha
	void MoveForward(float value);
	void MoveRight(float value);
	void LookAtCursor();
	void InitMesh();
	void InitCamera();
	

};
