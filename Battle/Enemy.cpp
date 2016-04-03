#include "Battle/Player.h"
#include "Battle/Enemy.h"

namespace BATTLE {

	Enemy::Enemy( ) : mLevel(0), 	mLiveFlag(true) {
		//構造体を初期化
		mStatus.hp = 0;
		mStatus.hpMax = 0;
		mStatus.atk = 0;
		mStatus.def = 0;
		mStatus.spd = 0;
		mStatus.level = 0;
	}

	void Enemy::setStatus(int lv) {
		if ( lv > 0 ) {
			mLevel = lv;
		} else {
			mLevel = 1;
		}
		mStatus.hpMax = 32 + ( mLevel * 10 );
		mStatus.hp = mStatus.hpMax;
		mStatus.atk = 4 + ( mLevel * 6 );
		mStatus.def = 1 + ( mLevel * 2 );
		mStatus.spd = 1 + ( mLevel * 2 );
		mStatus.level = mLevel;
	}

	int Enemy::calcHP(Player* player) {
		int pAtk = player->getAtk();
		int damage = (player->getAtk()) - mStatus.def; //プレイヤーのatk取得
		damage = ( damage < 0 ) ? 1 : damage;
		int resultHP = 0; //計算結果を入れる
		resultHP = mStatus.hp - damage;
		resultHP = ( resultHP < 0 ) ? 0 : resultHP; //HPが0以下になっていないか
		resultHP = ( resultHP > mStatus.hpMax ) ? mStatus.hpMax : resultHP; //最大値を超えていないか
		mStatus.hp = resultHP; //敵HPを減らす
		return damage;
	}

	int Enemy::getLevel() const {
		return mLevel;
	}

	Status Enemy::getStatus() const {
		return mStatus;
	}

	bool Enemy::isLive() {
		if ( mStatus.hp <= 0 ) { //死んでたらfalseを返却
			mLiveFlag = false;
			return false;
		}
		return true;
	}

	void Enemy::kill() {
		mLiveFlag = false;
	}

} //namespace Battle