#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <time.h>

//���ڴ�
#define TRUE	1
#define FALSE	0
#define BEFORE  1
#define AFTER   0

#define TSIZE   16 // �������� 16
#define BUFSIZE   4 //�������� 4

//search range
#define SR_W    4 
#define SR_H    4

//���� size
#define ROW			720			
#define COL			480


typedef struct _Buffer
{
	double QuantNum; //����ȭ ���
	int MV_X,MV_Y; //��� ����
	int Flag; //���������Ҷ� 9������ ��� 

	unsigned char  *Input; // ���翵��
	unsigned char  *Output;	// after������ ������ ����
	unsigned char  *PastInput; //  before����
	unsigned char  *CurBlk;	// 720*480 ������ ������ ���� ��  16*16�������� ���ۺ�

	int            *Inter_DifferBlk; //�ð������� ������ (16*16)
	unsigned char  *Inter_Reconstructed; // �ð������� ������ (720*480)
	int            *Inter_quantization;  //�ð������� ����ȭ�Ⱥ� (16*16)
	double         *Inter_inquantization; // �ð������� ������ȭ�� �� (16*16)
	unsigned char  *Past_Reconstructed; // before������ ������������ ������ ���� 720*480
	unsigned char  *MoveCompensatedBlk; //  ��Ǻ��ͷ� ã��  16*16 ���ۺ�. 
	

	int            *Intra_DifferBlk; // ���������� ������ (4*4)
	unsigned char  *Intra_predict;   // ���������� ������ (4*4)
	unsigned char  *Intra_Reconstructed; //���������� ������ (720*480)
	unsigned char  *Intra_CurBlk;	// 16*16�� CurBlk���� 4*4���ڵ��Ҷ�����  ��� ���� �� 	
	int            *Intra_quantization;  //���������� ����ȭ�� �� (4*4)
 	double         *Intra_inquantization; //���������� ������ȭ�� ��(4*4)

	int            *Intra_Transfer_quantization; //16*16�������� ���ڴ��� ������ ����ȭ�� ������ 4*4 �������� ����ȭ�� �� 16���� �� �迭�� ����.

}Buffer;

typedef Buffer Buf;

void SubMain( Buf *DB );
void BufCon( Buf *DB, int OrderFlag ); //���� �б�, ���� �����Ҵ�, �����ϴ� �Լ� 

void Inter_Difference(Buf *DB, int Blk_Row, int Blk_Col); //�ð����� ��Ǻ��Ϳ� �������� ���ϴ� �Լ�
void Inter_Quantization( Buf *DB ); //�ð����� ����ȭ�ϴ� �Լ�
void Inter_InQuantization( Buf *DB ); //�ð����� ������ȭ �ϴ� �Լ�
void Inter_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col); //�ð����� reconstruct(�����ȵ�����)���ϴ� �Լ�



void Intra_Prediction(Buf *DB, int Mode, int Blk_Row, int Blk_Col); //�������� ������ ���ϴ� �Լ�
void Intra_Difference(Buf *DB, int Blk_Row, int Blk_Col); //�������� ������ ���� ���� ����� flag�� �������� ���ϴ� �Լ� 
void Intra_Quantization( Buf *DB ); // �������� ����ȭ �ϴ� �Լ�
void Intra_InQuantization( Buf *DB ); //�������� ������ȭ �ϴ� �Լ�
void Intra_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col); //�������� reconstruct(�����ȵ�����)���ϴ� �Լ�

void Before_Intra_Encoder(Buf *DB); //before���� ���ڴ�
void Encoder(Buf *DB); //after���� ���ڴ�
void PSNR( Buf *DB,int OrderFlag ); //psnr���ϴ� �Լ�.


