#ifndef INCLUDED_ANIMATION_H
#define INCLUDED_ANIMATION_H

//�w��J�E���^���̊ԃA�j���[�V�����̗L�����������N���X
/*�g����
�E�R���X�g���N�^�ɃA�j���[�V����������t���[�����ƃR�}(����)��
�Eanimate()�ŃA�j���[�V�������L�����̔���ƃR�}����̃^�C�~���O�̎�true�ԋp
�Estart()�̓J�E���^��1�ɂ��ăA�j���[�V������L���ɂ���
�Ereset()�͊e�ϐ���������Ԃɖ߂�
*/

class Animation {
public:
	Animation( int flameNum, int divideNum ); //�t���[�����ƃR�}��
	~Animation();
	bool animate(); //�A�j���̃R�}���ɉ�����true��Ԃ�
	bool getmIsAnimating();
	int getNowDivNum();
	void start(); //����J�n
	void reset(); //�ϐ��̃��Z�b�g
private:
	unsigned int mCount; //�J�E���^
	unsigned int mEndCount; //�I������^�C�~���O
	int mNowDivNum; //���������ڂ�(�O�`divideNum)
	int mValidTiming; //�A�j���[�V�������ԁ�������(���R�}��)
	bool mIsAnimating; //�A�j���\�V���������ۂ�
};

#endif