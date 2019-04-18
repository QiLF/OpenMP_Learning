#pragma once
#include<omp.h>
#include"settings.h"

int para_quicksort_partition(int A[], int p, int r);//�������������黮��
void para_quicksort(int A[], int p, int r);//�����������㷨

/*
*@brief ���������г���
*@param A ����������飬ʹ��A[p...r]
*@param p ��ʼ�±�
*@param r ��ֹ�±�
*/
void para_quicksort(int A[], int p, int r)
{
	if (p < r) {
		int q = para_quicksort_partition(A, p, r);
		if (r - p > PARA_THRESHOLD) {
#pragma omp parallel sections
			{
#pragma omp section
				para_quicksort(A, p, q - 1);
#pragma omp section
				para_quicksort(A, q + 1, r);
			}
		}
		else {
			para_quicksort(A, p, q - 1);
			para_quicksort(A, q + 1, r);
		}
	}
}
/*
*@return q �����黮��Ϊ�����ֵ���ֵ�±�
*@param A ����������飬ʹ��A[p...r]
*@param p ��ʼ�±�
*@param r ��ֹ�±�
*/
int para_quicksort_partition(int A[], int p, int r)
{
	int x = A[r];	//ѡ��A[r]��Ϊ��ֵ
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (A[j] <= x) {
				i++;
			//swap(A[i], A[j]);
			{
				//����A[i]��A[j],ʹ��A[p...i]��С����ֵ
				int tmp = A[i];
				A[i] = A[j];
				A[j] = tmp;
			}
		}
	}
	//swap(A[i+1], A[r])
	{
		int tmp = A[i + 1];
		A[i + 1] = A[r];
		A[r] = tmp;
	}
	return i + 1;
}


