#pragma once
#include "../Object/Common/Transform.h"
#include "SceneBase.h"
#include<map>

class SceneManager;
class Grid;
class SkyDome;
class AnimationController;

class TitleScene 
	: public SceneBase
{

public:
	TitleScene(void);
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	enum class IMG
	{
		TITLE,
		START,
		PUSH_BUTTON
		
	};

	int count_;

	//プレイヤーのアニメーション制御
	AnimationController* animationController_;	

	// タイトル画像
	int imgTitle_;

	//スタート画像
	int imgStart_;

	//Pushしてくれ画像
	int imgPush_;

	//グリッド線
	Transform transform_;	//プレイヤーのモデル制御

	// 背景
	std::unique_ptr<SkyDome> skyDome_;

	//
	std::map<IMG, int> images_;

};
