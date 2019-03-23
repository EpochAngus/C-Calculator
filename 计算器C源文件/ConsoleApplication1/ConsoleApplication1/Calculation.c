#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

//数字栈 
typedef struct nstack
{
	double num[20];
	int top;
}NumStack;

//符号栈
typedef struct sstack
{
	char symbol[20];
	int level[20];
	int top;
}SymbolStack;

double solve(char str1[]);

int main()
{
	char str1[] = "1+1+2*2/4+3-5*(4+6-8*7)+5";	//第二个符号优先级等于第一个符号 先算第一个优先级 再继续
	char str2[] = "2-2-2";						//第二个符号优先级大于第一个符号 继续读
	char str3[] = "3*3*3";						//第二个符号优先级小于第一个符号 计算第一个优先级 继续读
	char str4[] = "4/4/1";						//如果遇到( 则继续进 直到读到第二个符号为) 计算第一个符号 直到当前符号为( 将其出栈
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
	int flag=1;																//上一个字符若为数字则为0，若为符号则为1
	char ch,temp;
	char *str1;
	int notchange = 1;
	int dotflag=0;															//dotflag为0不是点 1是点
	length = strlen(str);
	//需要处理的字符串为str1 最后补*
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
	ntStack.top = -1;														//top指向的是具有value的最后一个区域
	stStack.top = -1;
	stStack.symbol[++stStack.top] = '$';
	stStack.level[0] = 0;												//*号优先级最低
	//进行入栈操作 同时进行粗略计算并消去圆括号
	while (stStack.symbol[0] == '$')										//当符号栈里的所有*都出栈后 
	{
		//进行数字和符号入栈
		if ((ch = str1[i]) != '\0')											//当前点不是字符串末尾的'\0'时
		{
			//进行入栈操作
			//如果是0~9之间的数
			if (ch >= 48 && ch <= 57)										//ascii '0'=48 9='57'
			{
				if (flag == 1)												//若为数字
				{
					ntStack.top++;
					flag = 0;
				}
				if (dotflag == 0)
					for (int j = 0; j < 10; j++)								//在0到9之间遍历,确定这一位是哪个数
					{
						if (ch - 48 == j)
							ntStack.num[ntStack.top] = ntStack.num[ntStack.top] * 10 + j;
					}
				else
				{
					for (int j = 0; j < 10; j++)								//在0到9之间遍历,确定这一位是哪个数
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
			//如果是符号
			else//'+','-'优先级为1 '*','/','^','%'优先级为2,'(',')'优先级为3
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
				flag = 1;													//置当前进栈为符号
			}
		}

		//处理当前进栈为右括号的情况 将左括号与右括号内的所有内容计算完毕 最后将括号出栈
		if (stStack.symbol[stStack.top] == ')')
		{
			//当左括号与右括号在栈中相邻时出栈
			while (stStack.symbol[stStack.top - 1] != '(')
			{
				temp = stStack.symbol[stStack.top - 1];
				a1 = ntStack.num[ntStack.top];
				a2 = ntStack.num[ntStack.top-1];
				//因为根号是单目运算符 所以单独处理
				if (temp == '~')
				{
					//a3保存结果
					a3 = sqrt(a1);
					//符号出栈
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top] = NULL;
					stStack.level[stStack.top--] = 0;
					//实数出栈
					ntStack.num[ntStack.top] = a3;
					continue;
				}
				else if (temp == 's')
				{
					//a3保存结果
					a3 = sin(a1);
					//符号出栈
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top] = NULL;
					stStack.level[stStack.top--] = 0;
					//实数出栈
					ntStack.num[ntStack.top] = a3;
					continue;
				}
				else if (temp == 'c')
				{					//a3保存结果
					a3 = cos(a1);
					//符号出栈
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top] = NULL;
					stStack.level[stStack.top--] = 0;
					//实数出栈
					ntStack.num[ntStack.top] = a3;
					continue;
				}
				//若是双目运算符
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
					//符号出栈
					stStack.level[stStack.top - 1] = stStack.level[stStack.top];
					stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
					stStack.level[stStack.top] = 0;
					stStack.symbol[stStack.top--] = NULL;
					//浮点数出栈
					ntStack.num[ntStack.top--] = 0;
					ntStack.num[ntStack.top] = a3;
				}
			}
			//退出循环 处理左括号和右括号
			stStack.symbol[stStack.top] = NULL;
			stStack.symbol[stStack.top - 1] = NULL;
			stStack.level[stStack.top--] = 0;
			stStack.level[stStack.top--] = 0;
		}
		//做了符号入栈 且上一个符号的优先级高于本次入栈符号的优先级
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
				//a3保存结果
				a3 = sqrt(a1);
				//符号出栈
				stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
				stStack.level[stStack.top - 1] = stStack.level[stStack.top];
				stStack.symbol[stStack.top] = NULL;
				stStack.level[stStack.top--] = 0;
				//实数出栈
				ntStack.num[ntStack.top] = a3;
				i++;
				continue;
			}
			else if (stStack.symbol[stStack.top-1] == 's')
			{
				a1 = ntStack.num[ntStack.top];
				//a3保存结果
				a3 = sin(a1);
				//符号出栈
				stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
				stStack.level[stStack.top - 1] = stStack.level[stStack.top];
				stStack.symbol[stStack.top] = NULL;
				stStack.level[stStack.top--] = 0;
				//实数出栈
				ntStack.num[ntStack.top] = a3;
				continue;
			}
			else if (stStack.symbol[stStack.top-1] == 'c')
			{	
				a1 = ntStack.num[ntStack.top];
				//a3保存结果
				a3 = cos(a1);
				//符号出栈
				stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
				stStack.level[stStack.top - 1] = stStack.level[stStack.top];
				stStack.symbol[stStack.top] = NULL;
				stStack.level[stStack.top--] = 0;
				//实数出栈
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
			//符号出栈
			stStack.level[stStack.top - 1] = stStack.level[stStack.top];
			stStack.symbol[stStack.top - 1] = stStack.symbol[stStack.top];
			stStack.level[stStack.top] = 0;
			stStack.symbol[stStack.top--] = NULL;
			//实数出栈
			ntStack.num[ntStack.top--] = 0;
			ntStack.num[ntStack.top] = a3;
		}
		i++;
	}
	return ntStack.num[0];
}
