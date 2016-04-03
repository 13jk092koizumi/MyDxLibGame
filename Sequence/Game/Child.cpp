#include "DxLib.h"
#include "Sequence/Game/Child.h"
#include "Sequence/Game/Parent.h"

namespace Sequence {
	namespace Game {

		Child::~Child(){
			//‰½‚à‚µ‚È‚¢
		}

		Base* Child::update( Base* p ) {
			Parent* parent = dynamic_cast<Parent*>( p );
			if ( parent == 0 ) {
				DxLib_End(); //‚ ‚è“¾‚È‚¢‚Ì‚ÅƒGƒ‰[
			}
			return update( parent );
		}

	} //namespace Game
} //namespace Sequence