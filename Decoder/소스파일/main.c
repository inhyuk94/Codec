#include "buf.h"
//13010849 ������

void main()
{		
	Buf InOut;	

	BufCon( &InOut, TRUE );

	SubMain( &InOut );

	BufCon( &InOut, FALSE );
}

void SubMain( Buf *DB )
{
	
	double sec;
	clock_t start, end;
	
	printf("decoder \n");
	printf("����ȭ ��� �Է��ϼ��� : ");
	scanf_s(" %lf", &DB->QuantNum );


	printf(" *** before ���� ���ڵ� ***\n");
	start = clock();
	Before_Intra_Decoder(DB);
	end = clock();
	sec = ((double)end - start)/1000;
	printf("����ð� : %lf \n", sec);
	PSNR(DB,BEFORE);
	printf("\n\n-----------------------------------------------------------\n\n");
	
	printf(" *** after ���� ���ڵ� ***\n");
	start = clock();
	Decoder(DB);
	end = clock();
	sec = ((double)end - start)/1000;
	printf("����ð� : %lf \n", sec);
	PSNR(DB,AFTER);
	
	
	
}