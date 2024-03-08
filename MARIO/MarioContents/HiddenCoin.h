#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AHiddenCoin : public AActor
{
public:
	AHiddenCoin();
	~AHiddenCoin();

	AHiddenCoin(const AHiddenCoin& _Other) = delete;
	AHiddenCoin(AHiddenCoin&& _Other) noexcept = delete;
	AHiddenCoin& operator=(const AHiddenCoin& _Other) = delete;
	AHiddenCoin& operator=(AHiddenCoin&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
};

