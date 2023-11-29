#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineBlend.h>

// data
#include "ContentsEvent.h"
#include "BiologyData.h"
#include "IngredientData.h"
#include "ItemData.h"
#include "ProductRecipeData.h"
#include "QuestData.h"


void ContentsCore::InitResources()
{
	// �÷��� ����
	FileLoadFunction::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Creature");				// ũ��ó
	FileLoadFunction::LoadAllDirFile("Resources\\PlayContents\\PlayResourecs\\Map");						// ��
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\EillieBody");	// �ٸ�
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Ellie\\Broom");			// ���ڷ�
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\NPC");					// NPC 
	FileLoadFunction::LoadAllFileInPath("Resources\\PlayContents\\PlayResourecs\\Fx");					// Fx

	GameEngineSprite::CreateSingle("Broom_Particle.png");

	{
		//UI
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\UI");
		std::vector<GameEngineDirectory> Directions = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directions.size(); i++)
		{
			GameEngineDirectory Direction = Directions[i];
			std::vector<GameEngineFile> Files = Direction.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile pFile = Files[i];
				GameEngineTexture::Load(pFile.GetStringPath());
			}
		}
	}

	{
		// Map
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("Resources\\PlayContents\\PlayResourecs\\Map\\");
		std::vector<GameEngineDirectory> Directions = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directions.size(); i++)
		{
			GameEngineDirectory Direction = Directions[i];
			std::vector<GameEngineFile> Files = Direction.GetAllFile();
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile pFile = Files[i];
				GameEngineSprite::CreateSingle(pFile.GetFileName());
			}
		}
	}

	LoadContentsData();
}


void ContentsCore::LoadContentsData()
{
	ContentsEvent::Init();

	// ������
	ItemData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "����� ��", EITEM_TYPE::Ingredient });
	ItemData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "���ø�����", EITEM_TYPE::Ingredient });
	ItemData::CreateData("BushBug_Water", { "BushBug_Water", "��Ǯ ���� ��", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "��ǳ ��� ��", EITEM_TYPE::Ingredient });
	ItemData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "����������", EITEM_TYPE::Ingredient });
	ItemData::CreateData("FlowerBird_Water", { "FlowerBird_Water", "���ɹ�", EITEM_TYPE::Ingredient });
	ItemData::CreateData("MoonButterfly_Water", { "MoonButterfly_Water", "�޺� ���� ��", EITEM_TYPE::Ingredient });


	ItemData::CreateData("Mongsiri_Collect", { "Mongsiri_Collect", "���ø���", EITEM_TYPE::Source });
	ItemData::CreateData("BushBug_Collect", { "BushBug_Collect", "���� ����", EITEM_TYPE::Source });
	ItemData::CreateData("WitchFlower_Collect", { "WitchFlower_Collect", "�����", EITEM_TYPE::Source });
	ItemData::CreateData("FlowerBird_Collect", { "FlowerBird_Collect", "����", EITEM_TYPE::Source });
	ItemData::CreateData("MapleHerb_Collect", { "MapleHerb_Collect", "��ǳ ���", EITEM_TYPE::Source });
	ItemData::CreateData("SilverStarFlower_Collect", { "SilverStarFlower_Collect", "�������� ����", EITEM_TYPE::Source });
	ItemData::CreateData("MoonButterfly_Collect", { "MoonButterfly_Collect", "�޺� ����", EITEM_TYPE::Source });
	ItemData::CreateData("PumpkinTerrier_Collect", { "PumpkinTerrier_Collect", "ȣ�� �������� �� ����", EITEM_TYPE::Source });
	ItemData::CreateData("BubbleLizard_Collect", { "BubbleLizard_Collect", "�������", EITEM_TYPE::Source });

	// ����Ʈ
	ItemData::CreateData("Item_Etc_10", { "Item_Etc_10", "����� ������", EITEM_TYPE::Quest });

	// ����
	ItemData::CreateData("BadGrassPotion", { "BadGrassPotion", "���� Ǯ ���Ź���", EITEM_TYPE::Potion });
	ItemData::CreateData("NutritionPotion", { "NutritionPotion", "���� ���� ����", EITEM_TYPE::Potion });
	ItemData::CreateData("FirecrackerPotion", { "FirecrackerPotion", "���� ����", EITEM_TYPE::Potion });

	ItemData::CreateData("UncurseCandy", { "UncurseCandy", "�������� ����", EITEM_TYPE::Potion });
	ItemData::CreateData("HealingCandy", { "HealingCandy", "ȸ�� ����", EITEM_TYPE::Potion });

	// ������� 
	ItemData::CreateData("Branch_Collect", { "Branch_Collect", "��������", EITEM_TYPE::RepairMaterial });

	// ����
	ItemData::CreateData("Food_CranApple", { "Food_CranApple", "���", EITEM_TYPE::Food });

	// ����
	ItemData::CreateData("Item_Etc_11", { "Item_Etc_11", "���ڸ�ä", EITEM_TYPE::Tool });
	ItemData::CreateData("Item_Etc_12", { "Item_Etc_12", "���ڷ�", EITEM_TYPE::Tool });



	// ��� ����
	IngredientData::CreateData("Mongsiri_Water", { "Mongsiri_Water", "���ø�����", "Mongsiri_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("PumpkinTerrier_Powder", { "PumpkinTerrier_Powder", "ȣ�� ������ �� �Ŀ��", "PumpkinTerrier_Collect", EBrewingMachineType::Roaster, 4 });
	IngredientData::CreateData("BushBug_Water", { "BushBug_Water", "���ұ�����", "BushBug_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("FlowerBird_Water", { "FlowerBird_Water", "���ɹ�", "FlowerBird_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("BubbleLizard_Water", { "BubbleLizard_Water", "���������", "BubbleLizard_Collect", EBrewingMachineType::Extractor, 2 });

	IngredientData::CreateData("WitchFlower_Water", { "WitchFlower_Water", "����� ��", "WitchFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("SilverStarFlower_Water", { "SilverStarFlower_Water", "����������", "SilverStarFlower_Collect", EBrewingMachineType::Extractor, 2 });
	IngredientData::CreateData("MapleHerb_Water", { "MapleHerb_Water", "��ǳ ��� ��", "MapleHerb_Collect", EBrewingMachineType::Extractor, 2 });

	// ����
	BiologyData::CreateData("Mongsiri", { "Mongsiri", "���ø�", "Mongsiri_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest ,EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::Day });
	BiologyData::CreateData("PumpkinTerrier", { "PumpkinTerrier", "ȣ�� ������", "PumpkinTerrier_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlains, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("BushBug", { "BushBug", "���� ����", "BushBug_Collect", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("FlowerBird", { "FlowerBird", "���ϻ�", "FlowerBird_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::Day });
	BiologyData::CreateData("BubbleLizard", { "BubbleLizard", "Ǫ�� ��� ������", "BubbleLizard_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Day });

	// �Ĺ�
	BiologyData::CreateData("WitchFlower", { "WitchFlower", "�����", "WitchFlower_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::None, EECOLOGYTYPE::AllDay });
	BiologyData::CreateData("SilverStarFlower", { "SilverStarFlower", "��������", "SilverStarFlower_Collect", ETOOLTYPE::Dragonfly, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestWaterfall, EECOLOGYTYPE::Night });
	BiologyData::CreateData("MapleHerb", { "MapleHerb", "��ǳ ���", "MapleHerb_Collect", ETOOLTYPE::Gloves, EECOLOGYTYPE::GreenForest, EECOLOGYTYPE::ForestPlateau, EECOLOGYTYPE::AllDay });

	// ����
	ProductRecipeData::CreateData("BadGrassPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"WitchFlower_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Four, "BadGrassPotion", "���� Ǯ ���� ����" , {} });
	ProductRecipeData::CreateData("NutritionPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1}, {"MapleHerb_Water", 1 },{"BushBug_Water", 1  }}, EBREWING_DIFFICULTY::Normal, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Three, "NutritionPotion", "���� ���� ����", {} });
	ProductRecipeData::CreateData("FirecrackerPotion", { std::vector<ProductRecipeData::MaterialInfo>{{"SilverStarFlower_Water", 1,}, { "FlowerBird_Water", 1 },{"BushBug_Water", 1} }, EBREWING_DIFFICULTY::Hard, EBREWING_DIRECTION::StirLeft, EBREWING_FIRE::Two, "FirecrackerPotion", "���� ����" , {} });

	// ����
	/*std::vector<ProduectDESC> UncurseCandyDESCArray = { {EPRODUCTDESCTYPE::Observation, "���డ ���� ���� �� ���� ����ϱ� ������, ���� ���̶�� �̸��� �ٿ�����."},{EPRODUCTDESCTYPE::, "���డ ���� ���� �� ���� ����ϱ� ������, ���� ���̶�� �̸��� �ٿ�����."} };*/
	ProductRecipeData::CreateData("UncurseCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"Mongsiri_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirNone, EBREWING_FIRE::Three,  "UncurseCandy", "�������� ����" });
	ProductRecipeData::CreateData("HealingCandy", { std::vector<ProductRecipeData::MaterialInfo>{{"WitchFlower_Water", 1}, {"MapleHerb_Water", 1 } }, EBREWING_DIFFICULTY::Easy, EBREWING_DIRECTION::StirRight, EBREWING_FIRE::Four, "HealingCandy", "ġ�� ����" });

	QuestData::CreateData("FindLetter", { "FindLetter" , "���� �б�", "���翡 �ִ� ������ �о��." });
}



void ContentsCore::InitMaterialResoruces()
{
	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src����
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("Blend_Light", Desc);

		std::shared_ptr<GameEngineMaterial> LightMaterial = GameEngineMaterial::Create("2DTexture_Light");
		LightMaterial->SetVertexShader("TextureShader_VS");
		LightMaterial->SetPixelShader("TextureShader_PS");
		LightMaterial->SetBlendState("Blend_Light");
	}

	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src����
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		GameEngineBlend::Create("Overlay", Desc);

		std::shared_ptr<GameEngineMaterial> OverRayMaterial = GameEngineMaterial::Create("Texture2D_Overlay");
		OverRayMaterial->SetVertexShader("TextureShader_VS");
		OverRayMaterial->SetPixelShader("TextureShader_PS");
		OverRayMaterial->SetBlendState("Overlay");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("SkyLightEffect2D");
		Mat->SetVertexShader("SkyLightEffect_VS");
		Mat->SetPixelShader("SkyLightEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("OutLineEffect2D");
		Mat->SetVertexShader("OutLineEffect_VS");
		Mat->SetPixelShader("OutLineEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("GaugeTexture2D");
		Mat->SetVertexShader("GaugeShader_VS");
		Mat->SetPixelShader("GaugeShader_PS");
	}
}

void ContentsCore::InitAutoCompile()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("Resources");
		Dir.MoveChild("GameEngineContentsShader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

		for (GameEngineFile& pFile : Files)
		{
			GameEngineShader::AutoCompile(pFile);
		}
	}
}