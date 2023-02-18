// Fill out your copyright notice in the Description page of Project Settings.


#include "LuckyProjectile.h"

// Sets default values
ALuckyProjectile::ALuckyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Init();
}

// Called when the game starts or when spawned
void ALuckyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALuckyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mOverridePath)
		doOverridePath(DeltaTime);
	else
		doPath(DeltaTime);

	timeAlive += DeltaTime;
	if (timeAlive >= mLifeTime || timeAlive >= maxLifeTime) Destroy();
}

void ALuckyProjectile::doPath(float DeltaTime)
{
	FVector loc = GetActorLocation();
	FVector dist = GetActorForwardVector() * (mSpeed * DeltaTime);
	SetActorLocation(loc + dist);
}

void ALuckyProjectile::Init()
{
	USphere = CreateDefaultSubobject<USphereComponent>(TEXT("Ball"));
	RootComponent = USphere;
	USphere->SetRelativeScale3D(FVector::OneVector * 0.4);

	UMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	UMesh-> SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Meshes/Shapes/Shape_Sphere.Shape_Sphere"));
	if (Mesh.Succeeded())
	{
		UMesh->SetStaticMesh(Mesh.Object);
		UMesh->SetRelativeLocation(FVector(0.0, 0.0, -30.0));
		UMesh->SetRelativeScale3D(FVector::OneVector * 0.61);
	}
}