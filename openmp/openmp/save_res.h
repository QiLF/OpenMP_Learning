#pragma once
#include<iostream>
#include<fstream>
using namespace std;

/*
* 打印一个数组
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
* 将结果追加到res.txt的结尾
*/
void saveRes(double para_cost, double serial_cost, int arr_size)
{
	ofstream ofile;	//定义输出文件
	ofile.open("res.txt", iostream::app);	//res.txt作为输出文件打开
	ofile <<para_cost<<" "<<serial_cost<<" "<<arr_size<<endl;	//将结果写入文件
	ofile.close();	//关闭文件
}