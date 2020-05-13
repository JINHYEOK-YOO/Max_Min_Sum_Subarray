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
	int n;	// 배열 크기
	int maxSubSum = INT_MIN;	// 얻어진 1차원 배열 내에서 연속부분배열의 합 최댓값
	int maxSum = INT_MIN;	// 2차원 배열 전체에서 연속부분배열의 합 최댓값
	int minSubSum = INT_MAX;	// 얻어진 1차원 배열 내에서 연속부분배열의 합 최솟값
	int minSum = INT_MAX;	// 2차원 배열 전체에서 연속부분배열의 합 최솟값
	int maxStartCol1 = 0, minStartCol1 = 0;	// 연속부분배열 시작점 예비 후보
	int maxStartCol2 = 0, minStartCol2 = 0;	// 연속부분배열 시작점 최종 후보
	int maxEndCol = 0, minEndCol = 0;	// 연속부분배열 끝점 후보
	Point maxStartPoint, maxEndPoint;	// 최대 연속부분배열 합 시작점 , 끝점
	Point minStartPoint, minEndPoint;	// 최소 연속부분배열 합 시작점, 끝점

	cin >> n;
	vector< vector<int> > s;	// 사용자 입력 배열
	vector< vector<int> > c;	// 열 누적 합 배열
	vector<int> rMax(n);	// 행끼리 뺀 값 들어갈 1차원 배열 for 최댓값
	vector<int> rMin(n);	// 행끼리 뺀 값 들어갈 1차원 배열 for 최솟값

	/* Vector 크기 설정 */
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
			cin >> s[i][j];	// 입력
		}
	}

	///* Calculate *///
	for (int j = 0; j < n; j++)
		c[0][j] = 0;	// 1번째 행은 전부 0

	/* 배열의 세로 방향으로 값을 누적 합하여 배열을 채워간다.*/
	for (int j = 0; j < n; j++)
	{
		for (int i = 1; i < n + 1; i++)
			c[i][j] = c[i - 1][j] + s[i - 1][j];
	}

	/* k = (부분배열의 시작 행 - 1)*/
	/* i = (부분배열 끝 행) */
	/* j = (부분배열의 열) */
	for (int k = 0; k < n + 1; k++)
	{
		for (int i = k + 1; i < n + 1; i++)
		{
			maxStartCol1 = 0;
			minStartCol1 = 0;
			/* Kadane 알고리즘 적용할 1차원 배열 생성 */
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