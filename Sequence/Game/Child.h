#ifndef INCLUDED_SEQUENCE_GAME_CHILD_H
#define INCLUDED_SEQUENCE_GAME_CHILD_H

namespace Sequence {
	namespace Game {
		class Parent;

		class Child{
		public:
			virtual ~Child() {} //何もしない
			virtual Child* update( Parent* ) = 0; //シーケンス遷移
		};



	} //namespace Sequence
} //namespace Game

#endif
