#ifndef CMODELX_H
#define CMODELX_H		

#include <vector>		//vector�N���X�̃C���N���[�h(���I�z��)
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"
#include "CMyShader.h"
class CModelX;		//CModelX�N���X�̐錾
class CSkinWeights;
class CMaterial;	//�N���X�̐錾
class CAnimationSet;
class CAnimation;
class CAnimationKey;

#define MODEL_FILE "���O�i.x"	//���̓t�@�C����

//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=0;}

//CMesh�N���X�̒�`
class CMesh{
public:
	int mVertexNum;	//���_��
	CVector *mpVertex;	//���_�f�[�^
	int mFaceNum;	//�ʐ�
	int *mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�
	int mNormalNum;		//�@����
	CVector *mpNormal;	//�@���f�[�^
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;	//�}�e���A���ԍ���(�ʐ�)
	int *mpMaterialIndex;	//�}�e���A���ԍ�
	//�e�N�X�`�����W�f�[�^
	float *mpTextureCoords;

	std::vector<CMaterial*>mMaterial;	//�}�e���A���f�[�^
	std::vector<CSkinWeights*>mSkinWeights;	//�X�L���E�F�C�g

	//�}�e���A�����̖ʐ�
	std::vector<int>mMaterialVertexCount;
	//���_�o�b�t�@���ʎq
	GLuint mMyVertexBufferId;
	//���_�o�b�t�@�쐬
	void CreateVertexBuffer();

	CVector *mpAnimateVertex;	//�A�j���[�V�����p���_
	CVector *mpAnimateNormal;	//�A�j���[�V�����p�@��

	//�R���X�g���N�^
	CMesh()
		:mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		, mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)
		, mpAnimateVertex(nullptr)
		, mpAnimateNormal(nullptr)
		, mpTextureCoords(nullptr)
		, mMyVertexBufferId(0)
	{}
	//�f�X�g���N�^
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
		//�X�L���E�F�C�g�̍폜
		for (int i = 0; i < mSkinWeights.size(); i++){
			delete mSkinWeights[i];
		}
	}
	//�ǂݍ��ݏ���
	void Init(CModelX *model);
	void Render();

	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX *model);

	void AnimateVertex(CMatrix*);
};

//CModelXFrame�N���X�̒�`
class CModelXFrame{
public:
	std::vector<CModelXFrame*>mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;	//�ϊ��s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�
	CMesh mMesh;	//Mesh�f�[�^
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	CModelXFrame()
		:mpName(nullptr)
		, mIndex(0){}	//�R���X�g���N�^
	//�f�X�g���N�^
	~CModelXFrame(){
		//�q�t���[�������ׂĉ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete *itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
	}
	void Render();
	CMatrix mCombinedMatrix;	//�����s��
	//�����s��̍쐬
	void AnimateCombined(CMatrix* parent);
};


/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX
{
public:
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
	std::vector<CModelXFrame*>mFrame;	//�t���[���̔z��
	std::vector<CAnimationSet*>mAnimationSet;	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CMaterial*>mMaterial;	//�}�e���A���̔z��

	CModelX()
		:mpPointer(nullptr)
		, mpSkinningMatrix(nullptr)
	{}

	~CModelX(){
		if (mFrame.size() > 0){
			delete mFrame[0];
		}
		for (int i = 0; i < mAnimationSet.size(); i++){
			delete mAnimationSet[i];
		}
		for (int i = 0; i < mMaterial.size(); i++){
			delete mMaterial[i];
		}
		SAFE_DELETE_ARRAY(mpSkinningMatrix);
	}
	//�t�@�C���̓ǂݍ���
	void Load(char* file);
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//���������_�̃f�[�^�̎擾
	float GetFloatToken();
	//�����f�[�^�̎擾
	int GetIntToken();
	void Render();
	//�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	CModelXFrame* FindFrame(char* name);
	void AnimateFrame();
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	//���_�ɃA�j���[�V������K�p
	void AnimateVertex();
	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);

	void AnimateVertex(CMatrix*);
	/*
	�A�j���[�V�����𔲂��o��
	idx:�����������A�j���[�V�����Z�b�g�̔ԍ�
	start:�����������A�j���[�V�����̊J�n����
	end:�����������A�j���[�V�����̏I������
	name:�ǉ�����A�j���[�V�����Z�b�g�̖��O
	*/
	void SeparateAnimationSet(int idx, int start, int end, char* name);

	//�V�F�[�_�[�p�X�L���}�g���b�N�X
	CMatrix *mpSkinningMatrix;
	CMyShader mShader;	//�V�F�[�_�[�̃C���X�^���X

	//�V�F�[�_�[���g�����`��
	void RenderShader(CMatrix *m);
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights{
public:
	char *mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mIndexNum;		//���_�ԍ���
	int *mpIndex;		//���_�ԍ��z��
	float *mpWeight;	//���_�E�F�C�g�z��
	CMatrix mOffset;	//�I�t�Z�b�g�}�g���b�N�X

	CSkinWeights(CModelX *model);

	~CSkinWeights(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};
/*
CAnimationSet
�A�W���[�V�����Z�b�g
*/
class CAnimationSet{
public:
	float mTime;		//���ݎ���
	float mWeight;		//�d��
	float mMaxTime;		//�ő厞��
	//�A�j���[�V�����Z�b�g��
	char *mpName;
	//�A�j���[�V����
	std::vector<CAnimation*>mAnimation;
	CAnimationSet(CModelX *model);
	CAnimationSet(){}
	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (int i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}
};
/*
CAnimation
�A�j���[�V�����N���X
*/
class CAnimation{
public:
	char *mpFrameName;		//�t���[����
	int mFrameIndex;		//�t���[���ԍ�

	int mKeyNum;	//�L�[��(���Ԑ�)
	CAnimationKey *mpKey;	//�L�[�̔z��

	CAnimation(CModelX *model);
	CAnimation(){}

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};
/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey{
public:
	//����
	float mTime;
	//�s��
	CMatrix mMatrix;
};


#endif