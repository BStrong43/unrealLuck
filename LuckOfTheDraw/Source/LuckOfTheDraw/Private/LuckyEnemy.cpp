// Fill out your copyright notice in the Description page of Project Settings.


#include "LuckyEnemy.h"

// Sets default values
ALuckyEnemy::ALuckyEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UMag = CreateDefaultSubobject<ULuckyMagazine>(TEXT("Magazine"));

	UCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = UCapsule;

	UMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	UMesh->SetupAttachment(RootComponent);

	UGunBarrel = CreateDefaultSubobject<USceneComponent>(TEXT("Barrel"));
	UGunBarrel->SetupAttachment(UMesh);
	UGunBarrel->SetRelativeLocation(FVector(50.0, 0.0, 12.5));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> capsuleMesh(TEXT("/Game/Meshes/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	if (capsuleMesh.Succeeded())
	{
		UMesh->SetStaticMesh(capsuleMesh.Object);
		UMesh->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
		UMesh->SetRelativeScale3D(FVector(1.36, 1.36, 1.778));
	}

	UMove = CreateDefaultSubobject<ULEMovement>(TEXT("Movement"));
	UMove->UpdatedComponent = RootComponent;

	shootTime = mShootTimer;
}

// Called when the game starts or when spawned
void ALuckyEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALuckyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ALuckyEnemy::EnemyTakeDamage(float dmg)
{
	float newHealth = mHealth - dmg;
	Destroy();
	return newHealth;
}

ALuckyProjectile* ALuckyEnemy::Shoot() 
{
	return UMag->shootProjectile(UGunBarrel->GetComponentLocation(), GetActorRotation(), this);

}

void ALuckyEnemy::startShootTimer()
{

}

void ALuckyEnemy::stopShootTimer()
{

}