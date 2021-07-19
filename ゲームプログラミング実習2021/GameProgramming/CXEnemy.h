#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy :public CXCharacter{
public:
	CXEnemy();
	void Init(CModelX *model);
	CCollider mEnemyColSphereBody;	//��
	CCollider mEnemyColSphereHead;	//��
	CCollider mEnemyColSphereSword0;	//��
	CCollider mEnemyColSphereSword1;	//��
	CCollider mEnemyColSphereSword2;	//��

	//�Փˏ���
	void Collision(CCollider *m, CCollider *o);

};

#endif