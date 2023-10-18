#include "PreCompile.h"
#include "WitchHouse_DownFloor.h"

#include "CameraControler.h"
#include "Ellie.h"
#include "BackDrop_WitchHouse_DownFloor.h"
#include "PortalObject.h"


WitchHouse_DownFloor::WitchHouse_DownFloor()
{
}

WitchHouse_DownFloor::~WitchHouse_DownFloor()
{
}


void WitchHouse_DownFloor::Start()
{
	PlayLevel::Start();

	std::string Name = "WitchHouse_DownFloor";
	SetName(Name);


	if (nullptr != m_LevelCameraControler)
	{
		m_LevelCameraControler->SetCameraMode(ECAMERAMODE::Fix);
	}
}

void WitchHouse_DownFloor::Update(float _Delta)
{
	PlayLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown('T', this))
	{
		m_Ellie->Transform.SetLocalPosition(float4::ZERO);
	}
}

void WitchHouse_DownFloor::LevelStart(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelStart(_NextLevel);

	LoadTexture();
	LoadSprite();
	LoadActor();

	SetEllieLevelChangeLocation(_NextLevel);

	CameraSetting();
}

void WitchHouse_DownFloor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	PlayLevel::LevelEnd(_NextLevel);

	ReleaseSprite();
	ReleaseTexture();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region LoadResource

void WitchHouse_DownFloor::LoadTexture()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
    			GameEngineTexture::Load(File.GetStringPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor\\Down_Sprite");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}
}

void WitchHouse_DownFloor::LoadSprite()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile File = Files[i];
		GameEngineSprite::CreateSingle(File.GetFileName());
	}


	// Dust
	GameEngineSprite::CreateCut("DownFloor_dust_remove.png", 22, 1);
	
	// Jucier
	GameEngineSprite::CreateCut("DownFloor_Extractor_0.png", 5, 4);
	GameEngineSprite::CreateCut("DownFloor_Extractor_1.png", 5, 4);

	// Pot
	GameEngineSprite::CreateCut("Pot_Fire_Large.png", 5, 5);
	GameEngineSprite::CreateCut("Pot_Fire_Small.png", 5, 5);
	GameEngineSprite::CreateCut("Pot_Fx_Boil.png", 4, 4);
	GameEngineSprite::CreateCut("Pot_Fx_Fail.png", 5, 4);
	GameEngineSprite::CreateCut("Pot_Fx_IdleA.png", 5, 5);
	GameEngineSprite::CreateCut("Pot_Fx_IdleB.png", 5, 5);
	GameEngineSprite::CreateCut("Pot_Fx_Steam.png", 5, 5);
	GameEngineSprite::CreateCut("Pot_Fx_Success.png", 5, 5);

	// Roaster
	GameEngineSprite::CreateCut("Roaster_0.png", 7, 7);
	GameEngineSprite::CreateCut("Roaster_0_Top.png", 7, 6);
}

void WitchHouse_DownFloor::LoadActor()
{
	if (nullptr == m_BackDrop)
	{
		m_BackDrop = CreateActor<BackDrop_WitchHouse_DownFloor>(EUPDATEORDER::Objects);
	}

	if (nullptr == m_BackDrop)
	{
		MsgBoxAssert("액터가 존재하지 않습니다.");
		return;
	}

	m_BackDrop->Init();
}


#pragma endregion 

#pragma region Initial Setting

// 레벨전환시 앨리의 시작위치를 지정해줍니다.
void WitchHouse_DownFloor::SetEllieLevelChangeLocation(class GameEngineLevel* _NextLevel)
{
	float4 SpawnPosition = float4::ZERO;

	std::string NextLevelName = _NextLevel->GetName();
	if (NextLevelName == "WitchHouse_UpFloor")
	{
		SpawnPosition = { 548.0f , -228.0f };
	}


	if (nullptr == m_Ellie)
	{
		MsgBoxAssert("앨리를 생성하지 않았습니다.");
		return;
	}
	m_Ellie->SetSpawnLocalPosition(SpawnPosition);
}

void WitchHouse_DownFloor::CameraSetting()
{
	if (nullptr != GlobalValue::g_CameraControler)
	{
		if (GlobalValue::g_CameraControler != m_LevelCameraControler)
		{
			MsgBoxAssert("현재 카메라 매니저가 아닙니다.");
			return;
		}

		float4 HWinScale = GlobalValue::GetWindowScale().Half();
		HWinScale.Y *= -1.0f;

		GlobalValue::g_CameraControler->SetLocalPostion(HWinScale);
	}
}

#pragma endregion 

#pragma region Update



#pragma endregion 

#pragma region Release


void WitchHouse_DownFloor::ReleaseSprite()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			GameEngineSprite::Release(pFile.GetFileName());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor\\Down_Sprite");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			GameEngineSprite::Release(pFile.GetFileName());
		}
	}
}

void WitchHouse_DownFloor::ReleaseTexture()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\WitchHouse_DownFloor\\Down_Sprite");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile pFile = Files[i];
			GameEngineTexture::Release(pFile.GetFileName());
		}
	}
}

#pragma endregion 