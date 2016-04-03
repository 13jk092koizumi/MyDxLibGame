#include "Battle/Player.h"
//TODO:�Z�[�u�f�[�^����L�����̃X�e�[�^�X��ǂݍ��߂�悤��

namespace BATTLE {

	Player::Player(int lv) :	mLive(true)	{
		//�Ƃ肠�������x��1�̃X�e�[�^�X�ŏ�����
		hpMax = 108;
		hp = hpMax;
		atk = 32;
		def = 5;
		spd = 4;
		level = lv;
		charaKind = PLAYER;
	}

	Player::~Player() {
		//TODO:���̂Ƃ��뉽�����Ȃ�
	}

	bool Player::isLive() {
		if ( mLive ) {
			return true; //�܂������Ă�
		}
		return false; //����ł�
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
		level > 50 ? 50 : level; //���x���L���b�v�𒴂��ĂȂ����`�F�b�N
		hpMax = 20 * level + 108;
		hp = hpMax;
		atk = 6 * level + 32;
		def = 2 * level + 5;
		spd = level + 4;
	}

} //namespace BATTLE
