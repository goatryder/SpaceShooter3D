// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Player.h"

// Sets default values
ASS_Player::ASS_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	ParticleSystems = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	DeathExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathExposionSound"));

	ShipMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleSystems->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	DeathExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ASS_Player::BeginPlay()
{
	Super::BeginPlay();
	
	Current_Location = GetActorLocation();
	Current_Rotation = GetActorRotation();

	// bHit = false;
	// bDead = false;

	// Current_X_Velocity = 0.0f;
	// Current_Y_Velocity = 0.0f;
	// bIsFiring = false;
	// WeaponFireRate = 0.25f;
	// TimeSinceLastShot = 0.0f;
	// PlayerScore = 0.0f;

	Max_Health = 100.0f;
	Current_Health = 100.0f;

	Max_Armour = 100.0f;
	Current_Armour = 100.0f;

	ExplosionFX->Deactivate();
	DeathExplosionSound->Deactivate();

	OnActorBeginOverlap.AddDynamic(this, &ASS_Player::OnBeginOverlap);
}

// Called every frame
void ASS_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Update ship location
	if (Current_X_Velocity != 0.0f || Current_Y_Velocity != 0.0f) {
		
		Current_Location.X += Current_X_Velocity * DeltaTime;
		Current_Location.Y += Current_Y_Velocity * DeltaTime;

		SetActorLocation(Current_Location);
	}

	// Update ship rotation, slightly rotate on movement
	if (Current_Y_Velocity > 0.1f) {

		SetActorRotation(FRotator(
			Current_Rotation.Pitch + 45.0f,
			Current_Rotation.Yaw,
			Current_Rotation.Roll
		));
	
	} 
	else if (Current_Y_Velocity < -0.1f) {
	
		SetActorRotation(FRotator(
			Current_Rotation.Pitch - 45.0f,
			Current_Rotation.Yaw,
			Current_Rotation.Roll
		));
	
	}
	else {
	
		SetActorRotation(Current_Rotation);
	
	}

	// set ship move boundaries X axis
	if (GetActorLocation().X > Field_Width) {

		Current_Location = FVector(Field_Width - BoundaryLimitOffset, Current_Location.Y, Current_Location.Z);

	}
	else if (GetActorLocation().X < -Field_Width) {

		Current_Location = FVector(-Field_Width + BoundaryLimitOffset, Current_Location.Y, Current_Location.Z);
	
	}

	// set shit move boundaries Y axis
	if (GetActorLocation().Y > Field_Height) {

		Current_Location = FVector(Current_Location.X, Field_Height - BoundaryLimitOffset, Current_Location.Z);

	}
	else if (GetActorLocation().Y < -Field_Height) {

		Current_Location = FVector(Current_Location.X, -Field_Height + BoundaryLimitOffset, Current_Location.Z);

	}

	// handle firing
	if (bIsFiring) {

		if (TimeSinceLastShot > WeaponFireRate) {

			FireWeapon();
			TimeSinceLastShot = 0.0f;

		}
	}

	TimeSinceLastShot += DeltaTime;

}

// Called to bind functionality to input
void ASS_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASS_Player::MoveRight);
	PlayerInputComponent->BindAxis(FName("MoveUp"), this, &ASS_Player::MoveUp);
	
	PlayerInputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ASS_Player::StartFirinig);
	PlayerInputComponent->BindAction(FName("Fire"), IE_Released, this, &ASS_Player::StopFirinig);

}

void ASS_Player::MoveRight(float AxisValue)
{
	Current_X_Velocity = MaxVelocity * AxisValue;
}

void ASS_Player::MoveUp(float AxisValue)
{
	Current_Y_Velocity = MaxVelocity * AxisValue;
}


void ASS_Player::StartFirinig()
{
	bIsFiring = true;
}

void ASS_Player::StopFirinig()
{
	bIsFiring = false;
}

void ASS_Player::FireWeapon()
{
	
	// spawn projectile
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	AActor* SpawnedProjectile = GetWorld()->SpawnActor(WeaponProjectile_BP, &Current_Location, &Current_Rotation, Params);

}

void ASS_Player::CollectablePickup()
{
}	


void ASS_Player::OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor)
{
}
