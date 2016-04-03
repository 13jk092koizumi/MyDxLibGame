#ifndef INCLUDED_SEQUENCE_GAME_DUNGEON_H
#define INCLUDED_SEQUENCE_GAME_DUNGEON_H

#include "Child.h"
class Image;
class Window;

namespace Sequence {
	namespace Game {
		class Parent;

		//�_���W����
		class Dungeon : public Child{
		public:
			Dungeon();
			~Dungeon();
			Child* update(Parent*);
		private:
			void drawState(); //��ʂ��\��
			bool checkFirstLoop(); //���߂Ẵ��[�v���ǂ������ׂ�
			void changeCursor(); //�J�[�\�����L�[�ɂ���ĕϓ�

			enum WinName_Dungeon{
				WINNAME_FLOOR, //���̊K�w
				WINNAME_PROGRESS, //�T���x
				WINNAME_SELECTMENU, //�Z���N�g���j���[
				WINNAME_CHARA, //�L����
				WINNAME_STATUS, //HP��o���l�Ȃ�
				WINNAME_BOSSDOOR, //�{�X�����̃h�A
			};
			Image* mImage;
			Window* mWindow;
			int mCursorPosition; //�J�[�\���ʒu
			int mFrameCount; //�t���[���J�E���^
			bool mFirstFlag; //���߂Ẵ��[�v���ǂ���
			//�L�[�̉�����Ԕz��B�Y����0��UP,1��DOWN�L�[
			bool mNowKey[2]; //���݃t���[���̃L�[
			bool mOldKey[2]; //�O�̃t���[���̃L�[

		};

	} //namespace Game
} //namespace Sequence

#endif
