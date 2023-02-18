// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
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

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UMesh;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* UGunMesh;
	UPROPERTY(VisibleAnywhere) USceneComponent* UGunBarrel;
	UPROPERTY(EditAnywhere) UCameraComponent* UCamera;
	UPROPERTY(EditAnywhere) USpringArmComponent* UCamBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ULuckyMagazine* UMag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float mHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float mSpeed = 250;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float mCursorSensitivity = 2500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool mUseBPMovement = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool mOverrideFire = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool mOverrideAltFire = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UInputAction* AltFireAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
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
	
	//virgin blueprint functions for harry

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character")
	void doOverrideShoot();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character")
	void doOverrideAltFire();
	UFUNCTION(BlueprintCallable, Category = "Character")
	void Fire();
	UFUNCTION(BlueprintCallable, Category = "Character")
	void Reload();
	UFUNCTION(BlueprintCallable, Category = "Character")
	void AltFire();

private:
	float mDeltaTime = 0.0167;
	float mCursorHeight = 50;
	
	//gigachad functions harry will never see hahahahaha
	void MoveForward(float value);
	void MoveRight(float value);
	void CursorX(float value);
	void CursorY(float value);
	void CursorXY(FVector value);
	void HandleShoot(const FInputActionValue& value);
	void HandleReload(const FInputActionValue& value);
	void HandleAltFire(const FInputActionValue& value);
	void HandleMove(const FInputActionValue& value);
	void HandleLook(const FInputActionValue& value);
	void LookAtCursor();
	void InitMesh();
	void InitCamera();
	void InitGun();
	void InitCursor();
};
