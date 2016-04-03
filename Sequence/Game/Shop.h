#ifndef INCLUDED_SEQUENCE_GAME_SHOP_H
#define INCLUDED_SEQUENCE_GAME_SHOP_H

#include "Sequence/Game/Child.h"
class Image;

namespace Sequence {
	namespace Game {
		class Parent;

		class Shop : public Child {
		public:
			Shop();
			~Shop();
			Child* update( Parent* );
		private:
			Image* mImage;
		};

	} //namespace Game
} //namespace Sequence

#endif