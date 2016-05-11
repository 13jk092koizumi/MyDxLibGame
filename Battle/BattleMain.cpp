#include "DxLib.h"
#include <vector> //getEnemyStatus()�Ŏg��
using namespace std;

#include "Battle/BattleMain.h"
#include "Battle/Player.h"
#include "Battle/Enemy.h"
#include "Animation.h"
#include "GlobalValues.h"

namespace BATTLE {

	BattleMain::BattleMain() :
		mEnemyNum(0),
		//mCount(0),
		//mStartCount(0),
		mEnemyDamage(0),
		mPlayerDamage(0),
		mBattleWin(false),
		mPlayerLive(true),
		mIsCalcHP(false),
		mPlayer(0),
		mEnemy(0),
		mAnimation(0) {
		//�G����
		mEnemyNum = GetRand( enemyMax ); //1~5�̗���
		if ( mEnemyNum <= 0 || mEnemyNum > 5 ) { //�ςȒl�ɂȂ�����1�ɂ���
			mEnemyNum = 1;
		}
		mPlayer = new Player(3);
		mPlayer->setStatus();
		mEnemy = new Enemy[ mEnemyNum ];
		//�G�̐������߂�(�P�`�T)
		for ( int i = 0; i < mEnemyNum; ++i ) {
			int rand = GetRand( 4 ) + 1;
			mEnemy[ i ].setStatus( mPlayer->getLevel() + rand );
		}
		mAnimation = new Animation( 30, 3 );
	}

	BattleMain::~BattleMain() {
		delete mPlayer; mPlayer = 0;
		delete[] mEnemy; mEnemy = 0;
	}

	//TODO:�����ɑI�������G�̔ԍ���ǉ�
	bool BattleMain::exeTurn(int flameCount, int command ,int targetNum) {
		//Global::moveScreen(flameCount, "�R�}���h���s��");
		switch ( command ) {
			case 1: //��������
				DrawString( 200, 200, "���������I", GetColor( 255, 0, 0 ) );
				if ( mIsCalcHP ) { //HP�̌v�Z�����ǂ���
						Status status = mEnemy[ targetNum ].getStatus();
						DrawFormatString( 300, 0, GetColor( 255, 255, 255 ), "NowPlayerHP:%d/%d", mPlayer->getHP(), mPlayer->getHPMax() );
						DrawFormatString( 230, 40, GetColor( 255, 255, 255 ), "�G��%d�̃_���[�W�I�IEnemyHP:%d/%d", mEnemyDamage, status.hp, status.hpMax );
						break;
				}
				reduceEnemyHP(); //HP�v�Z
				break;

			case 101:case 102:case 103:case 104:case 105: //�X�L��
				DrawFormatString( 200, 200, GetColor( 255, 255, 255 ), "�X�L��%d", command - 100 );
				break;

			case 200: //�ɂ���
				DrawString( 200, 200, "�ɂ���I", GetColor( 255, 255, 255 ) );
				break;
		}
		if ( isBattleEnd() ) { //�o�g���I��
			return true; //�o�g���I����true�ԋp
		}
		
		return false; //�܂��o�g����
	}

	vector<int> BattleMain::getEnemyStatus( ) {
		vector<Status> s; //�G�X�e�[�^�X�̍\���̂��擾
		for ( int i = 0; i < mEnemyNum; ++i ) {
			s.push_back( mEnemy[ i ].getStatus() ); //i�Ԗڂ̓G�̃X�e�[�^�X�\���̂��擾
		}
		Status* data = s.data();
		vector<int> returndata;
		int j = 0;
		for ( auto itr = s.begin(); itr != s.end(); ++itr) {
			returndata.push_back( data[ j ].hp ); //j�Ԗڂ̓GHP�擾
			++j;
		}
		return returndata;
	}

	int BattleMain::getEnemyNum() const {
		return mEnemyNum;
	}

	void BattleMain::resetTurn() {
		mIsCalcHP = false;
	}

	bool BattleMain::isBattleEnd() {
		int deathNum = 0; //�G���S�����񂾂�
		for ( int i = 0; i < mEnemyNum; ++i ) {
			if ( mEnemy[ i ].isLive() == false ) {
				++deathNum;
			}
			DrawFormatString( 0, 100, GetColor( 255, 0, 0 ), "deathNum:%d", deathNum );
		}
		//�f�o�b�O
		DrawFormatString( 0, 120, GetColor( 255, 0, 0 ), "mEnemyNum:%d", mEnemyNum);
		DrawFormatString( 0, 140, GetColor( 255, 0, 0 ), "E0isLive():%d", mEnemy[0].isLive() );
		if ( deathNum > 0 ) {
			return true; //�G�S�ŁB�o�g���I��
		}
		return false; //�܂��I�����Ȃ�
	}

	bool BattleMain::isGameOver() {
		//TODO:�v���C���[������ł���Q�[���I�[�o�[�ɂ���
		return false;
	}

	void BattleMain::result() {
		DrawBox( 0, 0, Global::WindowWidth, Global::WindowHeight, GetColor( 255, 0, 0 ), true );
		DrawString( 200, 300, "���U���g���", GetColor( 255, 255, 255 ) );
	}

	void BattleMain::reduceEnemyHP( int targetNum ) {
		/*1�D�v���[���[�̍U���͎Q��
		�@2�D�G��HP�Q��
		 3�D�G��HP�|�v���C���[�̍U����(�ЂƂ܂��P����)
		 (TODO:�o�͌n�͌�ł܂Ƃ߂�)
		 4�D�_���[�W�ʂ���ʂɏo��
		 5�DHP�̎c�ʂ̏o��
		 */

		mEnemyDamage = mEnemy[ 0 ].calcHP( mPlayer );

		mIsCalcHP = true; //�v�Z���I������
	}

} //namespace BATTLE