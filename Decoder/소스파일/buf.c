#include "buf.h"

void BufCon( Buf *DB, int OrderFlag )
{
	if( OrderFlag )
	{
		FILE *fp,*op,*sp,*np;
		fopen_s( &fp, "football(720x480)_after.y", "rb" );	//psnrȮ���ϱ� ���ؼ� after�������� 
		fopen_s( &op, "football(720x480)_before.y", "rb" ); //psnrȮ���ϱ� ���ؼ� befoer��������		
		fopen_s( &sp, "Before_Intra_Reconstructed_football.y", "rb" ); //�̽���ġ Ȯ���ϱ����� ���ڴ����� before������ reconstructed ����
		fopen_s( &np, "After_reconstructed result.y", "rb" ); // �̽���ġ Ȯ���ϱ����� ���ڴ����� after������ reconstructed ����

		DB->Input         = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char)); //after����
		DB->PastInput     = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));	//before����
		DB->Output     = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char));

		DB->Inter_Reconstructed   = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char)); //�ð������� ������ ���� 720*480
		DB->Inter_quantization    = (int*)calloc(TSIZE*TSIZE, sizeof(int)); //�ð����� ����ȭ��
		DB->Inter_inquantization  = (double*)calloc(TSIZE*TSIZE, sizeof(double)); //�ð����� ������ȭ��
		DB->Past_Reconstructed    = (unsigned char*)calloc(ROW*COL, sizeof(unsigned char)); //Before���� ���ڵ��� ������
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