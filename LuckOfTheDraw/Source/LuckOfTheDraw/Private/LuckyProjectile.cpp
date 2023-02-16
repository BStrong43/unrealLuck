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

}

void ALuckyProjectile::Init()
{
	USphere = CreateDefaultSubobject<USphereComponent>(TEXT("Ball"));
	RootComponent = USphere;

	UMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	UMesh-> SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Meshes/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	if (Mesh.Succeeded())
	{
		UMesh->SetStaticMesh(Mesh.Object);
		UMesh->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
		UMesh->SetRelativeScale3D(FVector::OneVector * .1);
	}
}