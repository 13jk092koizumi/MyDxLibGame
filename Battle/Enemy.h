#ifndef INCLUDED_BATTLE_ENEMY_H
#define INCLUDED_BATTLE_ENEMY_H

namespace BATTLE {
	class Player;

	struct Status {
		int hp; //HP
		int hpMax; //HP�ő�l
		int atk; //�U����
		int def; //�h���
		int spd; //�f����
		int level; //���x��
	};

	class Enemy {
	public:
		Enemy();
		~Enemy() {}
		int calcHP( Player* player ); //�G��HP�v�Z�B�_���[�W�܂��͉񕜗ʂ�ԋp
		void kill(); //���S�t���O�����ĂĎE��
		bool isLive(); //�����Ă邩
		void setStatus( int lv );
		int getLevel() const; //�G�̃��x��
		Status getStatus() const; //�e��X�e�[�^�X
	private:
		int mLevel;
		bool mLiveFlag; //�����Ă邩�̃t���O
		Status mStatus;
	};

} //namespace BATTLE

#endif
