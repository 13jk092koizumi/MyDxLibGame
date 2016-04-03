#include "DxLib.h"
#include "Sequence/Parent.h"
#include "Sequence/Game/Parent.h"

#include "Sequence/Game/BaseTown.h"
#include "Sequence/Title.h"
#include "Sequence/GameOver.h"
#include "Sequence/Ending.h"

namespace Sequence {
	namespace Game {

		Parent::Parent() :
			mChild( 0 ),
			mNextSequence(NEXT_NONE){
			//最初は拠点の街からスタート
			mChild = new BaseTown();
		}

		Parent::~Parent() {
			if ( mChild != 0 ) {
				delete mChild;
				mChild = 0;
			}
		}

		Sequence::Child* Parent::update( GrandParent* ){
			Sequence::Child* next = this;
			Sequence::Game::Child* nextChild = mChild->update( this );
			//遷移判定
			if ( nextChild != mChild ) {
				delete( mChild ); mChild = 0; //mChildのdelete
				mChild = nextChild; //mChildとnextChildの値が違えば遷移が発生する。
			}
			nextChild = 0;

			switch ( mNextSequence ) {
				case NEXT_ENDING:
					next = new Ending;
					break;
				case NEXT_TITLE:
					next = new Title;
					break;
				case NEXT_GAME_OVER:
					next = new GameOver;
					break;
			}
			mNextSequence = NEXT_NONE;
			
			return next;
		}

		void Parent::moveTo( NextSequence next ) {
			if ( mNextSequence != NEXT_NONE ) {
				ErrorLogAdd( "error: moveTo failed. at Parent.cpp in line 51\n" );
				DxLib_End();
			}
			mNextSequence = next;
		}

	} //namespace Game
} //namespace Sequence