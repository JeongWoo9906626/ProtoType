#include "Koopa.h"
#include "Mario.h"
#include "KoopaFire.h"

AKoopa::AKoopa()
{
}

AKoopa::~AKoopa()
{
}

void AKoopa::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Monster);
	Renderer->SetImage("Koopa_Left.png");
	Renderer->SetTransform({ {0, 0}, {256 * 2.0f, 256 * 2.0f} });

	Renderer->CreateAnimation("Idle_Left", "Koopa_Left.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Walk_Left", "Koopa_Left.png", 0, 3, 0.1f, true);
	
	Renderer->CreateAnimation("Walk_Right", "Koopa_Right.png", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Idle_Right", "Koopa_Right.png", 0, 0, 0.1f, true);

	Collision = CreateCollision(ECollisionOrder::Goomba);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetPosition({ -30, -70 });
	Collision->SetScale({ 140, 140 });

	BottomCollision = CreateCollision(ECollisionOrder::Goomba);
	BottomCollision->SetColType(ECollisionType::Rect);
	BottomCollision->SetPosition({ 0, 0 });
	BottomCollision->SetScale({ 10, 10 });

	Renderer->ChangeAnimation("Walk_Left");
}

void AKoopa::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> BridgeTopResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BridgeTopResult))
	{
		IsCollision = true;

		FVector KoopaCollisionPos = BottomCollision->GetActorBaseTransform().GetPosition();
		FVector KoopaCollisionScale = BottomCollision->GetActorBaseTransform().GetScale();

		FVector BridgeCollisionPos = BridgeTopResult[0]->GetActorBaseTransform().GetPosition();
		FVector BridgeCollisionScale = BridgeTopResult[0]->GetActorBaseTransform().GetScale();

		SetActorLocation({ KoopaCollisionPos.X, BridgeCollisionPos.Y - 3.0f });
	}
	else
	{
		IsCollision = false;
	}

	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult))
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
			UContentsHelper::MarioDie = true;
			Mario->StateChange(EPlayState::Die);
			return;
		}
	}

	Walk(_DeltaTime);
}

void AKoopa::DirCheck()
{
	FVector MarioPos = AMario::MainPlayer->GetActorLocation();
	FVector MyPos = GetActorLocation();
	
	EActorDir Curdir = DirState;

	if (MarioPos.X > MyPos.X)
	{
		DirState = EActorDir::Right;
	}
	else
	{
		DirState = EActorDir::Left;
	}

	if (Curdir != DirState)
	{
		Renderer->ChangeAnimation(GetAnimationName());
	}
}

void AKoopa::Walk(float _DeltaTime)
{
	if (false == UContentsHelper::MarioDie)
	{
		DirCheck();
	}

	switch (DirState)
	{
	case EActorDir::Left:
		Dir = -1;
		break;
	case EActorDir::Right:
		Dir = 1;
		break;
	}

	if (true == UContentsHelper::KoopaWake && false == UContentsHelper::KoopaDie)
	{
		if (CurJumpTime >= JumpTime)
		{
			AddActorLocation(FVector::Up * 10);
			CurJumpTime = 0.0f;
			JumpSpeed = -150.0f;
		}
		if (IsCollision == true)
		{
			CurJumpTime += _DeltaTime;
		}

		AddActorLocation({ Dir * WalkSpeed * _DeltaTime, 0.0f });
	}

	if (true == UContentsHelper::KoopaIsFire && false == UContentsHelper::KoopaDie)
	{
		float FirePos = 0.0f;
		FVector KoopaPos = GetActorLocation();
		int RandomValue = rand() % 10 + 1;
		if (RandomValue > 5)
		{
			FirePos = -10.0f;
		}
		else
		{
			FirePos = -100.0f;
		}

		if (false == FirstShot)
		{
			AKoopaFire* KoopaFire = GetWorld()->SpawnActor<AKoopaFire>(ERenderOrder::Fire);
			KoopaFire->SetFireDir(EActorDir::Left);
			KoopaFire->SetActorLocation({ 6550.0f, KoopaPos.Y + FirePos });
			FirstShot = true;
		}

		if (CurFireTime >= FireTime)
		{
			CurFireTime = 0.0f;
			AKoopaFire* KoopaFire = GetWorld()->SpawnActor<AKoopaFire>(ERenderOrder::Fire);
			KoopaFire->SetFireDir(DirState);
			KoopaFire->SetActorLocation({ KoopaPos.X, KoopaPos.Y + FirePos });
		}
		CurFireTime += _DeltaTime;
	}

	if (false == IsCollision)
	{
		JumpSpeed += GravitySpeed * _DeltaTime;
		AddActorLocation({ 0.0f, JumpSpeed * _DeltaTime });
	}
}

std::string AKoopa::GetAnimationName()
{
	std::string AnimationName = "";
	switch (DirState)
	{
	case EActorDir::Left:
		AnimationName = "Walk_Left";
		break;
	case EActorDir::Right:
		AnimationName = "Walk_Right";
		break;
	}

	return AnimationName;
}

