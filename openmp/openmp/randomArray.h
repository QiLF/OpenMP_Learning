#pragma once
#include<stdlib.h>
#include<time.h>
using namespace std;

void genRandArr(int A[],int n) {
	srand((unsigned)time(NULL));//�������
	for (int i = 0; i < n; i++) {
		A[i] = rand();
	}
}