#include "DxLib.h"

#include "Sequence/Title.h"
#include "Sequence/Parent.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/GameOver.h"
#include "Image.h"
#include "Window.h"
#include "GlobalValues.h"

namespace {
	char* list[] = {
		"�͂��߂���",
		"�Â�����",
	};
	//�J�E���^�p�ϐ�
	int nowCount = 0;
	int oldCount = 0;
	int TimeSensor = 0; //�w��J�E���^�������Ăяo���Ȃ��Ƃ��g��
}

namespace Sequence {

	Title::Title() :
		mImage( 0 ),
		mWindow(0),
		mCursorPosition(-1),
		mPushFlag(false),
		mGameStartFlag(false) {
		//�����o�z�񏉊���
		memset( mNowKey, 0, sizeof mNowKey );
		memset( mOldKey, 0, sizeof mOldKey );
		mImage = new Image( "data/image/title.png" );
		mWindow = new Window;
		Sleep( 200 );
	}

	Title::~Title() {
		if ( mImage != 0 ) {
			delete mImage;
			mImage = 0;
		}
		if ( mWindow != 0 ) {
			delete mWindow;
			mWindow = 0;
		}
	}

	Child* Title::update( Parent* ) {
		Child* next = this; //���N���XChild�̊��N���XBase�փ|�C���^��n���B
		//�����L�[�������ꂽ��BaseTown�֑J��
		drawState();
		//���j���[�\�����Ă��Ȃ��Ƃ�
		if ( !mMenuFlag ) {
			DrawString( 200, 200, "push any key.", GetColor( 255, 255, 255 ) );
		}
		//�����L�[�������ꂽ�Ƃ�
		if ( CheckHitKeyAll( )) {
			mPushFlag = true;
			if ( CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) { //ESCAPE�L�[�̎��͏������Ȃ��悤�ɂ���
				drawState();
				if ( mGameStartFlag ) { //�Q�[���X�^�[�g�̏����𖞂������Ƃ�
					next = new Game::Parent();
				}
			}
		}

		return next;
	}

	void Title::drawState() {
		
		//�w�i�`��
		mImage->setImgHandle();
		mImage->drawGraph( 0, 0 );
		
		//�����L�[�������ꂽ�烁�j���[�\��
		if ( mPushFlag ) { 
			startMenu();
			mMenuFlag = true;
			if ( CheckHitKey( KEY_INPUT_X ) ) { //x�ŃL�����Z��������
				mPushFlag = false;
				mMenuFlag = false;
			}
		}

		changeCursor();

		if ( CheckHitKey( KEY_INPUT_SPACE ) ) { //space(����)��������
			//���j���[�I��
			switch ( mCursorPosition ) {
				case SMENU_HAJIMEKARA: //�͂��߂���
					//TODO:�X�g�[���[�e�����O�����
					mGameStartFlag = true;
					break;
				case SMENU_TUDUKIKARA: //�Â�����
					mGameStartFlag = true;
					break;
				default:
					mGameStartFlag = false;
					break;
			}
		}
			//TODO:debag DrawFormatString( 400, 0, GetColor( 255, 255, 255 ), "cursor:%d", mCursorPosition );
	}
	
	void Title::startMenu() {
		//menu�`��
		mWindow->drawWindow( 240, 200, 380, 400, Window::WINDOW_LINE );
		mWindow->drawListOnWindow( 2, mCursorPosition,  list);
	}

	void Title::changeCursor() {
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
			mCursorPosition = ( mCursorPosition > 1 ) ? 1 : mCursorPosition;

		}
		mOldKey[ 0 ] = mNowKey[ 0 ]; //���݂̏�Ԃ�ۑ�
		mOldKey[ 1 ] = mNowKey[ 1 ];

	}

} //namespace Sequence