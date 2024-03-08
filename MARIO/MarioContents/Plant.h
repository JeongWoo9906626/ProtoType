#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class APlant : public AActor
{
public:
	APlant();
	~APlant();

	APlant(const APlant& _Other) = delete;
	APlant(APlant&& _Other) noexcept = delete;
	APlant& operator=(const APlant& _Other) = delete;
	APlant& operator=(APlant&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EPlantState _State);
	void StateUpdate(float _DeltaTime);

	void MoveStart();
	void WaitStart();
	void StopStart();

	void Move(float _DeltaTime);
	void Wait(float _DeltaTime);
	void Stop(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	EPlantState State = EPlantState::None;

	FVector DirVector = FVector::Up;

	bool IsUp = true;

	float MoveSpeed = 50.0f;
	float MaxMoveY = 90.0f;
	float CurMoveY = 0.0f;

	float CurTime = 0.0f;
	float WaitTime = 2.0f;
};

