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
#define BUFSIZE   4 // �������� 4

//���� size
#define ROW			720			
#define COL			480


typedef struct _Buffer
{
	double QuantNum; //����ȭ ���
	int MV_X,MV_Y; //��� ����
	int Flag; // �������� ���

	unsigned char  *Input; // ���翵��
	unsigned char  *PastInput; //  before����
	unsigned char  *Output;	//���ڵ��� ����
	

	unsigned char  *Inter_Reconstructed;	// �ð������� ������ (720*480)
	int            *Inter_quantization;    //�ð������� ����ȭ�Ⱥ� (16*16)
	double         *Inter_inquantization;  // �ð������� ������ȭ�� �� (16*16)
	unsigned char  *Past_Reconstructed;  // before������ ������������ ������ ���� 720*480
	unsigned char  *MoveCompensatedBlk;  //   ��Ǻ��ͷ� ã�� 16*16 ���ۺ�

	
	unsigned char  *Intra_predict; // ���������� ������ (4*4)
	unsigned char  *Intra_Reconstructed; //���������� ������ (720*480)
	int            *Intra_quantization;  //���������� ����ȭ�� �� (4*4)
	double         *Intra_inquantization; //���������� ������ȭ�� ��(4*4)


	unsigned char  *Before_Reconstructed; //�̽���ġ Ȯ���ϱ� ���� before������ �������� 
	unsigned char  *After_Reconstructed;  //�̽���ġ Ȯ���ϱ� ���� after������ ��������
	
	int            *Intra_Transfer_quantization; //���ڴ����� ����ȭ�����͸� �о���� 16*16��
}Buffer;

typedef Buffer Buf;

void SubMain( Buf *DB );
void BufCon( Buf *DB, int OrderFlag ); //���� �б�, ���� �����Ҵ�, �����ϴ� �Լ� 

void Inter_InQuantization( Buf *DB ); //�ð����� ������ȭ �ϴ� �Լ�
void Inter_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col); //�ð����� reconstruct(�����ȵ�����)���ϴ� �Լ�

void Intra_Prediction(Buf *DB, int Mode, int Blk_Row, int Blk_Col); //�������� ������ ���ϴ� �Լ�
void Intra_InQuantization( Buf *DB ); //�������� ������ȭ �ϴ� �Լ�
void Intra_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col); //�������� reconstruct(�����ȵ�����)���ϴ� �Լ�

void Before_Intra_Decoder(Buf *DB); //before���� ���ڴ�
void Decoder(Buf *DB); //after���� ���ڴ�
void PSNR( Buf *DB,int OrderFlag ); //�̽���ġ ���ο� psnr���ϴ� �Լ�. 


