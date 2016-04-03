#include "Battle/Player.h"
//TODO:セーブデータからキャラのステータスを読み込めるように

namespace BATTLE {

	Player::Player(int lv) :	mLive(true)	{
		//とりあえずレベル1のステータスで初期化
		hpMax = 108;
		hp = hpMax;
		atk = 32;
		def = 5;
		spd = 4;
		level = lv;
		charaKind = PLAYER;
	}

	Player::~Player() {
		//TODO:今のところ何もしない
	}

	bool Player::isLive() {
		if ( mLive ) {
			return true; //まだ生きてる
		}
		return false; //死んでた
	}

	int Player::getLevel() const {
		return level;
	}

	int Player::getHP() const {
		return hp;
	}

	int Player::getHPMax() const {
		return hpMax;
	}

	int Player::getAtk() const {
		return atk;
	}

	void Player::setStatus() {
		level > 50 ? 50 : level; //レベルキャップを超えてないかチェック
		hpMax = 20 * level + 108;
		hp = hpMax;
		atk = 6 * level + 32;
		def = 2 * level + 5;
		spd = level + 4;
	}

} //namespace BATTLE
