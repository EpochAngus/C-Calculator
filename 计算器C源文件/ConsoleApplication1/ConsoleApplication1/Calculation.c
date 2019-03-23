#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

//����ջ 
typedef struct nstack
{
	double num[20];
	int top;
}NumStack;

//����ջ
typedef struct sstack
{
	char symbol[20];
	int level[20];
	int top;
}SymbolStack;

double solve(char str1[]);

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
	char str9[] = "3.3+3.3";
	char str10[] = "5/(3*(2.0))";
	char str11[] = "2%0";
	char str12[] = "0/2";
	char str13[] = "0%2";
	char str14[] = "~5";
	char str15[] = "~";
	char str16[] = "s1";
	char str17[] = "c1";
	char str18[] = "1+(1+(2+3))";
	double a = solve(str18);
	printf("%lf",a);
}

double solve(char str[])
{
	int ntNum, stNum;
	int length;
	int i = 0;
	double a1, a2, a3;
	int flag=1;																//��һ���ַ���Ϊ������Ϊ0����Ϊ������Ϊ1
	char ch,temp;
	char *str1;
	int notchange = 1;
	int dotflag=0;															//dotflagΪ0���ǵ� 1�ǵ�
	length = strlen(str);
	//��Ҫ������ַ���Ϊstr1 ���*
	str1 = (char *)malloc((length+1) * sizeof(char));
	strcpy(str1, str);
	str1[length] = '$';
	str1[length+1] = '\0';
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
	stStack.level[0] = 0;												//*�����ȼ����
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
				if (dotflag == 0)
					for (int j = 0; j < 10; j++)								//��0��9֮�����,ȷ����һλ���ĸ���
					{
						if (ch - 48 == j)
							ntStack.num[ntStack.top] = ntStack.num[ntStack.top] * 10 + j;
					}
				else
				{
					for (int j = 0; j < 10; j++)								//��0��9֮�����,ȷ����һλ���ĸ���
					{
						if (ch - 48 == j)
						{
							ntStack.num[ntStack.top] =ntStack.num[ntStack.top]+j*(1.0/pow(10,dotflag));
							dotflag++;
						}
					}
				}
			}
			else if (ch == '.')
			{
				dotflag = 1;
			}
			//����Ƿ���
			else//'+','-'���ȼ�Ϊ1 '*','/','^','%'���ȼ�Ϊ2,'(',')'���ȼ�Ϊ3
			{
				dotflag = 0;
				if (ch == '+' || ch == '-')
				{
					stStack.symbol[++stStack.top] = ch;
					stStack.level[stStack.top] = 1;
				}
				else if (ch == '*' || ch == '/' || ch == '^' || ch == '%'||ch=='~')
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
				else if (ch == 's' || ch == 'c')
				{
					stStack.symbol[++stStack.top] = ch;
					stStack.level[stStack.top] = 2;
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
				a2 = ntStack.num[ntStack.top-1];
				//��Ϊ�����ǵ�Ŀ����� ���Ե�������
				if (temp == '~')
				{
					//a3������
					a3 = sqrt(a1);
					//���ų�ջ
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top] = NULL;
					stStack.level[stStack.top--] = 0;
					//ʵ����ջ
					ntStack.num[ntStack.top] = a3;
					continue;
				}
				else if (temp == 's')
				{
					//a3������
					a3 = sin(a1);
					//���ų�ջ
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top] = NULL;
					stStack.level[stStack.top--] = 0;
					//ʵ����ջ
					ntStack.num[ntStack.top] = a3;
					continue;
				}
				else if (temp == 'c')
				{					//a3������
					a3 = cos(a1);
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
					else if (temp == '^')
						a3 = pow(a2, a1);
					else if (temp == '%')
					{
						if (a1 == 0)
							return 0;
						a3 =(int)a2%(int)a1;
					}	
					else if (temp == '/')
					{
						if (a1 == 0)
							return 0;
						a3 = a2 / a1;
					}
					//���ų�ջ
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top] = 0;
					stStack.symbol[stStack.top--] = NULL;
					//��������ջ
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
			else if (stStack.symbol[stStack.top-1] == '~')
			{					
				a1 = ntStack.num[ntStack.top];
				//a3������
				a3 = sqrt(a1);
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
			else if (stStack.symbol[stStack.top-1] == 's')
			{
				a1 = ntStack.num[ntStack.top];
				//a3������
				a3 = sin(a1);
				//���ų�ջ
				stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
				stStack.level[stStack.top - 1] = stStack.level[stStack.top];
				stStack.symbol[stStack.top] = NULL;
				stStack.level[stStack.top--] = 0;
				//ʵ����ջ
				ntStack.num[ntStack.top] = a3;
				continue;
			}
			else if (stStack.symbol[stStack.top-1] == 'c')
			{	
				a1 = ntStack.num[ntStack.top];
				//a3������
				a3 = cos(a1);
				//���ų�ջ
				stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
				stStack.level[stStack.top - 1] = stStack.level[stStack.top];
				stStack.symbol[stStack.top] = NULL;
				stStack.level[stStack.top--] = 0;
				//ʵ����ջ
				ntStack.num[ntStack.top] = a3;
				continue;
			}
			temp = stStack.symbol[stStack.top - 1];
			a1 = ntStack.num[ntStack.top];
			a2 = ntStack.num[ntStack.top-1];
			if (temp == '+')
				a3 = a2 + a1;
			else if (temp == '-')
				a3 = a2 - a1;
			else if (temp == '*')
				a3 = a2*a1;
			else if (temp == '^')
				a3 = pow(a2, a1);
			else if (temp == '%')
			{
				if (a1 == 0)
					return 0;
				a3 = (int)a2 % (int)a1;
			}			
			else if (temp == '/')
			{
				if (a1 == 0)
					return 0;
				a3 = a2 / a1;
			}
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
