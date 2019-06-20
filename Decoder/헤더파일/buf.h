#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <time.h>

//디코더 
#define TRUE	1
#define FALSE	0
#define BEFORE  1
#define AFTER   0

#define TSIZE   16 // 블럭사이즈 16
#define BUFSIZE   4 // 블럭사이즈 4

//영상 size
#define ROW			720			
#define COL			480


typedef struct _Buffer
{
	double QuantNum; //양자화 계수
	int MV_X,MV_Y; //모션 벡터
	int Flag; // 공간예측 모드

	unsigned char  *Input; // 현재영상
	unsigned char  *PastInput; //  before영상
	unsigned char  *Output;	//디코딩된 영상
	

	unsigned char  *Inter_Reconstructed;	// 시간예측의 리컨블럭 (720*480)
	int            *Inter_quantization;    //시간예측의 양자화된블럭 (16*16)
	double         *Inter_inquantization;  // 시간예측의 역양자화된 블럭 (16*16)
	unsigned char  *Past_Reconstructed;  // before영상의 공간예측으로 복원된 영상 720*480
	unsigned char  *MoveCompensatedBlk;  //   모션벡터로 찾은 16*16 버퍼블럭

	
	unsigned char  *Intra_predict; // 공간예측의 예측블럭 (4*4)
	unsigned char  *Intra_Reconstructed; //공간예측의 리컨블럭 (720*480)
	int            *Intra_quantization;  //공간예측의 양자화된 블럭 (4*4)
	double         *Intra_inquantization; //공간예측의 역양자화된 블럭(4*4)


	unsigned char  *Before_Reconstructed; //미스매치 확인하기 위한 before영상의 복원영상 
	unsigned char  *After_Reconstructed;  //미스매치 확인하기 위한 after영상의 복원영상
	
	int            *Intra_Transfer_quantization; //디코더에서 양자화데이터를 읽어오는 16*16블럭
}Buffer;

typedef Buffer Buf;

void SubMain( Buf *DB );
void BufCon( Buf *DB, int OrderFlag ); //파일 읽기, 변수 동적할당, 해제하는 함수 

void Inter_InQuantization( Buf *DB ); //시간예측 역양자화 하는 함수
void Inter_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col); //시간예측 reconstruct(복원된데이터)구하는 함수

void Intra_Prediction(Buf *DB, int Mode, int Blk_Row, int Blk_Col); //공간예측 예측블럭 구하는 함수
void Intra_InQuantization( Buf *DB ); //공간예측 역양자화 하는 함수
void Intra_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col); //공간예측 reconstruct(복원된데이터)구하는 함수

void Before_Intra_Decoder(Buf *DB); //before영상 디코더
void Decoder(Buf *DB); //after영상 디코더
void PSNR( Buf *DB,int OrderFlag ); //미스매치 여부와 psnr구하는 함수. 


