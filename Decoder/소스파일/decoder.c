#include "buf.h"

void Decoder(Buf *DB)
{

	int i, j, Blk_Row, Blk_Col; //  Blk_Row, Blk_Col : 720*480영상을 16*16블럭으로 나눴을때의 블럭 가로,세로 인덱스
	int Buf_Blk_Row, Buf_Blk_Col; // 16*16블럭을 4*4블럭으로 나눴을떄의 블럭 가로,세로 인덱스
	int FlagCnt[9] = {0}; // 모드개수를 세기위한 변수
	int FlagBlk[ BUFSIZE*BUFSIZE ] = {0};// 16*16블럭을 4*4블럭으로 나눴을때 16개의 블럭이 나오는데, 그때 각 예측모드를 저장.
	int MV_SUM = 0 ; //모션벡터 합. 
	int intra_or_inter; // 공간예측인지 시간예측인지 디코더에서 읽어온 것을 저장하는 flag변수
	int Inter_Coded_cnt=0; // 시간예측 블럭 개수
	int Intra_Coded_cnt=0; // 공간예측 블럭 개수 

	FILE *fp, *qp, *op ,*sp, *np;
	fopen_s( &sp, "intra or inter.txt", "rb" );	
	fopen_s( &qp, "intra mode flag.txt","rb" );
	fopen_s( &fp, "intra encoder result.txt", "rb" );	
	fopen_s( &op, "inter encoder result.txt", "rb" );
	fopen_s( &np, "decoded result.img", "wb" );

	//720*480을 16*16사이즈로 블럭코딩.
	for (Blk_Col = 0; Blk_Col < (COL) / TSIZE; Blk_Col++)
	{
		for (Blk_Row = 0; Blk_Row < (ROW) / TSIZE; Blk_Row++)
		{
			fscanf(sp, "%d ", &intra_or_inter); // 파일에서 공간인지 시간인지 읽어옴

			if(intra_or_inter == 0) // 공간이면 
			{
				Intra_Coded_cnt++; // 공간예측 개수 ++

				for(i = 0; i<TSIZE ; i++)
					for(j=0; j<TSIZE; j++)
						fscanf(fp, "%d ", &*(DB->Intra_Transfer_quantization +i*TSIZE +j)); //16*16블럭에 양자화된 데이터 저장

				 //16*16사이즈를 4*4로 블럭코딩 
				for (Buf_Blk_Col = 0; Buf_Blk_Col < TSIZE/BUFSIZE; Buf_Blk_Col++)
					for (Buf_Blk_Row = 0; Buf_Blk_Row < TSIZE/BUFSIZE; Buf_Blk_Row++)
					{
						fscanf(qp, "%d ", &DB->Flag); //모드 읽어옴 

						//16*16 블럭에 저장된 양자화 데이터를 4*4 양자화 블럭에 옮김.
						for(i =0; i<BUFSIZE; i++)
							for(j=0; j<BUFSIZE; j++)
								*(DB->Intra_quantization + i*BUFSIZE +j) = *(DB->Intra_Transfer_quantization + (Buf_Blk_Col*TSIZE*BUFSIZE) + (Buf_Blk_Row*TSIZE) + i*BUFSIZE + j) ;

						Intra_InQuantization(DB); // 역양자화
						Intra_Reconstruct(DB, Blk_Row*BUFSIZE + Buf_Blk_Row, Blk_Col*BUFSIZE + Buf_Blk_Col); 
						//복원, 블럭 인덱스를 인수로 전달할 떄  720*480 영상에서 4*4블럭의 인덱스를  인수로 전달,그래서 Blk_Row*BUFSIZE + Buf_Blk_Row, Blk_Col*BUFSIZE + Buf_Blk_Col임
						*(FlagBlk + BUFSIZE*Buf_Blk_Col + Buf_Blk_Row) = DB->Flag; // 모드를 FlagBlk 배열에 저장

					}

					for(i = 0 ; i < TSIZE ; i++)//
						for(j = 0 ; j < TSIZE ; j++)//
						{    //공간예측의 에러가  더 작을때 인코더와 마찬가지로 시간예측의 리컨블럭에 공간예측의 리컨블럭을 복사하여 최종 reconstructed로 갱신
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

			else if(intra_or_inter == 1) //시간이면
			{
				Inter_Coded_cnt++; //시간예측 개수 ++
				fscanf(op, "%d ", &DB->MV_Y); //모션벡터 읽어오기
				fscanf(op, "%d ", &DB->MV_X);
				for (i = 0; i < TSIZE; i++)
					for (j = 0; j < TSIZE; j++)
					{
						fscanf(op, "%d ", &*(DB->Inter_quantization + i*TSIZE +j)); //양자화 데이터 읽어오기
					}

					Inter_InQuantization(DB); //역양자화
					Inter_Reconstruct(DB,Blk_Row, Blk_Col); //복원
					MV_SUM += abs(DB->MV_Y) + abs(DB->MV_X); //모션벡터 절대값 합

					for (i = 0; i < TSIZE; i++)
						for (j = 0; j < TSIZE; j++)
						{
							 //시간예측의 에러가  더 작을때 인코더와 마찬가지로 공간예측의 리컨블럭에 시간예측의 리컨블럭을 복사하여 최종 reconstructed로 갱신
							*(DB->Output + (Blk_Col*ROW*TSIZE)+ (Blk_Row*TSIZE)+ i*ROW+ j) =  *(DB->Inter_Reconstructed + (Blk_Col*ROW*TSIZE)+ (Blk_Row*TSIZE)+ i*ROW+ j);	
							*(DB->Intra_Reconstructed + (Blk_Col*TSIZE*ROW) + (Blk_Row*TSIZE)+ i*ROW+ j)=*(DB->Inter_Reconstructed + (Blk_Col*TSIZE*ROW) + (Blk_Row*TSIZE)+ i*ROW+ j);
						}
			}
		}
	}

	printf("모션벡터 절대값의 합 : %d\n", MV_SUM);
	printf("Intra Coded Block 개수 : %d\n\n",Intra_Coded_cnt);
	printf("Inter Coded Block 개수 : %d\n\n",Inter_Coded_cnt);

	for(i=0 ; i < 9 ; i++)
		printf("모드 %d의 개수 : %d\n",i,*( FlagCnt + i));


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
			printf("모드 %d의 개수 : %d\n",i,*( FlagCnt + i));

		fclose(fp);

}
