#include<iostream>
#include<queue>
using namespace std;

int w[] = { 12,8,15 };
const int n = sizeof(w) / sizeof(w[0]);
int c = 20;
int cw = 0;
int i = 0;
int bestw = 0;
int r = 0; //记录未选择的数总和

struct Node
{
    Node(int w, int l, Node* p, bool left)
    {
        level = l;
        weight = w;
        parent = p;
        isLeft = left;
    }
    Node* parent;
    bool isLeft;
    int level;
    int weight;
};
queue<Node*> que;
Node* bestNode = nullptr;

void addLiveNode(int w, int l, Node* p, bool isLeft)
{
    Node* node = new Node(w, l, p, isLeft);
    que.push(node);

    if (l == n && w == bestw)
    {
        bestNode = node;
    }
}

int maxBound(int i)
{
    int sum = 0;
    for (int j = i + 1; j < n; ++j)
    {
        sum += w[j];
    }
    return sum;
}

int main()
{
    Node* parent = nullptr;
    int wt = 0;
    while (i < n)
    {
        wt = cw + w[i];
        if (wt <= c)
        {
            if (wt > bestw)
            {
                bestw = wt;
            }
            addLiveNode(wt, i + 1, parent, true);
        }

        r = maxBound(i);
        if (r + cw >= bestw)
        {
            addLiveNode(cw, i + 1, parent, false);
        }

        Node* node = que.front();
        que.pop();
        i = node->level;
        cw = node->weight;
        parent = node;
    }

    int bestx[n] = { 0 };
    for (int j = n - 1; j >= 0; --j)
    {
        bestx[j] = bestNode->isLeft ? 1 : 0;
        bestNode = bestNode->parent;
    }

    for (int v : bestx)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << "bestw:" << bestw << endl;
    return 0;
}
