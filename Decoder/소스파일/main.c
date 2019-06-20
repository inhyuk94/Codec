#include "buf.h"
//13010849 이인혁

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
	printf("양자화 계수 입력하세요 : ");
	scanf_s(" %lf", &DB->QuantNum );


	printf(" *** before 영상 디코딩 ***\n");
	start = clock();
	Before_Intra_Decoder(DB);
	end = clock();
	sec = ((double)end - start)/1000;
	printf("실행시간 : %lf \n", sec);
	PSNR(DB,BEFORE);
	printf("\n\n-----------------------------------------------------------\n\n");
	
	printf(" *** after 영상 디코딩 ***\n");
	start = clock();
	Decoder(DB);
	end = clock();
	sec = ((double)end - start)/1000;
	printf("실행시간 : %lf \n", sec);
	PSNR(DB,AFTER);
	
	
	
}