#pragma once

int quicksort_partition(int A[], int p, int r);//快速排序子数组划分
void quicksort(int A[], int p, int r);//快速排序串行算法


/*
*@return q 将数组划分为两部分的轴值下标
*@param A 待排序的数组，使用A[p...r]
*@param p 起始下标
*@param r 终止下标
*/
int quicksort_partition(int A[], int p, int r)
{
	int x = A[r];	//选择A[r]作为轴值
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (A[j] <= x) {
			i++;
			//swap(A[i], A[j]);
			{
				//交换A[i]和A[j],使得A[p...i]恒小于轴值
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
	return i+1;
}

/*
*@brief 快速排序串行程序
*@param A 待排序的数组，使用A[p...r]
*@param p 起始下标
*@param r 终止下标
*/
void quicksort(int A[],int p,int r)
{
	if (p < r) {
		int q = quicksort_partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}
