#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"
class CXPlayer :public CXCharacter{
public:
	//更新処理
	void Update();
	void Init(CModelX *model);
	//デフォルトコンストラクタ
	CXPlayer();
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	CCollider mColSphereSword;	//剣

};


#endif