#include "DxLib.h"
#include "Sequence/Ending.h"
#include "Sequence/Parent.h"
#include "Sequence/Title.h"
#include "Image.h"

namespace Sequence {

	Ending::Ending() : mImage( 0 ) {
		mImage = new Image( "data/image/ending.dds" );
	}

	Ending::~Ending() {
		delete mImage; mImage = 0;
	}

	Child* Ending::update( Parent* ) {
		Child* next = this;
		if ( WaitTimer(2000) ) { //2•b‘Ò‚Â 
			next = new Title;
		}
		//•`‰æ
		mImage->setImgHandle();
		mImage->drawGraph( 0, 0 );
		
		return next;
	}

} //namespace Sequence