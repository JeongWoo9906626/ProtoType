#include "Coin.h"
#include "Brick.h"

ACoin::ACoin()
{
}

ACoin::~ACoin()
{
}

void ACoin::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Coin);
	Renderer->SetImage("Coin.png");
	Renderer->SetTransform({ { 0, 0 }, { 64 * 1.5f, 64 * 1.5f } });

	Renderer->CreateAnimation("CoinSpawn", "Coin.png", 0, 3, 0.03f, true);
}

void ACoin::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void ACoin::StateChange(ECoinState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ECoinState::CoinSpawn:
			CoinSpawnStart();
			break;
		case ECoinState::CoinDestroy:
			CoinDestroyStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ACoin::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ECoinState::CoinSpawn:
		CoinSpawn(_DeltaTime);
		break;
	case ECoinState::CoinDestroy:
		CoinDestroy(_DeltaTime);
		break;
	default:
		break;
	}
}

void ACoin::CoinSpawnStart()
{
	FirstPos = GetActorLocation();
	AddActorLocation({ 0.0f, -60.0f });
	Renderer->ChangeAnimation("CoinSpawn");
	UContentsHelper::CoinCount++;
	UContentsHelper::Score += 100;
}

void ACoin::CoinDestroyStart()
{
	Renderer->SetActive(false);
}

void ACoin::CoinSpawn(float _DeltaTime)
{
	if (false == IsDown)
	{
		FVector CurPos = GetActorLocation();
		if (CurPos.Y - FirstPos.Y > MoveUpPos)
		{
			AddActorLocation(FVector::Up * MoveUpSpeed * _DeltaTime);
		}
		else
		{
			IsDown = true;
		}
	}
	else
	{
		FVector CurPos = GetActorLocation();
		if (CurPos.Y - (FirstPos.Y - 40.0f) < 0.0f)
		{
			AddActorLocation(FVector::Down * MoveUpSpeed * _DeltaTime);
		}
		else
		{
			float MoveDownPos = 100.0f;
			StateChange(ECoinState::CoinDestroy);
			return;
		}
	}
}

void ACoin::CoinDestroy(float _DeltaTime)
{
	Destroy();
}
