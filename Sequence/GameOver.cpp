#include "DxLib.h"
#include "GameOver.h"
#include "Sequence/Parent.h"
#include "Title.h"
#include "Image.h"

namespace Sequence {

	GameOver::GameOver() : mImage(0) {
		mImage = new Image( "data/image/gameover.png" );
	}

	GameOver::~GameOver() {
		if ( mImage != 0 ) {
			delete mImage;
			mImage = 0;
		}
	}

	Child* GameOver::update(Parent* parent) {
		Child* next = this;
		
		mImage->setImgHandle();
		mImage->drawGraph( 0, 0 );
		DrawFormatString(0,0,GetColor(255,255,255), "now is GameOver." );
		ScreenFlip();
		WaitTimer( 2000 );
		next = new Title();
		
		return next;
	}

} //namespace Sequence