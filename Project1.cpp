#include <iostream> 
#include <vector> 
#include <string> 
#include <set>
#include <algorithm>
#include <fstream> 

using namespace std;
/*�����洢Ŀ���ļ���*/
string file_nameOutput, file_nameId, file_nameNum;

/*��ȡ�ı��ļ��е���Ϣ��*/
string GetText();

/*���ڴ���޷����������������ɳ�����*/
set<int>Num;
vector<int>NUM;

/*���ڴ���û���ʶ�����������ɱ�ʶ����*/
set<string>Id;
vector<string>ID;

/*���һ�����ʷ���,��λ��i��ʼ���ҡ�
  //������һ�����ò���j��������������������һ���ַ���str��λ�á�*/
string GetWord(string str, int i, int& j);

/*�������������ȥ�ַ����������Ŀո�ͻ���
  //��һ������ΪĿ���ַ������ڶ�������Ϊ��ʼλ��
  //����ֵΪ�����Ŀո�ͻ��к�ĵ�һ����Ч�ַ����ַ�����λ��*/
int DeleteNull(string str, int i);

/*�ж�i��ǰ��ָ���ַ��Ƿ�Ϊһ���ֽ�����ǵĻ������棬��֮��*/
bool IsBoundary(string str, int i);

/*�ж�i��ǰ��ָ���ַ��Ƿ�Ϊһ����������ǵĻ������棬��֮��*/
bool IsOperation(string str, int i);

/*�˺�����һ��pair���������output.txt�ļ���*/
void OutFile(vector<pair<int, string> > v);

/*�˺������û���ʶ�������idlist.txt�ļ���*/
void OutFileId(vector<string> s);

/*�˺������޷������������uintlist.txt�ļ���*/
void OutFileNum(vector<int> s);

/*�˺�������һ���ַ������飬�������дʷ�����������һ��pair������*/
vector<pair<int, string> > analyst(vector<string> vec);

/*�˺����жϴ��ݵĲ����Ƿ�Ϊ�ؼ��֣��ǵĻ��������棬��֮���ؼ�*/
bool IsKey(string str);

/*
����ķ������£�
�ؼ��֣�1
��ʶ����2
�޷���������3
�����������4
�ָ�����5
�Ƿ��ַ���6
��ϵ�����7��7
*/
int main()
{
	string com1 = " ";
	string com2 = "\n";
	string fileline = GetText();
	int begin = 0, end = 0;
	vector<string> array;//�������Լ����ַ��Ŵ���
	do
	{
		begin = DeleteNull(fileline, begin);
		string nowString;
		nowString = GetWord(fileline, begin, end);
		if (end == -1)
			break;
		if (nowString.compare(com1) && nowString.compare(com2))
			array.push_back(nowString);
		begin = end + 1;
	} while (true);
	vector<pair<int, string> > mid_result;
	mid_result = analyst(array);//���д���������Ԫʽ�����������
	OutFile(mid_result);//������������output.txt
	OutFileId(ID);//����û���ʶ�������idlist.txt
	OutFileNum(NUM);//�������������uintlist.txt
	for (int i = 0; i < mid_result.size(); i++)//�������ӡ������̨��
		if (mid_result[i].first == 6)
		{
			cout << "ERROR" << endl;
		}
		else
			cout << "(" << mid_result[i].first << " , " << mid_result[i].second << ")" << endl;
	cout << "**********************************************************************\n";
	cout << "***��������ɴʷ���������������Ѿ��洢��F��" << file_nameOutput << ',' << file_nameId << ',' << file_nameNum << "�ļ��У����� * **\n";
	cout << "**********************************************************************\n";
	system("pause");
	return 0;
}

/*��ȡ�ı��ļ��е���Ϣ*/
string GetText()
{
	string file_name1;
	cout << "������Դ�ļ���������·���ͺ�׺������";
	cin >> file_name1;
	ifstream infile(file_name1.c_str(), ios::in);
	if (!infile)
	{
		cerr << "�޷����ļ�!" << file_name1.c_str() << " !!!" << endl;
		exit(-1);
	}
	cout << endl;
	char f[1000];
	infile.getline(f, 1000, EOF);
	infile.close();
	return f;
}

/*���һ�����ʷ���,��λ��i��ʼ���ҡ�
//������һ�����ò���j��������������������һ���ַ���ԭ�ַ�����λ�á�*/
string GetWord(string str, int i, int& j)
{
	string no_use("() {} , ;  + = * / - < > \" \' \\ [] &");
	j = str.find_first_of(no_use, i);
	if (j == -1)
		return "";
	if (i != j)
		j--;
	return str.substr(i, j - i + 1);
}

/*�������������ȥ�ַ����������Ŀո�ͻ���
//��һ������ΪĿ���ַ������ڶ�������Ϊ��ʼλ��
//����ֵΪ�����Ŀո�ͻ��к�ĵ�һ����Ч�ַ����ַ�����λ��*/
int DeleteNull(string str, int i)
{
	for (;; i++)
		if (str[i] != ' '&&str[i] != '\n')
			return i;
}

/*�ж�i��ǰ��ָ���ַ��Ƿ�Ϊһ���ֽ�����ǵĻ������棬��֮��*/
bool IsBoundary(string str, int i)
{
	int t;
	char arr[11] = { ',',';','{','}','(',')','\"','\'','[',']','\\' };
	for (t = 0; t < 11; t++)
		if (str[i] == arr[t])
			return true;
	return false;
}

/*�ж�i��ǰ��ָ���ַ��Ƿ�Ϊһ����ĸ���ǵĻ������棬��֮��*/
bool Isalpha(string str, int i)
{
	int t;
	if (str[i] <= 'z'&&str[i] >= 'a' || str[i] <= 'Z'&&str[i] >= 'A')
		return true;
	return false;
}

/*�ж�i��ǰ��ָ���ַ��Ƿ�Ϊһ��������������ǵĻ������棬��֮��*/
bool IsCOperation(string str, int i)
{
	int t;
	char arr[7] = { '+','-','*','/','%','=','&' };
	for (t = 0; t < 7; t++)
		if (str[i] == arr[t])
			return true;
	return false;
}

/*�ж�i��ǰ��ָ���ַ��Ƿ�Ϊһ����ϵ��������ǵĻ������棬��֮��*/
bool IsOperation(string str, int i)
{
	int t;
	char arr[3] = { '<','>' };
	for (t = 0; t < 3; t++)
		if (str[i] == arr[t])
			return true;
	return false;
}

/*�˺����жϴ��ݵĲ����Ƿ�Ϊ�ؼ��֣��ǵĻ��������棬��֮���ؼ�*/
bool IsKey(string str)
{
	string
		reslist[25] = { "#include","scanf","printf","stdio.h","void","main","%d","%f","char","double","int","long","double","float","for","while","do","break","continue",
		"switch","short","case","return","if","else" };
	vector<string> ppp(reslist, reslist + 25);
	int u;
	for (u = 0; u < ppp.size(); u++)
		if (!str.compare(ppp[u]))
			return true;
	return false;
}

/*�˺�����һ�����ַ������������һ���ļ���*/
void OutFile(vector<pair<int, string> > v)
{
	file_nameOutput = "F:/output.txt";
	ofstream outfile(file_nameOutput.c_str(), ios::out);
	if (!outfile)
	{
		cerr << "�޷����ļ�!" << file_nameOutput.c_str() << " !!!" << endl;
		exit(-1);
	}
	cout << endl;
	int i;
	for (i = 0; i < v.size(); i++)
		if (v[i].first == 6)
		{
			outfile << "ERROR" << endl;
		}
		else
			outfile << "(" << v[i].first << " , " << v[i].second << ")" << endl;
	outfile << "/*finished*/";
	outfile.close();
	return;
}
/*�˺������û���ʶ�������idlist.txt�ļ���*/
void OutFileId(vector<string> s)
{
	file_nameId = "F:/idlist.txt";
	ofstream outfile(file_nameId.c_str(), ios::out);
	if (!outfile)
	{
		cerr << "�޷����ļ�!" << file_nameId.c_str() << " !!!" << endl;
		exit(-1);
	}
	cout << endl;
	for (auto it = s.begin(); it != s.end(); it++)
	{
		outfile << *it << endl;
	}
	outfile << "/*finished*/";
	outfile.close();
	return;
}

/*�˺������޷������������uintlist.txt�ļ���*/
void OutFileNum(vector<int> s)
{
	file_nameNum = "F:/uintlist.txt";
	ofstream outfile(file_nameNum.c_str(), ios::out);
	if (!outfile)
	{
		cerr << "�޷����ļ�!" << file_nameNum.c_str() << " !!!" << endl;
		exit(-1);
	}
	cout << endl;
	for (auto it = s.begin(); it != s.end(); it++)
	{
		outfile << *it << endl;
	}
	outfile << "/*finished*/";
	outfile.close();
	return;
}

/*�˺�������һ���ַ������飬�������дʷ�����������һ��pair������*/
vector<pair<int, string> > analyst(vector<string> vec)
{
	vector<pair<int, string> > temp;
	int i;
	for (i = 0; i < vec.size(); i++)
	{
		if (vec[i].size() == 1)
		{
			if ((vec[i] == ">" || vec[i] == "<" || vec[i] == "!" || vec[i] == "=") && vec[i + 1] == "=")
			{
				string jk = vec[i];
				jk.append(vec[++i], 0, 1);
				pair<int, string> pp(7, jk);
				temp.push_back(pp);
				continue;
			}
			if ((vec[i] == "+"&&vec[i + 1] == "+") || (vec[i] == "-"&&vec[i + 1] == "-"))
			{
				string jk = vec[i];
				jk.append(vec[++i], 0, 1);
				pair<int, string> pp(4, jk);
				temp.push_back(pp);
				continue;
			}
			if (IsBoundary(vec[i], 0))
			{
				pair<int, string> pp(5, vec[i]);
				temp.push_back(pp);
			}
			else if (IsCOperation(vec[i], 0))
			{
				pair<int, string> pp(4, vec[i]);
				temp.push_back(pp);
			}
			else if (IsOperation(vec[i], 0))
			{
				pair<int, string> pp(7, vec[i]);
				temp.push_back(pp);
			}
			else if (vec[i][0] <= '9'&&vec[i][0] >= '0')
			{
				pair<int, string> pp(3, vec[i]);
				int cnt = Num.size();
				Num.insert(atoi(vec[i].c_str()));//��1λ������������string����ת��Ϊint���ͣ�����Num��
				if (cnt != Num.size())
				{
					NUM.push_back(atoi(vec[i].c_str()));
				}
				temp.push_back(pp);
			}
			else if (Isalpha(vec[i], 0))
			{
				pair<int, string> pp(2, vec[i]);
				int cnt = Id.size();
				Id.insert(vec[i]);
				if (cnt != Id.size())
				{
					ID.push_back(vec[i]);
				}
				temp.push_back(pp);
			}
			else//����
			{
				pair<int, string> pp(6, vec[i]);
				temp.push_back(pp);
			}
		}
		else if (vec[i][0] <= '9'&&vec[i][0] >= '0')
		{
			pair<int, string> pp(3, vec[i]);
			int cnt = Num.size();
			Num.insert(atoi(vec[i].c_str()));//������1λ������������string����ת��Ϊint���ͣ�����Num��
			if (cnt != Num.size())
			{
				NUM.push_back(atoi(vec[i].c_str()));
			}
			temp.push_back(pp);
		}
		else if (IsKey(vec[i]))
		{
			pair<int, string> pp(1, vec[i]);
			temp.push_back(pp);
		}
		else if (Isalpha(vec[i], 0))
		{
			pair<int, string> pp(2, vec[i]);
			int cnt = Id.size();
			Id.insert(vec[i]);
			if (cnt != Id.size())
			{
				ID.push_back(vec[i]);
			}
			temp.push_back(pp);
		}
		else//����
		{
			pair<int, string> pp(6, vec[i]);
			temp.push_back(pp);
		}
	}
	return temp;
}