#include "buf.h"

void Decoder(Buf *DB)
{

	int i, j, Blk_Row, Blk_Col; //  Blk_Row, Blk_Col : 720*480������ 16*16������ ���������� �� ����,���� �ε���
	int Buf_Blk_Row, Buf_Blk_Col; // 16*16���� 4*4������ ���������� �� ����,���� �ε���
	int FlagCnt[9] = {0}; // ��尳���� �������� ����
	int FlagBlk[ BUFSIZE*BUFSIZE ] = {0};// 16*16���� 4*4������ �������� 16���� ���� �����µ�, �׶� �� ������带 ����.
	int MV_SUM = 0 ; //��Ǻ��� ��. 
	int intra_or_inter; // ������������ �ð��������� ���ڴ����� �о�� ���� �����ϴ� flag����
	int Inter_Coded_cnt=0; // �ð����� �� ����
	int Intra_Coded_cnt=0; // �������� �� ���� 

	FILE *fp, *qp, *op ,*sp, *np;
	fopen_s( &sp, "intra or inter.txt", "rb" );	
	fopen_s( &qp, "intra mode flag.txt","rb" );
	fopen_s( &fp, "intra encoder result.txt", "rb" );	
	fopen_s( &op, "inter encoder result.txt", "rb" );
	fopen_s( &np, "decoded result.img", "wb" );

	//720*480�� 16*16������� ���ڵ�.
	for (Blk_Col = 0; Blk_Col < (COL) / TSIZE; Blk_Col++)
	{
		for (Blk_Row = 0; Blk_Row < (ROW) / TSIZE; Blk_Row++)
		{
			fscanf(sp, "%d ", &intra_or_inter); // ���Ͽ��� �������� �ð����� �о��

			if(intra_or_inter == 0) // �����̸� 
			{
				Intra_Coded_cnt++; // �������� ���� ++

				for(i = 0; i<TSIZE ; i++)
					for(j=0; j<TSIZE; j++)
						fscanf(fp, "%d ", &*(DB->Intra_Transfer_quantization +i*TSIZE +j)); //16*16���� ����ȭ�� ������ ����

				 //16*16����� 4*4�� ���ڵ� 
				for (Buf_Blk_Col = 0; Buf_Blk_Col < TSIZE/BUFSIZE; Buf_Blk_Col++)
					for (Buf_Blk_Row = 0; Buf_Blk_Row < TSIZE/BUFSIZE; Buf_Blk_Row++)
					{
						fscanf(qp, "%d ", &DB->Flag); //��� �о�� 

						//16*16 ���� ����� ����ȭ �����͸� 4*4 ����ȭ ���� �ű�.
						for(i =0; i<BUFSIZE; i++)
							for(j=0; j<BUFSIZE; j++)
								*(DB->Intra_quantization + i*BUFSIZE +j) = *(DB->Intra_Transfer_quantization + (Buf_Blk_Col*TSIZE*BUFSIZE) + (Buf_Blk_Row*TSIZE) + i*BUFSIZE + j) ;

						Intra_InQuantization(DB); // ������ȭ
						Intra_Reconstruct(DB, Blk_Row*BUFSIZE + Buf_Blk_Row, Blk_Col*BUFSIZE + Buf_Blk_Col); 
						//����, �� �ε����� �μ��� ������ ��  720*480 ���󿡼� 4*4���� �ε�����  �μ��� ����,�׷��� Blk_Row*BUFSIZE + Buf_Blk_Row, Blk_Col*BUFSIZE + Buf_Blk_Col��
						*(FlagBlk + BUFSIZE*Buf_Blk_Col + Buf_Blk_Row) = DB->Flag; // ��带 FlagBlk �迭�� ����

					}

					for(i = 0 ; i < TSIZE ; i++)//
						for(j = 0 ; j < TSIZE ; j++)//
						{    //���������� ������  �� ������ ���ڴ��� ���������� �ð������� �������� ���������� �������� �����Ͽ� ���� reconstructed�� ����
							*(DB->Inter_Reconstructed + (Blk_Col*TSIZE*ROW) + (Blk_Row*TSIZE)+ i*ROW+ j)=*(DB->Intra_Reconstructed + (Blk_Col*TSIZE*ROW) + (Blk_Row*TSIZE)+ i*ROW+ j);
							*(DB->Output + (Blk_Col*TSIZE*ROW) + (Blk_Row*TSIZE)+ i*ROW+ j ) = *(DB->Intra_Reconstructed + (Blk_Col*TSIZE*ROW) + (Blk_Row*TSIZE)+ i*ROW+ j);
						}
						for(i=0 ; i<BUFSIZE*BUFSIZE ; i++)
						{
							if(*(FlagBlk + i) == 0)     *( FlagCnt+0) +=1;
							else if(*(FlagBlk + i) == 1) *( FlagCnt+1) +=1;
							else if(*(FlagBlk + i) == 2) *( FlagCnt+2) +=1;
							else if(*(FlagBlk + i) == 3) *( FlagCnt+3) +=1;
							else if(*(FlagBlk + i) == 4) *( FlagCnt+4) +=1;
							else if(*(FlagBlk + i) == 5) *( FlagCnt+5) +=1;
							else if(*(FlagBlk + i) == 6) *( FlagCnt+6) +=1;
							else if(*(FlagBlk + i) == 7) *( FlagCnt+7) +=1;
							else if(*(FlagBlk + i) == 8) *( FlagCnt+8) +=1;
						}

			}

			else if(intra_or_inter == 1) //�ð��̸�
			{
				Inter_Coded_cnt++; //�ð����� ���� ++
				fscanf(op, "%d ", &DB->MV_Y); //��Ǻ��� �о����
				fscanf(op, "%d ", &DB->MV_X);
				for (i = 0; i < TSIZE; i++)
					for (j = 0; j < TSIZE; j++)
					{
						fscanf(op, "%d ", &*(DB->Inter_quantization + i*TSIZE +j)); //����ȭ ������ �о����
					}

					Inter_InQuantization(DB); //������ȭ
					Inter_Reconstruct(DB,Blk_Row, Blk_Col); //����
					MV_SUM += abs(DB->MV_Y) + abs(DB->MV_X); //��Ǻ��� ���밪 ��

					for (i = 0; i < TSIZE; i++)
						for (j = 0; j < TSIZE; j++)
						{
							 //�ð������� ������  �� ������ ���ڴ��� ���������� ���������� �������� �ð������� �������� �����Ͽ� ���� reconstructed�� ����
							*(DB->Output + (Blk_Col*ROW*TSIZE)+ (Blk_Row*TSIZE)+ i*ROW+ j) =  *(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE)+ (Blk_Row*TSIZE)+ i*ROW+ j);	
							*(DB->Intra_Reconstructed + (Blk_Col*TSIZE*ROW) + (Blk_Row*TSIZE)+ i*ROW+ j)=*(DB->Inter_Reconstructed + (Blk_Col*TSIZE*ROW) + (Blk_Row*TSIZE)+ i*ROW+ j);
						}
			}
		}
	}

	printf("��Ǻ��� ���밪�� �� : %d\n", MV_SUM);
	printf("Intra Coded Block ���� : %d\n\n",Intra_Coded_cnt);
	printf("Inter Coded Block ���� : %d\n\n",Inter_Coded_cnt);

	for(i=0 ; i < 9 ; i++)
		printf("��� %d�� ���� : %d\n",i,*( FlagCnt + i));


	fwrite( DB->Output, sizeof(unsigned char), ROW*COL, np );


	fclose(fp);
	fclose(qp);
	fclose(op);
	fclose(sp);
	fclose(np);

}


void Before_Intra_Decoder(Buf *DB)
{

	int i, j, Blk_Row, Blk_Col;
	int  FlagCnt[9] = {0};
	FILE *fp;
	fopen_s( &fp, "before_encoder_result.txt", "rb" );	

	for (Blk_Col = 0; Blk_Col < (COL) / BUFSIZE; Blk_Col++)
	{
		for (Blk_Row = 0; Blk_Row < (ROW) / BUFSIZE; Blk_Row++)
		{

			fscanf(fp, "%d ", &DB->Flag);
			for(i =0; i<BUFSIZE; i++)
				for(j=0; j<BUFSIZE; j++)
					fscanf(fp, "%d ", &(*(DB->Intra_quantization + i*BUFSIZE +j)));

			Intra_InQuantization(DB);
			Intra_Reconstruct(DB,Blk_Row, Blk_Col);


			if(DB->Flag == 0)     *( FlagCnt+0) +=1;
			else if(DB->Flag ==1) *( FlagCnt+1) +=1;
			else if(DB->Flag ==2) *( FlagCnt+2) +=1;
			else if(DB->Flag ==3) *( FlagCnt+3) +=1;
			else if(DB->Flag ==4) *( FlagCnt+4) +=1;
			else if(DB->Flag ==5) *( FlagCnt+5) +=1;
			else if(DB->Flag ==6) *( FlagCnt+6) +=1;
			else if(DB->Flag ==7) *( FlagCnt+7) +=1;
			else if(DB->Flag ==8) *( FlagCnt+8) +=1;


		}
	}

	for (i = 0; i < COL; i++)
		for (j = 0; j < ROW; j++)
		{
			*(DB->Past_Reconstructed + i*ROW +j) = *(DB->Intra_Reconstructed + i*ROW + j);
		}

		for(i=0 ; i < 9 ; i++)
			printf("��� %d�� ���� : %d\n",i,*( FlagCnt + i));

		fclose(fp);

}
