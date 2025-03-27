// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGobelin.h"
#include "MyEnviro.h"
#include "Kismet/GameplayStatics.h"

AMyGobelin::AMyGobelin()
{
    isDead = false;
    
	CapsuleComponent->InitCapsuleSize(50.0f, 50.0f);  // Exemple de taille de la capsule (rayon, hauteur)
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);


    CapsuleComponent->SetNotifyRigidBodyCollision(true);
	CapsuleComponent->OnComponentHit.AddDynamic(this, &AMyGobelin::OnHit);
}

void AMyGobelin::BeginPlay()
{
    Super::BeginPlay();

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("SkeletalMesh'/Enemy/Mesh/SM_EnemyGoblin.FBX'"));
    if (SkeletalMeshAsset.Succeeded())
    {
        SkeletalMeshComponent->SetSkeletalMesh(SkeletalMeshAsset.Object);
    }
}

void AMyGobelin::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyGobelin::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor)
    {
        AMyEnviro* envirro = Cast<AMyEnviro>(OtherActor);

        if (envirro)
        {
            isDead = true;

            GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AMyGobelin::DestroyAfterDelay, 1.0f, false);

            if (VFXSystem)
            {
                UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFXSystem, GetActorLocation());
            }
        }
    }
}

void AMyGobelin::DestroyAfterDelay()
{
    Destroy();
}