#ifndef INCLUDED_SEQUENCE_GAME_CHILD_H
#define INCLUDED_SEQUENCE_GAME_CHILD_H

namespace Sequence {
	namespace Game {
		class Parent;

		class Child{
		public:
			virtual ~Child() {} //�������Ȃ�
			virtual Child* update( Parent* ) = 0; //�V�[�P���X�J��
		};



	} //namespace Sequence
} //namespace Game

#endif
