#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Common/Flame.h"
#include "../Input/Controller.h"
#include "../Object/Common/Capsule.h"
#include "../Object/Common/Collider.h"
#include "../Object/SkyDome.h"
#include "../Object/Stage.h"
#include "../Object/StagePiece.h"
#include "../Object/Player.h"
#include "GameScene.h"
#include "../Object/Common/Grid.h"
#include "../Object/SwingPoint.h"
#include "../Object/Character.h"

GameScene::GameScene(void)
	:SceneBase()
{
	player_ = nullptr;
}

void GameScene::Init(void)
{
	//SetUseASyncLoadFlag(TRUE);
	isLoaded = false;
	//�X�e�[�W
	stage_ = std::make_unique<Stage>();
	//�v���C���[
	player_ = std::make_unique < Player>();
	// �X�J�C�h�[��
	skyDome_ = std::make_unique<SkyDome>();
	// �O���b�h��
	grid_ = std::make_unique<Grid>();
	swi_ =std::make_unique<SwingPoint>();

	stage_->Init();
	swi_->Load();
	player_->Init();

	//�R�C��
	MakeCharacter();
	for (const auto& c : characters_)
	{
		c->Init();
	}
	isHitNum_ = 0;
	for (int i = 1; i <= 1; i++)
	{
		auto p = stage_->GetPiece();
		auto oo = p[static_cast<Stage::STAGE_NUM>(i - 1)];
		player_->AddCollider(oo->GetTransform()->collider);
	}
	skyDome_->Init();
	grid_->Init();
	//�J�����̐ݒ�
	lpSceneMng.GetCamera()->ChangeMode(Camera::MODE::FOLLOW);
	lpSceneMng.GetCamera()->SetTransform(player_->GetTransform());
	isLoaded_ = true;
}

void GameScene::Update(void)
{	
	auto& ins = InputManager::GetInstance();
	if(isHitNum_==characters_.size())
	{
		for (int cnt = 0; cnt < 100; cnt++)
		{
			continue;
		}
		lpSceneMng.ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}
	if(player_->IsAlive())
	{
		lpSceneMng.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
	auto swingPos = swi_->SetSwingPoint(player_->GetTransform()->pos);
	auto gravity= swi_->SetGravity(player_->GetTransform()->pos);
	player_->Update(lpSceneMng.GetDeltaTime(), lpSceneMng.GetCamera()->GetDir(), gravity, swingPos);
	skyDome_->Update();
	stage_->Update();
	// �L�����N�^�[
	for (const auto& c : characters_)
	{
		c->Update();
	}
	IsHitCharcterPlayer();
}

void GameScene::Draw(void)
{
	for (const auto& c : characters_)
	{
		c->Draw();
	}
	skyDome_->Draw();
	stage_->Draw();
	player_->Draw();
	swi_->Draw();
}

void GameScene::DrawDebug(void)
{
}

void GameScene::Release(void)
{	
}

void GameScene::Load(void)
{

	stage_->Init();
	player_->Init();
	skyDome_->Init();
	grid_->Init();
	lpSceneMng.GetCamera()->ChangeMode(Camera::MODE::FOLLOW);
	lpSceneMng.GetCamera()->SetTransform(player_->GetTransform());
	isLoaded_ = true;
}

void GameScene::MakeCharacter(void)
{
	Transform trans;
	//Character* character;
	trans.pos = { 10167, 648, 25656 };
	trans.scl = { 1.0f,1.0f, 1.0f };
	trans.quaRot = Quaternion::Euler(
		AsoUtility::Deg2RadF(-0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);
	characters_.emplace_back(std::make_unique< Character>(trans));

	trans.pos = { 12065, 4094, 20288 };
	trans.scl = { 1.0f,1.0f, 1.0f };
	trans.quaRot = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);
	characters_.emplace_back(std::make_unique< Character>(trans));
	for (auto& c :characters_)
	{
		c->Init();
	}
}

void GameScene::IsHitCharcterPlayer(void)
{

	// �R�C���ƃv���C���[�̏Փ˔���
	auto p = player_->GetTransform();

	for (const auto& c : characters_)
	{
		//�\������Ă���Ƃ�
		if (c->GetHit())
		{
			//�Փ˔���
			auto hit = MV1CollCheck_Sphere(p->modelId, -1, c->GetPos(), c->COL_RADIUS);
			MV1CollResultPolyDimTerminate(hit);

			//�ЂƂł��Փ˂��Ă�����
			if (hit.HitNum > 0)
			{
				c->Hit();
				isHitNum_++;
				break;
			}
		}
	}
}