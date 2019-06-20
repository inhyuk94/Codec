#include "buf.h"
void Inter_InQuantization( Buf *DB )
{
	int i, j;
	double temp;

	for (i = 0; i < TSIZE; i++)
		for (j = 0; j < TSIZE; j++)
			{
				temp = *(DB-> Inter_quantization+i*TSIZE + j) * DB->QuantNum;
				//�ݿø� math.h�� �߰��ص� round�Լ��� ��� �׳� ����
				if(temp < 0)       temp = temp - 0.5;
				else if( temp > 0) temp = temp + 0.5;
				*(DB->Inter_inquantization + i*TSIZE + j) = temp;
			}
}
void Inter_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col)
{
	int i,j;
	int temp;

	for(i = 0 ; i < TSIZE ; i++)
		for(j = 0 ; j <TSIZE ; j++)
		{
			//���ڴ����� �о�� ��Ǻ��͸� �̿��Ͽ� 16*16�������� MoveCompensatedBlk ���� ���� ����.
			//���� = ������ȭ + ��Ǻ��ͷ� ã�� �������� ����� ��
			*(DB->MoveCompensatedBlk + i*TSIZE + j) = *(DB->Past_Reconstructed + ((Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)) + (DB->MV_Y*ROW) + DB->MV_X + (ROW *i) + j);
			temp =   *(DB->Inter_inquantization + i*TSIZE +j) + *(DB->MoveCompensatedBlk + i*TSIZE +j);
			temp = temp > 255 ? 255 : temp < 0 ? 0 : temp;
			*(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE)+ (Blk_Row*TSIZE)+ i*ROW+ j) =  temp;		
		}	
}



