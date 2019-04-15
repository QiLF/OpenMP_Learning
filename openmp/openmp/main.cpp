#include<iostream>
#include<omp.h>
#include<time.h>
#include "quicksort_single.h"
#include "quicksort_parallel.h"
#include "randomArray.h"
#include "save_res.h"
#include "settings.h"

using namespace std;

int A[ARRAY_SIZE] = {};
int B[ARRAY_SIZE] = {};

void onetest(double &para_cost,double &serial_cost)
{
	//---------------------------初始化随机数组---------------------------
	genRandArr(A, ARRAY_SIZE);
	memcpy(B, A, sizeof(B));
#ifdef PRINT_ON
	printArr(A, ARRAY_SIZE);
	printArr(B, ARRAY_SIZE);
#endif // PRINT_ON
	clock_t begin, end;
	//---------------------------并行算法----------------------------
	double  once_para_cost;
	begin = clock();	//计时开始
	para_quicksort(A, 0, ARRAY_SIZE - 1);
	end = clock();	//计时结束
	once_para_cost = (double)(end - begin) / CLOCKS_PER_SEC;
#ifdef PRINT_ON
	cout << "并行算法执行时间为:" << once_para_cost << "seconds" << endl;
#endif // PRINT_ON
	//---------------------------串行算法----------------------------
	double  once_serial_cost;
	begin = clock();	//计时开始
	quicksort(B, 0, ARRAY_SIZE - 1);
	end = clock();	//计时结束
	once_serial_cost = (double)(end - begin) / CLOCKS_PER_SEC;
#ifdef PRINT_ON
	cout << "串行算法执行时间为:" << once_serial_cost << "seconds" << endl;
#endif // PRINT_ON
	//---------------------------计算加速比----------------------------
#ifdef PRINT_ON
	cout << "单次加速比(Ts/Tp)为:" << once_serial_cost / once_para_cost << endl;
#endif // PRINT_ON

	para_cost += once_para_cost;
	serial_cost += once_serial_cost;
}

int main()
{
	omp_set_num_threads(4);//设置线程数为4
	//omp_set_nested(1);//允许并行嵌套，时间反而增加了
	double para_cost = 0;
	double serial_cost = 0;
	for (int i = 0; i < RUN_TIMES; i++) {
		onetest(para_cost, serial_cost);
	}
	para_cost /= RUN_TIMES;
	serial_cost /= RUN_TIMES;
	saveRes(para_cost, serial_cost, ARRAY_SIZE);
	
/*
	{//调试随机数
	printArr(A, 10);
	genRandArr(A, 10, 10);
	printArr(A,10);
	}
*/

/*
	{//调试文件读写
		saveRes(1100, 2200, 3300);
	}
*/

	system("pause");
	return 0;
}