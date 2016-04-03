#ifndef INCLUDED_SEQUENCE_GAME_BASETOWN_H
#define INCLUDED_SEQUENCE_GAME_BASETOWN_H

#include "Sequence/Game/Child.h"
class Image;
class Window;

namespace Sequence {
	namespace Game {
		class Parent;
		
		//���_�̊X�B��������Q�[�����X�^�[�g����B
		class BaseTown : public Child {
		public:
			BaseTown();
			~BaseTown();
			Child* update( Parent* );
			
		private:
			void drawState(); //��ʂ��\��
			void changeCursor();
			void MenuExplanation(); //���j���[�̐�����
			bool checkFirstLoop(); //�ŏ��̃��[�v���ǂ����𒲂ׂ�
			int mCursorPosition; //�J�[�\���ʒu
			bool mFirstFlag; //��ԍŏ��̃��[�v���ǂ���
			int mFrameCount; //1�t���[������1������
			bool mNowKey[ 2 ]; //���݃t���[���̃L�[
			bool mOldKey[ 2 ]; //1�t���[���O�̃L�[
			Image* mImage;	//�X�̉摜
			Window* mWindow; //�E�B���h�E
		};

	} //namespace Game
} //namespace Sequence

#endif