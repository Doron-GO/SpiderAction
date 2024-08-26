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

	//�v���C���[�̃A�j���[�V��������
	AnimationController* animationController_;	

	// �^�C�g���摜
	int imgTitle_;

	//�X�^�[�g�摜
	int imgStart_;

	//Push���Ă���摜
	int imgPush_;

	//�O���b�h��
	Transform transform_;	//�v���C���[�̃��f������

	// �w�i
	std::unique_ptr<SkyDome> skyDome_;

	//
	std::map<IMG, int> images_;

};