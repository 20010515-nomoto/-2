#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy :public CXCharacter{
public:
	CXEnemy();
	void Init(CModelX *model);
	CCollider mEnemyColSphereBody;	//‘Ì
	CCollider mEnemyColSphereHead;	//“ª
	CCollider mEnemyColSphereSword;	//Œ•
};

#endif