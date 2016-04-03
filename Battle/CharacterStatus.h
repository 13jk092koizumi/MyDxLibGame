#ifndef INCLUDED_BATTLE_CHARACTERSTATUS_H
#define INCLUDED_BATTLE_CHARACTERSTATUS_H

class CharacterStatus {
public:
	CharacterStatus() : hp(0),hpMax(0),atk(0),def(0),spd(0),charaKind(NONE_CHARA){}
	~CharacterStatus() {} //なにもしない
protected:
	enum EnemyKind {
		PLAYER, //プレーヤー
		ENEMY, //敵
		NONE_CHARA,
	};
	int hp; //HP
	int hpMax; //HP最大値
	int atk; //攻撃力
	int def; //防御力
	int spd; //素早さ
	int level; //レベル
	int exp; //経験値
	int nextExp; //レベルアップに必要な経験値
	EnemyKind charaKind; //敵かプレイヤーか
};

#endif
