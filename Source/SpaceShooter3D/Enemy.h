// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"

#include "PickUp.h"
#include "Projectile.h"

#include "Enemy.generated.h"

UCLASS()
class SPACESHOOTER3D_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ExplosionFX;

	UPROPERTY(EditAnywhere)
	UAudioComponent* ExplosionSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> EnemyProjectile;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<APickUp> PickupCan;

	UPROPERTY(EditAnywhere)
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APickUp> PickupCan;
	
	UWorld* ThisWorld;

	FVector CurrentLocation;
	FRotator CurrentRotation;

	float TotalTime;
	float RandomStart;

	UPROPERTY(EditAnywhere)
	float WeaponFireRate;

	UPROPERTY(EditAnywhere)
	float WeaponBurstDelay;

	float fTimeSinceLastShot;
	float fCurrentBurstDelay;

	UPROPERTY(EditAnywhere)
	float DestroyTimer;

	bool bHit;
	bool bDestroy;

	UFUNCTION()
	void OnBeginOverlap(AActor* EnemyActor, AActor* OtherActor);

};
