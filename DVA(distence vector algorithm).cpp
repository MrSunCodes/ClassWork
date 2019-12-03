/*
目的网络用数字表示
*/
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct table {				//；路由表
	int k = 0;
	int targetNet[100];	//目的网络	
	int distence[100];//距离
	int nextRoute[100];//吓一跳
}Table[100];
//class route {
//private:
//
//public:
//	int n;//网络数量
//	int addr;//路由器地址
//	vector<int>Net;//跟路由器相连的网络地址
//	vector<int>nextRoute;//相邻路由器
//	vector<table>table;
//	route(int n)
//	{
//		for (int i = 0; i <= n; i++)
//		{
//			table temp = { 0,0 };
//			table.push_back(temp);
//		}
//	}
//};
int find(table a, int b)
{
	for (int i = 0; i < a.k; i++)
	{
		if (a.targetNet[i] == b)
		{
			return i;
		}
	}
	return -1;
}
void change(table &a, table b, int at, int bt)
{
	table bp = b;
	for (int i = 0; i < bp.k; i++)
	{
		bp.nextRoute[i] = bt;
		bp.distence[i]++;
	}
	for (int i = 0; i < bp.k; i++)
	{
		int temp = find(a, bp.targetNet[i]);
		if (temp == -1)
		{
			a.targetNet[a.k] = bp.targetNet[i];
			a.distence[a.k] = bp.distence[i];
			a.nextRoute[a.k] = bp.nextRoute[i];
			a.k++;
		}
		else {
			if (a.nextRoute[temp] == bt)
			{
				a.targetNet[temp] = bp.targetNet[i];
				a.distence[temp] = bp.distence[i];
			}
			else {
				if (bp.distence[i] < a.distence[temp])
				{
					a.distence[temp] = bp.distence[i];
				}
			}
		}
	}
}
int Rout[100][100];
int main(void)
{
	int rout, network;
	cout << "请输入路由器数量和网络数量，中间以空格间隔：" << endl;
	cin >> rout >> network;
	for (int i = 0; i <= rout; i++)
	{
		for (int j = 0; j <= network; j++)
		{
			Rout[i][j] = -1;
		}
	}
	cout << "请输入路由器和网络，按0加0终止" << endl;
	int R, N;
	while (true)
	{
		scanf_s("%d %d", &R, &N);
		if (R == 0 && N == 0)
		{
			break;
		}
		Rout[R][N] = 1;
	}
	int connect[100][100];
	fill(connect[0], connect[0] + 100 * 100, 0);
	for (int j = 1; j <= network; j++)
	{
		for (int a = 1; a <= rout; a++)
		{
			for (int b = a + 1; b <= rout; b++)
			{
				if (Rout[a][j] == 1 && Rout[b][j] == 1)
				{
					connect[a][b] = 1;
				}
			}
		}
	}
	/*for (int i = 1; i <= rout; i++)
	{
		for (int j = 1; j <= network; j++)
		{
			cout << Rout[i][j] << ' ';
		}
		cout << endl;
	}*/
	/*for (int i = 1; i <= rout; i++)
	{
		for (int j = 1; j <= network; j++)
		{
			cout << connect[i][j] << ' ';
		}
		cout << endl;
	}*/
	for (int i = 1; i <= rout; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			Table[i].targetNet[j] = -1;
			Table[i].distence[j] = -1;
			Table[i].nextRoute[j] = -1;
		}
	}
	for (int i = 1; i <= rout; i++)//算法第一步
	{
		for (int j = 1; j <= network; j++)
		{
			if (Rout[i][j] == 1)
			{
				Table[i].targetNet[Table[i].k] = j;
				Table[i].distence[Table[i].k] = 1;
				Table[i].nextRoute[Table[i].k] = 0;
				Table[i].k++;
			}
		}
	}
	for (int m = 0; m < 10; m++)
	{
		for (int i = 1; i <= rout; i++)
		{
			for (int j = i + 1; j <= rout; j++)
			{
				if (connect[i][j] == 1)
				{
					change(Table[i], Table[j], i, j);
					change(Table[j], Table[i], j, i);
				}
			}
		}
	}
	for (int i = 1; i <= rout; i++)
	{
		cout << "路由器：" << i << ':' << endl;
		for (int j = 0; j < Table[i].k; j++)
		{
			cout << Table[i].targetNet[j] << ' ' << Table[i].distence[j] << ' ' << Table[i].nextRoute[j] << endl;
		}
	}
	system("pause");
	return 0;
}
