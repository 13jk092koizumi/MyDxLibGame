#include "DxLib.h"
#include <vector>
using namespace std;

#include "Sequence/Game/Battle.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Dungeon.h"
#include "Battle/BattleMain.h"
#include "Image.h"
#include "Window.h"
#include "GlobalValues.h"

using namespace BATTLE;

namespace {
	unsigned int WHITE = GetColor( 255, 255, 255 );
	char* menuList[] = {
		"��������",
		"�X�L��",
		"�ɂ���",
	};
	char* skillMenu[] = {
		"�X�L��1",
		"�X�L��2",
		"�X�L��3",
		"�X�L��4",
		"�X�L��5",
	};

} //namespace

namespace Sequence {
	namespace Game {
			Battle::Battle() :
				mFramecount( 0 ),
				mImage( 0 ),
				mWindow( 0 ),
				mBattleMain(0),
				��IsSkillMenu( false ),
				mCommandPhase(true), //�ŏ��̓R�}���h�I���t�F�[�Y
				mActPhase(false),
				mDecideCommand(false)
			{
				//�����o�z��̏�����
				memset( mCursorPosition, -1, sizeof mCursorPosition );
				memset( mNowKey, 0, sizeof mNowKey );
				memset( mOldKey, 0, sizeof mOldKey );

				mImage = new Image[ 3 ]{ "data/image/dng01.jpg" ,"data/image/chara/007.png","data/image/battler00/animal05.png" };
				mImage[ 0 ].setImgHandle();
				mImage[ 1 ].setImgHandle();
				mImage[ 2 ].setImgHandle();
				mWindow = new Window[ 5 ];

				mBattleMain = new BattleMain;
			}

			Battle::~Battle() {
				delete[] mImage;
				mImage = 0;

				delete[] mWindow;
				mWindow = 0;
			}

			Child* Battle::update( Parent* parent ) {
				Child* next = this;
				//��ʕ`��
				mImage[ 0 ].drawGraph( 0, 0 );
				drawState();
				//�R�}���h�I���t�F�[�Y��
				if ( mCommandPhase ) {
					mBattleMain->resetTurn(); //�^�[���̏�����
					mDecideCommand = false; //�R�}���h������
					selectCommand();
					DrawString( 100, 3, "�R�}���h��I�����Ă��������B", ::WHITE );

					if ( mDecideCommand ) {
						mCommandPhase = false; //�I���t�F�[�Y���I�t��
						mActPhase = true; //���s�t�F�[�Y���I����
					}
					mFramecount = 0;
				}
				if ( mActPhase  && mFramecount < 60) {
					//TODO:�o�g���̃A�j���[�V���������E�W�I�I��
					if ( mBattleMain->doTurn( mFramecount, commandKind() ) ) {
						next = new Dungeon; //doTurn��true�Ȃ�o�g�����I������
					}
					++mFramecount;
					if ( mFramecount == 60 ) {
						mActPhase = false;
						mCommandPhase = true;
					}
				}
				
				if ( CheckHitKey( KEY_INPUT_D ) ) {
					clsDx(); //printfDx clear
					next = new Dungeon;
				} else if ( CheckHitKey( KEY_INPUT_G ) ) {
					clsDx();
					parent->moveTo( Parent::NEXT_GAME_OVER );
				}


				return next;
			}

			void Battle::drawState() {
				//���b�Z�[�W���O
				mWindow[ WINNAME_B_MESSAGE ].drawWindow( 2, 2, 639, 30, Window::WINDOW_LINE );
				DrawFormatString( 20, 5, ::WHITE, "�G���P���Ă����I�I" );
				/*�v���C���[*/
				//�X�e�[�^�X�\��
				mWindow[ WINNAME_B_STATUS ].drawWindow( 380, 350, 630, 470, Window::WINDOW_LINE );
				mWindow[ WINNAME_B_STATUS ].drawHPBar( 415, 385, 100 );
				//���x��
				DrawFormatString( 385, 355, ::WHITE, "���x���@%d", 1 );
				//HP
				DrawString( 385, 385, "HP", ::WHITE );
				DrawFormatString( 440, 386, ::WHITE, "%d  /  %d", 108, 108 );
				//EXP
				DrawString( 385, 415, "EXP", ::WHITE );
				DrawFormatString( 440, 416, ::WHITE, "%d / %d", 0, 1200 );
				//GOLD
				DrawString( 385, 450, "������", ::WHITE );
				DrawFormatString( 480, 450, ::WHITE, "%d G", 1000 );
				//�L�����摜
				mWindow[ WINNAME_B_CHARA ].drawWindow( 330, 350, 378, 470, Window::WINDOW_LINE );
				mImage[ 1 ].drawGraph( 333, 355, false );
				
				/*�G*/
				//�G�摜TODO:�����_���ɓG�����ł���悤��
				int counter = 0;
				counter = GetRand( 100 );
				//DrawFormatString( 400, 200, ::WHITE, "count:%d", counter );
				mImage[ 2 ].drawRotaGraph( 300, 220, 1.5, 0.0, true );
				if ( counter % 100 == 0 ) {
					mImage[ 2 ].drawRotaGraph( 300, 220, 1.6, 0.0, true );
				}
				//�G�̎c��HP��\��
				vector<int>& v = mBattleMain->getEnemyStatus();
				int i = 0;
				for ( auto itr = v.begin(); itr != v.end(); ++itr ) {
					DrawFormatString( 100, 30 + 20 * i, ::WHITE, "enemy%d:%d", i, v.at(i) );
					++i;
				}
				
			}

			void Battle::selectCommand() {
				//�R�}���h���j���[�`��
				mWindow[ WINNAME_B_MENU1 ].drawWindow( 3, 350, 120, 478, Window::WINDOW_LINE );
				mWindow[ WINNAME_B_MENU1 ].drawListOnWindow( 3, mCursorPosition[ WINNAME_B_MENU1 ], ::menuList );
				//SPACE�L�[�������ꂽ���ǂ���
				mNowKey[ 2 ] = Global::isKeyOn( KEY_INPUT_SPACE );
				//�J�[�\���ړ�
				if ( !��IsSkillMenu ) { //�X�L�����j���[���J����Ă��Ȃ�
					changeCursor( WINNAME_B_MENU1, 3 );
					//���j���[����
					if ( !mOldKey[ 2 ] && mNowKey[ 2 ] && mCursorPosition[ WINNAME_B_MENU1 ] == 1 ) { //�X�L����I������
						++mKeyCount;
						��IsSkillMenu = true;
					}
				}
				//�X�L�����j���[����
				if ( mKeyCount > 0 && ��IsSkillMenu ) { //space�L-�̃J�E���g��0�ȏ�ŃX�L�����j���[���L���ł���
					changeCursor( WINNAME_B_MENU2, 5/*TODO:�X�L���ꗗ�̐�*/ );
					mWindow[ WINNAME_B_MENU2 ].drawWindow( 110, 270, 320, 478, Window::WINDOW_LINE );
					mWindow[ WINNAME_B_MENU2 ].drawListOnWindow( 5, mCursorPosition[ WINNAME_B_MENU2 ], ::skillMenu );
				}

				if ( Global::isKeyOn( KEY_INPUT_X ) ) { //X��UP,DOWN�L�[����������
					mKeyCount = 0;
					��IsSkillMenu = false;
					mCursorPosition[WINNAME_B_MENU2] = -1;
				}

				//����{�^����������Ă��āA���J�[�\���ʒu�����̐��̂Ƃ��R�}���h���m�肷��
				if ( !mOldKey[ 2 ] && mNowKey[ 2 ] && mCursorPosition[WINNAME_B_MENU1] != 1  && mCursorPosition[ WINNAME_B_MENU1 ] >= 0 ) {
					//�X�L����I�����Ă��Ȃ�
					mDecideCommand = true; //�R�}���h�m��
				} else if ( !mOldKey[ 2 ] && mNowKey[ 2 ] && mCursorPosition[ WINNAME_B_MENU2 ] >= 0 ) {
					//�X�L�����j���[�̉�������ɃJ�[�\��������
					mDecideCommand = true;
				}

				//���݂̏�Ԃ�ۑ�
				for ( int i = 0; i < sizeof mOldKey; i++ ) {
					mOldKey[ i ] = mNowKey[ i ];
				}

			}

			void Battle::changeCursor( int cursorIndex, int listSize ) {
				//�܂���L�[�������ꂽ���ǂ���
				mNowKey[ 0 ] = Global::isKeyOn( KEY_INPUT_UP );
				if ( !mOldKey[ 0 ] && mNowKey[ 0 ] ) { //�O������ĂȂ��č�������Ă�����
					mCursorPosition[ cursorIndex ] -= 1; //�J�[�\�������
					mCursorPosition[ cursorIndex ] = ( mCursorPosition[ cursorIndex ] < 0 ) ? 0 : mCursorPosition[ cursorIndex ];
				}
				//���ɉ��L�[�������ꂽ���ǂ���
				mNowKey[ 1 ] = Global::isKeyOn( KEY_INPUT_DOWN );
				if ( !mOldKey[ 1 ] && mNowKey[ 1 ] ) {
					mCursorPosition[ cursorIndex ] += 1; //�J�[�\��������
					mCursorPosition[ cursorIndex ] = ( mCursorPosition[ cursorIndex ] > listSize - 1 ) ? listSize - 1 : mCursorPosition[ cursorIndex ];
				}
			}

			int Battle::commandKind() {
				switch ( mCursorPosition[ 0 ] ) {
					case 0:
						//��������
						return 1;
					case 1:
						//�X�L��
						switch ( mCursorPosition[ 1 ] ) {
							case 0:
								return 101;
							case 1:
								return 102;
							case 2:
								return 103;
							case 3:
								return 104;
							case 4:
								return 105;
						}
						break;
					case 2:
						//�ɂ���
						return 200;
				}
			}

	} //namespace Game
} //namespace Sequence
