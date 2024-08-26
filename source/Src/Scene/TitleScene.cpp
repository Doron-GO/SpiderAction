#include <string>
#include <DxLib.h>
#include "../Object/Common/AnimationController.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Input/InputManager.h"
#include "../Object/Common/Grid.h"
#include "../Input/Controller.h"
#include "../Object/SkyDome.h"
#include "../Manager/Camera.h"
#include "../Common/Flame.h"
#include "../Application.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
	:SceneBase()
{
	imgPush_ = -1;
	imgTitle_ = -1;
	skyDome_ = nullptr;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{

	ResourceManager& rm = lpResourceMng;

	// 画像読み込み
	images_.emplace(IMG::START,rm.Load(ResourceManager::SRC::START).handleId_) ;
	images_.emplace(IMG::TITLE,rm.Load(ResourceManager::SRC::TITLE).handleId_) ;

	transform_.SetModel(
		lpResourceMng.LoadModelDuplicate(ResourceManager::SRC::STAGE));
		transform_.scl = { 0.5f,0.5f ,0.5f };
	transform_.pos = { 0.0f, 0.0f, 0.0f };
	transform_.localPos = { -3000.0f, -1300.0f, 0.0f };
	transform_.pos = VAdd(transform_.pos, transform_.localPos);

	transform_.quaRot = Quaternion();
	transform_.quaRotLocal =
		Quaternion::Euler({ 0.0f, 0.0f, 0.0f });
	transform_.Update();
	std::string path = Application::PATH_MODEL + "Player/";

	// 定点カメラ
 	SceneManager::GetInstance().GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

	count_ = 0;
}

void TitleScene::Update(void)
{

	count_++;
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
	MV1DrawModel(transform_.modelId);
	//タイトル画像
	DrawRotaGraph(static_cast<int>(Application::SCREEN_SIZE_X / 2.0f), 250, 0.35, 0.0, images_[IMG::TITLE], true, 5.0);
	DrawRotaGraph(static_cast<int>(Application::SCREEN_SIZE_X / 2.0f), 550, 0.35, 0.0, images_[IMG::START], true,5.0);
}

