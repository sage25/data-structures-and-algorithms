#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<queue>
using namespace std;

class DirGraph
{
private:
	//顶点定义
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
			perror("文件打开失败");
			return;
		}

		//占用第0号位置
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

	//深度优先搜索
	void dfs()
	{
		vector<bool> vec(vertics.size(), false);
		dfs(1, vec);
		cout << endl;
	}
	//广度优先搜索
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
private:
	//深度优先搜索实现
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
};


int main()
{
	DirGraph graph;
	graph.readFile("data.txt");
	graph.show();
	graph.dfs();
	graph.bfs();
	return 0;
}