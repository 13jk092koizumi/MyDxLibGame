#ifndef INCLUDED_BATTLE_ENEMY_H
#define INCLUDED_BATTLE_ENEMY_H

namespace BATTLE {
	class Player;

	struct Status {
		int hp; //HP
		int hpMax; //HP最大値
		int atk; //攻撃力
		int def; //防御力
		int spd; //素早さ
		int level; //レベル
	};

	class Enemy {
	public:
		Enemy();
		~Enemy() {}
		int calcHP( Player* player ); //敵のHP計算。ダメージまたは回復量を返却
		void kill(); //死亡フラグをたてて殺す
		bool isLive(); //生きてるか
		void setStatus( int lv );
		int getLevel() const; //敵のレベル
		Status getStatus() const; //各種ステータス
	private:
		int mLevel;
		bool mLiveFlag; //生きてるかのフラグ
		Status mStatus;
	};

} //namespace BATTLE

#endif
