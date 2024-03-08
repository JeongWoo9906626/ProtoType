#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABridge : public AActor
{
public:
	ABridge();
	~ABridge();

	ABridge(const ABridge& _Other) = delete;
	ABridge(ABridge&& _Other) noexcept = delete;
	ABridge& operator=(const ABridge& _Other) = delete;
	ABridge& operator=(ABridge&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* TopCollision = nullptr;
};

