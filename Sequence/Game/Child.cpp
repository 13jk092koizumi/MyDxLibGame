#include "DxLib.h"
#include "Sequence/Game/Child.h"
#include "Sequence/Game/Parent.h"

namespace Sequence {
	namespace Game {

		Child::~Child(){
			//何もしない
		}

		Base* Child::update( Base* p ) {
			Parent* parent = dynamic_cast<Parent*>( p );
			if ( parent == 0 ) {
				DxLib_End(); //あり得ないのでエラー
			}
			return update( parent );
		}

	} //namespace Game
} //namespace Sequence