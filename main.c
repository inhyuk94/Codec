#include "buf.h"
//13010849 이인혁

void main()
{		
	Buf InOut;	

	BufCon( &InOut, TRUE ); //파일 read , 메모리 동적 할당

	SubMain( &InOut );

	BufCon( &InOut, FALSE ); //해제
}

void SubMain( Buf *DB )
{
	
	double sec;
	clock_t start, end;
	
	printf("encoder \n");
	printf("양자화 계수 입력하세요 : ");
	scanf_s(" %lf", &DB->QuantNum );


	printf(" *** before 영상 인코딩 ***\n");
	start = clock();
	Before_Intra_Encoder(DB);
	end = clock();
	sec = ((double)end - start)/1000;
	printf("실행시간 : %lf \n", sec);
	PSNR(DB,BEFORE);
	printf("\n\n-----------------------------------------------------------\n\n");
	
	printf(" *** after 영상 인코딩 ***\n");
	start = clock();
	Encoder(DB);
	end = clock();
	sec = ((double)end - start)/1000;
	printf("실행시간 : %lf \n", sec);
	PSNR(DB,AFTER);
	
	
	
}