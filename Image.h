#ifndef INCLUDED_IMAGE_H
#define INCLUDED_IMAGE_H

class Image {
public:
	//�����͉摜�̃t�@�C���p�X
	Image( const char* filename );
	~Image();
	void setImgHandle();	//�摜�n���h���̃Z�b�g
	void setDivImgHandle( int AllNum, int XNum, int YNum, int XSize, int YSize );	//�����摜�̃n���h�����Z�b�g
	int* getHnadle() const; //�n���h����Ԃ�
	
	void drawGraph( int dstX, int dstY, bool TransFlag = false ) const ; //�摜�̕`��
	void drawRotaGraph( int dstX, int dstY, float scale, float angle, bool TransFlag = false ) const; //�摜�����W�ϊ����ĕ`��
	void drawDivGraph( int index, int dstX, int dstY, bool TransFlag = false ) const; //�����摜�̕`��
	void drawRotaDivGraph( int index, int dstX, int dstY, float scale, float angle, bool TransFlag = false ) const; //�����摜�����W�ϊ����ĕ`��

private:
	const char* mFilename; //�t�@�C���p�X
	int mHandle; //�ʏ�̉摜�p�n���h��
	int* mHandleArray;	//�����摜�p�n���h���z��
};


#endif