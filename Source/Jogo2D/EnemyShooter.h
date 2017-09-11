// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyShooter.generated.h"

/**
 * 
 */
UCLASS()
class JOGO2D_API AEnemyShooter : public AEnemy
{
	GENERATED_BODY()

	AEnemyShooter();

public:

	void BeginPlay() override;

	void Tick(float DeltaTime) override;


private:

	UPROPERTY(EditAnywhere)
		class UBoxComponent* AreaToShoot;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> MyBullet;

	UFUNCTION()
		void OnOverlapBeginStartShot(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapBeginStopShot(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool CanShot;

	void Shoot();

};
