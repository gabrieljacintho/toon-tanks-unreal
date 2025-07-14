// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		APlayerController* PlayerController = Tank->GetPlayerController();
		if (PlayerController)
		{
			Tank->DisableInput(PlayerController);
			PlayerController->bShowMouseCursor = false;
		}
	}
	else if (ATower* DeadTower = Cast<ATower>(DeadActor))
	{
		DeadTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0));
}