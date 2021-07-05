#include "CXPlayer.h"
#include "CKey.h"

//XVˆ—
void CXPlayer::Update(){
	if (CKey::Push('W')){
		ChangeAnimation(1, true, 60);
		mPosition += CVector(0.0f, 0.0f, 0.1f);
	}
	else{
		ChangeAnimation(0, true, 60);
	}
	CXCharacter::Update();
}