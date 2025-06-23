#include<iostream>
#include<queue>
using namespace std;

//ͨ�������TopK����
void topK1(int arr[], int size,int k)
{
	//���������
	priority_queue<int>maxheap;
	for (int i = 0; i < k; i++)
	{
		maxheap.push(arr[i]);
	}
	//��СԪ�طŽ�ȥ��
	for (int i = k; i < size; i++)
	{
		if (arr[i] < maxheap.top())
		{
			maxheap.pop();
			maxheap.push(arr[i]);
		}
	}
	cout << "��Сk��Ԫ��λ: ";
	for (int i = 0; i < k; i++)
	{
		cout << maxheap.top() << ' ';
		maxheap.pop();
	}
	cout << endl;
}

//���ŷָ�
int partition(int arr[], int l, int r)
{
	int val = arr[l];
	int i = l, j = r;
	while (i < j)
	{
		while(i < j && arr[j] > val)
			j--;
		if (i < j)
			arr[i++] = arr[j];
		while (i < j && arr[i] < val)
			i++;
		if (i < j)
			arr[j--] = arr[i];
	}
	arr[i] = val;
	return i;
}

//ͨ�����ŷָ����TopK����
void topK2(int arr[], int size, int k)
{
	int pos = k - 1;
	int l = 0, r = size - 1;
	while (l <= r)
	{
		int i = partition(arr, l, r);
		if (i == pos)
			break;
		else if (i < pos)
			l = i + 1;
		else
			r = i - 1;
	}
	cout << "��Сk��Ԫ��Ϊ: ";
	for (int i = 0; i < k; ++i) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

int main()
{
	int arr[] = { 21,84,65,17,20,94,15,64,54,94 };
	//�������3����СԪ�ء�
	topK1(arr, 10, 3);
	
	//���ŷָ���3����СԪ��
	topK2(arr, 10, 3);
	return 0;
}