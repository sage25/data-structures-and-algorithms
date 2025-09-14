#include<vector>
#include<iostream>
#include<queue>
using namespace std;

using uint = unsigned int;
const int INF = INT_MAX;

#if 0
//迪杰斯特拉算法求解有向图最短带权路径（贪心算法+广度优先）
int Dijkstra(vector<vector<uint>>& graph,
			int start,
			int end)
{
	const int N = graph.size();

	vector<uint>dis(N, 0);	//存储最短路径
	vector<bool>use(N, false);
	//把start放入S集合
	use[start] = true;
	dis[start] = 0;
	//初始化start到个节点的权值
	for (int i = 0; i < N; ++i)
	{
		dis[i] = graph[start][i];
	}

	//处理每一个U集合中的元素
	for (int i = 1; i < N; ++i)
	{
		//找到最小权值
		int min = INF;
		int k = -1;
		for (int j = 0; j < N; ++j)
		{
			if ((!use[j]) && dis[j] < min)
			{
				min = dis[j];
				k = j;
			}
		}
		if (k == -1)
		{
			break;
		}
		use[k] = true;
		for (int j = 0; j < N; ++j)
		{
			if (!use[j] && min + graph[k][j] < dis[j])
			{
				dis[j] = min + graph[k][j];
			}
		}
	}
	for (auto it : dis)
	{
		cout << it << " ";
	}
	cout << endl;
	return dis[end];
}
#endif

//使用小根堆优化
int Dijkstra(vector<vector<uint>>& graph,
	int start,
	int end)
{
	priority_queue < pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>> que;
	const int N = graph.size();

	vector<uint>dis(N, 0);	//存储最短路径
	vector<bool>use(N, false);
	//把start放入S集合
	use[start] = true;
	dis[start] = 0;
	//初始化start到个节点的权值
	for (int i = 0; i < N; ++i)
	{
		dis[i] = graph[start][i];
		if (i != start)
		{
			que.emplace(graph[start][i], i);
		}
	}

	//处理每一个U集合中的元素
	while(!que.empty())
	{
		auto pair = que.top();
		que.pop();
		if (pair.first == INF)
		{
			break;
		}
		//找到最小权值
		int min = pair.first;
		int k = pair.second;
		if (use[k])
		{
			continue;
		}

		for (int j = 0; j < N; ++j)
		{
			if ((!use[j]) && dis[j] < min)
			{
				min = dis[j];
				que.emplace(graph[start][j], j);
			}
		}
		if (k == -1)
		{
			break;
		}
		use[k] = true;
		for (int j = 0; j < N; ++j)
		{
			if (!use[j] && min + graph[k][j] < dis[j])
			{
				dis[j] = min + graph[k][j];
			}
		}
	}
	for (auto it : dis)
	{
		cout << it << " ";
	}
	cout << endl;
	return dis[end];
}

/*
int main()
{
	vector<vector<uint>> graph =
	{
		{0, 6, 3, INF, INF, INF},
		{6, 0, 2, 5, INF, INF},
		{3, 2, 0, 3, 4, INF},
		{INF, 5, 3, 0, 2, 3},
		{INF, INF, 4, 2, 0, 5},
		{INF, INF, INF, 3, 5, 0}
	};
	int distance = Dijkstra(graph, 0, 3);
	if (distance == INF)
	{
		cout << "不存在有效路径" << endl;
	}
	else
	{
		cout << "distance:" << distance << endl;
	}
	return 0;
}
*/