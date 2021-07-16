#include "CXPlayer.h"
#include "CKey.h"
#include "CCollisionManager.h"

CXPlayer::CXPlayer()
:mColSphereBody(this, nullptr, CVector(), 0.5f)
, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
	//タグ設定
	mTag = EPLAYER;
	mColSphereSword.mTag = CCollider::ESWORD;
}

void CXPlayer::Init(CModelX *model){
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	mColSphereHead.mpMatrix = &mpCombinedMatrix[11];
	mColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}

//更新処理
void CXPlayer::Update(){
	if (mAnimationIndex == 3 && mAnimationFrame >= mAnimationFrameSize){
		ChangeAnimation(4, false, 30);
	}
	else if (mAnimationIndex == 4 && mAnimationFrame >= mAnimationFrameSize){
		ChangeAnimation(0, true, 60);
	}
	else if (mAnimationIndex != 3 && mAnimationIndex != 4){
		if (CKey::Push('W')){
			ChangeAnimation(1, true, 60);
			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		}
		else{
			ChangeAnimation(0, true, 60);
		}
		if (CKey::Push('A')){
			mRotation.mY += 2;
		}
		if (CKey::Push('D')){
			mRotation.mY -= 2;
		}
		if (CKey::Once(' ')){
			ChangeAnimation(3, false, 30);
		}
	}
	CXCharacter::Update();
}