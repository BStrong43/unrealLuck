// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "LuckyCursor.h"
#include "LuckyProjectile.h"
#include "LuckyMagazine.h"
#include "LuckyCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float mCursorSensitivity = 1000;

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UMesh;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UGunMesh;
	UPROPERTY(VisibleAnywhere) USceneComponent* UGunBarrel;
	UPROPERTY(VisibleAnywhere) UCameraComponent* UCamera;
	UPROPERTY(VisibleAnywhere) USpringArmComponent* UCamBoom;
	UPROPERTY(VisibleAnywhere) ULuckyMagazine* UMag;

	//TODO: Figure out Enhanced Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool mUseBPMovement = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* AltFireAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ReloadAction;


protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;
	ALuckyCursor* mCursor;
	ALuckyProjectile* mProj;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

private:
	float mDeltaTime = 0.0167;
	float mCursorHeight = 50;

	//virgin blueprint functions for harry
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnHandleShoot(const FInputActionValue& value);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnHandleReload(const FInputActionValue& value);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnHandleAltFire(const FInputActionValue& value);
	UFUNCTION(BlueprintCallable, Category = "Character")
	void OnHandleMove(const FInputActionValue& value);
	UFUNCTION(BlueprintCallable, Category = "Character")
	void OnHandleLook(const FInputActionValue& value);
	
	//gigachad functions harry will never see hahahahaha
	void MoveForward(float value);
	void MoveRight(float value);
	void CursorX(float value);
	void CursorY(float value);
	void CursorXY(FVector value);
	void Fire();
	void AltFire();
	void Reload();
	void LookAtCursor();
	void InitMesh();
	void InitCamera();
	void InitGun();
	void InitCursor();
};
