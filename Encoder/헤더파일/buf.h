#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <time.h>

//인코더
#define TRUE	1
#define FALSE	0
#define BEFORE  1
#define AFTER   0

#define TSIZE   16 // 블럭사이즈 16
#define BUFSIZE   4 //블럭사이즈 4

//search range
#define SR_W    4 
#define SR_H    4

//영상 size
#define ROW			720			
#define COL			480


typedef struct _Buffer
{
	double QuantNum; //양자화 계수
	int MV_X,MV_Y; //모션 벡터
	int Flag; //공간예측할때 9가지의 모드 

	unsigned char  *Input; // 현재영상
	unsigned char  *Output;	// after영상의 리컨된 영상
	unsigned char  *PastInput; //  before영상
	unsigned char  *CurBlk;	// 720*480 영상을 블럭으로 나눌 때  16*16사이즈의 버퍼블럭

	int            *Inter_DifferBlk; //시간예측의 잔차블럭 (16*16)
	unsigned char  *Inter_Reconstructed; // 시간예측의 리컨블럭 (720*480)
	int            *Inter_quantization;  //시간예측의 양자화된블럭 (16*16)
	double         *Inter_inquantization; // 시간예측의 역양자화된 블럭 (16*16)
	unsigned char  *Past_Reconstructed; // before영상의 공간예측으로 복원된 영상 720*480
	unsigned char  *MoveCompensatedBlk; //  모션벡터로 찾은  16*16 버퍼블럭. 
	

	int            *Intra_DifferBlk; // 공간예측의 잔차블럭 (4*4)
	unsigned char  *Intra_predict;   // 공간예측의 예측블럭 (4*4)
	unsigned char  *Intra_Reconstructed; //공간예측의 리컨블럭 (720*480)
	unsigned char  *Intra_CurBlk;	// 16*16의 CurBlk블럭을 4*4블럭코딩할때마다  담는 버퍼 블럭 	
	int            *Intra_quantization;  //공간예측의 양자화된 블럭 (4*4)
 	double         *Intra_inquantization; //공간예측의 역양자화된 블럭(4*4)

	int            *Intra_Transfer_quantization; //16*16사이즈의 디코더에 전송할 양자화된 블럭으로 4*4 사이즈의 양자화된 블럭 16개를 이 배열에 저장.

}Buffer;

typedef Buffer Buf;

void SubMain( Buf *DB );
void BufCon( Buf *DB, int OrderFlag ); //파일 읽기, 변수 동적할당, 해제하는 함수 

void Inter_Difference(Buf *DB, int Blk_Row, int Blk_Col); //시간예측 모션벡터와 잔차블럭을 구하는 함수
void Inter_Quantization( Buf *DB ); //시간예측 양자화하는 함수
void Inter_InQuantization( Buf *DB ); //시간예측 역양자화 하는 함수
void Inter_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col); //시간예측 reconstruct(복원된데이터)구하는 함수



void Intra_Prediction(Buf *DB, int Mode, int Blk_Row, int Blk_Col); //공간예측 예측블럭 구하는 함수
void Intra_Difference(Buf *DB, int Blk_Row, int Blk_Col); //공간예측 에러가 가장 적은 모드의 flag와 잔차블럭을 구하는 함수 
void Intra_Quantization( Buf *DB ); // 공간예측 양자화 하는 함수
void Intra_InQuantization( Buf *DB ); //공간예측 역양자화 하는 함수
void Intra_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col); //공간예측 reconstruct(복원된데이터)구하는 함수

void Before_Intra_Encoder(Buf *DB); //before영상 인코더
void Encoder(Buf *DB); //after영상 인코더
void PSNR( Buf *DB,int OrderFlag ); //psnr구하는 함수.


