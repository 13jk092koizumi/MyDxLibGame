#ifndef INCLUDED_BATTLE_CHARACTERSTATUS_H
#define INCLUDED_BATTLE_CHARACTERSTATUS_H

class CharacterStatus {
public:
	CharacterStatus() : hp(0),hpMax(0),atk(0),def(0),spd(0),charaKind(NONE_CHARA){}
	~CharacterStatus() {} //�Ȃɂ����Ȃ�
protected:
	enum EnemyKind {
		PLAYER, //�v���[���[
		ENEMY, //�G
		NONE_CHARA,
	};
	int hp; //HP
	int hpMax; //HP�ő�l
	int atk; //�U����
	int def; //�h���
	int spd; //�f����
	int level; //���x��
	int exp; //�o���l
	int nextExp; //���x���A�b�v�ɕK�v�Ȍo���l
	EnemyKind charaKind; //�G���v���C���[��
};

#endif
