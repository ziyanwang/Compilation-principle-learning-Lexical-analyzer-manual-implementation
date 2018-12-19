#include<iostream>
#include<stack>
#include<string.h>
#include<math.h>
char *c=new char[20];
int numOfChar=0; 
int begin=0;
//action�� 
int action[20][20]={
	//+ - * / ( ) num $ 
	{0,0,0,0,4,0,5,0},
	{6,7,8,9,0,0,0,666},
	{-4,-4,8,9,0,-4,0,-4},
	{-7,-7,-7,-7,0,-7,0,-7},
	{0,0,0,0,4,0,5,0},
	{-9,-9,-9,-9,0,-9,0,-9},
	{0,0,0,0,4,0,5,0},
	{0,0,0,0,4,0,5,0},
	{0,0,0,0,4,0,5,0},
	{0,0,0,0,4,0,5,0},
	{6,7,8,9,0,15,0,0},
	{-2,-2,8,9,0,-2,0,-2},
	{-3,-3,8,9,0,-3,0,-3},
	{-5,-5,-5,-5,0,-5,0,-5},
	{-6,-6,-6,-6,0,-6,0,-6},
	{-8,-8,-8,-8,0,-8,0,-8}
};

//goto�� 
int goto_table[20][20]={
	// e,t,f
	{0,1,2,3},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,10,2,3},
	{0,0,0,0},
	{0,0,11,3},
	{0,0,12,3},
	{0,0,0,13},
	{0,0,0,14},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
};

using namespace std;
int turnToInt()//�������ֵת��Ϊ���е�״̬ 
{
	if(c[begin]=='+')
		{
			return 0;
		}
		else if(c[begin]=='-')
		{
			return 1;
		}
		else if(c[begin]=='*')
		{
			return 2;
		}
		else if(c[begin]=='/')
		{
			return 3;
		}
		else if(c[begin]=='(')
		{
			return 4;
		}
		else if(c[begin]==')')
		{
			return 5;
		}
		else if(c[begin]>='0'&&c[begin]<='9')
		{
			//�����num���ܻ�ܶ����� 
			while(c[begin+1]>='0'&&c[begin+1]<='9')
			{
				begin++;
			}
			return 6;
		}
		else if(c[begin]=='$')
		{
			return 7;
		}
}

void grammar_translation()
{
	string grammar[20]={
	" ",
	"S->E",
	"E->E+T","E->E-T","E->T",
	"T->T*F","T->T/F","T->F",
	"F->(E)","F->num"
};

	stack<int> stkForChar;
	stack<int> stkForState;
	
	stkForState.push(0);
	while(true)
	{
		int temp_state=stkForState.top();//�ҳ�Ŀǰ��ջ��״̬ 
		//+ - * / ( ) num $ 
		int temp_string=turnToInt();
		int temp_operate=action[temp_state][temp_string];//ͨ����ѯaction���ò��� 
		if(temp_operate==666)//����״̬ 
		{
			cout<<"ACC"<<endl;
			break;
		}
		else if(temp_operate>0)//�ƽ����� 
		{
			//���ַ�ѹ���ַ�ջ 
			stkForChar.push(turnToInt());
			begin++;
			//���µ�״̬ѹ��״̬ջ 
			stkForState.push(action[temp_state][temp_string]);
			cout<<"shift "<<action[temp_state][temp_string]<<endl;
		}
		else if(temp_operate<0)//��Լ���� 
		{
			cout<<"reduce by "<< grammar[abs(temp_operate)] <<endl;
			//"E->E+T",
			if(temp_operate==-2)
			{
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.push(-1);
				stkForState.push(goto_table[stkForState.top()][1]);
			}
			//"E->E-T",
			if(temp_operate==-3)
			{
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.push(-1);
				stkForState.push(goto_table[stkForState.top()][1]);
			}
			//"E->T",
			if(temp_operate==-4)
			{
				stkForChar.pop();
				stkForState.pop();
				stkForChar.push(-1);
				stkForState.push(goto_table[stkForState.top()][1]);
			}
			//"T->T*F"
			if(temp_operate==-5)
			{
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.push(-2);
				stkForState.push(goto_table[stkForState.top()][2]);
			}
			//"T->T/F",
			if(temp_operate==-6)
			{
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.push(-2);
				stkForState.push(goto_table[stkForState.top()][2]);
			}
			//"T->F",
			if(temp_operate==-7)
			{
				stkForChar.pop();
				stkForState.pop();
				stkForChar.push(-2);
				stkForState.push(goto_table[stkForState.top()][2]);
			}
			//"F->(E)",
			if(temp_operate==-8)
			{
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.pop();
				stkForState.pop();
				stkForChar.push(-3);
				stkForState.push(goto_table[stkForState.top()][3]);
			}
			//"F->num"
			if(temp_operate==-9)
			{
				stkForChar.pop();
				stkForState.pop();
				stkForChar.push(-3);
				stkForState.push(goto_table[stkForState.top()][3]);
			}
		}
		else if(temp_operate==0)
		{
			cout<<"ERROR"<<endl;
			break;
		}
	}
}

int main()
{
	
	string str;
	cin>>str;
	//ʹ��һ��string����������ַ�����
	//���ҽ���ת��Ϊ�ַ����鷽�㴦�� 
	strcpy(c,str.c_str());
	numOfChar=str.length();
	c[numOfChar]='$';
	grammar_translation();
	return 0;
}
