#include "DxLib.h"
#include "Sequence/Game/BaseTown.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Dungeon.h"
#include "Sequence/Game/Shop.h"
#include "Sequence/Title.h"
#include "Image.h"
#include "Window.h"
#include "GlobalValues.h"

namespace {
	char* list[] = {
		"�������",
		"�X�e�[�^�X",
		"�V���b�v",
		"�X�L������"
	};
	char* explainSelect[] = {
		"��������Ă������҂��܂��傤�B",
		"�X�e�[�^�X�̏ڍׂ�\�����܂��B",
		"�����⓹��𔄔��ł��܂��B",
		"�X�L�����S�[���h�ŋ����ł��܂��B"
	};
	//�F
	const unsigned int WHITE = GetColor( 255, 255, 255 );	//��
	//�t���[������p
	int nowCounter = 0;
	int oldCounter = 0;
	int TimeSensor = 0;
	int FrameTime = 0;
}

namespace Sequence {
	namespace Game {

		BaseTown::BaseTown() :
			mImage(0),
			mCursorPosition(-1),
			mFrameCount(0),
			mFirstFlag(false) {
			//�����o�z�񏉊���
			memset( mOldKey, 0, sizeof mOldKey );
			memset( mNowKey, 0, sizeof mNowKey );
			mImage = new Image[ 2 ]{ "data/image/town.png" ,"data/image/chara/007.png"};
			mWindow = new Window[4];
			//�w�i�摜�ǂݍ���
			mImage[ 0 ].setImgHandle();
			mImage[ 1 ].setImgHandle();
		}

		BaseTown::~BaseTown() {
			delete[] mImage;
			mImage = 0;
			delete[] mWindow;
			mWindow = 0;
		}

		Child* BaseTown::update(Parent* parent) {
			Child* next = this;
			//��ʕ`��
			drawState();
			
			if ( CheckHitKey( KEY_INPUT_SPACE ) ) {
				switch ( mCursorPosition ) {
					case 0:
						next = new Dungeon;
						break;
					case 1:
						//TODO:�X�e�[�^�X�\��
						break;
					case 2:
						next = new Shop;
						break;
					case 3:
						//TODO:�X�L������
						break;
					default:
						break; //�������Ȃ�
				}
			} else if ( CheckHitKey( KEY_INPUT_BACK ) ) {
				parent->moveTo( Parent::NEXT_TITLE );
			}
			return next;
		}

		void BaseTown::drawState() {
			//�ŏ��̃��[�v���ǂ���
			if ( checkFirstLoop() || mFrameCount<Global::WaitFrame ) {
				//���[�h��ʂ�\��
				Global::moveScreen( mFrameCount, "Now Loading" );
				++mFrameCount;
			} else {
				mImage[ 0 ].drawGraph( 0, 0 );
				//��ʂ��\��
				DrawString( 10, 25, "�x�[�X�^�E��", GetColor( 50, 50, 50 ) );
				mWindow[ 0 ].drawWindow( 10, 50, 200, 370, Window::WINDOW_LINE );

				//�J�[�\�����̓`�F�b�N
				changeCursor();

				//���j���[���X�g
				mWindow[ 0 ].drawListOnWindow( 4, mCursorPosition, list );

				//���j���[�̐�����
				MenuExplanation();

				//HP�Ȃ�
				//TODO:�L�����̃X�e�[�^�X�ƘA��������
				mWindow[ 1 ].drawWindow( 380, 350, 630, 470, Window::WINDOW_LINE );
				mWindow[ 1 ].drawHPBar( 415, 385, 100 );
				DrawFormatString( 385, 355, ::WHITE, "���x���@%d", 1 );
				DrawString( 385, 385, "HP", ::WHITE );
				DrawFormatString( 440, 386, ::WHITE, "%d  /  %d", 108, 108 );

				//�L�����摜
				mWindow[ 2 ].drawWindow( 330, 350, 378, 470, Window::WINDOW_LINE );
				mImage[ 1 ].drawGraph( 333, 355, true );

				//�����S�[���h�\��
				mWindow[ 3 ].drawWindow( 480, 5, 639, 30, Window::WINDOW_LINE );
				DrawFormatString( 480, 7, WHITE, "������ %d", 1000 );
				DrawString( 619, 7, "G", WHITE );
			}
		}

		void BaseTown::MenuExplanation() {
			int posY = mWindow[ 0 ].getHeight() / 4; //�E�B���h�E�T�C�Y��4(list[]�̗v�f��)�Ŋ���
			for ( int i = 0; i < 4; ++i ) {
				if ( i == mCursorPosition ) {
					SetDrawBlendMode( DX_BLENDMODE_ALPHA, 190 ); //�A���t�@�u�����h���[�h�ɃZ�b�g
					DrawBox( 210, ( posY * i ) + 60, 531, ( posY*i ) + 80, GetColor( 50, 50, 50 ), true );
					SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 255 );
					DrawString( 210, (posY * i)+60, ::explainSelect[ i ], ::WHITE );
				}
			}
		}

		void BaseTown::changeCursor() {
			//�J�[�\���ړ�
			//�܂���L�[�������ꂽ���ǂ���
			mNowKey[ 0 ] = Global::isKeyOn( KEY_INPUT_UP );
			if ( !mOldKey[ 0 ] && mNowKey[ 0 ] ) { //�O������ĂȂ��č�������Ă�����
				--mCursorPosition; //�J�[�\�������
				mCursorPosition = ( mCursorPosition < 0 ) ? 0 : mCursorPosition;
			}
			//���ɉ��L�[�������ꂽ���ǂ���
			mNowKey[ 1 ] = Global::isKeyOn( KEY_INPUT_DOWN );
			if ( !mOldKey[ 1 ] && mNowKey[ 1 ] ) {
				++mCursorPosition; //�J�[�\��������
				mCursorPosition = ( mCursorPosition > 3 ) ? 3 : mCursorPosition;

			}
			mOldKey[ 0 ] = mNowKey[ 0 ]; //���݂̏�Ԃ�ۑ�
			mOldKey[ 1 ] = mNowKey[ 1 ];
			
		}

		bool BaseTown::checkFirstLoop() {
			//����true��������ŏ�����Ȃ�
			if ( mFirstFlag ) {
				return false;
			}
			mFirstFlag = true;
			return true;
		}

	} //namespace Game
} //namespace Sequence
