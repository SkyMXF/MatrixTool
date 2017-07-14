#include <iostream>
#include <cmath>

#include "MatrixTool.h"

void MatrixTool::matMulti(Mat & result, Mat & matA, Mat & matB)
//����˷�,result���ڵ���ǰʹ�ú��ʵ���������Create
{
	int i, j, k;
	for (i = 0; i < result.row; i++)
	{
		for (j = 0; j < result.col; j++)
		{
			result.data[i * result.col + j] = 0.0;		//��Ϊ��Ҫ�ۼ�,��˽�result��ʼ��Ϊ0����
		}
	}

	for (int i = 0; i < matA.row; i++)
	{
		for (int j = 0; j < matB.col; j++)
		{
			for (int k = 0; k < matA.col; k++)
			{
				result.data[i * result.col + j] += matA.data[i * matA.col + k] * matB.data[k * matB.col + j];
				//result��i��j�� = A�е�i��k�� * B�е�k��j��
			}
		}
	}
}

void MatrixTool::matTrans(Mat & result, Mat & matA)
//����ת��,result���ڵ���ǰʹ�ú��ʵ���������Create
{
	for (int i = 0; i < matA.row; i++)
	{
		for (int j = 0; j < matA.col; j++)
		{
			result.data[j * result.col + i] = matA.data[i * matA.col + j];
			//result��j��i�� = A�е�i��j��
		}
	}
}

bool MatrixTool::Gauss(Mat & result, Mat & matA)
//���ò�����Ԫ�ĸ�˹��ȥ������A�������
{
	if (matA.row != matA.col)
		return false;				//���Ƿ���

	int i, j, k;
	double max, temp;
	int n = matA.row;
	Mat matT(n, n);					//��ʱ����

	for (i = 0; i < n; i++)			//��A����������ʱ����t[n][n]��
	{
		for (j = 0; j < n; j++)
		{
			matT.data[i * n + j] = matA.data[i * n + j];
		}
	}

	//��ʼ��result����Ϊ��λ��
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			result.data[i * n + j] = (i == j) ? 1.0 : 0;
		}
	}

	for (i = 0; i < n; i++)
	{
		//Ѱ����Ԫ  
		max = matT.data[i * n + i];
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (fabs(matT.data[j * n + i]) > fabs(max))
			{
				max = matT.data[j * n + i];
				k = j;
			}
		}
		//�����Ԫ�����в��ǵ�i�У������н���  
		if (k != i)
		{
			for (j = 0; j < n; j++)
			{
				temp = matT.data[i * n + j];
				matT.data[i * n + j] = matT.data[k * n + j];
				matT.data[k * n + j] = temp;
				//B���潻��  
				temp = result.data[i * n + j];
				result.data[i * n + j] = result.data[k * n + j];
				result.data[k * n + j] = temp;
			}
		}
		//�ж���Ԫ�Ƿ�Ϊ0, ����, �����A�������Ⱦ���,�����������  
		if (matT.data[i * n + i] == 0)
		{
			return false;				//no inverse matrix
		}
		//��ȥA�ĵ�i�г�ȥi������ĸ���Ԫ��  
		temp = matT.data[i * n + i];
		for (j = 0; j < n; j++)
		{
			matT.data[i * n + j] = matT.data[i * n + j] / temp;				//���Խ����ϵ�Ԫ�ر�Ϊ1  
			result.data[i * n + j] = result.data[i * n + j] / temp;			//�������  
		}
		for (j = 0; j < n; j++)        //��0��->��n��  
		{
			if (j != i)                //���ǵ�i��  
			{
				temp = matT.data[j * n + i];
				for (k = 0; k < n; k++)        //��j��Ԫ�� - i��Ԫ��*j��i��Ԫ��  
				{
					matT.data[j * n + k] = matT.data[j * n + k] - matT.data[i * n + k] * temp;
					result.data[j * n + k] = result.data[j * n + k] - result.data[i * n + k] * temp;
				}
			}
		}
	}
	return true;
}
