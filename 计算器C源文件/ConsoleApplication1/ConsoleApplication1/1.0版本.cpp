#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

//����ջ 
typedef struct nstack
{
	int num[20];
	int top;
}NumStack;

//����ջ
typedef struct sstack
{
	char symbol[20];
	int level[20];
	int top;
}SymbolStack;

int solve(char str1[]);

int main()
{
	char str1[] = "1+1+2*2/4+3-5*(4+6-8*7)+5";	//�ڶ����������ȼ����ڵ�һ������ �����һ�����ȼ� �ټ���
	char str2[] = "2-2-2";						//�ڶ����������ȼ����ڵ�һ������ ������
	char str3[] = "3*3*3";						//�ڶ����������ȼ�С�ڵ�һ������ �����һ�����ȼ� ������
	char str4[] = "4/4/1";						//�������( ������� ֱ�������ڶ�������Ϊ) �����һ������ ֱ����ǰ����Ϊ( �����ջ
	char str5[] = "(5+2*(1+2+3))*3-5/1";
	char str6[] = "1+1+~4";
	char str7[] = "6%7";
	char str8[] = "~23";
	int a = solve(str5);
	printf("%d", a);
}

int solve(char str[])
{
	int ntNum, stNum;
	int length;
	int i = 0;
	int a1, a2, a3;
	int flag = 1;																//��һ���ַ���Ϊ������Ϊ0����Ϊ������Ϊ1
	char ch, temp;
	char *str1;
	int notchange = 1;
	length = strlen(str);
	//��Ҫ������ַ���Ϊstr1 ���*
	str1 = (char *)malloc((length + 1) * sizeof(char));
	strcpy(str1, str);
	str1[length] = '$';
	str1[length + 1] = '\0';
	NumStack ntStack;
	SymbolStack stStack;
	for (int i = 0; i < 20; i++)
	{
		stStack.symbol[i] = NULL;
		stStack.level[i] = 0;
		ntStack.num[i] = 0;
	}
	ntStack.top = -1;														//topָ����Ǿ���value�����һ������
	stStack.top = -1;
	stStack.symbol[++stStack.top] = '$';
	stStack.level[0] = 0;													//*�����ȼ����
																			//������ջ���� ͬʱ���д��Լ��㲢��ȥԲ����
	while (stStack.symbol[0] == '$')										//������ջ�������*����ջ�� 
	{
		//�������ֺͷ�����ջ
		if ((ch = str1[i]) != '\0')											//��ǰ�㲻���ַ���ĩβ��'\0'ʱ
		{
			//������ջ����
			//�����0~9֮�����
			if (ch >= 48 && ch <= 57)										//ascii '0'=48 9='57'
			{
				if (flag == 1)												//��Ϊ����
				{
					ntStack.top++;
					flag = 0;
				}
				for (int j = 0; j < 10; j++)								//��0��9֮�����,ȷ����һλ���ĸ���
				{
					if (ch - 48 == j)
						ntStack.num[ntStack.top] = ntStack.num[ntStack.top] * 10 + j;
				}
			}
			//����Ƿ���
			else//'+','-'���ȼ�Ϊ1 '*','/','^','%'���ȼ�Ϊ2,'(',')'���ȼ�Ϊ3
			{
				if (ch == '+' || ch == '-')
				{
					stStack.symbol[++stStack.top] = ch;
					stStack.level[stStack.top] = 1;
				}
				else if (ch == '*' || ch == '/' || ch == '^' || ch == '%' || ch == '~')
				{
					stStack.symbol[++stStack.top] = ch;
					stStack.level[stStack.top] = 2;
				}
				else if (ch == '(')
				{
					stStack.symbol[++stStack.top] = ch;
					stStack.level[stStack.top] = 3;
				}
				else if (ch == ')')
				{
					stStack.symbol[++stStack.top] = ch;
					stStack.level[stStack.top] = 3;
				}
				else if (ch == '$')
				{
					stStack.symbol[++stStack.top] = ch;
					stStack.level[stStack.top] = 0;
				}
				flag = 1;													//�õ�ǰ��ջΪ����
			}
		}

		//����ǰ��ջΪ�����ŵ���� �����������������ڵ��������ݼ������ ������ų�ջ
		if (stStack.symbol[stStack.top] == ')')
		{
			//������������������ջ������ʱ��ջ
			while (stStack.symbol[stStack.top - 1] != '(')
			{
				temp = stStack.symbol[stStack.top - 1];
				a1 = ntStack.num[ntStack.top];
				a2 = ntStack.num[ntStack.top - 1];
				//��Ϊ�����ǵ�Ŀ����� ���Ե�������
				if (temp == '~')
				{
					//a3������
					a3 = (int)sqrt(a1);
					//���ų�ջ
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top] = NULL;
					stStack.level[stStack.top--] = 0;
					//ʵ����ջ
					ntStack.num[ntStack.top] = a3;
					continue;
				}
				//����˫Ŀ�����
				else
				{
					if (temp == '+')
						a3 = a2 + a1;
					else if (temp == '-')
						a3 = a2 - a1;
					else if (temp == '*')
						a3 = a2*a1;
					else if (temp == '/')
						a3 = a2 / a1;
					else if (temp == '^')
						a3 = pow(a2, a1);
					else if (temp == '%')
						a3 = a2%a1;
					//���ų�ջ
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top] = 0;
					stStack.symbol[stStack.top--] = NULL;
					//ʵ����ջ
					ntStack.num[ntStack.top--] = 0;
					ntStack.num[ntStack.top] = a3;
				}
			}
			//�˳�ѭ�� ���������ź�������
			stStack.symbol[stStack.top] = NULL;
			stStack.symbol[stStack.top - 1] = NULL;
			stStack.level[stStack.top--] = 0;
			stStack.level[stStack.top--] = 0;
		}
		//���˷�����ջ ����һ�����ŵ����ȼ����ڱ�����ջ���ŵ����ȼ�
		else if (flag == 1 && stStack.level[stStack.top] <= stStack.level[stStack.top - 1])
		{
			if (stStack.symbol[stStack.top] == '$'&&stStack.symbol[stStack.top - 1] == '$')
				break;
			else if (stStack.symbol[stStack.top - 1] == '(')
			{
				i++;
				continue;
			}
			else if (stStack.symbol[stStack.top - 1] == '~')
			{
				a1 = ntStack.num[ntStack.top];
				//a3������
				a3 = (int)sqrt(a1);
				//���ų�ջ
				stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
				stStack.level[stStack.top - 1] = stStack.level[stStack.top];
				stStack.symbol[stStack.top] = NULL;
				stStack.level[stStack.top--] = 0;
				//ʵ����ջ
				ntStack.num[ntStack.top] = a3;
				i++;
				continue;
			}
			temp = stStack.symbol[stStack.top - 1];
			a1 = ntStack.num[ntStack.top];
			a2 = ntStack.num[ntStack.top - 1];
			if (temp == '+')
				a3 = a2 + a1;
			else if (temp == '-')
				a3 = a2 - a1;
			else if (temp == '*')
				a3 = a2*a1;
			else if (temp == '/')
				a3 = a2*a1;
			else if (temp == '^')
				a3 = pow(a2, a1);
			else if (temp == '%')
				a3 = a2%a1;

			//���ų�ջ
			stStack.level[stStack.top - 1] = stStack.level[stStack.top];
			stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
			stStack.level[stStack.top] = 0;
			stStack.symbol[stStack.top--] = NULL;
			//ʵ����ջ
			ntStack.num[ntStack.top--] = 0;
			ntStack.num[ntStack.top] = a3;
		}
		i++;
	}
	return ntStack.num[0];
}
