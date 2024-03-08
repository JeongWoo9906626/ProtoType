#include "BirdgeHandle.h"
#include "Bridge.h"

ABirdgeHandle::ABirdgeHandle()
{
}

ABirdgeHandle::~ABirdgeHandle()
{
}

void ABirdgeHandle::AddBridge(ABridge* _Bridge)
{
	BridgeList.push_front(_Bridge);
}

void ABirdgeHandle::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision(ECollisionOrder::Box);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetTransform({ { 0,0 }, { 50, 50 } });

	Renderer = CreateImageRenderer(ERenderOrder::Item);
	Renderer->SetImage("Axe.png");
	Renderer->SetTransform({ { 0, 0 }, { 64, 64 } });
}

void ABirdgeHandle::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		IsCollision = true;
		UContentsHelper::KoopaDie = true;
		Renderer->ActiveOff();
	}

	if (IsCollision == true)
	{
		DestroyBridge(_DeltaTime);
	}
}

void ABirdgeHandle::DestroyBridge(float _DeltaTime)
{
	if (Count >= 13)
	{
		IsCollision = false;
		Destroy();
		return;
	}
	if (CurDestroyTime >= DestroyTime)
	{
		++Count;
		CurDestroyTime = 0.0f;
		BridgeList.front()->Destroy();
		BridgeList.pop_front();
	}
	else 
	{
		CurDestroyTime += _DeltaTime;
		
	}
}
