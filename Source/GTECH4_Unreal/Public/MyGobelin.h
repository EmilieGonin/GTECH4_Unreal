// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "MyGobelin.generated.h"

/**
 * 
 */
UCLASS()
class GTECH4_UNREAL_API AMyGobelin : public AMyActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyGobelin();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UParticleSystem* VFXSystem;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	bool isDead;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	bool GetIsDead() const { return isDead; }

	void DestroyAfterDelay();

	FTimerHandle DestroyTimerHandle;
};
