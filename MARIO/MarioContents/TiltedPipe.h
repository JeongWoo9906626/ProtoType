#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ATiltedPipe : public AActor
{
public:
	ATiltedPipe();
	~ATiltedPipe();

	ATiltedPipe(const ATiltedPipe& _Other) = delete;
	ATiltedPipe(ATiltedPipe&& _Other) noexcept = delete;
	ATiltedPipe& operator=(const ATiltedPipe& _Other) = delete;
	ATiltedPipe& operator=(ATiltedPipe&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;

};

