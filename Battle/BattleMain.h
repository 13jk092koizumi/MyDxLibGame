#ifndef INCLUDED_BATTLE_BATTLEMAIN_H
#define INCLUDED_BATTLE_BATTLEMAIN_H

namespace BATTLE {
	
	class Player;
	class Enemy;
	
	//バトル全体の管理
	class BattleMain {
	public:
		BattleMain();
		~BattleMain();

		bool doTurn( int flameCount, int command, int targetNum = 0 );
		vector<int> getEnemyStatus(); //敵のステータス情報を取得
		int getEnemyNum() const; //敵の数を返却
		void result(); //リザルト画面表示
		void resetTurn(); //ターンの処理をリセット
		bool isBattleEnd(); //バトルが終わったかどうか
		bool isGameOver(); //ゲームオーバー判定
	private:
		void reduceEnemyHP(int targetNum = 0); //こうげきに合わせて敵のHPを減らす
		void counterSet(); //現在のカウンタを保存

		const int enemyMax = 5; //敵の数の最大値

		int mEnemyNum; //１～５体の敵(乱数)
		//int mCount; //カウンタ
		//int mStartCount; //計測開始時のカウンタ
		int mEnemyDamage; //敵へのダメージ量
		int mPlayerDamage; //プレイヤーへのダメージ量
		
		bool mBattleWin; //勝ったかどうか
		bool mPlayerLive; //生きてるかどうか
		bool mIsCalcHP; //HPの計算をしたかどうか
		
		Player* mPlayer;
		Enemy* mEnemy;

	};


} //namespace Battle

#endif
