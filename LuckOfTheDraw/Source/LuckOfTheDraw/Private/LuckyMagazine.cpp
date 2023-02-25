// Fill out your copyright notice in the Description page of Project Settings.


#include "LuckyMagazine.h"

// Sets default values for this component's properties
ULuckyMagazine::ULuckyMagazine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	mag = TArray<int>();
	
	for (int i = 0; i < maxAmmo; i++)
	{
		mag.Add(0);
	}
}

LuckyProjectileType ULuckyMagazine::swapProjectile(int index, LuckyProjectileType newBullet)
{
	LuckyProjectileType tmp;
	tmp = static_cast<LuckyProjectileType>(mag[index]);
	mag[index] = newBullet;
	return tmp;
}

void ULuckyMagazine::addProjectile(int newBullet)
{
	mag.Add(newBullet);
}

void ULuckyMagazine::addProjectile(LuckyProjectileType newBullet)
{
	mag.Add(newBullet);
}

// Called when the game starts
void ULuckyMagazine::BeginPlay()
{
	Super::BeginPlay();
}

LuckyProjectileType ULuckyMagazine::RollBarrel()
{
	LuckyProjectileType tmp = static_cast<LuckyProjectileType>(mag[barrelIndex]);

	barrelIndex++;
	if (barrelIndex >= maxAmmo || barrelIndex > mag.Num()) 
	{
		Reload();
	}

	return tmp;
}

// Called every frame
void ULuckyMagazine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULuckyMagazine::Reload()
{
	barrelIndex = 0;
}

ALuckyProjectile* ULuckyMagazine::shootProjectile(FVector loc, FRotator rot, APawn* charRef = nullptr)
{
	ALuckyProjectile* tmp = nullptr;
	LuckyProjectileType inChamber = RollBarrel();

	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Instigator = charRef; //Get reference to player pawn
	spawnParameters.Owner = GetOwner();

	switch (inChamber)
	{
	case LuckyProjectileType::STANDARD:
	default:
		tmp = GetWorld()->SpawnActor<ALuckyProjectile>(ALuckyProjectile::StaticClass(), spawnParameters);
		tmp->SetActorLocationAndRotation(loc, rot);
		break;
	}

	return tmp;
}

void ULuckyMagazine::setHand(TArray<int> newMag, bool overrideMax = false)
{
	if (overrideMax)
	{
		mag = newMag;
		maxAmmo = newMag.Num();
		return;
	}
	else
	{
		for (int i = 0; i < newMag.Num(); i++)
		{
			if (mag.IsValidIndex(i))
				mag[i] = newMag[i];
			else
				break;
		}
	}
}