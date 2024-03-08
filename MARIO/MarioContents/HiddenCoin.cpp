#include "HiddenCoin.h"
#include "Mario.h"

AHiddenCoin::AHiddenCoin()
{
}

AHiddenCoin::~AHiddenCoin()
{
}

void AHiddenCoin::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Coin);
	Renderer->SetImage("HiddenCoin.png");
	Renderer->SetTransform({ { 0, 0 }, { 128 * 4.0f, 128 * 4.0f } });

	Renderer->CreateAnimation("CoinIdle", "HiddenCoin.png", 0, 2, 0.2f, true);
	Renderer->ChangeAnimation("CoinIdle");

	Collision = CreateCollision(ECollisionOrder::HiddenCoin);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetPosition({ 0, -30 });
	Collision->SetScale({ 40, 60 });
}

void AHiddenCoin::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		UContentsHelper::CoinCount++;
		UContentsHelper::Score += 100;
		Destroy();
	}
}

