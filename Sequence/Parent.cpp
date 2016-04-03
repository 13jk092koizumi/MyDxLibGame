#include "DxLib.h"
#include "Sequence/Parent.h"
//TODO:�V�[�P���X�t�@�C�����
#include "Sequence/Title.h"

namespace Sequence {
	Parent* Parent::mInstance = 0;

	void Parent::create() {
		mInstance = new Parent();
	}

	void Parent::destroy() {
		if ( mInstance == 0 ) {
			ErrorLogAdd("destroy()�Ɏ��s���܂����B");
			DxLib_End();
		}
		delete mInstance;
		mInstance = 0;
	}

	Parent* Parent::instance() {
		return mInstance;
	}

	Parent::Parent() :
		mChild( 0 ) {
		//�^�C�g����\��
		mChild = new Title();
	}

	Parent::~Parent() {
		if ( mChild != 0 ) {
			delete( mChild );
			mChild = 0;
		}
	}

	void Parent::update() {
		Child* nextChild = mChild->update( this );
		//�J�ڔ���
		if( nextChild != mChild ) {
			delete( mChild );
			mChild = 0;
			mChild = nextChild;
		}
		nextChild = 0;
	}

} //namespace Sequence
