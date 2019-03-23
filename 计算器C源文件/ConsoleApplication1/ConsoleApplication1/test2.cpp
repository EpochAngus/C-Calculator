#include<stdio.h>
#include<stdlib.h>
int get_saddle_point(int *matrix, int row, int line);

int main()
{
	int matrix[5*5] = {
	0,1,0,0,0,
	6,7,8,4,0,
	11,23,9,8,55,
	3,4,5,6,0,
	10,9,8,7,11 };
	get_saddle_point(matrix, 5, 5);
}

int get_saddle_point(int *matrix, int row, int line)
{
	int *rmin = (int *)malloc(row * sizeof(int));
	int *y_min = (int *)malloc(row * sizeof(int));
	int *lmax = (int *)malloc(line * sizeof(int));
	int temp;
	//�����������СԪ��
	for (int i = 0; i < row; i++)
	{
		rmin[i] = matrix[i*row+0];
		y_min[i] = 0;
		for (int j = 0; j < line; j++)
		{
			if (rmin[i] > matrix[i*row+j])
			{
				temp = matrix[i*row + j];
				matrix[i*row + j] = rmin[i];
				rmin[i] = matrix[i*row + j];
				y_min[i] = j;
			}
		}
	}
	//���ÿ������Ԫ��
	for (int i = 0; i < line; i++)									//ȡÿ��
	{
		lmax[i] = matrix[0*row+i];									//�ݴ�Ϊÿ�е�һ��Ԫ��Ϊ���
		for (int j = 0; j < row; j++) 
		{
			if (lmax[i] < matrix[j*row+i])							//������ֵ�Ƚ�С
			{
				temp=matrix[j*row + i];
				matrix[j*row + i] =lmax[i];
				lmax[i] = temp;
			}
		}
	}
	for (int i = 0; i < row; i++)
	{
		if (rmin[i] == lmax[y_min[i]])	//��Сֵ�����������ֵ���
			printf("(%d,%d)\n",i+1,y_min[i]+1);
	}
	return 0;
}