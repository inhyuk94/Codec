#include "buf.h"

void BufCon( Buf *DB, int OrderFlag )
{
	if( OrderFlag )
	{
		FILE *fp,*op;
		fopen_s( &fp, "football(720x480)_after.y", "rb" );	
		fopen_s( &op, "football(720x480)_before.y", "rb" );


		DB->Input         = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char)); //after영상
		DB->PastInput = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));	//before영상
		DB->CurBlk	      = (unsigned char*)calloc(TSIZE*TSIZE, sizeof(unsigned char)); //Input영상의 16*16블럭
		DB->Output         = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));

		DB->Inter_Reconstructed = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char)); //시간예측의 리컨된 영상 720*480
		DB->Inter_DifferBlk     = (int*)calloc(TSIZE*TSIZE, sizeof(int)); //시간예측의 잔차블럭
		DB->Inter_quantization = (int*)calloc(TSIZE*TSIZE, sizeof(int)); //시간예측 양자화블럭
		DB->Inter_inquantization = (double*)calloc(TSIZE*TSIZE, sizeof(double)); //시간예측 역양자화블럭
		DB->Past_Reconstructed = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));
		DB->MoveCompensatedBlk = (unsigned char*)calloc(TSIZE*TSIZE, sizeof(unsigned char));


		DB->Intra_Reconstructed = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));
		DB->Intra_DifferBlk     = (int*)calloc(BUFSIZE*BUFSIZE, sizeof(int));
		DB->Intra_CurBlk	      = (unsigned char*)calloc(BUFSIZE*BUFSIZE, sizeof(unsigned char));
		DB->Intra_predict       = (unsigned char*)calloc(BUFSIZE*BUFSIZE, sizeof(unsigned char));
		DB->Intra_quantization = (int*)calloc(BUFSIZE*BUFSIZE, sizeof(int));
		DB->Intra_inquantization = (double*)calloc(BUFSIZE*BUFSIZE, sizeof(double));

		DB->Intra_Transfer_quantization = (int*)calloc(TSIZE*TSIZE, sizeof(int));

		fread( DB->Input, sizeof(unsigned char), ROW*COL, fp );
		fread( DB->PastInput, sizeof(unsigned char), ROW*COL, op );


		fclose(fp);
		fclose(op);
		
	}	
	else
	{
	    free(DB->Input);       
		free(DB->PastInput); 
		free(DB->CurBlk);	
		free(DB->Output);

		free(DB->Inter_Reconstructed); 
		free(DB->Inter_DifferBlk);    
			      
		free(DB->Inter_quantization); 
		free(DB->Inter_inquantization); 
		free(DB->Past_Reconstructed); 
		free(DB->MoveCompensatedBlk); 

		free(DB->Intra_Reconstructed); 
		free(DB->Intra_DifferBlk);     
		free(DB->Intra_CurBlk);	     
		free(DB->Intra_predict);     
		free(DB->Intra_quantization); 
		free(DB->Intra_inquantization);

		free(DB->Intra_Transfer_quantization);

		

	}
}