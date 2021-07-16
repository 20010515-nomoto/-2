#include "CXEnemy.h"
#include "CCollisionManager.h"

CXEnemy::CXEnemy()
:mEnemyColSphereBody(this, nullptr, CVector(), 0.5f)
, mEnemyColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
, mEnemyColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{

}

void CXEnemy::Init(CModelX *model){
	CXCharacter::Init(model);
	//‡¬s—ñ‚ÌÝ’è
	mEnemyColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	mEnemyColSphereHead.mpMatrix = &mpCombinedMatrix[11];
	mEnemyColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}

void CXEnemy::Collision(CCollider *m, CCollider *o){
	if (m->mType == CCollider::ESPHERE){
		if (o->mType == CCollider::ESPHERE){
			if (o->mpParent->mTag == EPLAYER){
				if (o->mTag == CCollider::ESWORD){
					if (CCollider::Collision(m, o)){
						ChangeAnimation(11, false, 30);
					}
				}
			}
		}
	}
}