#pragma once
#include<iostream>
#include<fstream>
using namespace std;

/*
* ��ӡһ������
*/
void printArr(int A[],int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << A[i] << ", ";
	}
	cout << endl;
}

/*
* �����׷�ӵ�res.txt�Ľ�β
*/
void saveRes(double para_cost, double serial_cost, int arr_size)
{
	ofstream ofile;	//��������ļ�
	ofile.open("res.txt", iostream::app);	//res.txt��Ϊ����ļ���
	ofile <<para_cost<<" "<<serial_cost<<" "<<arr_size<<endl;	//�����д���ļ�
	ofile.close();	//�ر��ļ�
}