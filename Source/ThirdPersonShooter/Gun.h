// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root{ nullptr };

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh{ nullptr };

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlashEffect{ nullptr };

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect{ nullptr };

	UPROPERTY(EditAnywhere)
	float ShootingDist{ 1000.0f };

	UPROPERTY(VisibleAnywhere)
	float InDamage{ 20 };
};
