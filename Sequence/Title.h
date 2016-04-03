#ifndef INCLUDED_SEQUENCE_TITLE_H
#define INCLUDED_SEQUENCE_TITLE_H

#include "Sequence/Child.h"

class Image;
class Window;

namespace Sequence {
	class Parent;
	class Title : public Child {
	public:
		Title();
		~Title();
		Child* update( Parent* );
	private:
		enum StartMenu {
			SMENU_HAJIMEKARA, //�͂��߂���
			SMENU_TUDUKIKARA, //��������
		};
		void drawState(); //�e��`��
		void startMenu(); //�͂��߂��炩�Â������I��
		void changeCursor(); //�J�[�\������

		Image* mImage; //�^�C�g����ʉ摜
		Window* mWindow;
		int mCursorPosition; //�J�[�\���ʒu
		bool mMenuFlag; //���j���[��\�����Ă��邩�̃t���O
		bool mPushFlag; //�L�[�������ꂽ�Ƃ��̃t���O
		bool mGameStartFlag; //�Q�[���{�҂֑J�ڂ��邩�̃t���O
		bool mNowKey[2];
		bool mOldKey[2];
	};

} //namespace Sequence

#endif
