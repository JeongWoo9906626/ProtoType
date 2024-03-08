#include "BreakOne.h"

ABreakOne::ABreakOne()
{
}

ABreakOne::~ABreakOne()
{
}

void ABreakOne::BeginPlay()
{
   	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBrokenBrick.png");
	Renderer->SetTransform({ {0,0}, {32, 32} });

	Renderer->CreateAnimation("Spin", "OpenWorldBrokenBrick.png", 0, 3, 0.1f, true);
	
	Renderer->ChangeAnimation("Spin");
	Destroy(2.0f);
}

void ABreakOne::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	float XSpeed = 0.0f;
	UpSpeed += GravitySpeed * _DeltaTime;
	
	std::string DirName = GetName();
	if (DirName._Equal("LEFT"))
	{
		XSpeed = -30.0f;
	}
	else
	{
		XSpeed = 30.0f;
	}
	

	AddActorLocation({ XSpeed * _DeltaTime, UpSpeed * _DeltaTime });
}