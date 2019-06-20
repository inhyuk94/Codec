#include "buf.h"

void PSNR( Buf *DB ,int OrderFlag) 
{
	int i, j;
	double mse=0, psnr=0, max=0;
	unsigned char load_1=0, load_2=0;

	for( i=0; i<COL; i++ )
	{	
		for( j=0; j<ROW; j++ )
		{
			if( OrderFlag )
			{
				load_1 = *(DB->PastInput + i * ROW + j);
				load_2 = *(DB->Intra_Reconstructed + i * ROW + j);
			}
			else
			{
				load_1 = *(DB->Input + i * ROW + j);
				load_2 = *(DB->Output + i * ROW + j);
			}

			mse += ((load_1 - load_2) * (load_1 - load_2));
			if(load_1 > max)
				max = load_1;

		}
	}

	mse = mse / (ROW*COL);
	printf("MSE : %lf\n", mse);
	psnr = 20 * log10(max / sqrt(mse));
	printf("PSNR : %lf\n", psnr);


} 
