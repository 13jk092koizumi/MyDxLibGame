#ifndef INCLUDED_BATTLE_BATTLEMAIN_H
#define INCLUDED_BATTLE_BATTLEMAIN_H

class Animation;
namespace BATTLE {
	
	class Player;
	class Enemy;
	struct Status; //��`��Enemy.h
	
	//�o�g����HP�v�Z��G�t�F�N�g�\���Ȃ�
	class BattleMain {
	public:
		BattleMain();
		~BattleMain();

		bool exeTurn( int flameCount, int command, int targetNum = 0 );
		vector<Status> getEnemyStatus(); //�G�̃X�e�[�^�X�����擾
		int getEnemyNum() const; //�G�̐���ԋp
		int getDamege(int activeChara) const; //1�v���C���[�̃_���[�W��2�G�̃_���[�W��ԋp
		void result(); //���U���g��ʕ\��
		void resetTurn(); //�^�[���̏��������Z�b�g
		bool isBattleEnd(); //�o�g�����I��������ǂ���
		bool isGameOver(); //�Q�[���I�[�o�[����
	private:
		void reduceEnemyHP(int targetNum = 0); //���������ɍ��킹�ēG��HP�����炷

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
		Animation* mAnimation;

	};


} //namespace Battle

#endif
