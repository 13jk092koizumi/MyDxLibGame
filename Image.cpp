#include "DxLib.h"

#include "Image.h"

Image::Image( const char* filename ) :	
	mFilename(filename),
	mHandle(-1),
	mHandleArray(0){

}

Image::~Image() {
	if ( mHandleArray != 0 ) {
		delete[] mHandleArray;
	}
}

void Image::setImgHandle() {
	mHandle = LoadGraph( mFilename );
	if ( mHandle == -1 ) { 
		DxLib_End(); //エラー 
	}
}

void Image::setDivImgHandle(int AllNum, int XNum,int YNum,int XSize,int YSize) {
	mHandleArray = new int[ AllNum ];
	if ( LoadDivGraph( mFilename, AllNum, XNum, YNum, XSize, YSize, mHandleArray ) == -1) {
		DxLib_End(); //エラー
	}
}


void Image::drawGraph( int dstX, int dstY,bool TransFlag ) const {
	if ( DrawGraph( dstX, dstY, mHandle, TransFlag ) == -1 ) {
		DxLib_End();//エラー
	}
}

void Image::drawRotaGraph( int dstX, int dstY, float scale, float angle, bool TransFlag ) const {
	if ( DrawRotaGraph( dstX, dstY, scale, angle, mHandle, TransFlag ) == -1 ) {
		DxLib_End();//エラー
	}
}

void Image::drawDivGraph( int index , int dstX, int dstY, bool TransFlag) const {
		// グラフィックの描画
	if ( DrawGraph( dstX, dstY, mHandleArray[ index ], TransFlag ) == -1 ) {
		DxLib_End(); //エラー
	}
}

void Image::drawRotaDivGraph(int index,int dstX,int dstY, float scale,float angle,bool TransFlag) const {
	if ( DrawRotaGraph( dstX, dstY, scale, angle, mHandleArray[ index ], TransFlag ) == -1 ) {
		DxLib_End(); //エラー
	}
}