#pragma once

void matrix_multiply_serial(int *a, int row_a, int col_a,
	int *b, int row_b, int col_b,
	int *c)
{
	if (col_a != row_b) {
		//������飬�������������Ҫ��
		return;
	}
	int i, j, k;
	for (i = 0; i < row_a; i++) {
		int base_a = i * col_a;
		int base_c = i * col_b;
		for (j = 0; j < col_b; j++)
		{
			c[base_c + j] = 0; //���� c[i][j]
			for (k = 0; k < row_b; k++)
			{
				c[base_c + j] += a[base_a + k] * b[k*col_b + j]; // c[i][j]+=a[i][k]*b[k][j]
			}
		}
	}
}



//version 1 
//�ڲ����㷨�����ϼ򵥵ļ���parallel for�� �����ѭ�����л�
void matrix_multiply_v1(int *a, int row_a, int col_a,
						int *b, int row_b, int col_b,
						int *c)
{
	if (col_a != row_b) {
		//������飬�������������Ҫ��
		return;
	}
	int i, j, k;
#pragma omp for private(i,j,k)
	for (i = 0; i < row_a; i++) {
		int base_a = i * col_a;
		int base_c = i * col_b;
		for (j = 0; j < col_b; j++)
		{
			c[base_c + j] = 0; //���� c[i][j]
			for (k = 0; k < row_b; k++)
			{
				c[base_c + j] += a[base_a + k] * b[k*col_b + j]; // c[i][j]+=a[i][k]*b[k][j]
			}
		}
	}
}

//version 2
//��version 1�����Ͻ����Ż����ϲ������ʹ����ѭ��
void matrix_multiply_v2(int *a, int row_a, int col_a,
						int *b, int row_b, int col_b,
						int *c)
{
	if (col_a != row_b) {
		//������飬�������������Ҫ��
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
		c[base_c + j] = 0; //���� c[i][j]
		for (k = 0; k < row_b; k++)
		{
			c[base_c + j] += a[base_a + k] * b[k*col_b + j]; // c[i][j]+=a[i][k]*b[k][j]
		}
	}
}
