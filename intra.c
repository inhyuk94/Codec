#include "buf.h"

void Intra_prediction(Buf *DB, int Mode, int Blk_Row, int Blk_Col) //�������� ������ ���ϴ� �Լ�
{
	int i, j;
	unsigned char A,B,C,D,E,F,G,H,I,J,K,L,Q; //�� ���� ��,�������� ���� �����ϴ� �ȼ� �������

  	
	if( Blk_Col*BUFSIZE -1 < 0 &&  Blk_Row*BUFSIZE -1 <0) // 720*480�������� ���󿡼� 0���� ���϶� 
	{
		A = 128; B = 128; C = 128; D = 128; 
		E = 128; F = 128; G = 128; H = 128; 
		I = 128; J = 128; K= 128; L = 128; Q= 128;
	}
	else if( Blk_Col*BUFSIZE -1 < 0) // ���� ���� ���� 0��° �࿡ �ش�� ��
	{
		A = 128; B = 128; C = 128; D = 128; E = 128; F = 128; G = 128; H = 128; Q = 128;
		I = *(DB->Intra_Reconstructed + ((Blk_Row - 1)*BUFSIZE) + (ROW*0) + (BUFSIZE - 1));
		J = *(DB->Intra_Reconstructed + ((Blk_Row - 1)*BUFSIZE) + (ROW*1) + (BUFSIZE - 1));
		K = *(DB->Intra_Reconstructed + ((Blk_Row - 1)*BUFSIZE) + (ROW*2) + (BUFSIZE - 1));
		L = *(DB->Intra_Reconstructed + ((Blk_Row - 1)*BUFSIZE) + (ROW*3) + (BUFSIZE - 1));

	}
	else if( Blk_Row*BUFSIZE -1 < 0) // ���� ���� ������ 0���� ���� �ش�� ��
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
	else if( (Blk_Row+1)*BUFSIZE > ROW-1) //���� ���� ������ ���� �ش�� ��
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
	else //�� �� 
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

	
	// H.264�� 9���� ������� //

	if (Mode == 0) //����
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

	else if (Mode == 1) //����
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

	else if (Mode == 2) // DC����
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

	else if (Mode == 3) //�밢 �Ʒ�/���� ����
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
	else if (Mode == 4) //�밢 �Ʒ�/������ ����
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
	else if(Mode == 5) // ���� ���� ����
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
	else if(Mode == 6) // ����Ʒ� ����
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
	else if(Mode == 7) // ���� ������ ����
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
	else if(Mode == 8) // ���� ���� ����
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
void Intra_Difference(Buf *DB, int Blk_Row, int Blk_Col) //�������� ������ ���� ���� ����� flag�� �������� ���ϴ� �Լ�
{

	int mode, i, j;
	int SAD[9]={0}; // 9��������� ����������,(���۷� ���)
	int min,minindex;
	int differ[9][BUFSIZE*BUFSIZE] = {0}; //9��������� ������, (���۷λ��). 

	for (mode = 0; mode < 9; mode++) //��� (0~9) ��������� �������� �������� ���ϱ����� for��
	{
		Intra_prediction(DB, mode, Blk_Row, Blk_Col); 
		for (i = 0; i < BUFSIZE; i++)
			for (j = 0; j < BUFSIZE; j++)
			{
				//���� = ��ǲ - ����
				*(*(differ+mode)+ i*BUFSIZE +j) = *(DB->Intra_CurBlk + i*BUFSIZE + j) - *(DB->Intra_predict + i*BUFSIZE + j); 
				*(SAD + mode) += (*(*(differ+mode)+ i*BUFSIZE +j)) * (*(*(differ+mode)+ i*BUFSIZE +j));  //������(����)
			}
	}

	//�ʱⰪ ����
	min = *(SAD+0); 
	minindex = 0;

	for (i = 1; i < 9; i++) // �������� ���� ���� ��屸�ϱ� 
	{
		if (*(SAD+i) <= min)
		{
			min = *(SAD + i);
			minindex = i;
		}
	}

	DB->Flag = minindex; //������ ���� ���� ��带 Flag�� ����

	for(i=0;i <BUFSIZE; i++) 
		for(j=0; j<BUFSIZE; j++)
			*(DB->Intra_DifferBlk + i*BUFSIZE +j) = *(*(differ+minindex)+ i*BUFSIZE +j); //�ּҰ� ������ ���� ��忡 �ش��ϴ� ������ ���� 

}

void Intra_Quantization( Buf *DB)// �������� ����ȭ �ϴ� �Լ�
{
	int i, j;
	for (i = 0; i < BUFSIZE; i++)
		for (j = 0; j < BUFSIZE; j++)
			*(DB->Intra_quantization + i*BUFSIZE + j) = *(DB->Intra_DifferBlk + i*BUFSIZE + j) / DB->QuantNum;
}
void Intra_InQuantization( Buf *DB)// �������� ������ȭ �ϴ� �Լ�
{
	int i, j;
	double temp;
	for (i = 0; i < BUFSIZE; i++)
		for (j = 0; j < BUFSIZE; j++)
		{
			temp = *(DB-> Intra_quantization+i*BUFSIZE + j) * DB->QuantNum;
			//�ݿø� math.h�� �߰��ص� round�Լ��� ��� �׳� ����
			if(temp < 0)       temp = temp - 0.5; 
			else if( temp > 0) temp = temp + 0.5; 
			*(DB->Intra_inquantization +i*BUFSIZE + j) = temp;
		}
}
void Intra_Reconstruct( Buf *DB, int Blk_Row, int Blk_Col) //�����Լ�
{
	int i,j;
	int temp;

	Intra_prediction(DB, DB->Flag, Blk_Row, Blk_Col); //������ ���� ���� ��带 DB->flag �� �����߾���. �̰� �����Լ��� �����Ͽ� �������� ����

	for(i = 0 ; i < BUFSIZE ; i++)//
		for(j = 0 ; j < BUFSIZE ; j++)//
		{
			//���� = ������ȭ + ����
			temp = *(DB->Intra_inquantization + i*BUFSIZE + j) + *(DB->Intra_predict + i*BUFSIZE +j);
			temp = temp > 255 ? 255 : temp < 0 ? 0 : temp; //Ŭ����
			*(DB->Intra_Reconstructed + (Blk_Col*ROW*BUFSIZE) + (Blk_Row*BUFSIZE)+ i*ROW+ j )=  temp; 
		
		}	
}
