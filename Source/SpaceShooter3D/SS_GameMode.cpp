// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_GameMode.h"

// Sets default values
ASS_GameMode::ASS_GameMode()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MusicTrack = CreateDefaultSubobject<UAudioComponent>(TEXT("Music"));
	MusicTrack->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SpawnTimer = 0.0f;

	AsteroidSpawnLoc = FVector(1000.0f, 1000.0f, 1000.0f);
	AsteroidSpawnRot = FRotator(0.0f, 0.0f, 0.0f);

	EnemySpawnLoc = FVector(0.0f, 0.0f, 0.0f);
	EnemySpawnRot = FRotator(0.0f, 0.0f, 0.0f);

	ThisWorld = GetWorld();

}

// Called when the game starts or when spawned
void ASS_GameMode::BeginPlay()
{
	Super::BeginPlay();

	MusicTrack->Play();

	bPlayerDead = false;

}

// Called every frame
void ASS_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnTimer = FMath::RandRange(0, 1000);

	

	// spawn enemy
	if (Enemy) {
		 
		if (SpawnTimer > 990.0f) {

			AActor* NewEnemy = ThisWorld->SpawnActor(
				Enemy, &EnemySpawnLoc, &EnemySpawnRot, ActorNoSpawnParameters
			);

			if (NewEnemy) {

				NewEnemy->SetActorLocation(FVector(
					1000.0f, FMath::RandRange(-500, 500), 0.0f
				));

			}

		}

	}

	// spawn hazard (asteroid)
	if (HazardTemplate) {

		if (SpawnTimer > 995.0f) {

			AActor* NewHazard = ThisWorld->SpawnActor(
				HazardTemplate, &AsteroidSpawnLoc, &AsteroidSpawnRot, ActorNoSpawnParameters
			);

			/*
			if (NewHazard) {

				// Remove if useless (probably it is)
				NewHazard->SetActorLocation(FVector(
					1000.0f, 1000.0f, 1000.0f
				));
			}*/

		}

	}

}


void ASS_GameMode::RestartLevel(FName LevelName)
{

}