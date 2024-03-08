#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABreakBrick : public AActor
{
public:
	ABreakBrick();
	~ABreakBrick();

	ABreakBrick(const ABreakBrick& _Other) = delete;
	ABreakBrick(ABreakBrick&& _Other) noexcept = delete;
	ABreakBrick& operator=(const ABreakBrick& _Other) = delete;
	ABreakBrick& operator=(ABreakBrick&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EBoxState _State);
	void StateUpdate(float _DeltaTime);

	void IdleStart();
	void HitStart();
	void BreakStart();

	void Idle(float _DeltaTime);
	void Hit(float _DeltaTime);
	void Break(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	/*UImageRenderer* LeftTop = nullptr;
	UImageRenderer* LeftBottom = nullptr;
	UImageRenderer* RightTop = nullptr;
	UImageRenderer* RightBottom = nullptr;*/

	UCollision* TopCollision = nullptr;
	UCollision* BottomCollision = nullptr;
	UCollision* LeftCollision = nullptr;
	UCollision* RightCollision = nullptr;

	EBoxState State = EBoxState::None;
	EMarioSizeState MarioState = EMarioSizeState::None;

	int HitCount = 10;
	bool IsBreak = false;
	float MaxHitUpSize = 30.0f;
	float HitUpSpeed = 300.0f;
	FVector FirstPos = FVector::Zero;
	FVector MoveUpPos = FVector::Zero;
	FVector MoveDownPos = FVector::Zero;
};