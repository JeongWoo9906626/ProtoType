#include "TiltedPipe.h"

ATiltedPipe::ATiltedPipe()
{
}

ATiltedPipe::~ATiltedPipe()
{
}

void ATiltedPipe::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Pipe);
	Renderer->SetImage("TiltedPipe.png");
	Renderer->SetTransform({ {0,0}, {128, 128} });
}

void ATiltedPipe::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
