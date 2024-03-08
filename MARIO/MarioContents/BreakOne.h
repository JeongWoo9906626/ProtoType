#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABreakBrick;

class ABreakOne : public AActor
{
	friend ABreakBrick;

public:
	ABreakOne();
	~ABreakOne();

	ABreakOne(const ABreakOne& _Other) = delete;
	ABreakOne(ABreakOne&& _Other) noexcept = delete;
	ABreakOne& operator=(const ABreakOne& _Other) = delete;
	ABreakOne& operator=(ABreakOne&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;

	float UpSpeed = -300.0f;
	float GravitySpeed = 900.0f;
};

