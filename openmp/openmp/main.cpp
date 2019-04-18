#include<iostream>
#include<omp.h>
#include<time.h>
#include "quicksort_single.h"
#include "quicksort_parallel.h"
#include "randomArray.h"
#include "save_res.h"
#include "settings.h"
#include "matrix_multiply.h"

using namespace std;

int A[ARRAY_SIZE] = {};
int B[ARRAY_SIZE] = {};

int M_A1[MATRIX_A_ROW * MATRIX_A_COL] = {};
int M_B1[MATRIX_B_ROW * MATRIX_B_COL] = {};
int M_A2[MATRIX_A_ROW * MATRIX_A_COL] = {};
int M_B2[MATRIX_B_ROW * MATRIX_B_COL] = {};
int M_C[MATRIX_A_ROW * MATRIX_B_COL] = {};

void onetest(double &para_cost,double &serial_cost)
{
	//---------------------------��ʼ���������---------------------------
	genRandArr(A, ARRAY_SIZE);
	memcpy(B, A, sizeof(B));

	genRandArr(M_A1, MATRIX_A_ROW * MATRIX_A_COL);
	genRandArr(M_B1, MATRIX_B_ROW * MATRIX_B_COL);
	memcpy(M_A2, M_A1, sizeof(M_A1));
	memcpy(M_B2, M_B1, sizeof(M_B1));
#ifdef PRINT_ON
	printArr(A, ARRAY_SIZE);
	printArr(B, ARRAY_SIZE);
#endif // PRINT_ON
	clock_t begin, end;
	//---------------------------�����㷨----------------------------
	double  once_para_cost;
	begin = clock();	//��ʱ��ʼ
	//para_quicksort(A, 0, ARRAY_SIZE - 1);
	matrix_multiply_v1(M_A1,MATRIX_A_ROW,MATRIX_A_COL,M_B1,MATRIX_B_ROW,MATRIX_B_COL,M_C);
	end = clock();	//��ʱ����
	once_para_cost = (double)(end - begin) / CLOCKS_PER_SEC;
#ifdef PRINT_ON
	cout << "�����㷨ִ��ʱ��Ϊ:" << once_para_cost << "seconds" << endl;
#endif // PRINT_ON
	//---------------------------�����㷨----------------------------
	double  once_serial_cost;
	begin = clock();	//��ʱ��ʼ
	//quicksort(B, 0, ARRAY_SIZE - 1);
	matrix_multiply_serial(M_A2, MATRIX_A_ROW, MATRIX_A_COL, M_B2, MATRIX_B_ROW, MATRIX_B_COL, M_C);
	end = clock();	//��ʱ����
	once_serial_cost = (double)(end - begin) / CLOCKS_PER_SEC;
#ifdef PRINT_ON
	cout << "�����㷨ִ��ʱ��Ϊ:" << once_serial_cost << "seconds" << endl;
#endif // PRINT_ON
	//---------------------------������ٱ�----------------------------
#ifdef PRINT_ON
	cout << "���μ��ٱ�(Ts/Tp)Ϊ:" << once_serial_cost / once_para_cost << endl;
#endif // PRINT_ON

	para_cost += once_para_cost;
	serial_cost += once_serial_cost;
}

int main()
{
	//omp_set_num_threads(4);//�����߳���Ϊ4
	//omp_set_nested(1);//������Ƕ�ף�ʱ�䷴��������
	double para_cost = 0;
	double serial_cost = 0;
	for (int i = 0; i < RUN_TIMES; i++) {
		onetest(para_cost, serial_cost);
	}
	para_cost /= RUN_TIMES;
	serial_cost /= RUN_TIMES;
	saveRes(para_cost, serial_cost, ARRAY_SIZE);
	
/*
	{//���������
	printArr(A, 10);
	genRandArr(A, 10, 10);
	printArr(A,10);
	}
*/

/*
	{//�����ļ���д
		saveRes(1100, 2200, 3300);
	}
*/

	system("pause");
	return 0;
}