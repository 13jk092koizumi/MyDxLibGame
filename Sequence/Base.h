#ifndef INCLUDED_SEQUENCE_BASE_H
#define INCLUDED_SEQUENCE_BASE_H

namespace Sequence {
	
	class Base {
	public:
		virtual ~Base() {} //何もしない
		//TODO:共通の関数を書く
		virtual Base* update( Base* ) = 0; //描画関数
	};

} //namespace Sequence

#endif