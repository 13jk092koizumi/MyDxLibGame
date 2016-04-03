#ifndef INCLUDED_SEQUENCE_GAME_PARENT_H
#define INCLUDED_SEQUENCE_GAME_PARENT_H

#include "Sequence/Child.h"

namespace Sequence {
	class Parent;
	namespace Game {
		class Child;

		class Parent : public Sequence::Child {
		public:
			typedef Sequence::Parent GrandParent; //ãŠK‘w‚Ìe‚È‚Ì‚Å‘c•ƒ
			enum NextSequence{
				NEXT_ENDING,
				NEXT_GAME_OVER,
				NEXT_TITLE,

				NEXT_NONE,
			};

			Parent();
			~Parent();
			Sequence::Child* update( GrandParent* );
			void moveTo( NextSequence ); //ãŠK‘w‚ÉŸ‚ÌƒV[ƒPƒ“ƒX‚ğ“`‚¦‚é

		private:
			NextSequence mNextSequence;
			Game::Child* mChild;

		};


	} //namespace Game
} //namespace Sequence

#endif