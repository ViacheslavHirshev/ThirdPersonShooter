// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingTarget = UGameplayStatics::GetPlayerPawn(this, 0);
	SetFocus(AimingTarget);
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveToActor(AimingTarget, 200);
}