// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBullet.h"
#include "Personagem.h"





void AEnemyBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(APersonagem::StaticClass())) {
		APersonagem* Personagem = Cast<APersonagem>(OtherActor);
		if (Personagem) {
			Destroy();
		}
		
	}
}