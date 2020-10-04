// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	ExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathExposionSound"));

	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// TotalTime = 0.0f;
	// TimeSinceLastShot = 0.0f;
	DestroyTimer = 1.0f;

	// bHit = false;
	// bDestroy = false;

	ExplosionFX->Deactivate();
	ExplosionSound->Deactivate();

	ThisWorld = GetWorld();
	RandomStart = FMath::Rand();

	OnActorBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlap);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TotalTime += DeltaTime;
	fTimeSinceLastShot += DeltaTime;

	CurrentLocation = GetActorLocation();
	CurrentRotation = GetActorRotation();

	// Random Movement on Y Axis
	CurrentLocation.Y += FMath::Sin(TotalTime + RandomStart);

	// Move Backwards on X Axis
	SetActorLocation(CurrentLocation - CurrentVelocity * DeltaTime);

	// handle shooting
	if (fTimeSinceLastShot >= WeaponFireRate && !bHit) {

		if (fCurrentBurstDelay >= WeaponBurstDelay) {

			FActorSpawnParameters Params = {};
			Params.Owner = this;

			ThisWorld->SpawnActor(EnemyProjectile, &CurrentLocation, &CurrentRotation, Params);

			fCurrentBurstDelay = 0.0f;
		}

		fTimeSinceLastShot = 0.0f;
		fCurrentBurstDelay += DeltaTime;
	}

	// handle destroying and hiting
	if (bHit) {

		StaticMesh->SetVisibility(false);
		SetActorEnableCollision(false);
		ExplosionFX->Activate();
		ExplosionSound->Activate();

		DestroyTimer -= DeltaTime;
	 
	}

	else if (bDestroy) {
		Destroy();
	}

	else if (DestroyTimer <= 0.0f) {
		Destroy();
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemy::OnBeginOverlap(AActor* EnemyActor, AActor* OtherActor)
{

	if (OtherActor->ActorHasTag("Bounds")) {
		bDestroy = true;
	}

	else if (OtherActor->ActorHasTag("Asteroid") || OtherActor->ActorHasTag("Player")) {
		bHit = true;
	}

	else if (OtherActor->ActorHasTag("Projectile")) {
		
		bHit = true;
			
		// spawn pickup
		if (ThisWorld) {

			if (FMath::RandRange(0, 10) > 7) {

				FVector Current_Location = GetActorLocation();
				FRotator Current_Rotation = GetActorRotation();
				FActorSpawnParameters Params = {};

				ThisWorld->SpawnActor(PickupCan, &Current_Location, &Current_Rotation, Params);

			}
		}
	}

} // on begin overlap

