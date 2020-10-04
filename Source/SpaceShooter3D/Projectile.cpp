// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "SS_Player.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BulletComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneComponent"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));

	BulletComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	bHit = false;
	bDestroy = false;

}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetActorLocation();

	OnActorBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// move projectile
	CurrentLocation.X += ProjectileSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

	if (bHit)
		Destroy();

}


void AProjectile::OnBeginOverlap(AActor* ProjectileActor, AActor* OtherActor)
{

	if (OtherActor->ActorHasTag(FName("BoundsProjectile"))) {

		bHit = true;

	} // collide projectile bounds

	else if (OtherActor->ActorHasTag(FName("Asteroid"))) {

		ASS_Player* OwningPlayer = Cast<ASS_Player>(GetOwner());
		
		if (OwningPlayer)
			OwningPlayer->PlayerScore += 10.0f;
		
		bHit = true;
	
	} // player hit asteroid

	else if (OtherActor->ActorHasTag(FName("EnemyShip"))) {

		ASS_Player* OwningPlayer = Cast<ASS_Player>(GetOwner());
			
		if (OwningPlayer) {

			OwningPlayer->PlayerScore += 50.0f;
			
		} // player hit enemy

		if (OtherActor != GetOwner())  // ignore collision with projectile owner
			bHit = true;

	} // projectile hit enemy

	else if (ActorHasTag(FName("EnemyProjectile")) && OtherActor->ActorHasTag(FName("Player"))) {

		bHit = true;

	} // enemy projectile hit player
		
}
