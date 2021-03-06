//2016706018 박건희
//header file
#include <stdio.h>
#include <math.h>	//사인, 코사인함수 사용을 위해 호출

#define PI 3.1415926535897	//파이 정의

void Binary_PSK(char file_name[20], int phase, int sample_num, int bit_num);
// BPSK에 의한 bit판정
// 파일이름, 위상차이(90도 180도 차이), 심볼당 샘플갯수, 비트수

void DS_Binary_PSK(char file_name[20], int phase, int sample_num, int chip_period, int bit_num);
// DS/BPSK에 의한 bit판정
// 파일이름, 위상차이(180도 차이), 심볼당 샘플갯수, chip_period, 비트수




//main function
int main() {
	Binary_PSK("bpsk.dat", 180, 60, 1000);	//bpsk.dat, symbol간 phase차이 180, 심볼당 샘플수 60, 비트수 1000
	DS_Binary_PSK("dsbpsk.dat", 180, 60, 4, 1000);	//dsbpsk.dat, symbol간 phase차이 180, 심볼당 샘플수 60, chip_period=4, 비트수 1000
}



// BPSK function
void Binary_PSK(char file_name[20], int phase, int sample_num, int bit_num) {

	FILE* fin, * fbit;						//파일구조체의 포인터 선언
	fopen_s(&fin, file_name, "rt");			//fin에 file_name 인자에 들어가는 파일 txt 형태로 읽기
	fopen_s(&fbit, "bit.dat", "rt");		//fbit에 bit.dat 파일 txt 형태로 읽기
	float input[60] = { 0.0, };				// 파형 배열, sample 갯수 60개로 선언
	float sum = 0;				// ML Rule에 의거한 적분값
	int detect;								// 판정된 bit
	int bit;								// bit.dat에 저장된 실제 bit
	int i, k;								// 반복문용
	float error_count = 0;					// 에러 bit 갯수

	for (i = 0; i < bit_num; i++) {			//bit갯수 만큼 반복
		for (k = 0; k < sample_num; k++) {	//symbol당 sample수만큼 반복
			fscanf_s(fin, "%f", &input[k]);	//symbol의 sample을 input배열에 순서대로 저장
			sum += (input[k] * cos((2 * PI * k) / 8));									//sample을 코사인(위상 0도)과 correlation
		}									//for문 종료시 sum에 각 phase간의 sample 적분값 저장
		//적분값의 크기비교 후 판정
		if (sum > 0)						//부호로 결정된다.
			detect = 1;						
		else
			detect = 0;
		fscanf_s(fbit, "%d", &bit);			//실제 bit 읽어들임
		if (detect != bit)					//만약 판정된 bit와 실제 bit가 다르면 
			error_count++;					//에러 갯수 추가

		sum = 0;							//적분값 0 초기화
	}
	//모든 bit의 판정 종료

	printf("%s Binary_PSK error_count: %d, error_rate: %.1f%%\n", file_name, (int)error_count, error_count / (float)bit_num * 100);		//파일 이름, 에러비트갯수, 비트에러율 출력
}

// DS_BPSK function
void DS_Binary_PSK(char file_name[20], int phase, int sample_num, int chip_period, int bit_num) {

	FILE* fin, * fbit;						//파일구조체의 포인터 선언
	fopen_s(&fin, file_name, "rt");			//fin에 file_name 인자에 들어가는 파일 txt 형태로 읽기
	fopen_s(&fbit, "bit.dat", "rt");		//fbit에 bit.dat 파일 txt 형개로 선언태로 읽기
	float input[60] = { 0.0, };				// 파형 배열, sample 갯수 60
	float PNCODE[15] = { 1, -1, -1, -1, 1, 1, 1, 1, -1, 1, -1, 1, 1, -1, -1 };	//PNCODE
	float sum = 0;							// ML Rule에 의거한 적분값
	int detect;								// 판정된 bit
	int bit;								// bit.dat에 저장된 실제 bit
	int i, k;								// 반복문용
	float error_count = 0;					// 에러 bit 갯수

	for (i = 0; i < bit_num; i++) {			//bit갯수 만큼 반복
		for (k = 0; k < sample_num; k++) {	//symbol당 sample수만큼 반복
			fscanf_s(fin, "%f", &input[k]);	//symbol의 sample을 input배열에 순서대로 저장
			sum += (input[k] * cos((2 * PI * k) / 8) * PNCODE[k/chip_period]);									//sample을 코사인(위상 0도)과 correlation
		}									//for문 종료시 sum1, sum2에 각 phase간의 sample 적분값 저장
		//적분값의 크기비교 후 판정
		if (sum > 0)					
			detect = 1;					
		else
			detect = 0;
		fscanf_s(fbit, "%d", &bit);			//실제 bit 읽어들임
		if (detect != bit)					//만약 판정된 bit와 실제 bit가 다르면 
			error_count++;					//에러 갯수 추가

		sum = 0;							//적분값 0 초기화
	}
	//모든 bit의 판정 종료

	printf("%s DS_Binary_PSK error_count: %d, error_rate: %.1f%%\n", file_name, (int)error_count, error_count / (float)bit_num * 100);		//파일 이름, 에러비트갯수, 비트에러율 출력
}









// QPSK function
void Quadrature_PSK(char file_name[20], int phase, int sample_num, int bit_num) {

	FILE* fin, * fbit;						//파일구조체의 포인터 선언
	fopen_s(&fin, file_name, "rt");			//fin에 file_name 인자에 들어가는 파일 txt 형태로 읽기
	fopen_s(&fbit, "bit.dat", "rt");		//fbit에 bit.dat 파일 txt 형태로 읽기
	float input[40] = { 0.0, };				// 파형 배열, sample 갯수 40개인 점을 고려해서 40개로 선언
	float sum1 = 0, sum2 = 0;				// ML Rule에 의거한 적분값
	int detect;								// 판정된 bit
	int bit;								// bit.dat에 저장된 실제 bit
	int i, k;								// 반복문용 
	float error_count = 0;					// 에러 bit 갯수
	int sym_detect;
	for (i = 0; i < bit_num / 2; i++) {			//symbol당 2bit를 가지므로 bit갯수 절반 만큼 반복
		for (k = 0; k < sample_num; k++) {	//bit당 sample수만큼 반복
			fscanf_s(fin, "%f", &input[k]);	//bit의 sample을 input배열에 순서대로 저장
			sum1 += (input[k] * cos((2 * PI * k) / 10 + (phase / 180 * PI)));				//sample을 코사인축의 phase 45도에서 적분
			sum2 += (input[k] * sin((2 * PI * k) / 10 + (phase / 180 * PI)));				//sample을 사인축의 phase 45도에서 적분

		}									//for문 종료시 sum1,sum2에 bit 하나의 cos45도,sin45도에 대한 sample 적분값 저장

		fscanf_s(fbit, "%d", &bit);			//실제 bit 읽어들임
		if (sum1 > 0)							//첫번째비트판정 코사인45도 위치에서 적분값의 부호에따라 비트 결정
			detect = 1;
		else detect = 0;

		if (detect != bit)					//만약 판정된 bit와 실제 bit가 다르면 
			error_count++;					//에러 갯수 추가

		fscanf_s(fbit, "%d", &bit);			//실제 bit 읽어들임
		if (sum2 > 0)							//두번째비트판정 사인45도 위치에서 적분값의 부호에따라 비트 결정
			detect = 1;
		else detect = 0;

		if (detect != bit)					//만약 판정된 bit와 실제 bit가 다르면 
			error_count++;					//에러 갯수 추가

		sum1 = 0; sum2 = 0;
	}
	//모든 bit의 판정 종료

	printf("%s Quadrature_PSK error_count: %d, error_rate: %.1f%%\n", file_name, (int)error_count, error_count / (float)bit_num * 100);		//파일 이름, 에러비트갯수, 비트에러율 출력
}


