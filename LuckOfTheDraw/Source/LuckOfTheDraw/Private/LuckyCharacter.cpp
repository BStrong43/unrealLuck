// Fill out your copyright notice in the Description page of Project Settings.


#include "LuckyCharacter.h"

// Sets default values
ALuckyCharacter::ALuckyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitMesh();
	InitCamera();
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
		UMesh->SetStaticMesh(capsuleMesh.Object);
		UMesh->SetRelativeLocation(FVector(0.0, 0.0, 0.0));
		UMesh->SetRelativeScale3D(FVector::OneVector * 1.f);
	}
}

void ALuckyCharacter::InitCamera()
{
	UCamBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	UCamBoom->SetupAttachment(RootComponent);
	UCamBoom->SetRelativeLocation(FVector(0.0, 0.0, 1000.0));
	UCamBoom->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	UCamBoom->TargetArmLength = 600.0f;
	UCamBoom->bEnableCameraLag = true;
	UCamBoom->CameraLagSpeed = 800.f;

	UCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	UCamera->SetupAttachment(UCamBoom, USpringArmComponent::SocketName);
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