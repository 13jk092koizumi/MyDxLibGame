#ifndef INCLUDED_SEQUENCE_GAME_BATTLE_H
#define INCLUDED_SEQUENCE_GAME_BATTLE_H

#include "Child.h"
class Image;
class Window;
class Animation;

namespace BATTLE {
	class BattleMain;
}

namespace Sequence {
	namespace Game {

		class Parent;

		//�_���W����
		class Battle : public Child {
		public:
			Battle();
			~Battle();
			Child* update( Parent* );
		private:
			enum WinBattleName {
				WINNAME_B_MENU1, //���������E�X�L���E������
				WINNAME_B_MENU2, //�X�L���I��
				WINNAME_B_STATUS,
				WINNAME_B_MESSAGE,
				WINNAME_B_CHARA,
			};
			enum BattleState {
				Battle_Start, //�o�g���J�n
				Battle_CommandSelect, //�R�}���h�I��
				Battle_PlayerAct, //�v���C���[�̃R�}���h���s
				Battle_EnemyAct, //�G�̍U���A�N�V����
				Battle_Result, //���U���g��ʕ\��
				Battle_End, //�o�g���I��
				Battle_Gameover, //�Q�[���I�[�o�[
				Battle_None,
			};
			void drawState(); //��ʂ��\��
			void selectCommand(); //�R�}���h�I��
			void changeCursor( int cursorIndex, int listSize ); //�J�[�\���ʒu�����o�̕ύX
			int commandKind(); //���̃R�}���h��(���������E�X�L���E������)

			int mFramecount; //�t���[����(update()�̌Ă΂ꂽ��)
			int mCursorPosition[ 2 ]; //menu1��menu2�̃J�[�\���ʒu
			bool mNowKey[ 3 ]; //���݂̃L�[���
			bool mOldKey[ 3 ]; //�O�̃L�[���
			int mKeyCount; //�L�[��������Ă����瑝��
			bool ��IsSkillMenu; //�X�L�����j���[���J����Ă��邩

			Image* mImage;
			Window* mWindow;
			Animation* mAnimation;

			BATTLE::BattleMain* mBattleMain;
			BattleState mBattleState; //�o�g���̏��
			bool mCommandPhase; //�I���t�F�[�Y���ǂ���
			bool mActPhase; //���s�t�F�[�Y���ǂ���
			bool mDecideCommand; //�R�}���h�����肵�����ǂ���
		};


	} //namespace Game
} //namespace Sequence

#endif
