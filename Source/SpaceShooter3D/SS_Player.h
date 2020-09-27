// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"

#include "Projectile.h"

#include "SS_Player.generated.h"

UCLASS()
class SPACESHOOTER3D_API ASS_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASS_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystems;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ExplosionFX;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	UAudioComponent* DeathExplosionSound;


	UPROPERTY(EditAnywhere)
	float Field_Width;

	UPROPERTY(EditAnywhere)
	float Field_Height;

	UPROPERTY(EditAnywhere)
	float MaxVelocity;

	UPROPERTY(EditAnywhere)
	float BoundaryLimitOffset;

	UPROPERTY(BlueprintReadOnly)
	float Max_Health;

	UPROPERTY(BlueprintReadOnly)
	float Current_Health;
	
	UPROPERTY(BlueprintReadOnly)
	float Max_Armour;

	UPROPERTY(BlueprintReadOnly)
	float Current_Armour;


	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);

	void FireWeapon();
	void StartFirinig();
	void StopFirinig();

	bool bIsFiring;

	UPROPERTY(EditAnywhere)
	float WeaponFireRate;

	float TimeSinceLastShot;

	bool bHit;
	bool bDead;

	float Current_X_Velocity;
	float Current_Y_Velocity;

	UPROPERTY(BlueprintReadOnly)
	float PlayerScore;

	FVector Current_Location;
	FRotator Current_Rotation;
	FVector New_Location;

	UFUNCTION()
	void OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> WeaponProjectile_BP;

	void CollectablePickup();

};
