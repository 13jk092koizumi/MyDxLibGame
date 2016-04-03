#include "DxLib.h"
#include "Sequence/Parent.h"
//TODO:シーケンスファイルを列挙
#include "Sequence/Title.h"

namespace Sequence {
	Parent* Parent::mInstance = 0;

	void Parent::create() {
		mInstance = new Parent();
	}

	void Parent::destroy() {
		if ( mInstance == 0 ) {
			ErrorLogAdd("destroy()に失敗しました。");
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
		//タイトルを表示
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
		//遷移判定
		if( nextChild != mChild ) {
			delete( mChild );
			mChild = 0;
			mChild = nextChild;
		}
		nextChild = 0;
	}

} //namespace Sequence
