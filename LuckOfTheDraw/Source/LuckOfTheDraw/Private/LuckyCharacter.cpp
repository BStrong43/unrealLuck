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
}

// Called when the game starts or when spawned
void ALuckyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	UGunBarrel-> SetRelativeLocation(FVector(0.0, -50.0, 12.5));
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
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement Axis
	PlayerInputComponent->BindAxis("KeyboardY", this, &ALuckyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("KeyboardX", this, &ALuckyCharacter::MoveRight);

	//Action Bindings
	PlayerInputComponent->BindAction("Special", IE_Pressed, this, &ALuckyCharacter::SpecialAction);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ALuckyCharacter::Reload);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ALuckyCharacter::Shoot);

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

void ALuckyCharacter::LookAtCursor()
{
	//TO DO
	//Make Cursor Actor
	//Force rotation to cursor object
}

void ALuckyCharacter::SpecialAction()
{

}

void ALuckyCharacter::Shoot() 
{
	//Bang bang
}

void ALuckyCharacter::Reload()
{

}