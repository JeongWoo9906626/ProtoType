#include "MarioFire.h"

MarioFire::MarioFire()
{
}

MarioFire::~MarioFire()
{
}

void MarioFire::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Fire);
	Renderer->SetImage("Fire.png");
	Renderer->SetTransform({ { 0, 0 }, { 64, 64 } });
	Renderer->CreateAnimation("FireShot", "Fire.png", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("FireBomb", "FireBomb.png", 0, 2, 0.1f, false);

	Renderer->ChangeAnimation("FireShot");
}

void MarioFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
