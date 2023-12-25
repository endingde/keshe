#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
#include<fstream>
#include<map>
#include<queue>
#include<vector>
#include<iomanip>
#define maxn 100100

using namespace std;

map<char,int>tree;
int root = 52;


int deepest;
struct Node
{
	int num;
	int parent=-1, lch=-1, rch=-1;
	int weight;//0 or 1
	int depth;//�߶�
	int place;
}node[maxn];
queue<Node>q;
queue<Node>q1;
queue<Node>v[12];
//queue<Node>* v = new queue<Node>[15];
struct Tree
{
	int root;//���ڵ�
	int depth;//�������
}hfmtree;
void redo()//��ʼ��ֵ
{
	tree[' '] = 186, tree['A'] = 64, tree['B'] = 13, tree['C'] = 22, tree['D'] = 32, tree['E'] = 103, tree['F'] = 21, tree['G'] = 15, tree['H'] = 47, tree['I'] = 57, tree['J'] = 1, tree['K'] = 5, tree['L'] = 32, tree['M'] = 20, tree['N'] = 57, tree['O'] = 63, tree['P'] = 15, tree['Q'] = 1, tree['R'] = 48, tree['S'] = 51, tree['T'] = 80, tree['U'] = 23, tree['V'] = 8, tree['W'] = 18, tree['X'] = 1, tree['Y'] = 16, tree['Z'] = 1;
	node[0].num = 186, node[1].num = 64, node[2].num = 13, node[3].num = 22, node[4].num = 32, node[5].num = 103, node[6].num = 21, node[7].num = 15, node[8].num = 47, node[9].num = 57, node[10].num = 1, node[11].num = 5, node[12].num = 32, node[13].num = 20, node[14].num = 57, node[15].num = 63, node[16].num = 15, node[17].num = 1, node[18].num = 48, node[19].num = 51, node[20].num = 80, node[21].num = 23, node[22].num = 8, node[23].num = 18, node[24].num = 1, node[25].num = 16, node[26].num = 1;
}
void build_tree(int n)
{
	for (int i = n+1; i <= 2*n; i++)
	{
		int min1 = maxn, min2 = maxn;
		int lnode = -1, rnode = -1;
		for (int j = 0; j <= i-1; j++)
		{
			if (node[j].num < min1 && node[j].parent == -1)
			{
				min2 = min1;
				min1 = node[j].num;
				rnode = lnode;
				lnode = j;
				//cout <<"min1="<< min1 << " ";
			}
			else if (node[j].num < min2 && node[j].parent == -1)
			{
				min2 = node[j].num;
				rnode = j;
				//cout <<"min2="<< min2 << " ";
			}
		}
		//cout << node[lnode].num << " "<<node[rnode].num<<" ";
		node[lnode].parent = node[rnode].parent = i;
		node[i].lch = lnode, node[i].rch = rnode;
		node[i].num = node[lnode].num + node[rnode].num;
		//cout << "i"<<i<<'\n';
		//cout << node[i].num<<" ";
	}
}

void initialization(int i,int t)
{
	node[i].weight = t;
	//cout << "node[" << i << "].weight=" << node[i].weight<< "\n";
	//cout << node[i].lch;
	if (node[i].lch != -1)
	{
		node[i].place = 2 * node[node[i].parent].place;
		initialization(node[i].lch, 0);
	}
	if (node[i].rch != -1)
	{
		node[i].place = 2 * node[node[i].parent].place+1;
		initialization(node[i].rch, 1);
	}
}
void Encoding(string s)//����
{
	int length = s.length();
	ofstream file;
	file.open("CodeFile.txt", ios::out);
	for (int i = 0; i < length; i++)
	{
		char X;
		X = s[i];
		int t;
		if (X == ' ')t = 0;
		else
		{
			t = X - 64;
		}
		//cout <<'\n'<<t << '\n';
		int list1[100],list2[100];
		int tex1=0,tex2=0;//�����ָ��
		while (node[t].parent != -1)
		{
			list1[++tex1] = node[t].weight;
			//cout << tex1 << " " << node[t].weight << '\n';
			t = node[t].parent;
		}
		while (tex1>=1)
		{
			list2[++tex2] = list1[tex1];
			tex1--;
			//cout << list2[tex2];
			file << list2[tex2];
		}
		//cout << '\n';
		file << '\n';
	}
	file.close();
}

void Decoding()
{

	ifstream file;
	file.open("CodeFile.txt", ios::in);
	ofstream file1;
	file1.open("Textfile.txt", ios::out);

	if (!file.is_open())
	{
		cout << "Failed to open CodeFile.txt!" << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		int length;
		length = line.length();
		//cout <<length<<" "<< line << '\n';
		int temp = root;
		for (int i = 0; i <= length - 1; i++)
		{
			//cout << line[i] << "  \n";
			if (line[i] == '0')
			{
				node[i].place = 2 * node[node[i].parent].place;
				temp = node[temp].lch;
				//cout << "node[temp].lch=" << node[temp].lch << " ";
			}
			else if (line[i] == '1')
			{
				node[i].place = 2 * node[node[i].parent].place+1;
				temp = node[temp].rch;
				//cout << "node[temp].rch=" << node[temp].rch << " ";
			}

			// ����Ƿ񵽴��ļ�ĩβ
			if (file.eof())
			{
				cout << "Unexpected end of file!" << endl;
				file.close();
				file1.close();
				return;
			}
		}
		//cout << temp << " ";
		if (temp == 0)
		{
			cout << " ";
			file1 << ' ';
		}
		else
		{
			cout<< static_cast<char>(temp + 'A' - 1);
			file1 << static_cast<char>(temp + 'A' - 1);
		}
	}

	file.close();
	//file1.close();
}
void create_place(int temp)//��ֵÿһ���ڵ������
{
	if (temp == 52)
	{
		create_place(node[temp].lch);
		create_place(node[temp].rch);
	}
	if (node[temp].weight == 0 )
	{
		node[temp].place = node[node[temp].parent].place * 2;
		//cout << node[temp].num << "  " << node[temp].place << " \n";
		if (node[temp].lch != -1)create_place(node[temp].lch);
		if (node[temp].rch != -1)create_place(node[temp].rch);
	}
	if (node[temp].weight == 1 )
	{
		node[temp].place = node[node[temp].parent].place * 2+1;
		//cout << node[temp].num << "  " << node[temp].place << " \n";
		if (node[temp].lch != -1)create_place(node[temp].lch);
		if (node[temp].rch != -1)create_place(node[temp].rch);
	}
}
void tree_print(int temp)//��ӡ����
{
	node[temp].depth = 1;
	q.push(node[temp]);
	v[node[temp].depth].push(node[temp]);
	//cout << node[temp].num << " "<<node[temp].parent<<" ";
	while (!q.empty())
	{
		Node curr = q.front();
		if (curr.parent != -1)
		{
			curr.depth = node[curr.parent].depth + 1;
			if (curr.weight == 0)
			{
				node[node[curr.parent].lch].depth = curr.depth;
				node[node[curr.parent].lch].place = 2 * node[curr.parent].place;
			}
			if (curr.weight == 1)
			{
				node[node[curr.parent].rch].place = 2 * node[curr.parent].place +1;
				node[node[curr.parent].rch].depth = curr.depth;
			}
			//cout << node[curr.parent].num << " "<< node[curr.parent].depth<<" ";
		}
		v[curr.depth].push(curr);
		//cout << curr.parent << " " << curr.depth;
		//cout << curr.num<<"  "<<curr.depth<<" "<< curr.place << '\n';
		if (curr.lch != -1)q.push(node[curr.lch]);
		if (curr.rch != -1) q.push(node[curr.rch]);
		q.pop();
	}
	q1.push(node[temp]);
	deepest = 11;
	v[1].pop();
	for (int i = 11; i>=1; i--)
	{
		int t = 0;//t��������ڵ�����λ��
		int j = 11 - i + 1;//�߶�Ϊj
		for (int k = i; k >= 1; k--)//��ӡǰ׺�ո�
		{
			cout << "   ";
		}
		while (!v[j].empty())//v������Ϊ��
		{
			Node dex;
			if (j != 1)t = v[j].front().place - dex.place - 1;//t��������ڵ�����λ��
			while (t--)
			{
				cout << " ";
			}
			cout << v[j].front().num;
			for (int k = i; k >= 1; k--)
			{
				cout << " ";
			}
			dex = v[j].front();//���浱ǰλ�õĽڵ�
			v[j].pop();
			if (v[j].empty())break;
			t = v[j].front().place - dex.place-1;//t��������ڵ�����λ��
			
		}
		cout << "\n\n";
	}
}
void tree_printf()
{
	ifstream file;
	file.open("work.txt",ios::in);
	if (!file.is_open())
	{
		cout << "Failed to open CodeFile.txt!" << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		cout << line << '\n';
	}
	file.close();
}
void tree_P()
{
	ifstream file;
	file.open("CodeFile.txt", ios::in);
	string line;
	while (getline(file, line))
	{
		cout << line;
	}
}
void Code_print()
{
	int i = 0;
	ifstream file;
	file.open("CodeFile.txt", ios::in);
	string line;
	while (getline(file, line))
	{
		if (i == 0)
		{
			cout << "�ո� " << line<<'\n';
		}
		else
		{
			cout << static_cast<char>('A' + i) <<"�� " << line<<'\n';
		}
		i++;
	}
}
void menu() {
	cout << "			        ��������/������\n";
	cout << "-------------------------------------------------------------------------------\n";
	cout << "				1 ��ʼ������������������\n";
	cout << "				2 ����\n";
	cout << "				3 ����\n";
	cout << "				4 ��ӡ�����ļ�\n";
	cout << "				5 ��ӡ������\n";
	//cout << "				6 ��ӡ�����\n";
	cout << "				0 �˳�����\n";
	cout << "-------------------------------------------------------------------------------\n";
}
int main()
{
	node[52].place = 1;
	int tree_have = 0;//�ж��Ƿ���hfmtree
	int cl,n;


	redo();//���Լ��
	tree_have = 1;
	build_tree(26);
	initialization(52,-1);

	while (1)
	{
		menu();
		cout << "\n��ѡ���Ӧ�Ĺ���ѡ����в�����\n";
		cin >> cl;
			if (cl == 1)
			{
				ofstream filel;
				filel.open("hfmtree.txt", ios::out);
				ofstream file;
				file.open("hfm1tree.txt", ios::out);
				cout << "�����ַ��ĸ�����";
				cin >> n;
				for (int i = 0; i <= n - 1; i++)
				{
					cout << "�����" << i << "���ַ���Ȩֵ\n";
					char c;
					int num;
					cin >> c >> num;
					node[i].num = num;
					filel << "�ַ���" << c << "  Ȩֵ��" << num << '\n';
					file << c << num << '\n';
				}
				filel.close();
				file.close();
				build_tree(n - 1);
				initialization(2 * n - 2, -1);
				tree_have = 1;
				//����
			}
			else if (cl == 2)
			{
				if (tree_have == 0)
				{
					cout << "��δ������������\n";
					ifstream file2;
					file2.open("hfm1tree", ios::in);
					if (!file2) {
						std::cout << "�޷����ļ�!" << std::endl;
						return 1;
					}
					char ch;//��ȡ�ַ�
					int num;//��ȡȨֵ
					//file >> skipws; // �����հ��ַ�
					int i = 0;
					while (file2 >> ch >> num)
					{
						node[i++].num = num;//Ĭ�ϴ������ĸ˳��
					}
					file2.close();
				} 
				
				string s;
				cin.ignore();
				getline(cin, s);
				//cout << s;
				Encoding(s);
			}
			//����
			else if (cl == 3)
			{
				if (tree_have == 1)
				{
					Decoding();
					create_place(52);
				}
				else
					cout << "��δ������������\n";
			}
			//��ӡ�����ļ�
			else if (cl == 4)
			{
				if (tree_have == 1)
					tree_printf();
				else
					cout << "��δ������������\n";
			}
			else if (cl == 5)
			{
				if (tree_have == 1)
					tree_P();
				else
					cout << "��δ������������\n";
			}
			else
			{
				cout << "���������룡\n";
			}
		system("pause");
		system("cls");
	}
		
	//build_tree(26);
	//initialization(52, -1);
	//string s="THIS PROGRAME IS MY FAVORITE";
	//Encoding(s);
	//Decoding();
	//create_place(52);
	//tree_print(52);
	//tree_printf();
	return 0;
}