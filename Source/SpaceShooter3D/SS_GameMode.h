// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Enemy.h"
#include "Hazard.h"

#include "SS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER3D_API ASS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASS_GameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> Enemy;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHazard> HazardTemplate;

	UPROPERTY(EditAnywhere)
	UAudioComponent* MusicTrack;
	
	TSubclassOf<AHazard> GetHazardTemplate();

	int32 SpawnTimer;
	bool bPlayerDead;

	UFUNCTION()
	void RestartLevel(FName LevelName);

	bool bStart;

protected:
	FActorSpawnParameters ActorNoSpawnParameters;
	
	FVector AsteroidSpawnLoc;
	FRotator AsteroidSpawnRot;

	FVector EnemySpawnLoc;
	FRotator EnemySpawnRot;

	UWorld* ThisWorld;

	// add widgets

	
};
