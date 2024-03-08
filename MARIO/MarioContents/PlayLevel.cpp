#include "PlayLevel.h"
#include "BackGround.h"
#include "ContentsHelper.h"
#include "Mario.h"
#include "Goomba.h"
#include "Troopa.h"
#include "Plant.h"
#include "Flag.h"
#include "Brick.h"
#include "BreakBrick.h"
#include "ItemBox.h"
#include "Gate.h"
#include "HiddenGate.h"
#include "HiddenCoin.h"
#include "UI.h"
#include "Pipe.h"
#include "TiltedPipe.h"

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UContentsHelper::MapName = "FirstStage";

	ABackGround* BackGroundMap = SpawnActor<ABackGround>(ERenderOrder::Map);
	BackGroundMap->SetMapImage("Stage01.png");
	BackGroundMap->SetCollisionMapImage("Stage01_Col.png");
	BackGroundMap->SwitchDebug();

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });

	AMario* Mario = SpawnActor<AMario>(ERenderOrder::Player);
	Mario->SetName("Player");
	Mario->SetActorLocation({ 200, 500 });

	AFlag* Flag = SpawnActor<AFlag>(ERenderOrder::Map);
	Flag->SetActorLocation({ 705, 700 });
	Flag->SetActorLocation({ 12705, 700 });

	//AGoomba* Goomba = SpawnActor<AGoomba>(ERenderOrder::Monster);
	//Goomba->SetName("OpenWorldGoomba1");
	//Goomba->SetActorLocation({ 750, 600 });
	//AGoomba* Goomba2 = SpawnActor<AGoomba>(ERenderOrder::Monster);
	//Goomba2->SetName("OpenWorldGoomba2");
	//Goomba2->SetActorLocation({ 1260, 600 });

	//ATroopa* Turtle = SpawnActor<ATroopa>(ERenderOrder::Monster);
	//Turtle->SetName("OpenWorldTroopa");
	//Turtle->SetActorLocation({ 1600, 700 });
	//ATroopa* Turtle2 = SpawnActor<ATroopa>(ERenderOrder::Monster);
	//Turtle2->SetName("OpenWorldTroopa2");
	//Turtle2->SetActorLocation({ 1000, 700 });

	APlant* Plant = SpawnActor<APlant>(ERenderOrder::Plant);
	Plant->SetName("Plant");
	// 710 MaxTop 
	// 800 MaxBottom
	Plant->SetActorLocation({ 1855, 800 });

	// Level Change Gate
	AGate* Gate = SpawnActor<AGate>(ERenderOrder::Gate);
	Gate->SetName("Gate1");
	Gate->SetActorLocation({ 13140, 800 });

	// Pipe
	APipe* Pipe1 = SpawnActor<APipe>(ERenderOrder::Pipe);
	Pipe1->SetName("Pipe1");
	Pipe1->SetActorLocation({ 3712, 640 });

	APipe* Pipe2 = SpawnActor<APipe>(ERenderOrder::Pipe);
	Pipe2->SetName("Pipe1");
	Pipe2->SetActorLocation({ 10495, 769 });

	// TiltedPipe
	ATiltedPipe* TiltedPipe1 = SpawnActor<ATiltedPipe>(ERenderOrder::Pipe);
	TiltedPipe1->SetName("TiltedPipe1");
	TiltedPipe1->SetActorLocation({ 3970, 1728 });

	// Hidden Gate
	AHiddenGate* HiddenGateIn = SpawnActor<AHiddenGate>(ERenderOrder::Gate);
	HiddenGateIn->SetName("HiddenGate1");
	HiddenGateIn->SetGateState(EGateState::In);
	HiddenGateIn->SetActorLocation({ 3710, 580 });

	AHiddenGate* HiddenGateOut = SpawnActor<AHiddenGate>(ERenderOrder::Gate);
	HiddenGateOut->SetName("HiddenGate2");
	HiddenGateOut->SetGateState(EGateState::Out);
	HiddenGateOut->SetActorLocation({ 3963, 1700 });

	// HiddenCoin
	AHiddenCoin* HiddenCoin1 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin1->SetName("HiddenCoin1");
	HiddenCoin1->SetActorLocation({ 3360, 1600 });

	AHiddenCoin* HiddenCoin2 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin2->SetName("HiddenCoin2");
	HiddenCoin2->SetActorLocation({ 3423, 1600 });

	AHiddenCoin* HiddenCoin3 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin3->SetName("HiddenCoin3");
	HiddenCoin3->SetActorLocation({ 3486, 1600 });

	AHiddenCoin* HiddenCoin4 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin4->SetName("HiddenCoin4");
	HiddenCoin4->SetActorLocation({ 3549, 1600 });

	AHiddenCoin* HiddenCoin5 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin5->SetName("HiddenCoin5");
	HiddenCoin5->SetActorLocation({ 3612, 1600 });

	AHiddenCoin* HiddenCoin6 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin6->SetName("HiddenCoin6");
	HiddenCoin6->SetActorLocation({ 3675, 1600 });

	AHiddenCoin* HiddenCoin7 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin7->SetName("HiddenCoin7");
	HiddenCoin7->SetActorLocation({ 3738, 1600 });

	AHiddenCoin* HiddenCoin8 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin8->SetName("HiddenCoin8");
	HiddenCoin8->SetActorLocation({ 3360, 1500 });

	AHiddenCoin* HiddenCoin9 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin9->SetName("HiddenCoin9");
	HiddenCoin9->SetActorLocation({ 3423, 1500 });

	AHiddenCoin* HiddenCoin10 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin10->SetName("HiddenCoin10");
	HiddenCoin10->SetActorLocation({ 3486, 1500 });

	AHiddenCoin* HiddenCoin11 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin11->SetName("HiddenCoin11");
	HiddenCoin11->SetActorLocation({ 3549, 1500 });

	AHiddenCoin* HiddenCoin12 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin12->SetName("HiddenCoin12");
	HiddenCoin12->SetActorLocation({ 3612, 1500 });

	AHiddenCoin* HiddenCoin13 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin13->SetName("HiddenCoin13");
	HiddenCoin13->SetActorLocation({ 3675, 1500 });

	AHiddenCoin* HiddenCoin14 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin14->SetName("HiddenCoin14");
	HiddenCoin14->SetActorLocation({ 3738, 1500 });

	AHiddenCoin* HiddenCoin15 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin15->SetName("HiddenCoin15");
	HiddenCoin15->SetActorLocation({ 3423, 1400 });

	AHiddenCoin* HiddenCoin16 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin16->SetName("HiddenCoin16");
	HiddenCoin16->SetActorLocation({ 3486, 1400 });

	AHiddenCoin* HiddenCoin17 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin17->SetName("HiddenCoin17");
	HiddenCoin17->SetActorLocation({ 3549, 1400 });

	AHiddenCoin* HiddenCoin18 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin18->SetName("HiddenCoin18");
	HiddenCoin18->SetActorLocation({ 3612, 1400 });

	AHiddenCoin* HiddenCoin19 = SpawnActor<AHiddenCoin>(ERenderOrder::Coin);
	HiddenCoin19->SetName("HiddenCoin19");
	HiddenCoin19->SetActorLocation({ 3675, 1400 });

	// 아이템 박스
	AItemBox* ItemBrick0;
	ItemBrick0 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick0->SetName("Item0");
	ItemBrick0->SetActorLocation({ 1050, 650 });

	AItemBox* ItemBrick1;
	ItemBrick1 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick1->SetName("Item1");
	ItemBrick1->SetActorLocation({ 1364, 650 });

	AItemBox* ItemBrick2;
	ItemBrick2 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick2->SetName("Item2");
	ItemBrick2->SetActorLocation({ 1428, 400 });

	AItemBox* ItemBrick3;
	ItemBrick3 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick3->SetName("Item3");
	ItemBrick3->SetActorLocation({ 1492, 650 });

	AItemBox* ItemBrick4;
	ItemBrick4 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick4->SetName("Item4");
	ItemBrick4->SetActorLocation({ 5114, 650 });

	AItemBox* ItemBrick5;
	ItemBrick5 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick5->SetName("Item5");
	ItemBrick5->SetActorLocation({ 6192, 400 });

	AItemBox* ItemBrick6;
	ItemBrick6 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick6->SetName("Item6");
	ItemBrick6->SetActorLocation({ 7000, 650 });

	AItemBox* ItemBrick7;
	ItemBrick7 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick7->SetName("Item7");
	ItemBrick7->SetActorLocation({ 7300, 650 });

	AItemBox* ItemBrick8;
	ItemBrick8 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick8->SetName("Item8");
	ItemBrick8->SetActorLocation({ 7600, 650 });

	AItemBox* ItemBrick9;
	ItemBrick9 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick9->SetName("Item9");
	ItemBrick9->SetActorLocation({ 8314, 400 });

	AItemBox* ItemBrick10;
	ItemBrick10 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick10->SetName("Item10");
	ItemBrick10->SetActorLocation({ 8378, 400 });

	AItemBox* ItemBrick11;
	ItemBrick11 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick11->SetName("Item11");
	ItemBrick11->SetActorLocation({ 10992, 650 });

	// 동전 박스
	ABrick* OWBrick1;
	OWBrick1 = SpawnActor<ABrick>(ERenderOrder::Brick);
	OWBrick1->SetName("Brick1");
	OWBrick1->SetActorLocation({ 5050, 650 });

	// 일반 박스
	ABreakBrick* OWBreakBrick1;
	OWBreakBrick1 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick1->SetName("BreakBrick1");
	OWBreakBrick1->SetActorLocation({ 1300, 650 });

	ABreakBrick* OWBreakBrick2;
	OWBreakBrick2 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick2->SetName("BreakBrick2");
	OWBreakBrick2->SetActorLocation({ 1428, 650 });

	ABreakBrick* OWBreakBrick3;
	OWBreakBrick3 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick3->SetName("BreakBrick3");
	OWBreakBrick3->SetActorLocation({ 1556, 650 });

	ABreakBrick* OWBreakBrick4;
	OWBreakBrick4 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick4->SetName("BreakBrick4");
	OWBreakBrick4->SetActorLocation({ 5178, 650 });

	ABreakBrick* OWBreakBrick5;
	OWBreakBrick5 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick5->SetName("BreakBrick5");
	OWBreakBrick5->SetActorLocation({ 5256, 400 });

	ABreakBrick* OWBreakBrick6;
	OWBreakBrick6 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick6->SetName("BreakBrick5");
	OWBreakBrick6->SetActorLocation({ 5320, 400 });

	ABreakBrick* OWBreakBrick22;
	OWBreakBrick22 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick22->SetName("BreakBrick5");
	OWBreakBrick22->SetActorLocation({ 5384, 400 });

	ABreakBrick* OWBreakBrick7;
	OWBreakBrick7 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick7->SetName("BreakBrick7");
	OWBreakBrick7->SetActorLocation({ 5448, 400 });

	ABreakBrick* OWBreakBrick8;
	OWBreakBrick8 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick8->SetName("BreakBrick8");
	OWBreakBrick8->SetActorLocation({ 5512, 400 });

	ABreakBrick* OWBreakBrick9;
	OWBreakBrick9 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick9->SetName("BreakBrick9");
	OWBreakBrick9->SetActorLocation({ 5576, 400 });

	ABreakBrick* OWBreakBrick10;
	OWBreakBrick10 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick10->SetName("BreakBrick10");
	OWBreakBrick10->SetActorLocation({ 5640, 400 });

	ABreakBrick* OWBreakBrick11;
	OWBreakBrick11 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick11->SetName("BreakBrick11");
	OWBreakBrick11->SetActorLocation({ 6000, 400 });

	ABreakBrick* OWBreakBrick12;
	OWBreakBrick12 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick12->SetName("BreakBrick12");
	OWBreakBrick12->SetActorLocation({ 6064, 400 });

	ABreakBrick* OWBreakBrick13;
	OWBreakBrick13 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick13->SetName("BreakBrick13");
	OWBreakBrick13->SetActorLocation({ 6128, 400 });

	ABreakBrick* OWBreakBrick14;
	OWBreakBrick14 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick14->SetName("BreakBrick14");
	OWBreakBrick14->SetActorLocation({ 7800, 400 });

	ABreakBrick* OWBreakBrick15;
	OWBreakBrick15 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick15->SetName("BreakBrick15");
	OWBreakBrick15->SetActorLocation({ 7864, 400 });

	ABreakBrick* OWBreakBrick16;
	OWBreakBrick16 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick16->SetName("BreakBrick16");
	OWBreakBrick16->SetActorLocation({ 7928, 400 });

	ABreakBrick* OWBreakBrick17;
	OWBreakBrick17 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick17->SetName("BreakBrick17");
	OWBreakBrick17->SetActorLocation({ 8250, 400 });

	ABreakBrick* OWBreakBrick18;
	OWBreakBrick18 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick18->SetName("BreakBrick18");
	OWBreakBrick18->SetActorLocation({ 8314, 650 });

	ABreakBrick* OWBreakBrick19;
	OWBreakBrick19 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick19->SetName("BreakBrick19");
	OWBreakBrick19->SetActorLocation({ 10800, 650 });

	ABreakBrick* OWBreakBrick20;
	OWBreakBrick20 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick20->SetName("BreakBrick20");
	OWBreakBrick20->SetActorLocation({ 10864, 650 });

	ABreakBrick* OWBreakBrick21;
	OWBreakBrick21 = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick21->SetName("BreakBrick21");
	OWBreakBrick21->SetActorLocation({ 10928, 650 });
}

void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UPlayLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UPlayLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	GEngine->DestroyLevel("Play");
}
