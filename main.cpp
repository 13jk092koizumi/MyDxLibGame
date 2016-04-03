#include "DxLib.h"

#include "GlobalValues.h"
using namespace Global;
#include "Sequence/Parent.h"
#include "GameController.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	//ウィンドウモード
	if ( ChangeWindowMode( TRUE ) == -1 ) {
		return -1;
	}
	//DXライブラリ初期化と裏画面化
	if (DxLib_Init() == -1) {
		return -1;
	}
	if ( SetDrawScreen( DX_SCREEN_BACK ) != 0 ) {
		return -1;
	}
	//フォントの設定
	SetFontSize(FontSize);	//サイズ
	ChangeFont( "HGS創英角ﾎﾟｯﾌﾟ体" ); //字体
	ChangeFontType( DX_FONTTYPE_ANTIALIASING ); //アンチエイリアス

	//シングルトン作成
	if ( !Sequence::Parent::instance() ) {
		Sequence::Parent::create();
	}
	if ( !GameController::instance() ) {
		GameController::create();
	}

	//メインループ
	while ( true) {
		
		Sequence::Parent::instance()->update();
		GameController::instance()->control();
		
		//escapeキーが押されたらbreak;
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