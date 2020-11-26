//2016706018 �ڰ���
//header file
#include <stdio.h>
#include <math.h>	//����, �ڻ����Լ� ����� ���� ȣ��

#define PI 3.1415926535897	//���� ����

void Binary_PSK(char file_name[20], int phase, int sample_num, int bit_num);
// BPSK�� ���� bit����
// �����̸�, ��������(90�� 180�� ����), �ɺ��� ���ð���, ��Ʈ��

void DS_Binary_PSK(char file_name[20], int phase, int sample_num, int chip_period, int bit_num);
// DS/BPSK�� ���� bit����
// �����̸�, ��������(180�� ����), �ɺ��� ���ð���, chip_period, ��Ʈ��




//main function
int main() {
	Binary_PSK("bpsk.dat", 180, 60, 1000);	//bpsk.dat, symbol�� phase���� 180, �ɺ��� ���ü� 60, ��Ʈ�� 1000
	DS_Binary_PSK("dsbpsk.dat", 180, 60, 4, 1000);	//dsbpsk.dat, symbol�� phase���� 180, �ɺ��� ���ü� 60, chip_period=4, ��Ʈ�� 1000
}



// BPSK function
void Binary_PSK(char file_name[20], int phase, int sample_num, int bit_num) {

	FILE* fin, * fbit;						//���ϱ���ü�� ������ ����
	fopen_s(&fin, file_name, "rt");			//fin�� file_name ���ڿ� ���� ���� txt ���·� �б�
	fopen_s(&fbit, "bit.dat", "rt");		//fbit�� bit.dat ���� txt ���·� �б�
	float input[60] = { 0.0, };				// ���� �迭, sample ���� 60���� ����
	float sum = 0;				// ML Rule�� �ǰ��� ���а�
	int detect;								// ������ bit
	int bit;								// bit.dat�� ����� ���� bit
	int i, k;								// �ݺ�����
	float error_count = 0;					// ���� bit ����

	for (i = 0; i < bit_num; i++) {			//bit���� ��ŭ �ݺ�
		for (k = 0; k < sample_num; k++) {	//symbol�� sample����ŭ �ݺ�
			fscanf_s(fin, "%f", &input[k]);	//symbol�� sample�� input�迭�� ������� ����
			sum += (input[k] * cos((2 * PI * k) / 8));									//sample�� �ڻ���(���� 0��)�� correlation
		}									//for�� ����� sum�� �� phase���� sample ���а� ����
		//���а��� ũ��� �� ����
		if (sum > 0)						//��ȣ�� �����ȴ�.
			detect = 1;						
		else
			detect = 0;
		fscanf_s(fbit, "%d", &bit);			//���� bit �о����
		if (detect != bit)					//���� ������ bit�� ���� bit�� �ٸ��� 
			error_count++;					//���� ���� �߰�

		sum = 0;							//���а� 0 �ʱ�ȭ
	}
	//��� bit�� ���� ����

	printf("%s Binary_PSK error_count: %d, error_rate: %.1f%%\n", file_name, (int)error_count, error_count / (float)bit_num * 100);		//���� �̸�, ������Ʈ����, ��Ʈ������ ���
}

// DS_BPSK function
void DS_Binary_PSK(char file_name[20], int phase, int sample_num, int chip_period, int bit_num) {

	FILE* fin, * fbit;						//���ϱ���ü�� ������ ����
	fopen_s(&fin, file_name, "rt");			//fin�� file_name ���ڿ� ���� ���� txt ���·� �б�
	fopen_s(&fbit, "bit.dat", "rt");		//fbit�� bit.dat ���� txt ������ �����·� �б�
	float input[60] = { 0.0, };				// ���� �迭, sample ���� 60
	float PNCODE[15] = { 1, -1, -1, -1, 1, 1, 1, 1, -1, 1, -1, 1, 1, -1, -1 };	//PNCODE
	float sum = 0;							// ML Rule�� �ǰ��� ���а�
	int detect;								// ������ bit
	int bit;								// bit.dat�� ����� ���� bit
	int i, k;								// �ݺ�����
	float error_count = 0;					// ���� bit ����

	for (i = 0; i < bit_num; i++) {			//bit���� ��ŭ �ݺ�
		for (k = 0; k < sample_num; k++) {	//symbol�� sample����ŭ �ݺ�
			fscanf_s(fin, "%f", &input[k]);	//symbol�� sample�� input�迭�� ������� ����
			sum += (input[k] * cos((2 * PI * k) / 8) * PNCODE[k/chip_period]);									//sample�� �ڻ���(���� 0��)�� correlation
		}									//for�� ����� sum1, sum2�� �� phase���� sample ���а� ����
		//���а��� ũ��� �� ����
		if (sum > 0)					
			detect = 1;					
		else
			detect = 0;
		fscanf_s(fbit, "%d", &bit);			//���� bit �о����
		if (detect != bit)					//���� ������ bit�� ���� bit�� �ٸ��� 
			error_count++;					//���� ���� �߰�

		sum = 0;							//���а� 0 �ʱ�ȭ
	}
	//��� bit�� ���� ����

	printf("%s DS_Binary_PSK error_count: %d, error_rate: %.1f%%\n", file_name, (int)error_count, error_count / (float)bit_num * 100);		//���� �̸�, ������Ʈ����, ��Ʈ������ ���
}









// QPSK function
void Quadrature_PSK(char file_name[20], int phase, int sample_num, int bit_num) {

	FILE* fin, * fbit;						//���ϱ���ü�� ������ ����
	fopen_s(&fin, file_name, "rt");			//fin�� file_name ���ڿ� ���� ���� txt ���·� �б�
	fopen_s(&fbit, "bit.dat", "rt");		//fbit�� bit.dat ���� txt ���·� �б�
	float input[40] = { 0.0, };				// ���� �迭, sample ���� 40���� ���� ����ؼ� 40���� ����
	float sum1 = 0, sum2 = 0;				// ML Rule�� �ǰ��� ���а�
	int detect;								// ������ bit
	int bit;								// bit.dat�� ����� ���� bit
	int i, k;								// �ݺ����� 
	float error_count = 0;					// ���� bit ����
	int sym_detect;
	for (i = 0; i < bit_num / 2; i++) {			//symbol�� 2bit�� �����Ƿ� bit���� ���� ��ŭ �ݺ�
		for (k = 0; k < sample_num; k++) {	//bit�� sample����ŭ �ݺ�
			fscanf_s(fin, "%f", &input[k]);	//bit�� sample�� input�迭�� ������� ����
			sum1 += (input[k] * cos((2 * PI * k) / 10 + (phase / 180 * PI)));				//sample�� �ڻ������� phase 45������ ����
			sum2 += (input[k] * sin((2 * PI * k) / 10 + (phase / 180 * PI)));				//sample�� �������� phase 45������ ����

		}									//for�� ����� sum1,sum2�� bit �ϳ��� cos45��,sin45���� ���� sample ���а� ����

		fscanf_s(fbit, "%d", &bit);			//���� bit �о����
		if (sum1 > 0)							//ù��°��Ʈ���� �ڻ���45�� ��ġ���� ���а��� ��ȣ������ ��Ʈ ����
			detect = 1;
		else detect = 0;

		if (detect != bit)					//���� ������ bit�� ���� bit�� �ٸ��� 
			error_count++;					//���� ���� �߰�

		fscanf_s(fbit, "%d", &bit);			//���� bit �о����
		if (sum2 > 0)							//�ι�°��Ʈ���� ����45�� ��ġ���� ���а��� ��ȣ������ ��Ʈ ����
			detect = 1;
		else detect = 0;

		if (detect != bit)					//���� ������ bit�� ���� bit�� �ٸ��� 
			error_count++;					//���� ���� �߰�

		sum1 = 0; sum2 = 0;
	}
	//��� bit�� ���� ����

	printf("%s Quadrature_PSK error_count: %d, error_rate: %.1f%%\n", file_name, (int)error_count, error_count / (float)bit_num * 100);		//���� �̸�, ������Ʈ����, ��Ʈ������ ���
}


