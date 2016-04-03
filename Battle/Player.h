#ifndef INICLUDED_BATTLE_PLAYER_H
#define INICLUDED_BATTLE_PLAYER_H

//���N���X
#include "Battle/CharacterStatus.h"

namespace BATTLE {
	class Player : CharacterStatus {
	public:
		Player(int lv);
		~Player();
		bool isLive(); //�����Ă�?
		void setStatus(); //�X�e�[�^�X�Z�b�g
		int getLevel() const; //�v���C���[�̃��x��
		int getHP() const; //���݂�HP
		int getHPMax() const; //HP�ő�l
		int getAtk() const; //�v���C���[��atk
	private:
		bool mLive; //�������Ă��邩
	};
		
} //namespace BATTLE

#endif
