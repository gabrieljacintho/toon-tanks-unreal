// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Capsule);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::TurretLookAt(FVector Target)
{
	FVector Direction = Target - TurretMesh->GetComponentLocation();
	FRotator TargetRotation = FRotator(0.f, Direction.Rotation().Yaw, 0.f);

	FRotator CurrentRotation = TurretMesh->GetComponentRotation();
	TargetRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 25.f);

	TurretMesh->SetWorldRotation(TargetRotation);
}