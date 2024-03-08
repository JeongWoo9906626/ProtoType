#include "Goomba.h"
#include "Mario.h"
#include "Troopa.h"

AGoomba::AGoomba()
{
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("OpenWorldGoomba.png");
		Renderer->SetTransform({ { 0, 0 }, { 256 * 1.3f, 256 * 1.3f } });
	}

	{
		Renderer->CreateAnimation("GoombaDie", "OpenWorldGoomba.png", 2, 2, 0.1f, true);
		Renderer->CreateAnimation("GoombaMove", "OpenWorldGoomba.png", 0, 1, 0.2f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Goomba);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -30 });
		BodyCollision->SetScale({ 40, 40 });
	}

	{
		BottomCollision = CreateCollision(ECollisionOrder::Goomba);
		BottomCollision->SetColType(ECollisionType::Rect);
		BottomCollision->SetPosition({ 0, 0 });
		BottomCollision->SetScale({ 30, 10 });
	}

	StateChange(EMonsterState::Move);
}

void AGoomba::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	std::vector<UCollision*> MarioResult;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		UCollision* MarioPosition = MarioResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		FTransform Collision = MarioPosition->GetActorBaseTransform();

		FTransform MyTransform = BodyCollision->GetActorBaseTransform();

		if (Collision.GetPosition().Y + 32.0f < MyTransform.GetPosition().Y)
		{
			Player->StateChange(EPlayState::Kill);
			StateChange(EMonsterState::Dead);
			return;
		}
		else
		{
			if (Player->SizeState != EMarioSizeState::Small)
			{
				Player->StateChange(EPlayState::GrowDown);
				return;
			}
			else
			{
				Player->StateChange(EPlayState::Die);
				return;
			}
		}
	}

	std::vector<UCollision*> BoxTopResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BoxTopResult))
	{
		for (UCollision* BoxPosition : BoxTopResult)
		{
			IsBoxCollision = true;
		}
	}
	else
	{
		IsBoxCollision = false;
	}

	std::vector<UCollision*> TroopaResult;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Troopa, MarioResult))
	{
		StateChange(EMonsterState::Dead);
		return;
	}

	StateUpdate(_DeltaTime);
}

void AGoomba::StateChange(EMonsterState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EMonsterState::Move:
			MoveStart();
			break;
		case EMonsterState::CollisionMove:
			CollisionMoveStart();
			break;
		case EMonsterState::Dead:
			DeadStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AGoomba::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	case EMonsterState::CollisionMove:
		CollisionMove(_DeltaTime);
		break;
	default:
		break;
	}
}

void AGoomba::MoveStart()
{
	DestroyValue = false;
	Renderer->ChangeAnimation("GoombaMove");
}

void AGoomba::CollisionMoveStart()
{
	DestroyValue = false;
	Renderer->ChangeAnimation("GoombaMove");
}

void AGoomba::DeadStart()
{
	DestroyValue = true;
	Renderer->ChangeAnimation("GoombaDie");
	BodyCollision->ActiveOff();
	BottomCollision->ActiveOff();
	Destroy(0.5f);
}


void AGoomba::Move(float _DeltaTime)
{
	if (true == IsBoxCollision)
	{
		StateChange(EMonsterState::CollisionMove);
		return;
	}

	FVector ForwardVector = { 1.0f, 0.0f, 0.0f, 0.0f };
	GravityMove(_DeltaTime);

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 32.0f;
		break;
	case EActorDir::Right: 
		CheckPos.X += 32.0f;
		break;
	default:
		break;
	}
	CheckPos.Y -= 32.0f;

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		ChangeDir(DirState);
	}

	if (EActorDir::Left == DirState)
	{
		DirUnitVector = -1.0f;
	}
	else
	{
		DirUnitVector = 1.0f;
	}

	CheckWindowPosition();

	if (true == DestroyValue)
	{
		Destroy();
	}
	
	AddActorLocation(ForwardVector * DirUnitVector * MoveSpeed * _DeltaTime);
}

void AGoomba::CollisionMove(float _DeltaTime)
{
	if (false == IsBoxCollision)
	{
		StateChange(EMonsterState::Move);
		return;
	}

	FVector ForwardVector = { 1.0f, 0.0f, 0.0f, 0.0f };

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 32.0f;
		break;
	case EActorDir::Right:
		CheckPos.X += 32.0f;
		break;
	default:
		break;
	}
	CheckPos.Y -= 32.0f;

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		ChangeDir(DirState);
	}

	if (EActorDir::Left == DirState)
	{
		DirUnitVector = -1.0f;
	}
	else
	{
		DirUnitVector = 1.0f;
	}

	CheckWindowPosition();

	if (true == DestroyValue)
	{
		Destroy();
	}

	AddActorLocation(ForwardVector * DirUnitVector * MoveSpeed * _DeltaTime);
}

void AGoomba::GravityMove(float _DeltaTime)
{
	FVector GravityVector = { 0.0f, 1.0f, 0.0f, 0.0f };
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GravityVector = FVector::Zero;
	}
	else
	{
		AddActorLocation(GravityVector * GravitySpeed * _DeltaTime);
	}
}

void AGoomba::ChangeDir(EActorDir _State)
{
	if (EActorDir::Left == DirState)
	{
		DirState = EActorDir::Right;
	}
	else
	{
		DirState = EActorDir::Left;
	}
}

void AGoomba::CheckWindowPosition()
{
	FVector CurPosition = GetActorLocation();
	FVector CameraPos = GetWorld()->GetCameraPos();
	if (CameraPos.X >= CurPosition.X)
	{
		DestroyValue = true;
	}
}