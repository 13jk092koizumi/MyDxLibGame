#include "DxLib.h"
#include <vector> //getEnemyStatus()で使う
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
		//敵生成
		mEnemyNum = GetRand( enemyMax ); //1~5の乱数
		if ( mEnemyNum <= 0 || mEnemyNum > 5 ) { //変な値になったら1にする
			mEnemyNum = 1;
		}
		mPlayer = new Player(3);
		mPlayer->setStatus();
		mEnemy = new Enemy[ mEnemyNum ];
		//敵の数を決める(１～５)
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

	//TODO:引数に選択した敵の番号を追加
	bool BattleMain::exeTurn(int flameCount, int command ,int targetNum) {
		//Global::moveScreen(flameCount, "コマンド実行中");
		switch ( command ) {
			case 1: //こうげき
				DrawString( 200, 200, "こうげき！", GetColor( 255, 0, 0 ) );
				if ( mIsCalcHP ) { //HPの計算中かどうか
						Status status = mEnemy[ targetNum ].getStatus();
						DrawFormatString( 300, 0, GetColor( 255, 255, 255 ), "NowPlayerHP:%d/%d", mPlayer->getHP(), mPlayer->getHPMax() );
						DrawFormatString( 230, 40, GetColor( 255, 255, 255 ), "敵に%dのダメージ！！EnemyHP:%d/%d", mEnemyDamage, status.hp, status.hpMax );
						break;
				}
				reduceEnemyHP(); //HP計算
				break;

			case 101:case 102:case 103:case 104:case 105: //スキル
				DrawFormatString( 200, 200, GetColor( 255, 255, 255 ), "スキル%d", command - 100 );
				break;

			case 200: //にげる
				DrawString( 200, 200, "にげる！", GetColor( 255, 255, 255 ) );
				break;
		}
		if ( isBattleEnd() ) { //バトル終了
			return true; //バトル終了でtrue返却
		}
		
		return false; //まだバトル中
	}

	vector<int> BattleMain::getEnemyStatus( ) {
		vector<Status> s; //敵ステータスの構造体を取得
		for ( int i = 0; i < mEnemyNum; ++i ) {
			s.push_back( mEnemy[ i ].getStatus() ); //i番目の敵のステータス構造体を取得
		}
		Status* data = s.data();
		vector<int> returndata;
		int j = 0;
		for ( auto itr = s.begin(); itr != s.end(); ++itr) {
			returndata.push_back( data[ j ].hp ); //j番目の敵HP取得
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
		int deathNum = 0; //敵が全部死んだか
		for ( int i = 0; i < mEnemyNum; ++i ) {
			if ( mEnemy[ i ].isLive() == false ) {
				++deathNum;
			}
			DrawFormatString( 0, 100, GetColor( 255, 0, 0 ), "deathNum:%d", deathNum );
		}
		//デバッグ
		DrawFormatString( 0, 120, GetColor( 255, 0, 0 ), "mEnemyNum:%d", mEnemyNum);
		DrawFormatString( 0, 140, GetColor( 255, 0, 0 ), "E0isLive():%d", mEnemy[0].isLive() );
		if ( deathNum > 0 ) {
			return true; //敵全滅。バトル終了
		}
		return false; //まだ終了しない
	}

	bool BattleMain::isGameOver() {
		//TODO:プレイヤーが死んでたらゲームオーバーにする
		return false;
	}

	void BattleMain::result() {
		DrawBox( 0, 0, Global::WindowWidth, Global::WindowHeight, GetColor( 255, 0, 0 ), true );
		DrawString( 200, 300, "リザルト画面", GetColor( 255, 255, 255 ) );
	}

	void BattleMain::reduceEnemyHP( int targetNum ) {
		/*1．プレーヤーの攻撃力参照
		　2．敵のHP参照
		 3．敵のHP－プレイヤーの攻撃力(ひとまず単純に)
		 (TODO:出力系は後でまとめる)
		 4．ダメージ量を画面に出力
		 5．HPの残量の出力
		 */

		mEnemyDamage = mEnemy[ 0 ].calcHP( mPlayer );

		mIsCalcHP = true; //計算が終了した
	}

} //namespace BATTLE