#include "DxLib.h"

#include "GlobalValues.h"
using namespace Global;
#include "Sequence/Parent.h"
#include "GameController.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	//�E�B���h�E���[�h
	if ( ChangeWindowMode( TRUE ) == -1 ) {
		return -1;
	}
	//DX���C�u�����������Ɨ���ʉ�
	if (DxLib_Init() == -1) {
		return -1;
	}
	if ( SetDrawScreen( DX_SCREEN_BACK ) != 0 ) {
		return -1;
	}
	//�t�H���g�̐ݒ�
	SetFontSize(FontSize);	//�T�C�Y
	ChangeFont( "HGS�n�p�p�߯�ߑ�" ); //����
	ChangeFontType( DX_FONTTYPE_ANTIALIASING ); //�A���`�G�C���A�X

	//�V���O���g���쐬
	if ( !Sequence::Parent::instance() ) {
		Sequence::Parent::create();
	}
	if ( !GameController::instance() ) {
		GameController::create();
	}

	//���C�����[�v
	while ( true) {
		
		Sequence::Parent::instance()->update();
		GameController::instance()->control();
		
		//escape�L�[�������ꂽ��break;
		GameController::instance()->getAllKeyPressed();
		if ( ProcessMessage() == 0 && GameController::instance()->getKey( KEY_INPUT_ESCAPE) ) {
			break;
		}

		ScreenFlip();
		//InitGraph();
	}

	Sequence::Parent::destroy();
	GameController::destroy();
	
	DxLib_End();

	return 0;
}