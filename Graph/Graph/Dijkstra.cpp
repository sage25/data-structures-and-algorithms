#include<vector>
#include<iostream>
#include<queue>
using namespace std;

using uint = unsigned int;
const int INF = INT_MAX;

#if 0
//�Ͻ�˹�����㷨�������ͼ��̴�Ȩ·����̰���㷨+������ȣ�
int Dijkstra(vector<vector<uint>>& graph,
			int start,
			int end)
{
	const int N = graph.size();

	vector<uint>dis(N, 0);	//�洢���·��
	vector<bool>use(N, false);
	//��start����S����
	use[start] = true;
	dis[start] = 0;
	//��ʼ��start�����ڵ��Ȩֵ
	for (int i = 0; i < N; ++i)
	{
		dis[i] = graph[start][i];
	}

	//����ÿһ��U�����е�Ԫ��
	for (int i = 1; i < N; ++i)
	{
		//�ҵ���СȨֵ
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

//ʹ��С�����Ż�
int Dijkstra(vector<vector<uint>>& graph,
	int start,
	int end)
{
	priority_queue < pair<uint, int>, vector<pair<uint, int>>, greater<pair<uint, int>>> que;
	const int N = graph.size();

	vector<uint>dis(N, 0);	//�洢���·��
	vector<bool>use(N, false);
	//��start����S����
	use[start] = true;
	dis[start] = 0;
	//��ʼ��start�����ڵ��Ȩֵ
	for (int i = 0; i < N; ++i)
	{
		dis[i] = graph[start][i];
		if (i != start)
		{
			que.emplace(graph[start][i], i);
		}
	}

	//����ÿһ��U�����е�Ԫ��
	while(!que.empty())
	{
		auto pair = que.top();
		que.pop();
		if (pair.first == INF)
		{
			break;
		}
		//�ҵ���СȨֵ
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
		cout << "��������Ч·��" << endl;
	}
	else
	{
		cout << "distance:" << distance << endl;
	}
	return 0;
}
*/