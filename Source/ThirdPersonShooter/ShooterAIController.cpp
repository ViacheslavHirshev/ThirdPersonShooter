// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingTarget = UGameplayStatics::GetPlayerPawn(this, 0);

 	Patroling();
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//TrackPlayer();
}

void AShooterAIController::TrackPlayer()
{
	/*if (LineOfSightTo(AimingTarget, FVector::ZeroVector))
	{
		SetFocus(AimingTarget);
		MoveToActor(AimingTarget, 350);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}*/

	
}

void AShooterAIController::Patroling()
{
	if (AIBehaviorTree)
	{
 		RunBehaviorTree(AIBehaviorTree);
 		GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolingStartLocation"), GetPawn()->GetActorLocation());
	 	GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolingEndLocation"), FVector(3260.0, -6340.0, 0.0));
	}
}