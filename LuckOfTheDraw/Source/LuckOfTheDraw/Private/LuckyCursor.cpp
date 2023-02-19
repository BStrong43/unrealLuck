// Fill out your copyright notice in the Description page of Project Settings.

#include "LuckyCursor.h"

// Sets default values
ALuckyCursor::ALuckyCursor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init Mesh
	UMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = UMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Meshes/Shapes/Shape_Sphere.Shape_Sphere"));
	if (Mesh.Succeeded())
	{
		UMesh->SetStaticMesh(Mesh.Object);
		UMesh->SetRelativeLocation(FVector(0.0, 0.0, -50.0));
		UMesh->SetRelativeScale3D(FVector::OneVector * .6);
	}
}

// Called when the game starts or when spawned
void ALuckyCursor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALuckyCursor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TrackToMouse();
}

void ALuckyCursor::TrackToMouse()
{
	
}

void ALuckyCursor::Move(FVector value)
{
	value.Z = 88;
	if (GetActorLocation().Length() < mBoundingBoxDiameter)
		SetActorLocation(GetActorLocation() + value);
	else
		SetActorLocation(GetActorLocation() - value);
}

void ALuckyCursor::MoveX(float value)
{
	FVector mov = GetActorLocation() + (FVector::RightVector * value);
	mov.Z = 88;
	SetActorLocation(mov);

	if (mov.X > mBoundingBoxDiameter)
		mov.X = mBoundingBoxDiameter;
}

void ALuckyCursor::MoveY(float value)
{
	value *= 1.6;
	FVector mov = GetActorLocation() + (FVector::ForwardVector * value);
	mov.Z = 88;
	SetActorLocation(mov);

	if (mov.Y > mBoundingBoxDiameter)
		mov.Y = mBoundingBoxDiameter;
}