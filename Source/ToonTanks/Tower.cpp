// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank) // Tank != nullptr
	{
		FVector PlayerLocation = Tank->GetActorLocation();
		float Distance = FVector::Dist(GetActorLocation(), PlayerLocation);
		if (Distance <= FireRange)
		{
			TurretLookAt(PlayerLocation);
		}
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}