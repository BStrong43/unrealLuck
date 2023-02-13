// Fill out your copyright notice in the Description page of Project Settings.


#include "LuckyCharacter.h"

// Sets default values
ALuckyCharacter::ALuckyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALuckyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALuckyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mDeltaTime = DeltaTime;

}

// Called to bind functionality to input
void ALuckyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement Axis
	PlayerInputComponent->BindAxis("KeyboardX", this, &ALuckyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("KeyboardY", this, &ALuckyCharacter::MoveRight);

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

}

void ALuckyCharacter::Dash()
{

}

void ALuckyCharacter::Shoot() 
{
	
}

void ALuckyCharacter::Reload()
{

}