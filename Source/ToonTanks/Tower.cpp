// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		TurretLookAt(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

bool ATower::InFireRange()
{
	if (Tank) // Tank != nullptr
	{
		FVector PlayerLocation = Tank->GetActorLocation();
		float Distance = FVector::Dist(GetActorLocation(), PlayerLocation);
		return Distance <= FireRange;
	}

	return false;
}

void ATower::CheckFireCondition()
{
	if (!Tank || !Tank->bAlive)
	{
		return;
	}

	if (InFireRange())
	{
		Fire();
	}
}