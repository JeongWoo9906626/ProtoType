#include "Pipe.h"

APipe::APipe()
{
}

APipe::~APipe()
{
}

void APipe::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Pipe);
	Renderer->SetImage("Pipe.png");
	Renderer->SetTransform({ {0,0}, {128, 128} });
}

void APipe::Tick(float _DeltaTime)
{
}
