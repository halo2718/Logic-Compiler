#include<iostream>
#include<stack>
#include<cstring>
#include<cmath>
#include<cstdio>
using namespace std;
char s[10000];
struct Mi{char q;int v;}s0[10000],alpha[20];
int calcu[10000],op;
int bi[10000000],tmp[10000000];
int Truth[10000000][30];
stack<char> stk;

void Display()	//�����ʼ���� 
{
	cout<<"********************************************************************"<<endl;
	cout<<"��ɢ��ѧ��ֵ��ͷ�ʽ����v1.0  ����:����  ����ʱ��:2018/11/20\n"<<endl;
	cout<<"�ó���ʹ��c++��д��IDEΪDev-C++ 5.11, ����ϵͳΪWindows10\n"<<endl;
	cout<<"��������:�ó����ʵ�������������⹫ʽ�����⹫ʽ������ĸҪ��д����"<<endl;
	cout<<"������﷨��ȷ�ԣ������﷨��ȷ�����������沨��ʽ����ֵ��"<<endl;
	cout<<"�Լ��ɸ���ֵ��������⹫ʽ����ȡ��ʽ����ȡ��ʽ�����Լ�����ȡ��ʽ������ȡ��ʽ�ȡ�\n" <<endl;
	cout<<"���ӹ���:�ֶ�������ֵ���ܹ�������⹫ʽ��\n" <<endl;
	cout<<"********************************************************************\n"<<endl;
	cout<<"=======����˵��=======\n"<<endl;
	cout<<"�Ϸ���������Ϊ1,2,3" <<endl;
	cout<<"����1:ʵ�ֻ�������"<<endl;
	cout<<"����2:ʵ�ָ��ӹ���"<<endl;
	cout<<"����3:�˳�����\n"<<endl; 
	cout<<"======================\n"<<endl;
}

int count_k(int p)	//ͳ�����ŵĸ��� 
{
	int cnt=0;
	for(int i=0;i<p;i++)
	{
		if(s[i]=='('||s[i]==')')
		{
			cnt++;
		}
	}
	return cnt;
}

int Prior(char a)
{
	int b=0;
	if(a<=90&&a>=65)
	{
		b=4;
		return b;
	}
	else if(a=='!')
	{
		b=2;
	}
	else if(a=='&'||a=='|')
	{
		b=1;
	}
	else if(a=='^')
	{
		b=0;
	}
	else if(a=='~')
	{
		b=-1;
	}
	else if(a=='('||a==')')
	{
		b=3;
	}
	return b;
} 

void Z_H(int start,int end)	//����������⹫ʽ���沨��ʽ 
{
	int r=0,k=0;
	for(int i=start;i<=end;i++)
	{
		if(!stk.empty()&&stk.top()=='!')
		{
			if(s[i]=='!'||s[i]=='(')
			{
				stk.push(s[i]);
			}
			else
			{
				s0[r].q=s[i];
				r++;
				while(!stk.empty()&&Prior(stk.top())<=2)
				{
					s0[r].q=stk.top();
					r++;
					stk.pop();
				}
			}
		}
		else if(s[i]<=90&&s[i]>=65)
		{
			s0[r].q=s[i];
			r++;
		}
		else if(s[i]==')')
		{
			while(stk.top()!='(')
			{
				s0[r].q=stk.top();
				r++;
				stk.pop();
			}
			stk.pop();
		}
		else if(s[i]=='(')
		{
			stk.push(s[i]);
		}
		else if(!stk.empty()&&(Prior(stk.top())<Prior(s[i])))
		{
			stk.push(s[i]);
		}
		else if(!stk.empty()&&Prior(stk.top())>=Prior(s[i]))
		{
			if(stk.top()!='(')
			{
				while(!stk.empty()&&Prior(stk.top())>=Prior(s[i])&&stk.top()!='(')
				{
					s0[r].q=stk.top();
					r++;
					stk.pop();
				}
				stk.push(s[i]);
			}
			else
			{
				stk.push(s[i]);
			}
		}
		else if(stk.empty()&&s[i]=='!')
		{
			stk.push(s[i]);
		}
		else if((stk.empty())&&(s[i]=='|'||s[i]=='&'||s[i]=='~'||s[i]=='^')) 
		{
			stk.push(s[i]);
		}
	}
	while(!stk.empty()) 
	{
		s0[r].q=stk.top();
		r++;
		stk.pop();
	}
}

bool Check_K(int a)	//������ŵ��﷨��ȷ�� 
{
	int sum1=0,sum2=0;
	for(int i=0;i<=a;i++)
	{
		if(s[i]=='(')
		{
			if(i<a-1)
			{
				if(s[i+1]==')')
				{
					return false;
				}
			}
		sum1++;
		}
		else if(s[i]==')')
		{
			sum2++;
		}
		if(sum1<sum2)
		{
			return false;
		}
	}
	if(sum1==sum2)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Check_A(int a)	//�������ĸ��ص��﷨��ȷ�� 
{
	for(int i=0;i<a;i++)
	{
		if(s[i]<=90&&s[i]>=65) 
		{
			if((s[i+1]<=90&&s[i+1]>=65)||s[i+1]=='!')
			{
				return false;
			}
		}
	}
	return true;
}

bool Check_D(int a) //����Ƿ��г��Ϸ��ַ�������ַ����� 
{
	for(int i=0;i<=a;i++)
	{
		if(!((s[i]>=65&&s[i]<=90)||s[i]=='|'||s[i]=='&'||s[i]=='~'||s[i]=='^'||s[i]=='!'||s[i]=='('||s[i]==')'))
		return false;
	}
	return true;
}

bool Check_S(int a)	//�����������﷨��ȷ�� 
{
	for(int i=0;i<a-1;i++)
	{
		if(s[i]=='|'||s[i]=='&'||s[i]=='~'||s[i]=='^')
		{
			if(s[i+1]==')'||s[i+1]=='|'||s[i+1]=='&'||s[i+1]=='~'||s[i+1]=='^')
			{
				return false;
			}
		}
		else if(s[i]=='!')
		{
			if(s[i+1]==')'||s[i+1]=='|'||s[i+1]=='&'||s[i+1]=='~'||s[i+1]=='^')
			{
				return false;
			}
		}
		else if(s[i]=='(')
		{
			int tes=0;
			if(s[i+1]==')'||s[i+1]=='|'||s[i+1]=='&'||s[i+1]=='~'||s[i+1]=='^')
			{
				return false;
			}
			if(i-1>=0&&s[i-1]<=90&&s[i-1]>=65)
			{
				return false;
			}
			while(i+tes<=a-1&&s[i+tes]!=')')
			{
				tes++;
			}
			
			if(tes==2) return false;
		}
	}
	if(s[a]=='|'||s[a]=='&'||s[a]=='~'||s[a]=='^'||s[a]=='!')
	{
		return false;
	}
	return true;
}


bool Check_Grammar(int a)	//����������ʽ����ȷ�� 
{
	if(Check_K(a)&&Check_A(a)&&Check_S(a)&&Check_D(a))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Or(int a,int b)	//��������� 
{
	int s=1;
	if(a==0&&b==0)
	{
		s=0;
	}
	return s;
}

int And(int a,int b)	//���������� 
{
	int s=0;
	if(a==1&&b==1)
	{
		s=1;
	}
	return s;
}

int Not(int a)	//��������� 
{
	if(a==1)
	{
		return a-1;
	}
	else
	{
		return a+1;
	}
}

int Yunhan(int a,int b)	//�����̺����� 
{
	int s=1;
	if(a==1&&b==0)
	{
		s=0;
	}
	return s;
}

int SYH(int a,int b)	//����˫�̺����� 
{
	int s=1;
	if((a==0&&b==1)||(a==1&&b==0))
	{
		s=0;
	}
	return s;
}

int Count_Alpha(int n)	//ͳ���������ĸ��� 
{
	int cnt=0;
	for(int i=0;i<n;i++)
	{
		if(s0[i].q<=90&&s0[i].q>=65)
		{
			int t=0;
			for(int j=0;j<cnt;j++)
			{
				if(s0[i].q==alpha[j].q)
				{
					t=1;
					break;
				}
			}
			if(!t)
			{
				alpha[cnt].q=s0[i].q;
				cnt++;
			}
		}
	}
	return cnt;
}

void Collect_value(int n)	//ȡ��0��pow(2,n)-1������ֵ�Ķ����Ʊ�ʾ 
{
	for(int i=0;i<n;i++)
	{
		alpha[i].v=bi[i];
	}
}

void Give_Num(int m,int n)	//�����⹫ʽ���и�ֵ 
{
	for(int i=0;i<m;i++)
	{
		if(s0[i].q<=90&&s0[i].q>=65)
		{
			for(int j=0;j<n;j++)
			{
				if(alpha[j].q==s0[i].q)
				{
					s0[i].v=alpha[j].v;
				}
			}
		}
	}
}

int Cal(int n)	//�������⹫ʽ����ֵ 
{
	int ind=0;
	for(int i=0;i<n;i++)
	{
		if(s0[i].q<=90&&s0[i].q>=65)
		{
			ind++;
			int k=i+1,rec=s0[i].v;
			calcu[ind]=s0[i].v;
			s0[i].v=rec;
    	}
		else if(s0[i].q=='|'||s0[i].q=='&'||s0[i].q=='~'||s0[i].q=='^'||s0[i].q=='!')
		{
			if(s0[i].q=='|')
			{
				calcu[ind-1]=Or(calcu[ind-1],calcu[ind]);
			}
			if(s0[i].q=='&')
			{
				calcu[ind-1]=And(calcu[ind-1],calcu[ind]);
			}
			if(s0[i].q=='~')
			{
				calcu[ind-1]=SYH(calcu[ind-1],calcu[ind]);
			}
			if(s0[i].q=='^')
			{
				calcu[ind-1]=Yunhan(calcu[ind-1],calcu[ind]);
			}
			if(s0[i].q=='!')
			{
				ind++;
				calcu[ind-1]=Not(calcu[ind-1]);
			}
			ind--;
		}
	}
	return calcu[1];
}

void Print(int n,int m)	//�����ֵ�� 
{
	for(int i=0;i<n;i++)
	{
		cout<<Truth[m][i]<<" ";
	}
	cout<<Truth[m][n]<<endl;
}

void Xiqu(int a,int N)	//������ֵ�������ȡ��ʽ 
{
	int t=0,ccc=0;
	for(int i=a;i<=pow(2,N)-1+a;i++)
	{
		for(int j=0;j<=N;j++)
		{
			if(j==N&&Truth[i][j]==1)
			{
				t=1;
			}
		}
	}
	cout<<"��ȡ��ʽ:";
	if(t==0) 
	{ 
		cout<<"Empty!\n"<<endl;
		return ;
	}
	for(int i=a;i<=pow(2,N)-1+a;i++)
	{
		if(Truth[i][N]==1) ccc=i;
	}
	for(int i=a;i<=pow(2,N)-1+a;i++)
	{
		if(Truth[i][N]==1)
		{
			cout<<"(";
			for(int j=0;j<N;j++)
			{
				if(Truth[i][j]==1)
				{
					if(j==N-1&&i==ccc)
					{
						cout<<alpha[j].q<<")\n"<<endl;
						return ;
					}
					if(j<N-1)
					{
						cout<<alpha[j].q<<"&";
					}
					else
					{
						cout<<alpha[j].q;
					}
				}
				else
				{
					if(j==N-1&&i==ccc)
					{
						cout<<"!"<<alpha[j].q<<")\n"<<endl;
						return ;
					}
					if(j<N-1)
					{
						cout<<"!"<<alpha[j].q<<"&";
					}
					else
					{
						cout<<"!"<<alpha[j].q;
					}
				}
			}
			cout<<")|";
		}
	}
	cout<<"\n"<<endl;
}

void Hequ(int a,int N)	//������ֵ�������ȡ��ʽ
{
	int t=0,ccc=0;
	for(int i=pow(2,N)-1+a;i>=a;i--)
	{
		for(int j=0;j<=N;j++)
		{
			if(j==N&&Truth[i][j]==0)
			{
				t=1;
			}
		}
	}
	cout<<"��ȡ��ʽ:";
	if(t==0)
	{
		cout<<"Empty!\n"<<endl;
		return ;
	}
	for(int i=pow(2,N)-1+a;i>=a;i--)
	{
		if(Truth[i][N]==0) ccc=i;
	}
	for(int i=pow(2,N)-1+a;i>=a;i--)
	{
		if(Truth[i][N]==0)
		{
			cout<<"(";
			for(int j=0;j<N;j++)
			{
				if(Truth[i][j]==0)
				{
					if(i==ccc&&j==N-1)
					{
						cout<<alpha[j].q<<")\n"<<endl;
						return ;
					}
					if(j<N-1)
					{
						cout<<alpha[j].q<<"|";
					}
					else
					{
						cout<<alpha[j].q;
					}
				}
				else
				{
					if(i==ccc&&j==N-1)
					{
						cout<<"!"<<alpha[j].q<<")\n"<<endl;
						return ;
					}
					if(j<N-1)
					{
						cout<<"!"<<alpha[j].q<<"|";
					}
					else
					{
						cout<<"!"<<alpha[j].q;
					}
				}
			}
			cout<<")&";
		}
	}
	cout<<"\n"<<endl;
}

void M_Xiqu(int N)	//������ֵ���������ȡ��ʽ
{
	int j=0,k=0;
	cout<<"����ȡ��ʽΪ:"; 
	for(int i=0;i<pow(2,N);i++)
	{
		if(Truth[i][N]==1) tmp[j++]=i;
	}
	if(j==0)
	{
		cout<<"Empty!\n"<<endl;
		return ;
	}
	while(k<j-1) cout<<"m"<<tmp[k++]<<"|";
	cout<<"m"<<tmp[k]<<endl;
	k=0;
	cout<<"\n����:"<<"\\/";
	while(k<j-1) cout<<tmp[k++]<<",";
	cout<<tmp[k]<<endl;
	memset(tmp,0,sizeof(tmp));
	cout<<endl;
}

void M_Hequ(int N)	//������ֵ���������ȡ��ʽ
{
	int j=0,k=0;
	cout<<"����ȡ��ʽΪ:";
	for(int i=0;i<pow(2,N);i++)
	{
		if(Truth[i][N]==0) tmp[j++]=pow(2,N)-i-1;
	}
	if(j==0)
	{
		cout<<"Empty!\n"<<endl;
		return ;
	}
	while(k<j-1) cout<<"M"<<tmp[k++]<<"&";
	cout<<"M"<<tmp[k]<<endl;
	k=0;
	cout<<"\n����:"<<"/\\";
	while(k<j-1) cout<<tmp[k++]<<",";
	cout<<tmp[k]<<endl;
	memset(tmp,0,sizeof(tmp));
	cout<<endl;
}

int main()
{
/*	freopen("in_10.txt","r",stdin);
	freopen("data_10.txt","w",stdout);    */ 
	Display();
	while(true)
	{
		cout<<"������Ϸ������Կ�ʼ���������:"<<endl;
		cin>>op; 
		cout<<endl;
		if(op==3) return 0;
		else if(op==1)
		{
			cout<<"�������������⹫ʽ(�������Ϊ��д��ĸ):"<<endl;
			cin>>s;
			cout<<"\n**************���н��****************\n"<<endl;
			int len=strlen(s);
			if(!Check_Grammar(len-1))
			{
				cout<<"��������⹫ʽ���Ϸ�\n"<<endl; 
				cout<<"**************************************\n"<<endl;
				continue;
			}		 
			cout<<"��������⹫ʽ�Ϸ�\n"<<endl;
			Z_H(0,len-1); 
			cout<<"���沨��ʽΪ:"; 
			for(int i=0;i<len;i++)
			{
				cout<<s0[i].q;
			}
			int len0=len-count_k(len);
			int lena=Count_Alpha(len0);
			for(int i=0;i<pow(2,lena);i++)
			{
				int K=i;
				for(int j=lena-1;j>=0;j--)
				{
					bi[j]=K%2;
					K/=2;
				}
				Collect_value(lena);
				Give_Num(len0,lena);
				for(int j=0;j<lena;j++) Truth[i][j]=bi[j];
				Truth[i][lena]=Cal(len0);
			}
			cout<<"\n"<<endl;
			cout<<"�����⹫ʽ��ֵ��Ϊ:"<<endl;
			for(int i=0;i<lena;i++) cout<<alpha[i].q<<" ";
			cout<<"*"<<endl;
			for(int i=0;i<pow(2,lena);i++)
			{
				Print(lena,i);
			}
			cout<<endl;
			Xiqu(0,lena);
			Hequ(0,lena);
			M_Xiqu(lena);
			M_Hequ(lena);
			memset(alpha,0,sizeof(alpha));
			memset(Truth,0,sizeof(Truth));
			memset(s0,0,sizeof(s0));
			memset(calcu,0,sizeof(calcu));
			memset(bi,0,sizeof(bi));
			cout<<"**************************************"<<endl;
			}
		else if(op==2)
		{
			cout<<"������һ�����֣�����ʽ���������ĸ���:"<<endl; 
			int N=0;
			cin>>N;
			cout<<"\n������N+1����ĸ���Կո�ֿ�������ǰN����ĸΪ������Ӧ������ͬ:"<<endl;
			for(int i=0;i<=N;i++)
			{
				cin>>alpha[i].q;
			}
			cout<<"\n�밴�չ淶�ĸ�ʽ������ֵ����ȥ���������У��������ÿո���зֿ�(����(N+1)*pow(2,n)������):"<<endl;
			for(int i=0;i<pow(2,N);i++)
			{
				for(int j=0;j<=N;j++)
				{
					cin>>Truth[i][j];
				}
			} 
			cout<<"\n**************���н��****************\n"<<endl;
			Xiqu(0,N);
			Hequ(0,N);
			memset(alpha,0,sizeof(alpha));
			memset(Truth,0,sizeof(Truth));
			cout<<"**************************************"<<endl;
		}
		else cout<<"���ֲ��Ϸ�,����������!\n";
		cout<<endl;
	}
}

