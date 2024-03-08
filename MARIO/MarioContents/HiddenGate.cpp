#include "HiddenGate.h"

AHiddenGate::AHiddenGate()
{
}

AHiddenGate::~AHiddenGate()
{
}

void AHiddenGate::BeginPlay()
{
	AActor::BeginPlay();

	BodyCollision = CreateCollision(ECollisionOrder::Gate);
	BodyCollision->SetColType(ECollisionType::Rect);
	BodyCollision->SetPosition({ 0, 55 });
	BodyCollision->SetScale({ 120, 120 });
}

void AHiddenGate::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void AHiddenGate::SetGateState(EGateState _State)
{
	State = _State;
}

EGateState AHiddenGate::GetGateState()
{
	return State;
}
