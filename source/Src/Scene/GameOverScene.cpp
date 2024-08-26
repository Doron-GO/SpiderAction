#include "../Manager/ResourceManager.h"
#include"../Input/InputManager.h"
#include"../Manager/SceneManager.h"
#include "GameOverScene.h"
#include<DxLib.h>

#pragma region íËêî

const int CLEAR_POS_X = 0;
const int CLEAR_POS_Y = 0;

const int CONGRATULATIONS_POS_X = 150;
const int CONGRATULATIONS_POS_Y = 0;

const int PUSH_BUTTON_POS_X = 512;
const int PUSH_BUTTON_POS_Y = 500;

const float COUNT = 300.0f;
#pragma endregion


GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Init(void)
{	
	ResourceManager& rm = lpResourceMng;
	images_.emplace(IMG::CLEAR, rm.Load(ResourceManager::SRC::CLEAR).handleId_);
	images_.emplace(IMG::CONGRATULATIONS, rm.Load(ResourceManager::SRC::CONGRATULATIONS).handleId_);
	images_.emplace(IMG::PUSH_BUTTON, rm.Load(ResourceManager::SRC::START).handleId_);
}

void GameOverScene::Update(void)
{
	if (waitCount_++< COUNT)
	{
		return;
	}
	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

}

void GameOverScene::Draw(void)
{

	DrawGraph(CLEAR_POS_X, CLEAR_POS_Y, images_[IMG::CLEAR], true);
	DrawGraph(CONGRATULATIONS_POS_X, CONGRATULATIONS_POS_Y, images_[IMG::CONGRATULATIONS], true);
	DrawRotaGraph(PUSH_BUTTON_POS_X, PUSH_BUTTON_POS_Y, 1.0, 0.0, images_[IMG::PUSH_BUTTON], true);

}
