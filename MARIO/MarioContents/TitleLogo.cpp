#include "TitleLogo.h"
#include <EngineCore/EngineCore.h>

ATitleLogo::ATitleLogo() 
{
}

ATitleLogo::~ATitleLogo() 
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer();

	Renderer->SetImage(/*TODO 타이틀 로고 사진 이름*/"Mario_Title.png");
	// TODO
	// 위치 설정
	FVector WindowScale = GEngine->MainWindow.GetWindowScale();
	Renderer->SetTransform({ WindowScale.Half2D(), WindowScale });
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}

