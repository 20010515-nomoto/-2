#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"

#include "CRes.h"

#include "CKey.h"
#include "CMaterial.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CCollisionManager.h"

CMatrix Matrix;
//�L�����N�^�̃C���X�^���X
CXPlayer mPlayer;
//�G�̃C���X�^���X
CXEnemy mEnemy;

CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);

	CRes::sModelX.Load(MODEL_FILE);
	//�L�����N�^�[�Ƀ��f����ݒ�
	mPlayer.Init(&CRes::sModelX);
	//�G�̏����ݒ�
	mEnemy.Init(&CRes::sModelX);
	//�G�̈ʒu
	mEnemy.mPosition = CVector(7.0f, 0.0f, 0.0f);
}


void CSceneGame::Update() {
	//�L�����N�^�[�N���X�̍X�V
	mPlayer.Update();
	//�G�̍X�V
	mEnemy.Update();

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	//X��+��]
	if (CKey::Push('K')){
		Matrix = Matrix*CMatrix().RotateX(1);
	}
	//Y��+��]
	if (CKey::Push('L')){
		Matrix = Matrix*CMatrix().RotateY(1);
	}
	//X��-��]
	if (CKey::Push('I')){
		Matrix = Matrix*CMatrix().RotateX(-1);
	}
	//Y��-��]
	if (CKey::Push('J')){
		Matrix = Matrix*CMatrix().RotateY(-1);
	}
	//�s��ݒ�
	glMultMatrixf(Matrix.mF);
	//���_�ɃA�j���[�V������K�p����
	//CRes::sModelX.AnimateVertex();
	//���f���`��
	//CRes::sModelX.Render();
	mPlayer.Render();
	mEnemy.Render();

	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
	////�e�N�X�`���e�X�g
	//CRes::sModelX.mMaterial[0]->mTexture.DrawImage(
	//	-5, 5, -5, 5, 0, 128, 128, 0);


	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();

	return;
}

