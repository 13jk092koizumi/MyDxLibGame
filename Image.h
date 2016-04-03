#ifndef INCLUDED_IMAGE_H
#define INCLUDED_IMAGE_H

class Image {
public:
	//引数は画像のファイルパス
	Image( const char* filename );
	~Image();
	void setImgHandle();	//画像ハンドラのセット
	void setDivImgHandle( int AllNum, int XNum, int YNum, int XSize, int YSize );	//分割画像のハンドラをセット
	int* getHnadle() const; //ハンドラを返す
	
	void drawGraph( int dstX, int dstY, bool TransFlag = false ) const ; //画像の描画
	void drawRotaGraph( int dstX, int dstY, float scale, float angle, bool TransFlag = false ) const; //画像を座標変換して描画
	void drawDivGraph( int index, int dstX, int dstY, bool TransFlag = false ) const; //分割画像の描画
	void drawRotaDivGraph( int index, int dstX, int dstY, float scale, float angle, bool TransFlag = false ) const; //分割画像を座標変換して描画

private:
	const char* mFilename; //ファイルパス
	int mHandle; //通常の画像用ハンドラ
	int* mHandleArray;	//分割画像用ハンドラ配列
};


#endif