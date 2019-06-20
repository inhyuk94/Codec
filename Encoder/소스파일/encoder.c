#include "buf.h"

void Encoder(Buf *DB)
{

	int i, j, Blk_Row, Blk_Col; // Blk_Row, Blk_Col : 720*480������ 16*16������ ���������� �� ����,���� �ε���
	int Buf_Blk_Row, Buf_Blk_Col; // 16*16���� 4*4������ ���������� �� ����,���� �ε���
	int FlagCnt[9] = {0}; // ��尳���� �������� ����
	int FlagBlk[ BUFSIZE*BUFSIZE ] = {0}; // 16*16���� 4*4������ �������� 16���� ���� �����µ�, �׶� �� ������带 ����.
	int MV_SUM = 0 ; //��Ǻ��� ��.
	int Intra_errorsum=0; //�������� ������
	int Inter_errorsum=0; //�ð����� ������
	int Inter_Coded_cnt=0; // �ð����� �� ����
	int Intra_Coded_cnt=0; // �������� �� ���� 

	FILE *fp, *qp, *op ,*sp, *np;
	fopen_s( &sp, "intra or inter.txt", "wb" );	
	fopen_s( &qp, "intra mode flag.txt","wb" );
	fopen_s( &fp, "intra encoder result.txt", "wb" );	
	fopen_s( &op, "inter encoder result.txt", "wb" );
	fopen_s( &np, "After_reconstructed result.y", "wb" );

	//720*480�� 16*16������� ���ڵ�.
	for (Blk_Col = 0; Blk_Col < (COL) / TSIZE; Blk_Col++)
	{
		for (Blk_Row = 0; Blk_Row < (ROW) / TSIZE; Blk_Row++)
		{

			for (i = 0; i < TSIZE; i++)
				for (j = 0; j < TSIZE; j++)
				{   //16*16������� ���ڵ�
					*(DB->CurBlk + i*TSIZE + j) = *(DB->Input +(Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE) + (ROW *i) + j);
				}

				for (Buf_Blk_Col = 0; Buf_Blk_Col < TSIZE/BUFSIZE; Buf_Blk_Col++) //16*16���� 4*4������� ���ڵ� , 16*16���� 4*4�� �ɰ� ���������ϱ� ���� �ڵ�
					for (Buf_Blk_Row = 0; Buf_Blk_Row < TSIZE/BUFSIZE; Buf_Blk_Row++)
					{
						for (i = 0; i < BUFSIZE; i++)
							for (j = 0; j < BUFSIZE; j++)
							{   //16*16����� 4*4�� ���ڵ� 
								*(DB->Intra_CurBlk + i*BUFSIZE + j) = *(DB->CurBlk + (Buf_Blk_Col*TSIZE*BUFSIZE) + (Buf_Blk_Row*BUFSIZE) + i*TSIZE + j);
							}

							Intra_Difference(DB, Blk_Row*BUFSIZE + Buf_Blk_Row , Blk_Col*BUFSIZE + Buf_Blk_Col);  //�������� ������,flag����
							Intra_Quantization(DB); //����ȭ
							Intra_InQuantization(DB); //������ȭ
							//����, �� �ε����� �μ��� ������ ��  720*480 ���󿡼� 4*4���� �ε�����  �μ��� ����,�׷��� Blk_Row*BUFSIZE + Buf_Blk_Row, Blk_Col*BUFSIZE + Buf_Blk_Col��
							Intra_Reconstruct(DB,Blk_Row*BUFSIZE + Buf_Blk_Row, Blk_Col*BUFSIZE + Buf_Blk_Col); // ����
							*(FlagBlk + BUFSIZE*Buf_Blk_Col + Buf_Blk_Row) = DB->Flag; // ��带 FlagBlk �迭�� ����



							//16*16�������� ���ڴ��� ������ ����ȭ�� ������ 4*4 �������� ����ȭ�� �� 16���� �� �迭�� ����.
							for (i = 0; i < BUFSIZE; i++)
								for (j = 0; j < BUFSIZE; j++)
									*(DB->Intra_Transfer_quantization + (Buf_Blk_Col*TSIZE*BUFSIZE) + (Buf_Blk_Row*TSIZE) + i*BUFSIZE + j) = *(DB->Intra_quantization + i*BUFSIZE + j);

					}

					Inter_Difference(DB, Blk_Row, Blk_Col); //�������� ������, ��Ǻ��� ���ϴ� �Լ�
					Inter_Quantization(DB); //����ȭ
					Inter_InQuantization(DB); //������ȭ
					Inter_Reconstruct(DB,Blk_Row, Blk_Col); //����
					
					

					//Select() intra or inter ����
					Intra_errorsum=0;
					Inter_errorsum=0;
					for (i = 0; i < TSIZE; i++)
						for (j = 0; j < TSIZE; j++)
						{   // ����  = (��ǲ-����)^2
							Intra_errorsum +=  pow((*(DB->Input +(Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE) + (ROW *i) + j) - *(DB->Intra_Reconstructed + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j )),2.0);
							Inter_errorsum +=  pow((*(DB->Input +(Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE) + (ROW *i) + j) - *(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j )),2.0);
						}

						if(Intra_errorsum < Inter_errorsum) //���������� ������ �� ���� ��
						{
							fprintf(sp, "%d ", 0); // ������������ �ĺ����ִ� 0 �� ���Ͽ� ����
							Intra_Coded_cnt++; // ������������ �ڵ��� �� ���� ++
							for(i=0; i< BUFSIZE*BUFSIZE ; i++)
							{
								fprintf(qp, "%d ",FlagBlk[i] ); // �������� ��带 �����ϴ� ���Ͽ� ����
								
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
							for(i =0; i<TSIZE; i++)
								for(j=0; j<TSIZE; j++)
								{								
									fprintf(fp, "%d ", *(DB->Intra_Transfer_quantization + i*TSIZE +j)); //����ȭ ������ ����
									//���������� ������ �������� �ð������� recunstructed���� ���������� reconstruct�� �����͸� �����Ͽ� ���ŵ� reconstructed�����͸� ����Ѵ�.
									*(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j ) = *(DB->Intra_Reconstructed + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j );
									*(DB->Output + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j ) = *(DB->Intra_Reconstructed + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j );
								}
						}

						else  //�ð������� ������ �� ���� ��
						{

							MV_SUM += ( abs(DB->MV_Y) + abs(DB->MV_X) ); //��Ǻ��� ���밪 ��
							Inter_Coded_cnt++;// �ð��������� �ڵ��� �� ���� ++

							fprintf(sp, "%d ", 1); // �ð��������� �ĺ����ִ� 0 �� ���Ͽ� ����
							fprintf(op, "%d ", DB->MV_Y); //��Ǻ��� ����
							fprintf(op, "%d ", DB->MV_X);
							for(i =0; i<TSIZE; i++)
								for(j=0; j<TSIZE; j++)
								{
									fprintf(op, "%d ", *(DB->Inter_quantization + i*TSIZE +j) );
									//�ð������� ������ �������� ���������� recunstructed���� �ð������� reconstruct�� �����͸� �����Ͽ� ���ŵ� reconstructed�����͸� ����Ѵ�.
									*(DB->Intra_Reconstructed + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j ) = *(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j );
									*(DB->Output + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j ) = *(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE) + (Blk_Row*TSIZE)+ i*ROW+ j );
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

void Before_Intra_Encoder(Buf *DB)
{

	int i, j, Blk_Row, Blk_Col;
	int  FlagCnt[9] = {0};
	FILE *fp, *op;
	fopen_s( &fp, "before_encoder_result.txt", "wb" );	
	fopen_s( &op, "Before_Intra_Reconstructed_football.y", "wb" );

	for (Blk_Col = 0; Blk_Col < (COL) / BUFSIZE; Blk_Col++)
	{
		for (Blk_Row = 0; Blk_Row < (ROW) / BUFSIZE; Blk_Row++)
		{

			for (i = 0; i < BUFSIZE; i++)
			{
				for (j = 0; j < BUFSIZE; j++)
				{
					*(DB->Intra_CurBlk + i*BUFSIZE + j) = *(DB->PastInput +(Blk_Col*ROW*BUFSIZE) + (Blk_Row*BUFSIZE) + (ROW *i) + j);
				}
			}

			Intra_Difference(DB, Blk_Row, Blk_Col);
			Intra_Quantization(DB);
			Intra_InQuantization(DB);
			Intra_Reconstruct(DB,Blk_Row, Blk_Col);

			fprintf(fp, "%d ", DB->Flag);
			for(i =0; i<BUFSIZE; i++)
				for(j=0; j<BUFSIZE; j++)
					fprintf(fp, "%d ", *(DB->Intra_quantization + i*BUFSIZE +j));

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


		fwrite( DB->Past_Reconstructed, sizeof(unsigned char), ROW*COL, op );

		fclose(fp);
		fclose(op);

}

