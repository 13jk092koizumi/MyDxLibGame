#ifndef INCLUDED_SEQUENCE_GAMEOVER_H
#define INCLUDED_SEQUENCE_GAMEOVER_H

#include "Child.h"
class Image;

namespace Sequence {
	class Parent;

	class GameOver : public Child {
	public:
		GameOver();
		~GameOver();
		Child* update( Parent* );
	private:
		Image* mImage;
	};

} //namespace Sequence

#endif