#include "buf.h"

void Intra_prediction(Buf *DB, int Mode, int Blk_Row, int Blk_Col) //공간예측 예측블럭 구하는 함수
{
	int i, j;
	unsigned char A,B,C,D,E,F,G,H,I,J,K,L,Q; //블럭 밖의 위,왼쪽으로 가장 근접하는 픽셀 변수명들

  	
	if( Blk_Col*BUFSIZE -1 < 0 &&  Blk_Row*BUFSIZE -1 <0) // 720*480사이즈의 영상에서 0번쨰 블럭일때 
	{
		A = 128; B = 128; C = 128; D = 128; 
		E = 128; F = 128; G = 128; H = 128; 
		I = 128; J = 128; K= 128; L = 128; Q= 128;
	}
	else if( Blk_Col*BUFSIZE -1 < 0) // 블럭이 가장 위인 0번째 행에 해당될 때
	{
		A = 128; B = 128; C = 128; D = 128; E = 128; F = 128; G = 128; H = 128; Q = 128;
		I = *(DB->Intra_Reconstructed + ((Blk_Row - 1)*BUFSIZE) + (ROW*0) + (BUFSIZE - 1));
		J = *(DB->Intra_Reconstructed + ((Blk_Row - 1)*BUFSIZE) + (ROW*1) + (BUFSIZE - 1));
		K = *(DB->Intra_Reconstructed + ((Blk_Row - 1)*BUFSIZE) + (ROW*2) + (BUFSIZE - 1));
		L = *(DB->Intra_Reconstructed + ((Blk_Row - 1)*BUFSIZE) + (ROW*3) + (BUFSIZE - 1));

	}
	else if( Blk_Row*BUFSIZE -1 < 0) // 블럭이 가장 왼쪽인 0번쨰 열에 해당될 때
	{
		I = 128; J = 128; K= 128; L = 128; Q= 128;
		A = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 0);
		B = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 1);
		C = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 2);
		D = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 3);
		E = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 4);
		F = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 5);
		G = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 6);
		H = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 7);
	}
	else if( (Blk_Row+1)*BUFSIZE > ROW-1) //블럭이 가장 오른쪽 열에 해당될 때
	{

		Q = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) -1);
		A = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) +0);
		B = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) +1);
		C = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) +2);
		D = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) +3);
		I = *(DB->Intra_Reconstructed + (Blk_Col*(ROW)*BUFSIZE) + ((Blk_Row - 1)*BUFSIZE) + (ROW*0) + (BUFSIZE - 1));
		J = *(DB->Intra_Reconstructed + (Blk_Col*(ROW)*BUFSIZE) + ((Blk_Row - 1)*BUFSIZE) + (ROW*1) + (BUFSIZE - 1));
		K = *(DB->Intra_Reconstructed + (Blk_Col*(ROW)*BUFSIZE) + ((Blk_Row - 1)*BUFSIZE) + (ROW*2) + (BUFSIZE - 1));
		L = *(DB->Intra_Reconstructed + (Blk_Col*(ROW)*BUFSIZE) + ((Blk_Row - 1)*BUFSIZE) + (ROW*3) + (BUFSIZE - 1));
		E = D; 
		F = D;
		G = D; 
		H = D;
	}
	else //그 외 
	{
		A = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 0);
		B = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 1);
		C = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 2);
		D = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 3);
		E = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 4);
		F = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 5);
		G = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 6);
		H = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) + 7);
		I = *(DB->Intra_Reconstructed + (Blk_Col*(ROW)*BUFSIZE) + ((Blk_Row - 1)*BUFSIZE) + (ROW*0) + (BUFSIZE - 1));
		J = *(DB->Intra_Reconstructed + (Blk_Col*(ROW)*BUFSIZE) + ((Blk_Row - 1)*BUFSIZE) + (ROW*1) + (BUFSIZE - 1));
		K = *(DB->Intra_Reconstructed + (Blk_Col*(ROW)*BUFSIZE) + ((Blk_Row - 1)*BUFSIZE) + (ROW*2) + (BUFSIZE - 1));
		L = *(DB->Intra_Reconstructed + (Blk_Col*(ROW)*BUFSIZE) + ((Blk_Row - 1)*BUFSIZE) + (ROW*3) + (BUFSIZE - 1));
		Q = *(DB->Intra_Reconstructed + ((Blk_Col - 1)*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + ((ROW)*(BUFSIZE - 1)) -1);

	}

	
	// H.264의 9가지 예측모드 //

	if (Mode == 0) //수직
	{

		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if(j==0)
					*(DB->Intra_predict + i*BUFSIZE + j) = A;
				else if(j==1)
					*(DB->Intra_predict + i*BUFSIZE + j) = B;
				else if(j==2)
					*(DB->Intra_predict + i*BUFSIZE + j) = C;
				else if(j==3)
					*(DB->Intra_predict + i*BUFSIZE + j) = D;
			}
	}

	else if (Mode == 1) //수평
	{

		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if( i==0)
					*(DB->Intra_predict + i*BUFSIZE + j) = I;
				else if(i==1)
					*(DB->Intra_predict + i*BUFSIZE + j) = J;
				else if(i==2)
					*(DB->Intra_predict + i*BUFSIZE + j) = K;
				else if(i==3)
					*(DB->Intra_predict + i*BUFSIZE + j) = L;
			}
	}

	else if (Mode == 2) // DC예측
	{
		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if(Blk_Col == 0 && Blk_Row == 0)
					*(DB->Intra_predict + i*BUFSIZE + j) = 128;
				else if(Blk_Col == 0 )
					*(DB->Intra_predict + i*BUFSIZE + j) = (I + J + K + L + 2)/4;
				else if(Blk_Row == 0 )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + B + C + D + 2 )/4;
				else
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + B + C + D + I + J + K + L +4)/8;
			}
	}

	else if (Mode == 3) //대각 아래/왼쪽 예측
	{

		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if ( i+j == 0)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + 2*B + C + 2)/4;
				else if ( i+j == 1)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( B + 2*C + D + 2)/4;
				else if ( i+j == 2)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( C + 2*D + E + 2)/4;
				else if ( i+j == 3)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( D + 2*E + F + 2)/4;
				else if ( i+j == 4)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( E + 2*F + G + 2)/4;
				else if ( i+j == 5)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( F + 2*G + H + 2)/4;
				else if ( i+j == 6)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( G + 3*H + 2)/4;

			}

	}
	else if (Mode == 4) //대각 아래/오른쪽 예측
	{

		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if ( i-j == 3)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( J + 2*K + L + 2)/4;
				else if ( i-j == 2)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( I + 2*J + K + 2)/4;
				else if ( i-j == 1)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( Q + 2*I + J + 2)/4;
				else if ( i-j == 0)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + 2*Q + I + 2)/4;
				else if ( i-j == -1)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( Q + 2*A + B + 2)/4;
				else if ( i-j == -2)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + 2*B + C + 2)/4;
				else if ( i-j == -3)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( B + 2*C + D + 2)/4;

			}

	}
	else if(Mode == 5) // 수직 왼쪽 예측
	{
		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if ( i ==0 && j==0)
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + B+ 1 )/2;
				else if ( (i==0 && j==1) || (i==2 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( B + C + 1)/2;
				else if ( (i==0 && j==2) || (i==2 && j==1) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( C + D + 1)/2;
				else if ( (i==0 && j==3) || (i==2 && j==2) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( D + E + 1)/2;
				else if ( (i==2 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( E + F + 1)/2;
				else if ( (i==1 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + 2*B + C + 2)/4;
				else if ( (i==1 && j==1) || (i==3 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( B + 2*C + D + 2)/4;
				else if ( (i==1 && j==2) || (i==3 && j==1) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( C + 2*D + E + 2)/4;
				else if ( (i==1 && j==3) || (i==3 && j==2) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( D + 2*E + F + 2)/4;
				else if ( (i==3 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( E + 2*F + G + 2)/4;

			}
	}
	else if(Mode == 6) // 수평아래 예측
	{

		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if ( (i ==0 && j==0) || (i==1 && j==2))
					*(DB->Intra_predict + i*BUFSIZE + j) = ( Q + I + 1)/2;
				else if ( (i==0 && j==1) || (i==1 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( I + 2*Q + A + 2)/4;
				else if ( (i==0 && j==2) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( Q + 2*A + B + 2)/4;
				else if ( (i==0 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + 2*B + C + 2)/4;
				else if ( (i==1 && j==0) || (i==2 && j==2) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( I + J + 1)/2;
				else if ( (i==1 && j==1) || (i==2 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( Q + 2*I + J + 2)/4;
				else if ( (i==2 && j==0) || (i==3 && j==2) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( J + K + 1)/2;
				else if ( (i==2 && j==1) || (i==3 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( I + 2*J + K + 2)/4;
				else if ( (i==3 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( K + L + 1)/2;
				else if ( (i==3 && j==1) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( J + 2*K + L + 2)/4;

			}
	}
	else if(Mode == 7) // 수직 오른쪽 예측
	{

		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if ( (i ==0 && j==0) || (i==2 && j==1))
					*(DB->Intra_predict + i*BUFSIZE + j) = ( Q + A + 1)/2;
				else if ( (i==0 && j==1) || (i==2 && j==2) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + B + 1)/2;
				else if ( (i==0 && j==2) || (i==2 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( B + C + 1)/2;
				else if ( (i==0 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( C + D + 1)/2;
				else if ( (i==1 && j==0) || (i==3 && j==1) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( I + 2*Q + A + 2)/4;
				else if ( (i==1 && j==1) || (i==3 && j==2) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( Q + 2*A + B + 2)/4;
				else if ( (i==1 && j==2) || (i==3 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( A + 2*B + C + 2)/4;
				else if ( (i==1 && j==3) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( B + 2*C + D + 2)/4;
				else if ( (i==2 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( Q + 2*I + J + 2)/4;
				else if ( (i==3 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( I + 2*J + K + 2)/4;

			}
	}
	else if(Mode == 8) // 수평 위쪽 예측
	{

		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				if ( (i ==0 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( I + J + 1)/2;
				else if ( (i==0 && j==1) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( I + 2*J + K + 2)/4;
				else if ( (i==0 && j==2) || (i==1 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( J + K + 1)/2;
				else if ( (i==0 && j==3) || (i==1 && j==1) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( J + 2*K + L + 2)/4;
				else if ( (i==1 && j==2) || (i==2 && j==0) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( K + L + 1)/2;
				else if ( (i==1 && j==3) || (i==2 && j==1) )
					*(DB->Intra_predict + i*BUFSIZE + j) = ( K + 3*L + 2)/4;
				else 
					*(DB->Intra_predict + i*BUFSIZE + j) = L ; 


			}
	}

}
void Intra_Difference(Buf *DB, int Blk_Row, int Blk_Col) //공간예측 에러가 가장 적은 모드의 flag와 잔차블럭을 구하는 함수
{

	int mode, i, j;
	int SAD[9]={0}; // 9가지모드의 잔차제곱합,(버퍼로 사용)
	int min,minindex;
	int differ[9][BUFSIZE*BUFSIZE] = {0}; //9가지모드의 잔차블럭, (버퍼로사용). 

	for (mode = 0; mode < 9; mode++) //모든 (0~9) 예측모드의 잔차블럭과 에러값을 구하기위한 for문
	{
		Intra_prediction(DB, mode, Blk_Row, Blk_Col); 
		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				//잔차 = 인풋 - 예측
				*(*(differ+mode)+ i*BUFSIZE +j) = *(DB->Intra_CurBlk + i*BUFSIZE + j) - *(DB->Intra_predict + i*BUFSIZE + j); 
				*(SAD + mode) += (*(*(differ+mode)+ i*BUFSIZE +j)) * (*(*(differ+mode)+ i*BUFSIZE +j));  //제곱합(에러)
			}
	}

	//초기값 설정
	min = *(SAD+0); 
	minindex = 0;

	for (i = 1; i < 9; i++) // 잔차합이 가장 작은 모드구하기 
	{
		if (*(SAD+i) <= min)
		{
			min = *(SAD + i);
			minindex = i;
		}
	}

	DB->Flag = minindex; //에러가 가장 작은 모드를 Flag로 저장

	for(i=0;i <BUFSIZE; i++) 
		for(j=0; j<BUFSIZE; j++)
			*(DB->Intra_DifferBlk + i*BUFSIZE +j) = *(*(differ+minindex)+ i*BUFSIZE +j); //최소값 에러를 가진 모드에 해당하는 잔차블럭 저장 

}

void Intra_Quantization( Buf *DB)// 공간예측 양자화 하는 함수
{
	int i, j;
	for (i = 0; i < BUFSIZE; i++)
		for (j = 0; j < BUFSIZE; j++)
			*(DB->Intra_quantization + i*BUFSIZE + j) = *(DB->Intra_DifferBlk + i*BUFSIZE + j) / DB->QuantNum;
}
void Intra_InQuantization( Buf *DB)// 공간예측 역양자화 하는 함수
{
	int i, j;
	double temp;
	for (i = 0; i < BUFSIZE; i++)
		for (j = 0; j < BUFSIZE; j++)
		{
			temp = *(DB-> Intra_quantization+i*BUFSIZE + j) * DB->QuantNum;
			//반올림 math.h를 추가해도 round함수가 없어서 그냥 만듬
			if(temp < 0)       temp = temp - 0.5; 
			else if( temp > 0) temp = temp + 0.5; 
			*(DB->Intra_inquantization +i*BUFSIZE + j) = temp;
		}
}
void Intra_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col) //복원함수
{
	int i,j;
	int temp;

	Intra_prediction(DB, DB->Flag, Blk_Row, Blk_Col); //에러가 가장 작은 모드를 DB->flag 에 저장했었음. 이걸 예측함수에 전달하여 예측블럭을 구함

	for(i = 0 ; i < BUFSIZE ; i++)//
		for(j = 0 ; j < BUFSIZE ; j++)//
		{
			//복원 = 역양자화 + 예측
			temp = *(DB->Intra_inquantization + i*BUFSIZE + j) + *(DB->Intra_predict + i*BUFSIZE +j);
			temp = temp > 255 ? 255 : temp < 0 ? 0 : temp; //클리핑
			*(DB->Intra_Reconstructed + (Blk_Col*ROW*BUFSIZE) + (Blk_Row*BUFSIZE)+ i*ROW+ j )=  temp; 
		
		}	
}
