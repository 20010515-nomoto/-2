#include "CXPlayer.h"
#include "CKey.h"

//XVˆ—
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