#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AFlag : public AActor
{
public:
	AFlag();
	~AFlag();

	AFlag(const AFlag& _Other) = delete;
	AFlag(AFlag&& _Other) noexcept = delete;
	AFlag& operator=(const AFlag& _Other) = delete;
	AFlag& operator=(AFlag&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* FlagCollision = nullptr;
};

