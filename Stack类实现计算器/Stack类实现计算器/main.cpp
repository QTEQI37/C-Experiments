#include<iostream>
#include"stack.h"
using namespace std;

string GetSuffix(string s, stack s1);
int GetPri(char ch);
int GetResult(string str ,stack s);
int main() 
{
	while (true)
	{
		stack s1;//s1�ַ�ջ
		string OriEqu;//�����ַ����洢ԭ���ʽ
		cout << "����������Ҫ�����ʽ�ӣ����ԡ�=����β��";
		cin >> OriEqu;
		string Equ = GetSuffix(OriEqu, s1);//��ȡ��׺���ʽ
		stack s2;
		int result = GetResult(Equ, s2);//��ȡ������
		cout << "��ʽ�ӽ��Ϊ��" << result;
		cout << "�����Ƿ�Ҫ����:(Y/N)" << endl;
		char ch;
		cin >> ch;
		if (ch == 'N') 
		{
			return 0;
		}
	};
	return 0;
}

string GetSuffix(string OriEqu, stack s1)
{
	int i = 0;
	string str;//��׺���ʽ
	while (OriEqu.at(i) != '=')  //����ȫ���ַ�,�����ѹջ�����ֽ����ַ���
	{
		char ch = OriEqu.at(i);
		if (isdigit(ch))//�ж��ǲ�������
		{
			//�����ַ���
			str += ch;
		}
		else //�ָ��������ջ
		{
			if (ch == '(') //������ֱ����ջ
			{
				s1.push(ch);
			}
			else if (ch == ')') //��������Ҫ�ҵ�������
			{
				while ( !s1.isempty() && s1.gettop() != '(' )
				{
					str += s1.pop();//û�ҵ�������֮ǰ��ȫ���������ջ
				}
				if (s1.isempty())//���֮ǰ�Ƿ����������
				{
					cout << "���Ų�ƥ�䣡����" << endl;
					return "";
				}
				s1.pop();//�����ų�ջ
			}
			else if (GetPri(ch) == 2)
			{
				//*/���ȼ��ߣ�����ֱ����ջ
				while (s1.isempty() != true && s1.gettop() != '(' && GetPri(ch) == GetPri(s1.gettop()))//��Ϊ�ղ�����˲���������
				{
					s1.pop();
				}
				s1.push(ch);//����ǰ�������ջ
			}
			else if(GetPri(ch) ==1)
			{
				//+-���ȼ��ͣ���Ҫ�ѵȼ��ߵĶ���ջ�Լ�������ջ
				while (!s1.isempty() && s1.gettop() != '(' && GetPri(ch) <= GetPri(s1.gettop()))
				{
					str += s1.pop();
				}
				s1.push(ch);
			}
			else 
			{
				cout << "���ʽ�����Ƿ��ַ���" << endl;
				return "";
			}
		}
		i++;
	}
	while (s1.isempty() != true)
	{	
		if (s1.gettop() == '(')
        {
            cout << "���Ų�ƥ�䣡" << endl;
            return "";
        }
		str += s1.pop();
	}
	s1.clearstack();
	return str;
}

int GetResult(string str,stack s1) 
{
	int len = str.size();
	int i = 1;
	//���ڴ��ݹ������Ǻ�׺���ʽ����һ���ַ�һ��������,ֱ��ѹջ
	int number = str.at(0) - '0';
	s1.push(number);
	while (i < len)
	{
		char ch = str.at(i);
		if (isdigit(ch)) // �ж��Ƿ�Ϊ����
		{
			int num = ch - '0';
			s1.push(num);
		}
		else if (ispunct(ch)) // �ж��Ƿ�Ϊ�����
		{
			int num2 = s1.pop();
			int num1 = s1.pop();
			switch (ch)
			{
			case '+':
				s1.push(num1 + num2);
				break;
			case '-':
				s1.push(num1 - num2);
				break;
			case '*':
				s1.push(num1 * num2);
				break;
			case '/':
				if (num2 == 0)
				{
					cout << "��0����" << endl;
					return 0;
				}
				s1.push(num1 / num2);
				break;
			default:
				cout << "����Ĳ���" << endl;
				return 0;
			}
		}
		i++;
	}
	return s1.pop();
}

int GetPri(char ch) 
{
	int level = 0;//���ȼ�
	switch (ch)
	{
	case '+':
	case '-':
		level = 1;
		break;
	case '*':
	case '/':
		level = 2;
		break;
	default:
		break;
	}
	return level;
}