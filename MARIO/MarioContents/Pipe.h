#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class APipe : public AActor
{
public:
	APipe();
	~APipe();

	APipe(const APipe& _Other) = delete;
	APipe(APipe&& _Other) noexcept = delete;
	APipe& operator=(const APipe& _Other) = delete;
	APipe& operator=(APipe&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;

};

