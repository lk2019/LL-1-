#include<iostream>
#include<string>
#include<set>
#include<vector>
#include <algorithm>
#include<stack>
using namespace std;

struct terminator
{
	set<char> ister;
	set<char> notter;
};
terminator ter;
char begin_in;
void dealterminator(vector<string> str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != "$")
		{
			for (int j = 0; j < str[i].size(); j++)
			{
				if (str[i][j + 1] == '-'&&str[i][j + 2] == '>'&&str[i][j]!='|'&& str[i][j] != '~')
				{
					if (ter.ister.count(str[i][j]))
					{
						ter.ister.erase(str[i][j]);
					}
					ter.notter.insert(str[i][j]);
				}
				else if(str[i][j]!='-'&&str[i][j]!='>'&&!ter.notter.count(str[i][j])&& str[i][j] != '|'&& str[i][j] != '~')
				{
					ter.ister.insert(str[i][j]);
				}
			}				
		}
		else
		{
			ter.ister.insert('$');
		}
	}
}

vector<char> refirst(char ch, vector<string> str)
{
	vector<char> temp;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i][0] == ch)
		{
			for (int j = 3; j < str[i].size(); j++)
			{
				if (str[i][j - 1] == '>' || str[i][j - 1] == '|')
				{
					if (ter.ister.count(str[i][j])||str[i][j]=='~')
					{
						temp.push_back(str[i][j]);
					}
					else
					{
						vector<char> temp1;
						temp1 = refirst(str[i][j], str);
						vector<char>::iterator ir;
						if (*ir == '~'&&j < str[i].size() && ter.ister.count(str[i][j + 1]))
						{
							temp.push_back(str[i][j + 1]);
						}
						else
						{
							temp.push_back(*ir);
						}
					}
				}
			}
		}
	}
	return temp;
}
void printfirst(vector<vector<char>> first)
{
	for (int i = 0; i < first.size(); i++)
	{
		if (first[i][0] != '$')
		{
			cout << "first(" << first[i][0] << ")={";
			for (int j = 1; j < first[i].size(); j++)
			{
				cout << first[i][j] << "  ";
			}
			cout << "}" << endl;;
		}
	}
}
vector<vector<char>> first(vector<string> str)
{
	vector<vector<char>> first;
	
	for (int i = 0; i < str.size(); i++)
	{	
		vector<char> temp;
		temp.push_back(str[i][0]);
		for (int j = 1; j < str[i].size(); j++)
		{
			if (str[i][j - 1] == '>'|| str[i][j - 1]=='|')
			{
				if (ter.ister.count(str[i][j])||str[i][j]=='~')
				{
					temp.push_back(str[i][j]);
				}
				else
				{
					vector<char> temp1;
					temp1=refirst(str[i][j],str);
					vector<char>::iterator ir;
					for (ir = temp1.begin(); ir != temp1.end(); ir++)
					{
						if(*ir=='~'&&j<str[i].size()&&ter.ister.count(str[i][j+1]))
						{ 
							temp.push_back(str[i][j + 1]);
						}
						else
						{
							temp.push_back(*ir);
						}
					}
				}
			}
		}
		if (temp[0] != '$')
		{
			first.push_back(temp);
		}
	}
	printfirst(first);
	return first;
}

vector<vector<char>> follow(vector<vector<char>> first, vector<string> str)
{
	vector<vector<char>> follow;
	vector<vector<char>> oldfollow;
	char followstr;
	char begin = str[0][0];
	begin_in = begin;
	for (int i = 0; i < first.size(); i++)
	{
		vector<char> temp;
		temp.push_back(first[i][0]);
		follow.push_back(temp);
	}
	int num = 10;
	while(num>0)
	{
		num--;
		for (int i = 0; i < follow.size(); i++)
		{
			vector<char> temp;
			followstr = follow[i][0];
			for (int j = 0; j < str.size(); j++)
			{
				for (int k = 3; k < str[j].size(); k++)
				{
					if (str[j][k - 1] == followstr)
					{
						if (str[j][k] == '|'&&str[j][k - 1] == begin)
						{
							temp.push_back('$');
						}
						else if (ter.ister.count(str[j][k]))
						{
							temp.push_back(str[j][k]);
						}
						else if (ter.notter.count(str[j][k]))
						{
							for (int x = 0; x < first.size(); x++)
							{
								if (str[j][k] == first[x][0])
								{
									for (int y = 1; y < first[x].size(); y++)
									{
										if (first[x][y] != '~')
										{
											temp.push_back(first[x][y]);
										}
										else
										{
											for (int z = 0; z < follow.size(); z++)
											{
												if (str[j][k] == follow[z][0])
												{
													for (int c = 1; c < follow[z].size(); c++)
													{
														temp.push_back(follow[z][c]);
													}
												}
											}
											//
										}
									}
								}
							}
						}
						if (str[j][k] == '|' || k == str[j].size())
						{
							char tem = str[j][0];
							if (tem != str[j][k - 1])
							{
								for (int l = 0; l < follow.size(); l++)
								{
									if (tem == follow[l][0])
									{
										for (int x = 1; x < follow[l].size(); x++)
										{
											temp.push_back(follow[l][x]);
										}
									}
								}
							}
						}
					}
				}
			}
			vector<char>::iterator ir;
			for (ir = temp.begin(); ir != temp.end(); ir++)
			{
				follow[i].push_back(*ir);
			}
		}
	}
		for (int i = 0; i < follow.size(); i++)
		{
			sort(follow[i].begin(), follow[i].end());
			follow[i].erase(unique(follow[i].begin(), follow[i].end()), follow[i].end());
		}
	for (int i = 0; i < follow.size(); i++)
	{
		cout << "follow(" << follow[i][follow[i].size() - 1] << ")={";
		for (int j = follow[i].size()- 2; j >=0; j--)
		{
			cout << follow[i][j] << "  ";
		}
		cout << "}" << endl;;
	}
	return follow;
}

void repeattable(int num,int i,string atempstr, vector<vector<string>> &table,vector<vector<char>> first, vector<vector<char>>follow, vector<char> ister)
{
	if (ter.ister.count(atempstr[num]))
	{
		for (int ir = 0; ir < ister.size(); ir++)
		{
			if (atempstr[num] == ister[ir])
			{
				table[i][ir - 1] = atempstr;
			}
		}
	}
	if (num < atempstr.size() - 1)
	{
		for (int ir = 0; ir < first.size(); ir++)
		{
			if (atempstr[num] == first[ir][0])
			{
				for (int it = 1; it < first[ir].size(); it++)
				{
					if (first[ir][it] != '~')
					{
						for (int in = 0; in < ister.size(); in++)
						{
							if (first[ir][it] == ister[in])
							{
								table[i][in - 1] = atempstr;
								break;
							}
						}
					}
					else
					{
						repeattable(num+1, i, atempstr, table, first, follow, ister);
					}
				}
			}

		}
	}
}

void print(stack<char> sta)
{
	int x = sta.size();
	for (int i = 0; i < x; i++)
	{
		cout << sta.top();
		sta.pop();
	}
	if (sta.size() > 8)
	{
		cout << '\t' ;
	}
	else
	{
		cout << "\t\t" ;
	}
}


void stack_input(vector<vector<string>> &table, vector<char> ister, vector<vector<char>> first)
{
	stack<char> stack1;
	stack<char> input;
	stack1.push('$');
	stack1.push(begin_in);
	int i = 64;
	input.push('$');
	cout << "自动输入产生式为1，手动输入为其他" << endl;
	string in;
	cin >> in;
	string in_string;
	if (in == "1")
	{
		cout << "产生式为" << "#abaa%aba!" << endl;
		in_string = "#abaa%aba!";
	}
	else
	{
		cin >> in_string;
	}
	for (int i = in_string.size() - 1; i >=0; i--)
	{
		input.push(in_string[i]);
	}
	cout << "栈操作为" << endl;
	cout << "stack" << "\t\t" << "input" << "\t\t" << "action\t\t" << endl;;
	while (stack1.top() != '$'&&input.top() != '$')
	{
		i--;
		char sta = stack1.top();
		char inp = input.top();
		print(stack1);
		print(input);
		if (sta == inp)
		{
			stack1.pop();
			input.pop();
			cout << "terminal" << endl;;
		}
		else
		{
			char temp = stack1.top();
			char temp2 = input.top();
			for (int i = 0; i < first.size(); i++)
			{
				if (temp == first[i][0])
				{
					for (int j = 1; j < ister.size(); j++)
					{
						if (temp2 == ister[j])
						{
							stack1.pop();
							string temp3 = table[i][j - 1];
							if (temp3 != "~")
							{
								if (temp3.size() > 8)
								{
									cout << temp3 << '\t' << endl;
								}
								else
								{
									cout << temp3 << "\t\t"<< endl;
								}
								for (int k = temp3.size() - 1; k >= 0; k--)
								{
									stack1.push(temp3[k]);
								}
							}
							else
							{
								cout << "~" << endl;
							}
						}
					}
				}
			}
		}
		if (i == 0)
		{
			break;
		}
	}
	if (stack1.top() == '$'&&input.top() == '$')
	{
		print(stack1);
		print(input);
		cout << "accept" << endl;
	}
	else
	{
		cout << endl;
		cout << "不通过" << endl;
	}
}

void table(vector<vector<char>> first, vector<vector<char>>follow, vector<string> str)
{
	int a = ter.ister.size();
	int b = ter.notter.size();
	vector<vector<string>> table;
	for (int i = 0; i < b; i++)
	{
		vector<string> temp;
		for (int j = 0; j < a; j++)
		{
			temp.push_back("");
		}
		table.push_back(temp);
	}
	vector<char> ister;
	ister.push_back('\t');
	set<char>::iterator ir;
	for (ir = ter.ister.begin(); ir != ter.ister.end(); ir++)
	{
		ister.push_back(*ir);
	}
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i][0] != '$')
		{
			char temp = str[i][0];
			int k = 2;
			for (int j = 3; j < str[i].size(); j++)
			{
				
				if (str[i][j] == '>' || str[i][j] == '|'||j== str[i].size()-1)
				{

					string atempstr = str[i].substr(k+1, j-k);
					if (atempstr[atempstr.size() - 1] == '|')
					{
						atempstr.erase(atempstr.size() - 1);
					}
					k = j;
					if (ter.ister.count(atempstr[0]))
					{
						for (int ir = 0; ir < ister.size(); ir++)
						{
							if (atempstr[0] == ister[ir]&& atempstr[0] !='~')
							{
								table[i][ir-1] = atempstr;
							}
						}
					}
					else if(ter.notter.count(atempstr[0]))
					{
						repeattable(0,i, atempstr, table, first, follow, ister);
					}
				}
			}
			for (int j = 0; j < first.size(); j++)
			{
				if (temp == first[j][0])
				{
					for (int k = 0; k < first[j].size(); k++)
					{
						if (first[j][k] == '~')
						{
							for (int x = 0; x < follow.size(); x++)
							{
								if (temp == follow[x][follow[x].size()-1])
								{
									for (int it = 0; it < follow[x].size(); it++)
									{
										for (int ir = 1; ir < ister.size(); ir++)
										{
											if (follow[x][it] == ister[ir])
											{
												table[i][ir - 1] = '~';
												break;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout << "获得的表为" << endl;
	for (int i = 0; i < ister.size(); i++)
	{
		if (i > 0)
		{
			cout << ister[i]<<'\t';
		}
		else
		{
			cout << ister[i];
		}
	}
	cout << endl;
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size()+1; j++)
		{
			if (j > 0)
			{
				cout << table[i][j - 1] << '\t';
			}
			else
			{
				cout << first[i][0]<<'\t';
			}
		}
		cout << endl;
	}
	stack_input(table, ister,first);
}




void main()
{
	string a1 = "s->%at|u!";
	string a2 = "t->as|bat|~";
	string a3 = "u->#atu|~";
	cout << "输入上下文无关文法（空用~表示），输入完成后，在最后输出$结束" << endl;
	vector<string> LL;
	/*string input;
	while (input != "$")
	{
		cin >> input;
		LL.push_back(input);
	}*/
	vector<vector<char>> first1;
	vector<vector<char>> follow1;
	LL.push_back(a1);
	LL.push_back(a2);
	LL.push_back(a3);
	LL.push_back("$");
	dealterminator(LL);
	first1=first(LL);
	follow1=follow(first1,LL);
	table(first1, follow1,LL);
	system("pause");
}