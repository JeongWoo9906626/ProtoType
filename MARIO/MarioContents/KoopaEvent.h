#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AKoopaEvent : public AActor
{
public:
	AKoopaEvent();
	~AKoopaEvent();

	AKoopaEvent(const AKoopaEvent& _Other) = delete;
	AKoopaEvent(AKoopaEvent&& _Other) noexcept = delete;
	AKoopaEvent& operator=(const AKoopaEvent& _Other) = delete;
	AKoopaEvent& operator=(AKoopaEvent&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	UCollision* MoveCollision = nullptr;
	UCollision* FireCollision = nullptr;

};

