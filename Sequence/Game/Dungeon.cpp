#include "DxLib.h"
#include "Sequence/Game/Dungeon.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/BaseTown.h"
#include "Sequence/Game/Battle.h"
#include "Image.h"
#include "Window.h"
#include "GlobalValues.h"

namespace {

	char* list[] = {
		"��֐i��",
		"�X�֖߂�",
		"�{�X�ɒ��킷��!"
	};
	const unsigned int WHITE = GetColor( 255, 255, 255 ); //��
	const int menuHeight= Global::WindowHeight / 3; //�Z���N�g���j���[�̂�
	const int menuWidth = Global::WindowWidth / 3; //�Z���N�g���j���[�̂�
	int TimeSensor = 0;
} //namespace

namespace Sequence {
	namespace Game {

		Dungeon::Dungeon() :
			mImage( 0 ),
			mWindow(0),
			mFrameCount(0),
			mFirstFlag(false),
			mCursorPosition(-1) {
			//�����o�z��̏�����
			memset( mNowKey, 0, sizeof mNowKey );
			memset( mOldKey, 0, sizeof mOldKey );
			//�摜�͂����œǂݍ���ł���
			mImage = new Image[ 2 ]{ "data/image/dng01.jpg" ,"data/image/chara/007.png"}; //�_���W�����摜
			mImage[ 0 ].setImgHandle(); //�w�i�摜
			mImage[ 1 ].setImgHandle(); //�L�����摜
			mWindow = new Window[6];
		}

		Dungeon::~Dungeon() {
			delete[] mImage;
			mImage = 0;
			delete[] mWindow;
			mWindow = 0;
		}

		Child* Dungeon::update( Parent* ) {
			Child* next = this;

			if ( checkFirstLoop() || mFrameCount<Global::WaitFrame) {
				Global::moveScreen(mFrameCount,"�ړ���");
				++mFrameCount;
			} else {
				//�摜�`��
				mImage[ 0 ].drawGraph( 0, 0 );
				//TODO:�o�g��(�����X�^�[�ƃv���C���[�摜�\��)
				//��ʂ��\��
				drawState();
				changeCursor();
				if ( CheckHitKey( KEY_INPUT_SPACE ) ) {
					switch( mCursorPosition ) {
						case 0: //���֐i��
							next = new Battle;
							break;
						case 1: //�X�֖߂�
							next = new BaseTown;
							break;
						//case 2:
						//	next = new BossBattle;
						// break;
						default: break;
					}
				}
			}

			if ( CheckHitKey( KEY_INPUT_B ) ) {
				clsDx();
				next = new Battle;
			} else if ( CheckHitKey( KEY_INPUT_BACK ) ) {
				clsDx();
				next = new BaseTown;
			}
			
			return next;
		}

		void Dungeon::drawState() {
			//�t���A�\�� TODO:�t���A���ς�
			mWindow[ WINNAME_FLOOR ].drawWindow( 10, 4, 100, 30, Window::WINDOW_LINE );
			DrawFormatString( 13, 7, WHITE, "��%d�w", 1 );
			//�T���x�\�� TODO:�T���x�V�X�e������
			mWindow[ WINNAME_PROGRESS ].drawWindow( 500, 4, 679, 30, Window::WINDOW_LINE );
			DrawString( 501, 7, "�T���x", WHITE );
			//���j���[�\���B��ɐi�ނƃo�g���J�n�A�X�ɖ߂��BaseTown�ցB
			mWindow[ WINNAME_SELECTMENU ].drawWindow( menuWidth, menuHeight, menuWidth * 2, menuHeight * 2, Window::WINDOW_LINE );
			mWindow[ WINNAME_SELECTMENU ].drawListOnWindow( 3, mCursorPosition, list );
			//�X�e�[�^�X�\��
			mWindow[ WINNAME_STATUS ].drawWindow( 380, 350, 630, 470, Window::WINDOW_LINE );
			mWindow[ WINNAME_STATUS ].drawHPBar( 415, 385, 100 );
				//���x��
			DrawFormatString( 385, 355, ::WHITE, "���x���@%d", 1 );
				//HP
			DrawString( 385, 385, "HP", ::WHITE );
			DrawFormatString( 440, 386, ::WHITE, "%d  /  %d", 108, 108 );
				//EXP
			DrawString( 385, 415, "EXP", ::WHITE );
			DrawFormatString( 440, 416, ::WHITE, "%d / %d", 0, 1200 );
			//�L�����摜
			mWindow[ WINNAME_CHARA ].drawWindow( 330, 350, 378, 470, Window::WINDOW_LINE );
			mImage[ 1 ].drawGraph( 333, 355, true );
		}

		bool Dungeon::checkFirstLoop() {
			//����true��������ŏ�����Ȃ�
			if ( mFirstFlag ) {
				return false;
			}
			mFirstFlag = true;
			return true;
		}

		void Dungeon::changeCursor() {
			//�J�[�\���ړ�
			//�܂���L�[�������ꂽ���ǂ���
			mNowKey[0] = Global::isKeyOn( KEY_INPUT_UP );
			if ( !mOldKey[0] && mNowKey[0] ) { //�O������ĂȂ��č�������Ă�����
				--mCursorPosition; //�J�[�\�������
				mCursorPosition = ( mCursorPosition < 0 ) ? 0 : mCursorPosition;
			}
			//���ɉ��L�[�������ꂽ���ǂ���
			mNowKey[1] = Global::isKeyOn( KEY_INPUT_DOWN );
			if ( !mOldKey[1] && mNowKey[1] ) {
				++mCursorPosition; //�J�[�\��������
				mCursorPosition = ( mCursorPosition > 2 ) ? 2 : mCursorPosition;
				
			}
			mOldKey[ 0 ] = mNowKey[ 0 ]; //���݂̏�Ԃ�ۑ�
			mOldKey[ 1 ] = mNowKey[ 1 ];
			
		}

	} //namespace Game
} //namespace Sequence