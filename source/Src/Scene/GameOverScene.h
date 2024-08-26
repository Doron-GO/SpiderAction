#pragma once
#include "SceneBase.h"
#include<map>

class GameOverScene :
    public SceneBase
{
public:
	GameOverScene(void);
	~GameOverScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	enum class IMG
	{
		CLEAR,
		CONGRATULATIONS,
		PUSH_BUTTON
	};

	std::map<IMG,int> images_;

	//ボタンの判定開始までの時間
	float waitCount_;

};

