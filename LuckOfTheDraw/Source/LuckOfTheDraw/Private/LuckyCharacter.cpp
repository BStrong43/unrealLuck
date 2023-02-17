// Fill out your copyright notice in the Description page of Project Settings.


#include "LuckyCharacter.h"

// Sets default values
ALuckyCharacter::ALuckyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitMesh();
	InitCamera();
	InitGun();
	
	UMag = CreateDefaultSubobject<ULuckyMagazine>(TEXT("Magazine"));
}

// Called when the game starts or when spawned
void ALuckyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitCursor();
}

void ALuckyCharacter::InitMesh()
{
	UMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	UMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> capsuleMesh(TEXT("/Game/Meshes/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	if (capsuleMesh.Succeeded())
	{
		UMesh-> SetStaticMesh(capsuleMesh.Object);
		UMesh-> SetRelativeLocation(FVector(0.0, 0.0, -90.0));
		UMesh-> SetRelativeScale3D(FVector(1.36,1.36,1.778));
	}
}

void ALuckyCharacter::InitCamera()
{
	UCamBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	UCamBoom-> SetupAttachment(RootComponent);
	UCamBoom-> SetRelativeLocation(FVector(0.0, 0.0, 900.0));
	UCamBoom-> SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	UCamBoom-> TargetArmLength = 600.0f;
	UCamBoom-> bEnableCameraLag = true;
	UCamBoom-> CameraLagSpeed = 800.f;

	UCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	UCamera-> SetupAttachment(UCamBoom, USpringArmComponent::SocketName);
}

void ALuckyCharacter::InitGun()
{
	UGunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	UGunMesh-> SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Game/Meshes/Shapes/Shape_Pipe.Shape_Pipe"));
	if (mesh.Succeeded())
	{
		UGunMesh->SetStaticMesh(mesh.Object);
		UGunMesh->SetRelativeLocation(FVector(35.0, -12.5, 0.0));
		UGunMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 90.f));
		UGunMesh->SetRelativeScale3D(FVector::OneVector * 0.8);
	}

	UGunBarrel = CreateDefaultSubobject<USceneComponent>(TEXT("Barrel"));
	UGunBarrel-> SetupAttachment(UGunMesh);
	UGunBarrel-> SetRelativeLocation(FVector(0.0, 60.0, 12.5));
}

void ALuckyCharacter::InitCursor() 
{
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Instigator = NULL;
	spawnParameters.Owner = this;
	spawnParameters.Name = "Cursor";

	mCursor = GetWorld()->SpawnActor<ALuckyCursor>(ALuckyCursor::StaticClass(), spawnParameters);

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	mCursor->AttachToActor(this, rules);

}

// Called every frame
void ALuckyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mDeltaTime = DeltaTime;
	LookAtCursor();
}

// Called to bind functionality to input
void ALuckyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	check(PlayerInputComponent);

	if (mUseBPMovement)
	{
		if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, "Enhanced Input Loaded");
			if (ShootAction)
				PlayerEnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ALuckyCharacter::OnHandleShoot);
			else
				GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, "No Shoot Action Detected");

			if (AltFireAction)
				PlayerEnhancedInputComponent->BindAction(AltFireAction, ETriggerEvent::Triggered, this, &ALuckyCharacter::OnHandleAltFire);
			else
				GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, "No Alt Fire Action Detected");

			if (ReloadAction)
				PlayerEnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ALuckyCharacter::OnHandleReload);
			else
				GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, "No Reload Action Detected");

			if (LookAction)
				PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started, this, &ALuckyCharacter::OnHandleLook);
			else
				GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, "No Look Action Detected");

			if (MoveAction)
				PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &ALuckyCharacter::OnHandleMove);
			else
				GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, "No Move Action Detected");
		}
		
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Cyan, "Enhanced Input Not Loaded");

		//Movement Axis
		PlayerInputComponent->BindAxis("KeyboardY", this, &ALuckyCharacter::MoveForward);
		PlayerInputComponent->BindAxis("KeyboardX", this, &ALuckyCharacter::MoveRight);

		//Mouse Movement
		PlayerInputComponent->BindAxis("MouseX", this, &ALuckyCharacter::CursorX);
		PlayerInputComponent->BindAxis("MouseY", this, &ALuckyCharacter::CursorY);

		//Action Bindings
		PlayerInputComponent->BindAction("Special", IE_Pressed, this, &ALuckyCharacter::AltFire);
		PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ALuckyCharacter::Reload);
		PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ALuckyCharacter::Fire);
	}
}

void ALuckyCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void ALuckyCharacter::OnHandleMove(const FInputActionValue& value)
{
	if (value.GetMagnitudeSq() != 0.0f)
	{
		AddMovementInput(FVector::RightVector, value[0] * mSpeed, false);
		AddMovementInput(FVector::ForwardVector, value[0] * mSpeed, false);
	}
}
void ALuckyCharacter::OnHandleLook(const FInputActionValue& value)
{
	if (value.GetMagnitudeSq() != 0)
	{
		FVector loc = mCursor->GetActorLocation();
		FVector moveVec = FVector(value[0], value[1], 0);
		moveVec *= mCursorSensitivity;
		moveVec.Set(moveVec.X, moveVec.Y, mCursorHeight);

		mCursor->Move(moveVec);
	}
}

void ALuckyCharacter::OnHandleAltFire(const FInputActionValue& value)
{

}

void ALuckyCharacter::OnHandleReload(const FInputActionValue& value)
{

}

void ALuckyCharacter::OnHandleShoot(const FInputActionValue& value)
{
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Instigator = this;
	spawnParameters.Owner = NULL;
	
	mProj = GetWorld()->SpawnActor<ALuckyProjectile>(ALuckyProjectile::StaticClass(), spawnParameters);
	mProj->SetActorLocationAndRotation(UGunBarrel->GetComponentLocation(), GetActorRotation());
	
	mProj = nullptr;
}

void ALuckyCharacter::MoveForward(float value) 
{
	FVector moveVector = FVector::ForwardVector;
	moveVector *= mSpeed * value;
	FVector location = GetActorLocation() + (moveVector * mDeltaTime);
	SetActorLocation(location, true);
}

void ALuckyCharacter::MoveRight(float value) 
{
	FVector moveVector = FVector::RightVector;
	moveVector *= mSpeed * value;
	FVector location = GetActorLocation() + (moveVector * mDeltaTime);
	SetActorLocation(location, true);
}

void ALuckyCharacter::Reload()
{
	UMag->Reload();
}

void ALuckyCharacter::CursorX(float value)
{
	mCursor->MoveX(value);
}

void ALuckyCharacter::CursorY(float value)
{
	mCursor->MoveY(value);
}

void ALuckyCharacter::CursorXY(FVector value)
{
	mCursor->Move(value);
}

void ALuckyCharacter::Fire()
{
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Instigator = this;
	spawnParameters.Owner = NULL;

	mProj = GetWorld()->SpawnActor<ALuckyProjectile>(ALuckyProjectile::StaticClass(), spawnParameters);
	mProj->SetActorLocationAndRotation(UGunBarrel->GetComponentLocation(), GetActorRotation());
	mProj = nullptr;
}

void ALuckyCharacter::AltFire()
{

}

void ALuckyCharacter::LookAtCursor()
{
	//TO DO
	//Make Cursor Actor
	//Force rotation to cursor object

}



