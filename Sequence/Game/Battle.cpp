#include "DxLib.h"
#include <vector>
using namespace std;

#include "Sequence/Game/Battle.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Dungeon.h"
#include "Battle/BattleMain.h"
#include "Battle/Enemy.h"
#include "Image.h"
#include "Window.h"
#include "Animation.h"
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
	
	/*�A�j���[�V�������ʗp*/
	enum anime {
		ANIME_PATTACK, //�v���C���[�U���A�j���[�V����
		ANIME_EATTACK, //�G�U���A�j���[�V����
		ANIME_IMG_ENEMY, //�G�摜�̃A�j���[�V����
	};

} //namespace

namespace Sequence {
	namespace Game {
			Battle::Battle() :
				mFramecount( 0 ),
				mImage( 0 ),
				mWindow( 0 ),
				mAnimation(0),
				mBattleMain(0),
				��IsSkillMenu( false ),
				mBattleState(Battle_None),
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
				mBattleState = Battle_CommandSelect;
				mAnimation = new Animation[ 3 ]{ Animation( 30, 3 ), Animation(30,3), Animation(60,6) };
			}

			Battle::~Battle() {
				delete[] mImage;
				mImage = 0;

				delete[] mWindow;
				mWindow = 0;

				delete[] mAnimation;
				mAnimation = 0;
			}

			Child* Battle::update( Parent* parent ) {
				Child* next = this;
				//��ʕ`��
								
				//�A�j���[�V�����p�ϐ�
				bool isValidAnime = false;
				int nowDivNum = 0;
				int color = 0;

				//�o�g���̏�ԑJ��
				switch ( mBattleState ) {
					case Battle_CommandSelect:
						
						drawState();
						DrawFormatString( 20, 5, ::WHITE, "�G���P���Ă����I�I" );

						mBattleMain->resetTurn(); //�^�[���̏�����
						mDecideCommand = false; //�R�}���h������
						selectCommand();
						if ( mDecideCommand ) { //�R�}���h�����肵��
							mBattleState = Battle_PlayerAct;
						}
						break;
					
					case Battle_PlayerAct:
						if ( mBattleMain->exeTurn( mFramecount, commandKind() /*selectTarget()*/ ) ) { //�v���C���[�̃^�[���I��
							mBattleState = Battle_EnemyAct;
						}
						
						isValidAnime = mAnimation[ANIME_PATTACK].animate(); //�R�}����̃^�C�~���O��
						if ( isValidAnime && mAnimation[ANIME_PATTACK].getmIsAnimating() ) { //�A�j���[�V�������L���ł���
							nowDivNum = mAnimation[ANIME_PATTACK].getNowDivNum();
							color = 88 * nowDivNum;
							color = ( color > 255 ) ? 255 : color;
							/*TODO:�U���G�t�F�N�g�ɒu��������*/
							DrawBox( 0, 0,Global::WindowWidth,Global::WindowHeight, GetColor( color, color, color ),true );
							if ( nowDivNum > 1 ) {
								//�f�o�b�O
								int damage = mBattleMain->getDamege( 2 );
								if ( damage < 0 ) {
									damage = 11111111;
								}
								DrawFormatString( 20, 5, GetColor( 0, 0, 0 ), "�G��%d�̃_���[�W�I�I", damage ); //�_���[�W�ʕ\��
							}
						} else if ( mAnimation[ANIME_PATTACK].getmIsAnimating() == false ) {
							mAnimation[ANIME_PATTACK].end(); //�J�E���^��������
							mAnimation[ANIME_PATTACK].start();
							mBattleState = Battle_EnemyAct;
						}
//						++mFramecount;
//						if ( mFramecount > 60 ) {
//							mBattleState = Battle_EnemyAct;
//							mFramecount = 0;
//						}
						break;
					case Battle_EnemyAct:
						if ( mBattleMain->exeTurn( mFramecount, commandKind() ) ) { //�G�^�[���I��
							mBattleState = Battle_CommandSelect;
							if ( mBattleMain->isBattleEnd() ) { //�o�g�����I�����Ă���
								mBattleState = Battle_Result; //���U���g��ʕ\��
								if ( mBattleMain->isGameOver() ) { //�Q�[���I�[�o�[�t���O�𖞂����Ă���
									mBattleState = Battle_Gameover;//�Q�[���I�[�o�[��
								}
							}
						}

						++mFramecount;
						if ( mFramecount > 60 ) {
							mBattleState = Battle_CommandSelect;
							mFramecount = 0;
						}
						break;
					case Battle_Result:
						/*TODO:���U���g��ʕ\��(�I������t���O����������Battle_End��)*/
						++mFramecount;
						if ( mFramecount > 60 ) {
							mBattleState = Battle_End;
							mFramecount = 0;
						} else {
							mBattleMain->result();
						}
						break;
					case Battle_End:
						/*TODO:�I���A�j���[�V�����̕\��*/
						mBattleState = Battle_None; //�ϐ�������
						next = new Dungeon; //�_���W�����ɖ߂�
						break;
					case Battle_Gameover:
						parent->moveTo( Parent::NEXT_GAME_OVER ); //�Q�[���I�[�o�[��
						mBattleState = Battle_None; //�ϐ�������
						break;
					case Battle_None: //���肦�Ȃ��I�H
						DrawString( 0, 200, "NowBattleState is NONE!!!", GetColor( 255, 255, 0 ) );
						WaitKey();
						break;
				}

				/*
				//�R�}���h�I���t�F�[�Y��
				if ( mCommandPhase ) {
					mBattleMain->resetTurn(); //�^�[���̏�����
					mDecideCommand = false; //�R�}���h������
					selectCommand();

					if ( mDecideCommand ) {
						mCommandPhase = false; //�I���t�F�[�Y���I�t��
						mActPhase = true; //���s�t�F�[�Y���I����
					}
					mFramecount = 0;
				}
				if ( mActPhase  && mFramecount < 60) {
					//TODO:�o�g���̃A�j���[�V���������E�W�I�I��
					if ( mBattleMain->exeTurn( mFramecount, commandKind() ) ) {
						next = new Dungeon; //exeTurn��true�Ȃ�o�g�����I������
					}
					++mFramecount;
					if ( mFramecount == 60 ) {
						mActPhase = false;
						mCommandPhase = true;
					}
				}
				*/
				
				//�f�o�b�O
				DrawFormatString( 0, 200, GetColor(0,0,0), "mBattleState:%d", mBattleState );

				if ( Global::isKeyOn( KEY_INPUT_D ) ) {
					next = new Dungeon;
				} else if ( Global::isKeyOn ( KEY_INPUT_G ) ) {
					parent->moveTo( Parent::NEXT_GAME_OVER );
				}


				return next;
			}

			void Battle::drawState() {
				//�w�i
				mImage[ 0 ].drawGraph( 0, 0 );

				//���b�Z�[�W���O
				mWindow[ WINNAME_B_MESSAGE ].drawWindow( 2, 2, 639, 30, Window::WINDOW_LINE );
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
				drawEnemy();
				
			}

			void Battle::drawEnemy() {
				int enemyNum = mBattleMain->getEnemyNum(); //�G�̐��擾
				float scale = 0;
				int rand = GetRand( 100 );
				if ( rand == 0 ) {
					scale = 0.1f;
				}
				/*�G�摜�̕\��*/
				mAnimation[ ANIME_IMG_ENEMY ].animate();
				int nowDivNum = mAnimation[ANIME_IMG_ENEMY].getNowDivNum(); //���R�}�ڂ��擾
				int movePx = 0; //�G�摜�̏㉺�̈ړ���(�㉺�ɗh�炷)
				switch ( nowDivNum ) {
					case 1:
						movePx = 1;	break;
					case 2:
						movePx = 2;	break;
					case 3:
						movePx = 3;	break;
					case 4:
						movePx = 2;	break;
					case 5:
						movePx = 1;	break;
					case 6:
						movePx = 0;
						mAnimation[ ANIME_IMG_ENEMY ].end();
						mAnimation[ ANIME_IMG_ENEMY ].start(); //�A�j���[�V�����̍ĊJ
						break;
				}
				switch ( enemyNum ) {
					case 1:
						mImage[ 2 ].drawRotaGraph( Global::WindowWidth / 2, (Global::WindowHeight / 2) - movePx , 1.5f+scale, 0.0f ,true);
						break;
					case 2:
						for ( int i = 1; i <= enemyNum; ++i ) {
							mImage[ 2 ].drawRotaGraph( 640 - ( 440 * i / enemyNum ), 180 - movePx, 1.4f+scale, 0.0f, true );
						}
						break;
					case 3:
					case 4:
					case 5:
						for ( int i = 1; i <= enemyNum; ++i ) {
							mImage[ 2 ].drawRotaGraph( 640 - ( 540 * i / enemyNum ), 180 - movePx, 1.2f+scale, 0.0f, true );
 						}
						break;
				}
				/*�c��HP�̕\��*/
				SetFontSize( 12 ); //�����T�C�Y�ύX
				vector<Status> eStatus = mBattleMain->getEnemyStatus(); //vector�œG�̃X�e�[�^�X�\���̂̔z����擾
				Status* data = eStatus.data(); //�G��Status�\���̂̃|�C���^���擾
				int hpColor = 0; //HP�̐F
				int i = 0;
				for ( auto itr = eStatus.begin(); itr != eStatus.end(); ++itr ) {
					if( data[ i ].hp < data[ i ].hpMax * 0.3f ) 	{ //HP30%�ȉ��̂Ƃ�
						hpColor = GetColor( 250, 0, 0 ); //�����ۂ���
					} 
					else if ( data[i].hp < data[i].hpMax * 0.5f ) { //HP50%�ȉ��̂Ƃ�
						hpColor = GetColor( 255, 165, 0 ); //�I�����W
					}
					else {
						hpColor = GetColor( 255, 255, 255 ); //��
					}
					DrawFormatString( 640 - ( 540 * (i+1) / enemyNum ), 175, hpColor, "%d", eStatus[ i ] );
					++i;
				}

				SetFontSize( Global::FontSize );

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
						//break;
					case 2:
						//�ɂ���
						return 200;
				}
				return -1;
			}

	} //namespace Game
} //namespace Sequence
