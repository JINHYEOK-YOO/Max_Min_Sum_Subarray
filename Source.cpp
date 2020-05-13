#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct
{
	int row = 0;
	int col = 0;
} Point;

int main()
{
	///* Input and Initialize *///
	int n;	// �迭 ũ��
	int maxSubSum = INT_MIN;	// ����� 1���� �迭 ������ ���Ӻκй迭�� �� �ִ�
	int maxSum = INT_MIN;	// 2���� �迭 ��ü���� ���Ӻκй迭�� �� �ִ�
	int minSubSum = INT_MAX;	// ����� 1���� �迭 ������ ���Ӻκй迭�� �� �ּڰ�
	int minSum = INT_MAX;	// 2���� �迭 ��ü���� ���Ӻκй迭�� �� �ּڰ�
	int maxStartCol1 = 0, minStartCol1 = 0;	// ���Ӻκй迭 ������ ���� �ĺ�
	int maxStartCol2 = 0, minStartCol2 = 0;	// ���Ӻκй迭 ������ ���� �ĺ�
	int maxEndCol = 0, minEndCol = 0;	// ���Ӻκй迭 ���� �ĺ�
	Point maxStartPoint, maxEndPoint;	// �ִ� ���Ӻκй迭 �� ������ , ����
	Point minStartPoint, minEndPoint;	// �ּ� ���Ӻκй迭 �� ������, ����

	cin >> n;
	vector< vector<int> > s;	// ����� �Է� �迭
	vector< vector<int> > c;	// �� ���� �� �迭
	vector<int> rMax(n);	// �ೢ�� �� �� �� 1���� �迭 for �ִ�
	vector<int> rMin(n);	// �ೢ�� �� �� �� 1���� �迭 for �ּڰ�

	/* Vector ũ�� ���� */
	for (int i = 0; i < n + 1; i++)
	{
		vector<int> element(n);
		s.push_back(element);
		c.push_back(element);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> s[i][j];	// �Է�
		}
	}

	///* Calculate *///
	for (int j = 0; j < n; j++)
		c[0][j] = 0;	// 1��° ���� ���� 0

	/* �迭�� ���� �������� ���� ���� ���Ͽ� �迭�� ä������.*/
	for (int j = 0; j < n; j++)
	{
		for (int i = 1; i < n + 1; i++)
			c[i][j] = c[i - 1][j] + s[i - 1][j];
	}

	/* k = (�κй迭�� ���� �� - 1)*/
	/* i = (�κй迭 �� ��) */
	/* j = (�κй迭�� ��) */
	for (int k = 0; k < n + 1; k++)
	{
		for (int i = k + 1; i < n + 1; i++)
		{
			maxStartCol1 = 0;
			minStartCol1 = 0;
			/* Kadane �˰��� ������ 1���� �迭 ���� */
			for (int j = 0; j < n; j++)
				rMax[j] = rMin[j] = c[i][j] - c[k][j];
			maxSubSum = rMax[0];
			minSubSum = rMin[0];
			for (int j = 1; j < n; j++)
			{
				/*rMax[j] = max(rMax[j], rMax[j] + rMax[j - 1]) */
				if (rMax[j] < rMax[j] + rMax[j - 1])
					rMax[j] = rMax[j] + rMax[j - 1];
				else
					maxStartCol1 = j;
				if (maxSubSum < rMax[j])
				{
					maxSubSum = rMax[j];
					maxStartCol2 = maxStartCol1;
					maxEndCol = j;
				}

				/*rMin[j] = min(rMin[j], rMin[j] + rMin[j - 1]) */
				if (rMin[j] > rMin[j] + rMin[j - 1])
					rMin[j] = rMin[j] + rMin[j - 1];
				else
					minStartCol1 = j;
				if (minSubSum > rMin[j])
				{
					minSubSum = rMin[j];
					minStartCol2 = minStartCol1;
					minEndCol = j;
				}
			}
			if (maxSum < maxSubSum)
			{
				maxSum = maxSubSum;
				maxStartPoint.row = k;
				maxStartPoint.col = maxStartCol2;
				maxEndPoint.row = i - 1;
				maxEndPoint.col = maxEndCol;
			}
			if (minSum > minSubSum)
			{
				minSum = minSubSum;
				minStartPoint.row = k;
				minStartPoint.col = minStartCol2;
				minEndPoint.row = i - 1;
				minEndPoint.col = minEndCol;
			}
		}
	}

	///* Print *///
	cout << n << endl;
	cout << maxSum << endl;
	cout << "(" << maxStartPoint.row << ", " << maxStartPoint.col << ") ";
	cout << "(" << maxEndPoint.row << ", " << maxEndPoint.col << ") " << endl;
	cout << minSum << endl;
	cout << "(" << minStartPoint.row << ", " << minStartPoint.col << ") ";
	cout << "(" << minEndPoint.row << ", " << minEndPoint.col << ") " << endl;

	return 0;
}