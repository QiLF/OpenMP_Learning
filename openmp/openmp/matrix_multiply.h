#pragma once

void matrix_multiply_serial(int *a, int row_a, int col_a,
	int *b, int row_b, int col_b,
	int *c)
{
	if (col_a != row_b) {
		//参数检查，矩阵需满足相乘要求
		return;
	}
	int i, j, k;
	for (i = 0; i < row_a; i++) {
		int base_a = i * col_a;
		int base_c = i * col_b;
		for (j = 0; j < col_b; j++)
		{
			c[base_c + j] = 0; //计算 c[i][j]
			for (k = 0; k < row_b; k++)
			{
				c[base_c + j] += a[base_a + k] * b[k*col_b + j]; // c[i][j]+=a[i][k]*b[k][j]
			}
		}
	}
}



//version 1 
//在并行算法基础上简单的加上parallel for， 最外层循环并行化
void matrix_multiply_v1(int *a, int row_a, int col_a,
						int *b, int row_b, int col_b,
						int *c)
{
	if (col_a != row_b) {
		//参数检查，矩阵需满足相乘要求
		return;
	}
	int i, j, k;
#pragma omp for private(i,j,k)
	for (i = 0; i < row_a; i++) {
		int base_a = i * col_a;
		int base_c = i * col_b;
		for (j = 0; j < col_b; j++)
		{
			c[base_c + j] = 0; //计算 c[i][j]
			for (k = 0; k < row_b; k++)
			{
				c[base_c + j] += a[base_a + k] * b[k*col_b + j]; // c[i][j]+=a[i][k]*b[k][j]
			}
		}
	}
}

//version 2
//在version 1基础上进行优化，合并最外层和次外层循环
void matrix_multiply_v2(int *a, int row_a, int col_a,
						int *b, int row_b, int col_b,
						int *c)
{
	if (col_a != row_b) {
		//参数检查，矩阵需满足相乘要求
		return;
	}
	int i, j, k;
	i = j = 0;
	int index = 0;
	int end = row_a * col_b;
#pragma omp for private(i,j,k)
	for (index = 0; index < end; index++) {
		i = index / col_b;
		j = index % col_b;
		int base_a = i * col_a;
		int base_c = i * col_b;
		c[base_c + j] = 0; //计算 c[i][j]
		for (k = 0; k < row_b; k++)
		{
			c[base_c + j] += a[base_a + k] * b[k*col_b + j]; // c[i][j]+=a[i][k]*b[k][j]
		}
	}
}
