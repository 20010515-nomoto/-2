#include "CXEnemy.h"

CXEnemy::CXEnemy()
:mEnemyColSphereBody(this, nullptr, CVector(), 0.5f)
, mEnemyColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
, mEnemyColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{

}

void CXEnemy::Init(CModelX *model){
	CXCharacter::Init(model);
	//çáê¨çsóÒÇÃê›íË
	mEnemyColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	mEnemyColSphereHead.mpMatrix = &mpCombinedMatrix[11];
	mEnemyColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}