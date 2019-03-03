#include<iostream>
#include<omp.h>
#include"testOMP.h"

using namespace std;

void testMemory()
{
int x = 2;
#pragma omp parallel num_threads(2) shared(x)
	{
		if (omp_get_thread_num() == 0) {
			x = 5;
		}
		else {
			printf("1: Thread# %d: x = %d\n", omp_get_thread_num(), x);
		}
#pragma omp barrier
		if (omp_get_thread_num() == 0) {
			printf("2: Thread# %d: x = %d\n", omp_get_thread_num(), x);
		}
		else {
			printf("3: Thread# %d: x = %d\n", omp_get_thread_num(), x);
		}}
}

void testSum()
{
	int sum = 0;
	int a[11] = { 1,2,3,4,5,6,7,8,9,10,11 };
	int coreNum = omp_get_num_procs();
	cout << "核心数:" << coreNum << endl;
#pragma omp parallel for
	for (int i = 0; i < 11; i++)
	{
		sum += a[i];
	}
	cout << "sum:" << sum << endl;
}

void testSum2()
{
	int i, sum = 100;
#pragma omp parallel for reduction(+: sum)
	for (i = 0; i < 1000; i++) {
		sum += i;
	}
	printf("sum = %ld\n", sum);
}

void testHelloWorld()
{
	int nthreads, tid;
	char buf[32];
	/* Fork a team of threads */
#pragma omp parallel private(nthreads,tid)
	{
		tid = omp_get_thread_num(); /* Obtain and print thread id */
		printf("Hello, world from OpenMP thread %d\n", tid);
		if (tid == 0) /*Only master thread does this */
		{
			nthreads = omp_get_num_threads();
			printf(" Number of threads %d\n", nthreads);
		}
	}
}

void testParallelFor()
{
	int i = 0;
#pragma omp parallel for num_threads(4) private(i)
	for (i = 0; i < 12; i++)
	{
		printf("OpenMP Test, 线程编号为: %d,i=%d\n", omp_get_thread_num(),i);
	}
}

void testParallel()
{
//#pragma omp parallel
//	{
//		printf("Hello, World!, ThreadId = %d\n", omp_get_thread_num());
//	}
#pragma omp parallel num_threads(20)
	{
		printf("Hello, World!, ThreadId = %d\n", omp_get_thread_num());
	}
}

void testSections()
{
#pragma omp parallel sections 
{
#pragma omp section
	printf("section 1 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
	printf("section 2 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
	printf("section 3 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
	printf("section 4 ThreadId = %d\n", omp_get_thread_num());
	}
}

void testPrivate()
{
	int k = 100;
#pragma omp parallel for private(k)
	for (k = 0; k < 10; k++)
	{
		printf("k=%d\n", k);
	}
	printf("last k=%d\n", k);
}
int counter = 0;

#pragma omp threadprivate(counter)
int increment_counter()
{
	counter++;
	return(counter);
}
void testCopyprivate()
{
	

#pragma omp parallel
		{
			int count;
#pragma omp single copyprivate(counter)//去掉copyprivate将会导致只有主线程里的counter为51
			{
				counter = 50;
			}
			count = increment_counter();
			printf("ThreadId: %ld, count = %ld\n", omp_get_thread_num(), count);
		}
}



int main()
{
	//testParallelFor();
	//testParallel();
	//testSections();
	//testPrivate();
	testCopyprivate();
	system("pause");
	return 0;
}