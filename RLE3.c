#include <stdio.h>
#include <string.h>
#define N 256 * 256
unsigned char results[N] = {'\0'}; //encoding한 데이터를 저장할 배열
FILE *bin = 0;					   //encoding한 배열을 저장할 binary file

int encoding(unsigned char num[N])
{
	int i, cnt = 1, idx = 0;

	printf("인코딩 후 : ");
	for (i = 0; i < N; i++)
	{
		if (num[i] == 0)
			break;									//배열의 데이터가 끝나면 반복문 탈출
		if ((num[i] != num[i + 1]) || (cnt == 255)) //다음 번지의 데이터와 다르거나 반복횟수가 255가 되면 빈 배열에 반복횟수와 데이터를 저장
		{
			results[idx] = cnt;
			results[idx + 1] = num[i]; //데이터는 다음칸에 저장해야하므로 idx+1
			cnt = 1;				   //cnt를 1로 초기화
			printf("%d%c", results[idx], results[idx + 1]);
			idx += 2; //반복횟수와 데이터를 2칸씩 저장하기 때문에 2씩 증가
		}
		else
			cnt++;
	}
	//encoding된 배열을 binary file에 저장
	if (bin = fopen("en_code.bin", "wb"))
		fwrite(results, sizeof(unsigned char), N, bin);
	return;
}

int decoding(unsigned char en_number[N])
{
	int i, j, idx = 0;
	unsigned char de_number[2 * N] = {
		0,
	};
	for (i = 0;; i += 2)
	{
		if (en_number[i] == 0)
			break;
		for (j = 0; j < en_number[i]; j++) //반복횟수만큼 빈 배열에 데이터를 저장해야하므로 j는 en_number[i]까지 반복
		{
			printf("%c", en_number[i + 1]);
			de_number[idx] = en_number[i + 1];
			idx++;
		}
	}
	printf("\n결과 : %s\n", de_number);
	if (bin = fopen("string.bin", "rb"))
	{
		FILE *txt = 0; //decoding된 배열을 저장할 txt file
		if (txt = fopen("de_code.txt", "w"))
			fwrite(de_number, sizeof(unsigned char), N, txt);
	}
}

int main()
{
	unsigned char num[N];
	unsigned char num1[N];
	unsigned char num2[N];
	FILE *fp = fopen("string.txt", "r"); //입력 파일
	fgets(num, sizeof(num), fp);
	printf("인코딩 전 : %s\n", num);
	encoding(num);
	printf("\n\n배열 디코딩 과정 : ");
	decoding(results); //encoding된 배열을 decoding
	printf("\n");

	FILE *bin = fopen("en_code.bin", "rb"); //encoding된 binary file
	fgets(num1, sizeof(num1), bin);
	printf("binary file 디코딩 과정 : ");
	decoding(num1); //encoding된 binary file을 decoding

	FILE *txt = fopen("de_code.txt", "r"); //decodinge된 txt file
	fgets(num2, sizeof(num2), txt);

	if (strcmp(num, num2) == 0)
		printf("\n같다"); //입력파일과 최종 파일 비교
	else
		printf("\n다르다");
	return 0;
}