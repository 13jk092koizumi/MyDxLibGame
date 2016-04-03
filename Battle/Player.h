#ifndef INICLUDED_BATTLE_PLAYER_H
#define INICLUDED_BATTLE_PLAYER_H

//基底クラス
#include "Battle/CharacterStatus.h"

namespace BATTLE {
	class Player : CharacterStatus {
	public:
		Player(int lv);
		~Player();
		bool isLive(); //生きてる?
		void setStatus(); //ステータスセット
		int getLevel() const; //プレイヤーのレベル
		int getHP() const; //現在のHP
		int getHPMax() const; //HP最大値
		int getAtk() const; //プレイヤーのatk
	private:
		bool mLive; //今生きているか
	};
		
} //namespace BATTLE

#endif
