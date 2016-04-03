#ifndef INCLUDED_BATTLE_BATTLEMAIN_H
#define INCLUDED_BATTLE_BATTLEMAIN_H

namespace BATTLE {
	
	class Player;
	class Enemy;
	
	//�o�g���S�̂̊Ǘ�
	class BattleMain {
	public:
		BattleMain();
		~BattleMain();

		bool doTurn( int flameCount, int command, int targetNum = 0 );
		vector<int> getEnemyStatus(); //�G�̃X�e�[�^�X�����擾
		int getEnemyNum() const; //�G�̐���ԋp
		void result(); //���U���g��ʕ\��
		void resetTurn(); //�^�[���̏��������Z�b�g
		bool isBattleEnd(); //�o�g�����I��������ǂ���
		bool isGameOver(); //�Q�[���I�[�o�[����
	private:
		void reduceEnemyHP(int targetNum = 0); //���������ɍ��킹�ēG��HP�����炷
		void counterSet(); //���݂̃J�E���^��ۑ�

		const int enemyMax = 5; //�G�̐��̍ő�l

		int mEnemyNum; //�P�`�T�̂̓G(����)
		//int mCount; //�J�E���^
		//int mStartCount; //�v���J�n���̃J�E���^
		int mEnemyDamage; //�G�ւ̃_���[�W��
		int mPlayerDamage; //�v���C���[�ւ̃_���[�W��
		
		bool mBattleWin; //���������ǂ���
		bool mPlayerLive; //�����Ă邩�ǂ���
		bool mIsCalcHP; //HP�̌v�Z���������ǂ���
		
		Player* mPlayer;
		Enemy* mEnemy;

	};


} //namespace Battle

#endif
