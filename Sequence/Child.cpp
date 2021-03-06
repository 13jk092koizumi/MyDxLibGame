#include "DxLib.h"
#include "Sequence/Child.h"
#include "Sequence/Parent.h"

namespace Sequence {

	Child::~Child(){}

	//
	Base* Child::update( Base* p ) {
		Parent* parent = dynamic_cast< Parent* >( p );
		if ( parent == 0 ) {
			DxLib_End(); //あり得ないのでエラー
		}
		return update( parent );
	}

} //namespace Sequence