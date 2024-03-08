#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>
//#include "Mario.h"

enum ERenderOrder
{
	Map,
	UI,
	Plant,
	Gate,
	Coin,
	Monster,
	Brick,
	Item,
	Player,
	BreakOne,
	Fire,
	Pipe,
};

enum class ECollisionOrder
{
	Player,
	PlayerHead,
	PlayerBottom,
	Goomba,
	Troopa,
	Box,
	BoxTop,
	Gate,
	Flag,
	Step,
	HiddenCoin,
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EMonsterShootDir
{
	Left,
	Right
};

enum class EPlayState
{
	CameraFreeMove,
	FreeMove,
	Idle,
	Run,
	Reverse,
	Jump,
	Change,
	GrowUp,
	GrowDown,
	ChangeRed,
	HiddenStageEnter,
	HiddenStageOut,
	HiddenStageOutUp,
	Die,
	Kill,
	FinishMove,
	FinishReverse,
	FinishWalk,
	None,
};

enum class EMarioSizeState
{
	Small,
	Big,
	Red,
	Star,
	None
};

enum class EKoopaState
{
	Idle,
	Walk,
	Jump,
	Dead,
	None,
};

enum class EMonsterState
{
	Move,
	CollisionMove,
	Dead,
	Shoot,
	Wake,
	None
};

enum class EPlantState
{
	Move,
	Wait,
	Stop,
	None,
};

enum class EBoxState
{
	Idle,
	Hit,
	Break,
	Block,
	None,
};

enum class ECoinState
{
	CoinSpawn,
	CoinDestroy,
	None,
};

enum class EItemState
{
	Spawn,
	Move,
	CollisionMove,
	Eat,
	None,
};

enum class EGateState
{
	In,
	Out,
	None,
};

// Ό³Έν :
class UContentsHelper
{
public:
	static UWindowImage* MapColImage;

	static enum EMarioSizeState MSizeState;
	
	static int CoinCount;
	static int Score;
	static int Time;
	static int MainStage;
	static int SubStage;

	static std::string MapName;

	static bool KoopaDie;
	static bool KoopaWake;
	static bool KoopaIsFire;
	static bool MarioDie;

protected:

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

