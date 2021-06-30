#include "CXCharacter.h"

/*
Init
����������
*/
void CXCharacter::Init(CModelX *model){
	mpModel = model;
	//�ŏ��̃A�j���[�V�����ɂ���
	mAnimationIndex = 0;
	//�J��Ԃ��Đ�����
	mAnimationLoopFlg = true;
	//1�A�j���[�V�����ڂ̍ő�t���[����
	mAnimationFrameSize =
		model->mAnimationSet[0]->mMaxTime;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->mAnimationSet[mAnimationIndex]->mTime =
		mAnimationFrame;
	//�A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
}
/*
ChangeAnimation
�A�j���[�V������؂�ւ���
index:�A�j���[�V�����̔ԍ�
loop:true �J��Ԃ�
framesize:�Ō�܂ōĐ�����̂Ɏg�p�����t���[����
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize){
	//�����ꍇ�͐؂芷���Ȃ�
	if (mAnimationIndex == index)return;
	//���̃A�j���[�V�����̏d�݂�0.0(0%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 0.0f;
	//�ԍ��A�J��Ԃ��A�t���[������ݒ�
	mAnimationIndex = index % mpModel->mAnimationSet.size();
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->mAnimationSet[mAnimationIndex]->mTime =
		mAnimationFrame;
	//�A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
}
/*
Update
�X�V����
matrix:�ړ��A��]�A�g��k���̍s��
*/
void CXCharacter::Update(CMatrix &matrix){
	//�Ō�܂ōĐ����Ă��Ȃ�
	if (mAnimationFrame < mAnimationFrameSize){
		//�A�j���[�V�����̎��Ԃ��v�Z
		mpModel->mAnimationSet[mAnimationIndex]->mTime =
			mpModel->mAnimationSet[mAnimationIndex]->mMaxTime *
			mAnimationFrame / mAnimationFrameSize;
		//�t���[����i�߂�
		mAnimationFrame++;
	}
	else{
		//�J��Ԃ��̏ꍇ�́A�t���[����0�ɖ߂�
		if (mAnimationLoopFlg){
			//�A�j���[�V�����̃t���[�����ŏ��ɂ���
			mAnimationFrame = 0.0f;
			mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationFrame;
		}
		else{
			mpModel->mAnimationSet[mAnimationIndex]->mTime =
				mpModel->mAnimationSet[mAnimationIndex]->mMaxTime;
		}
	}
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->mFrame[0]->AnimateCombined(&matrix);
	//���_�ɃA�j���[�V������K�p����
	mpModel->AnimateVertex();
}
/*
�`�悷��
*/
void CXCharacter::Render(){
	mpModel->Render();
}