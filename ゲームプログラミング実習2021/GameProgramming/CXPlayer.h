#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"
class CXPlayer :public CXCharacter{
public:
	//�X�V����
	void Update();
	void Init(CModelX *model);
	//�f�t�H���g�R���X�g���N�^
	CXPlayer();
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword;	//��

};


#endif