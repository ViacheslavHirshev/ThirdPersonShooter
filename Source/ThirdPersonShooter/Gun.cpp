// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SkeletalMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashEffect, SkeletalMesh, TEXT("MuzzleFlashSocket"));

	APawn* GunOwner = Cast<APawn>(GetOwner());
	if (GunOwner == nullptr)
	{
		return;
	}

	AController* OwnerController = GunOwner->GetController();
	if (OwnerController == nullptr)
	{
		return;
	} 

	//Get location of player's viewpoint
	TUniquePtr<FVector> ViewpointLocation = MakeUnique<FVector>();
	TUniquePtr<FRotator> ViewpointRotation = MakeUnique<FRotator>();
	OwnerController->GetPlayerViewPoint(*ViewpointLocation, *ViewpointRotation);
	TUniquePtr<FVector> BulletEndPoint = MakeUnique<FVector>(*ViewpointLocation + ViewpointRotation->Vector() * ShootingDist);
	
	//Line tracing for shooting
	FHitResult HitResult;
	bool bIsLineTraceSucceed = GetWorld()->LineTraceSingleByChannel(HitResult, *ViewpointLocation, *BulletEndPoint, ECC_GameTraceChannel1);
	if (bIsLineTraceSucceed)
	{
		FVector ShotDirection{ -ViewpointRotation->Vector() };
		UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, HitResult.Location, ShotDirection.Rotation());

		if (HitResult.GetActor())
		{
			FPointDamageEvent PointDamageEvent(InDamage, HitResult, ShotDirection, nullptr);
			HitResult.GetActor()->TakeDamage(InDamage, PointDamageEvent, OwnerController, this);
		}
	}
	
}