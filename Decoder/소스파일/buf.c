#include "buf.h"

void BufCon( Buf *DB, int OrderFlag )
{
	if( OrderFlag )
	{
		FILE *fp,*op,*sp,*np;
		fopen_s( &fp, "football(720x480)_after.y", "rb" );	//psnr확인하기 위해서 after원본영상 
		fopen_s( &op, "football(720x480)_before.y", "rb" ); //psnr확인하기 위해서 befoer원본영상		
		fopen_s( &sp, "Before_Intra_Reconstructed_football.y", "rb" ); //미스매치 확인하기위한 인코더에서 before영상의 reconstructed 영상
		fopen_s( &np, "After_reconstructed result.y", "rb" ); // 미스매치 확인하기위한 인코더에서 after영상의 reconstructed 영상

		DB->Input         = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char)); //after영상
		DB->PastInput     = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));	//before영상
		DB->Output     = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));

		DB->Inter_Reconstructed   = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char)); //시간예측의 리컨된 영상 720*480
		DB->Inter_quantization    = (int*)calloc(TSIZE*TSIZE, sizeof(int)); //시간예측 양자화블럭
		DB->Inter_inquantization  = (double*)calloc(TSIZE*TSIZE, sizeof(double)); //시간예측 역양자화블럭
		DB->Past_Reconstructed    = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char)); //Before영상 디코딩된 데이터
		DB->MoveCompensatedBlk    = (unsigned char*)calloc(TSIZE*TSIZE, sizeof(unsigned char));

		DB->Intra_Reconstructed   = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));
		DB->Intra_predict         = (unsigned char*)calloc(BUFSIZE*BUFSIZE, sizeof(unsigned char));
		DB->Intra_quantization    = (int*)calloc(BUFSIZE*BUFSIZE, sizeof(int));
		DB->Intra_inquantization  = (double*)calloc(BUFSIZE*BUFSIZE, sizeof(double));

		DB->Before_Reconstructed    = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));
		DB->After_Reconstructed   = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));

		DB->Intra_Transfer_quantization = (int*)calloc(TSIZE*TSIZE, sizeof(int));
		

		fread( DB->Input, sizeof(unsigned char), ROW*COL, fp );
		fread( DB->PastInput, sizeof(unsigned char), ROW*COL, op );
		fread( DB->Before_Reconstructed, sizeof(unsigned char), ROW*COL, sp );
		fread( DB->After_Reconstructed, sizeof(unsigned char), ROW*COL, np );


		fclose(fp);
		fclose(op);
		fclose(sp);
		fclose(np);
	}	
	else
	{
	    free(DB->Input);       
		free(DB->PastInput); 
		free(DB->Output); 
			

		free(DB->Inter_Reconstructed);    
		free(DB->Inter_quantization); 
		free(DB->Inter_inquantization); 
		free(DB->Past_Reconstructed); 
		free(DB->MoveCompensatedBlk); 

		free(DB->Intra_Reconstructed); 
		free(DB->Intra_predict);     
		free(DB->Intra_quantization); 
		free(DB->Intra_inquantization);

		free(DB->Before_Reconstructed);
		free(DB->After_Reconstructed);
		
		free(DB->Intra_Transfer_quantization); 

	}
}