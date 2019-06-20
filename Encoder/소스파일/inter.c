#include "buf.h"

void Inter_Difference(Buf *DB, int Blk_Row, int Blk_Col) // �ð����� ��Ǻ��Ϳ� �������� ���ϴ� �Լ�
{
	
	int i, j, x, y, min; //
	int differ[TSIZE*TSIZE] = {0} ; //�������� �������� ���ϱ����� ���������� 
	int SAD = 0; //������ ������ 
	int cnt = 0;

	for (y = -SR_H ; y <= SR_H ; y++) //search range 
		for(x = -SR_W ; x <= SR_W ; x++)	
		{
			if( ( Blk_Col*TSIZE + y ) >=0 && ( Blk_Col*TSIZE + y + TSIZE) < COL )
			{
				if(   (Blk_Row*TSIZE + x ) >= 0  && (Blk_Row*TSIZE + x + TSIZE) < ROW  ) 
				{
					SAD = 0;
					for (i = 0; i < TSIZE; i++)
						for (j = 0; j < TSIZE; j++)
						{
							//���� ����� ��ġ�������� �ش��ϴ� before�� ������ ������� ���̸� �������� ����
							*(differ + i*TSIZE + j) = *(DB->CurBlk + i*TSIZE + j) - *(DB->Past_Reconstructed + ((Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)) + (y*ROW) + x + (ROW *i) + j);
							SAD += abs(*(differ + i*TSIZE + j) * *(differ + i*TSIZE + j)); //������ �������Ѽ� ����
						}

						if(cnt == 0) // min �� ��Ǻ��� �ʱⰪ�� �����ϱ����� for���� ó�����ư��� ó���� SAD�� min����, y= -SR_H, x= -SR_W �� ��Ǻ��͸� �ʱⰪ���� ����.
						{
							min = SAD;
							DB->MV_Y = y;
					        DB->MV_X = x;
							for (i = 0; i < TSIZE; i++)
								for (j = 0; j < TSIZE; j++)
									*(DB->Inter_DifferBlk + i*TSIZE +j) = *(differ + i*TSIZE +j);
						}
						else // ���������� ã���� SAD���� ���� �������� SAD(min)���� ���� �� ��Ǻ��Ϳ� ������ ���� 
						{
							if( SAD < min ) //SAD
							{
								min = SAD;
								DB->MV_Y = y;
							    DB->MV_X = x;
								for (i = 0; i < TSIZE; i++)
									for (j = 0; j < TSIZE; j++)
										*(DB->Inter_DifferBlk + i*TSIZE +j) = *(differ + i*TSIZE +j);
							}
						}
						cnt++;
				}			
			}
		}


}

void Inter_Quantization( Buf *DB ) //�ð����� ����ȭ�ϴ� �Լ�
{
	int i, j;
	for (i = 0; i < TSIZE; i++)
		for (j = 0; j < TSIZE; j++)
			*(DB->Inter_quantization + i*TSIZE + j) = *(DB->Inter_DifferBlk + i*TSIZE + j) / DB->QuantNum;

}
void Inter_InQuantization( Buf *DB ) //�ð����� ������ȭ�ϴ� �Լ�
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
void Inter_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col) //�ð����� reconstruct(�����ȵ�����)���ϴ� �Լ�
{
	int i,j;
	int temp;

	for(i = 0 ; i < TSIZE ; i++)
		for(j = 0 ; j <TSIZE ; j++)
		{
			//search range���� ã�� ���� ���������� ���� ������ ��Ǻ��͸� �̿��Ͽ� 16*16�������� MoveCompensatedBlk ���� ���� ����.
			//���� = ������ȭ + ��Ǻ��ͷ� ã�� �������� ����� ��
			*(DB->MoveCompensatedBlk + i*TSIZE + j) = *(DB->Past_Reconstructed + ((Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)) + (DB->MV_Y*ROW) + DB->MV_X + (ROW *i) + j);
			temp =   *(DB->Inter_inquantization + i*TSIZE +j) + *(DB->MoveCompensatedBlk + i*TSIZE +j);
			temp = temp > 255 ? 255 : temp < 0 ? 0 : temp; //Ŭ����
			*(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE)+ (Blk_Row*TSIZE)+ i*ROW+ j) =  temp;		
		}	
}



