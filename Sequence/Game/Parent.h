#ifndef INCLUDED_SEQUENCE_GAME_PARENT_H
#define INCLUDED_SEQUENCE_GAME_PARENT_H

#include "Sequence/Child.h"

namespace Sequence {
	class Parent;
	namespace Game {
		class Child;

		class Parent : public Sequence::Child {
		public:
			typedef Sequence::Parent GrandParent; //上階層の親なので祖父
			enum NextSequence{
				NEXT_ENDING,
				NEXT_GAME_OVER,
				NEXT_TITLE,

				NEXT_NONE,
			};

			Parent();
			~Parent();
			Sequence::Child* update( GrandParent* );
			void moveTo( NextSequence ); //上階層に次のシーケンスを伝える

		private:
			NextSequence mNextSequence;
			Game::Child* mChild;

		};


	} //namespace Game
} //namespace Sequence

#endif