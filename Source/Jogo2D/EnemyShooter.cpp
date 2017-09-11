// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyShooter.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Personagem.h"
#include "Bullet.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AEnemyShooter::AEnemyShooter()
{
	AreaToShoot = CreateDefaultSubobject<UBoxComponent>(TEXT("ShootAreaBox"));
	AreaToShoot->SetCollisionProfileName("OverlapAllDynamic");
	AreaToShoot->bGenerateOverlapEvents = true;
	AreaToShoot->OnComponentBeginOverlap.AddDynamic(this, &AEnemyShooter::OnOverlapBeginStartShot);
	AreaToShoot->OnComponentEndOverlap.AddDynamic(this, &AEnemyShooter::OnOverlapBeginStopShot);
	AreaToShoot->SetupAttachment(RootComponent);
}

void AEnemyShooter::BeginPlay()
{
	Super::BeginPlay();
	Lifes = 3;
}

void AEnemyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Shoot();
	
}

void AEnemyShooter::OnOverlapBeginStopShot(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap Stopped."));
		CanShot = false;
	}
}

void AEnemyShooter::OnOverlapBeginStartShot(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap Started."));
		CanShot = true;
	}
}

void AEnemyShooter::Shoot()
{
	if (CanShot) {
		UE_LOG(LogTemp, Warning, TEXT("CanShot."));
		APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
		if (Pawn) {
			UE_LOG(LogTemp, Warning, TEXT("Pawn Ok."));
			APersonagem* Personagem = Cast<APersonagem>(Pawn);
			UWorld* World = GetWorld();
			if (World) {
				UE_LOG(LogTemp, Warning, TEXT("World Ok."));
				FActorSpawnParameters SpawnParam;
				if (Personagem->GetActorLocation().X > GetActorLocation().X) {
					UE_LOG(LogTemp, Warning, TEXT("Atirou para DIREITA."));
					ABullet* Bullet = World->SpawnActor<ABullet>(MyBullet, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParam);
				} else {
					UE_LOG(LogTemp, Warning, TEXT("Atirou para ESQUERDA."));
					ABullet* Bullet = World->SpawnActor<ABullet>(MyBullet, GetActorLocation(), FRotator(0.0f, 180.0f, 0.0f), SpawnParam);
				}
			}
		}
	}
}
