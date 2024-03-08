#include "SpinFire.h"
#include "Mario.h"

ASpinFire::ASpinFire() 
{
}

ASpinFire::~ASpinFire() 
{
}

void ASpinFire::SetSpinDir(EActorDir _Dir)
{
	Dir = _Dir;
}

void ASpinFire::BeginPlay()
{
	AActor::BeginPlay();

	for (int i = 0; i < 6; i++)
	{
		Renderer[i] = CreateImageRenderer(ERenderOrder::Monster);
		Renderer[i]->SetImage("Fire.png");
		Renderer[i]->CreateAnimation("Spin", "Fire.png", 0, 3, 0.1f, true);
		Renderer[i]->SetTransform({ { 32.0f * i, 0.0f }, { 256.0f, 256.0f } });
		Renderer[i]->ChangeAnimation("Spin");
	}

	for (int i = 0; i < 6; ++i) {
		Collision[i] = CreateCollision(ERenderOrder::Monster);
		Collision[i]->SetColType(ECollisionType::CirCle);
		Collision[i]->SetTransform({ { 16.0f * i, 16.0f}, {32.0f , 32.0f} });
	}
}

void ASpinFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	for (int i = 0; i < 6; i++)
	{
		std::vector<UCollision*> MarioResult;
		if (true == Collision[i]->CollisionCheck(ECollisionOrder::Player, MarioResult))
		{
			UCollision* MarioCollision = MarioResult[0];
			AMario* Mario = (AMario*)MarioCollision->GetOwner();
			if (Mario->SizeState != EMarioSizeState::Small)
			{
				Mario->SizeState = EMarioSizeState::Small;
				Mario->StateChange(EPlayState::GrowDown);
				return;
			}
			else
			{
				Mario->StateChange(EPlayState::Die);
				return;
			}
		}
	}

	FireSpin(_DeltaTime);
}

void ASpinFire::FireSpin(float _DeltaTime)
{
	FVector SpinPos = FVector::Right;

	switch (Dir)
	{
	case EActorDir::Left:
		SpinDir = -1.0f;
		break;
	case EActorDir::Right:
		SpinDir = 1.0f;
		break;
	default:
		break;
	}

	Degree += 180.0f * _DeltaTime * SpinDir;

	for (int i = 0; i < 6; ++i)
	{
		FVector Pos = SpinPos * 24.f * i;
		Pos.RotationZToDeg(Degree);
		Renderer[i]->SetPosition(Pos);
		Collision[i]->SetPosition({Pos.X, Pos.Y - 12});	
	}
}

