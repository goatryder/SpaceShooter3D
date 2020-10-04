// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Enemy.h"
#include "Hazard.h"
#include "Blueprint/UserWidget.h"

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

	UFUNCTION(BlueprintCallable)
	void RestartLevel(FName LevelName);

	bool bStart;

	// add widgets
	
	UPROPERTY(EditAnywhere, Category = "HUD Elements")
	TSubclassOf<UUserWidget> Score_Widget_Class;

	UPROPERTY(EditAnywhere, Category = "HUD Elements")
	TSubclassOf<UUserWidget> Shield_And_Armour_Widget_Class;

	UPROPERTY(EditAnywhere, Category = "HUD Elements")
	TSubclassOf<UUserWidget> Restart_Widget_Class;

protected:
	FActorSpawnParameters ActorNoSpawnParameters;
	
	FVector AsteroidSpawnLoc;
	FRotator AsteroidSpawnRot;

	FVector EnemySpawnLoc;
	FRotator EnemySpawnRot;

	UWorld* ThisWorld;

	
	UUserWidget* Score_Widget;
	
	UUserWidget* Shield_Armour_Widget;

	UUserWidget* Restart_Widget;
	
	APlayerController* PC_Ref;

};
