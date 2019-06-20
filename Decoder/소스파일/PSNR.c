#include "buf.h"
//디코더
void PSNR( Buf *DB ,int OrderFlag)
{
	int i, j;
	double mse=0, psnr=0, max=0;
	double mse_2=0,psnr_2=0,max_2=0;
	unsigned char load_1=0, load_2=0, load_3 =0 ;

	for( i=0; i<COL; i++ )
	{	
		for( j=0; j<ROW; j++ )
		{
			if( OrderFlag )
			{
				load_1 = *(DB->PastInput + i * ROW + j);
				load_2 = *(DB->Before_Reconstructed + i * ROW + j);
				load_3 = *(DB->Past_Reconstructed + i * ROW + j);
				
			}
			else
			{
				load_1 = *(DB->Input + i * ROW + j);
				load_2 = *(DB->After_Reconstructed + i * ROW + j);
				load_3 = *(DB->Output + i * ROW + j);
			}

			mse += ((load_1 - load_3) * (load_1 - load_3));
			if(load_1 > max)
				max = load_1;

			mse_2 += ((load_2 - load_3) * (load_2 - load_3));
			if(load_2 > max_2)
				max_2 = load_2;
		}
	}

	
	mse = mse / (ROW*COL);
	printf("MSE : %lf\n", mse);
	psnr = 20 * log10(max / sqrt(mse));
	printf("PSNR : %lf\n", psnr);

	printf("\nMismatch 여부확인\n");
	mse_2 = mse_2 / (ROW*COL);
	printf("MSE : %lf\n", mse_2);
	psnr_2 = 20 * log10(max_2 / sqrt(mse_2));
	printf("PSNR : %lf\n", psnr_2);


} 
