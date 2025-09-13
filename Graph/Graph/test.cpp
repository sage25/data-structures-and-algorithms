#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<queue>
using namespace std;

class DirGraph
{
private:
	//���㶨��
	struct Vertic
	{
		Vertic(string data)
			: data_(data)
		{ }
		string data_;
		list<int> adjList;
	};
	vector<Vertic> vertics;
public:
	void readFile(string file)
	{
		FILE* pf = fopen(file.c_str(), "r");
		if (pf == nullptr)
		{
			perror("�ļ���ʧ��");
			return;
		}

		//ռ�õ�0��λ��
		vertics.emplace_back("");
		char buffer[1024] = { 0 };
		while (!feof(pf))
		{
			
			fgets(buffer, 1024, pf);
			string linestr(buffer);
			vertics.emplace_back(linestr.substr(0, linestr.size() - 1));
			fgets(buffer, 1024, pf);
			char* vertic_no = strtok(buffer, ",");
			while (vertic_no != nullptr)
			{
				int vex = atoi(vertic_no);
				if (vex > 0)
				{
					vertics.back().adjList.push_back(vex);
				}
				vertic_no = strtok(nullptr, ",");
			}
		}
		fclose(pf);
	}

	void show() const
	{
		for (int i = 1; i < vertics.size(); ++i)
		{
			cout << vertics[i].data_ << ":";
			for (auto& it : vertics[i].adjList)
			{
				cout << it << " ";
			}
			cout << endl;
		}
	}

	//�����������
	void dfs()
	{
		vector<bool> vec(vertics.size(), false);
		dfs(1, vec);
		cout << endl;
	}
	//�����������
	void bfs()
	{
		queue<int> que;
		vector<bool> visited(vertics.size(), false);
		que.push(1);
		visited[1] = true;

		while (!que.empty())
		{
			int no = que.front();
			que.pop();
			cout << vertics[no].data_ << " ";
			for (auto& it : vertics[no].adjList)
			{
				if (visited[it])
				{
					continue;
				}
				que.push(it);
				visited[it] = true;
			}
		}
		cout << endl;
	}
	//����Ȩֵ�����·����������ȣ�
	void shortPath(int start, int end)
	{
		queue<int> que;
		vector<int> visited(vertics.size(), 0);
		que.push(start);
		visited[start] = -1;

		while (!que.empty())
		{
			int no = que.front();
			que.pop();
			
			for (auto& it : vertics[no].adjList)
			{
				if (visited[it] != 0)
				{
					continue;
				}
				if (it == end)
				{
					//�ҵ���
					visited[it] = no;
					printPath(end, visited);
					return;
				}
				que.push(it);
				visited[it] = no;
			}
		}
		if (que.empty())
		{
			cout << "�޷��ҵ���start��end�����·��" << endl;
		}
		
	}
private:
	//�����������ʵ��
	void dfs(int start, vector<bool>& vec)
	{
		if (vec[start])
		{
			return;
		}
		cout << vertics[start].data_ << " ";
		vec[start] = true;

		for (auto it : vertics[start].adjList)
		{
			dfs(it, vec);
		}
	}
	void printPath(int end, vector<int>& visited)
	{
		/* �����ӡ
		while (end != -1)
		{
			cout << vertics[end].data_ << "<=";
			end = visited[end];
		}
		cout << endl;
		*/

		//�����ӡ
		if (end == -1)
		{
			return;
		}
		printPath(visited[end], visited);
		cout << vertics[end].data_ << " ";
	}
};


//int main()
//{
//	DirGraph graph;
//	graph.readFile("data.txt");
//	graph.show();
//	graph.dfs();
//	graph.bfs();
//	graph.shortPath(1, 3);
//	return 0;
//}