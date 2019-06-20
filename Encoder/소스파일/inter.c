#include "buf.h"

void Inter_Difference(Buf *DB, int Blk_Row, int Blk_Col) // 시간예측 모션벡터와 잔차블럭을 구하는 함수
{
	
	int i, j, x, y, min; //
	int differ[TSIZE*TSIZE] = {0} ; //가장적은 잔차블럭을 구하기위한 버퍼잔차블럭 
	int SAD = 0; //잔차값 제곱합 
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
							//현재 영상과 서치레인지에 해당하는 before의 복원된 영상과의 차이를 잔차블럭에 저장
							*(differ + i*TSIZE + j) = *(DB->CurBlk + i*TSIZE + j) - *(DB->Past_Reconstructed + ((Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)) + (y*ROW) + x + (ROW *i) + j);
							SAD += abs(*(differ + i*TSIZE + j) * *(differ + i*TSIZE + j)); //잔차값 제곱시켜서 더함
						}

						if(cnt == 0) // min 과 모션벡터 초기값을 저장하기위해 for문이 처음돌아갈때 처음의 SAD를 min으로, y= -SR_H, x= -SR_W 로 모션벡터를 초기값으로 저장.
						{
							min = SAD;
							DB->MV_Y = y;
					        DB->MV_X = x;
							for (i = 0; i < TSIZE; i++)
								for (j = 0; j < TSIZE; j++)
									*(DB->Inter_DifferBlk + i*TSIZE +j) = *(differ + i*TSIZE +j);
						}
						else // 범위내에서 찾을때 SAD값이 현재 가장작은 SAD(min)보다 작을 때 모션벡터와 잔차블럭 갱신 
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

void Inter_Quantization( Buf *DB ) //시간예측 양자화하는 함수
{
	int i, j;
	for (i = 0; i < TSIZE; i++)
		for (j = 0; j < TSIZE; j++)
			*(DB->Inter_quantization + i*TSIZE + j) = *(DB->Inter_DifferBlk + i*TSIZE + j) / DB->QuantNum;

}
void Inter_InQuantization( Buf *DB ) //시간예측 역양자화하는 함수
{
	int i, j;
	double temp;

	for (i = 0; i < TSIZE; i++)
		for (j = 0; j < TSIZE; j++)
			{
				temp = *(DB-> Inter_quantization+i*TSIZE + j) * DB->QuantNum;
				//반올림 math.h를 추가해도 round함수가 없어서 그냥 만듬
				if(temp < 0)       temp = temp - 0.5; 
				else if( temp > 0) temp = temp + 0.5; 
				*(DB->Inter_inquantization + i*TSIZE + j) = temp;
			}
}
void Inter_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col) //시간예측 reconstruct(복원된데이터)구하는 함수
{
	int i,j;
	int temp;

	for(i = 0 ; i < TSIZE ; i++)
		for(j = 0 ; j <TSIZE ; j++)
		{
			//search range에서 찾은 가장 잔차에러가 적은 영상의 모션벡터를 이용하여 16*16사이즈의 MoveCompensatedBlk 버퍼 블럭에 저장.
			//복원 = 역양자화 + 모션벡터로 찾은 움직임이 보상된 블럭
			*(DB->MoveCompensatedBlk + i*TSIZE + j) = *(DB->Past_Reconstructed + ((Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)) + (DB->MV_Y*ROW) + DB->MV_X + (ROW *i) + j);
			temp =   *(DB->Inter_inquantization + i*TSIZE +j) + *(DB->MoveCompensatedBlk + i*TSIZE +j);
			temp = temp > 255 ? 255 : temp < 0 ? 0 : temp; //클리핑
			*(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE)+ (Blk_Row*TSIZE)+ i*ROW+ j) =  temp;		
		}	
}



