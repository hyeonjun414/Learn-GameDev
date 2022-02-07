// B-1. Sort.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// 
// 1. 정렬의 종류
//  - 반복 정렬 : 배열을 유지함 ( O(n^2) )
//      1) 삽입 정렬 : 데이터를 훑어서 키의 위치를 정하고 데이터를 옮기며 삽입하는 방식.
//      2) 선택 정렬 : 데이터를 훑어본 후 가장 작은 값을 앞으로 배치 ( 최소 값이 하나씩 늘어남. )
//      3) 버블 정렬 : i의 데이터가 i+1의 데이터를 비교하여 데이터를 교체하는 방식 ( 최대 값이 하나씩 줄어듬 )
//  - 분할 정렬 : 배열을 깨뜨림 ( O(nlogn) or O(n) )
//      4) 합병 정렬 : 데이터를 하나가 될때까지 절반씩 나누며 정렬하는 방식
//      5)  퀵  정렬 : 첫 원소를 기준으로 작은 값, 큰 값으로 나누어 절반씩 나눠서 정렬하는 방식 
//


#include <iostream>
#include <vector>
#include <list>


#define SIZE 9
#define INF	 9999999

using namespace std;

void printVector(const vector<int>& vec)
{
	for (int i = 0; i < SIZE; i++)
		cout << vec[i] << ", ";

	cout << endl;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}


#pragma region Vector Sort
void selectionSort(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		int minValueIndex = i;

		for (int j = i; j < vec.size(); j++)
			minValueIndex = vec[j] < vec[minValueIndex] ? j : minValueIndex;

		swap(vec[i], vec[minValueIndex]);
	}
}
void insertionSort(vector<int>& vec)
{
	// 첫번째 원소는 비교 대상이 없으니 두번쨰 원소부터 정렬을 수행한다.
	for (int i = 1; i < vec.size(); i++)
	{
		// 현재 비교하는 값은 i번째 값이다.
		int j; // 값이 들어가는 위치의 인덱스를 저장할 필요가 있으므로 선언울 따로한다.
		int key = vec[i];
		// 비교되는 원소의 인덱스가 첫번째 원소의 위치에 도달하거나,
		// key 값보다 클 경우에 반복문을 종료한다.
		// 인덱스를 거꾸로 진행한다. -> j--;
		for (j = i - 1; j >= 0 && key < vec[j]; j--)
		{
			// 반복문이 진행되는 동안 키 값의 인덱스부터 원소들을 차례대로 한칸씩 뒤로 밀어준다.
			vec[j + 1] = vec[j];
		}
		// 키 값을 최종적인 위치에 삽입해준다.
		vec[j + 1] = key;
	}

}
void bubbleSort(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec.size() - i - 1; j++)
		{
			if (vec[j] > vec[j + 1])
				swap(vec[j], vec[j + 1]);
		}
	}
}

void merge(vector<int>& vec, int start_index, int mid_index, int end_index)
{
	vector<int> sorted;
	int left_index = start_index;
	int right_index = mid_index + 1;

	while (left_index <= mid_index && right_index <= end_index)
	{
		if (vec[left_index] < vec[right_index])
			sorted.push_back(vec[left_index++]);
		else
			sorted.push_back(vec[right_index++]);
	}

	if (left_index > mid_index) // 왼쪽 배열이 먼저 다 소진된 경우
	{
		// 오른쪽 배열 나머지를 전부 sorted 배열에 넣어야 한다.
		for (int i = right_index; i <= end_index; i++)
		{
			// 마지막인덱스까지 넣어준다.
			sorted.push_back(vec[i]);
		}
	}
	else // 오른쪽 배열이 먼저 다 소진된 경우
	{
		// 왼쪽 배열 나머지를 전부 sorted 배열에 넣어야 한다.
		for (int i = left_index; i <= mid_index; i++)
		{
			// 마지막인덱스까지 넣어준다.
			sorted.push_back(vec[i]);
		}
	}

	for (int i = start_index; i <= end_index; i++)
	{
		// sorted의 인덱스가 벡터의 인덱스와 같지 않기 때문에 i-start_index를 해줘야한다.
		vec[i] = sorted[i - start_index];
	}
}

void mergeSort(vector<int>& vec, int start_index, int end_index)
{
	if (start_index == end_index) return;

	int mid_index = (start_index + end_index) / 2;

	mergeSort(vec, start_index, mid_index);
	mergeSort(vec, mid_index + 1, end_index);
	merge(vec, start_index, mid_index, end_index);
}
void quickSort(vector<int>& vec, int start_index, int end_index)
{
	// 시작 지점이 끝 지점과 같거나 더 클때, 즉 더이상 구역을 나눌 수 없을 때 반환한다.
	if (start_index >= end_index) return;

	// 중간 지점을 pivot으로 지정한다.
	int pivot = vec[(start_index + end_index) / 2];
	// 기존의 시작 지점 정보와 끝 지점 정보를 유지하기 위해 변수를 생성한다.
	int low = start_index;
	int high = end_index;

	// 아래 위로 탐색하면서 pivot을 기준으로 작은 값을 좌측에, 큰 값을 우측에 위치시킨다.
	while (low <= high)
	{
		// 각 인덱스가 조건에 부합할 때까지 찾아낸다.
		while (vec[low] < pivot) low++;
		while (vec[high] > pivot) high--;

		// 찾아낸 인덱스의 값이 교차되지 않았다면 각 인덱스의 원소를 교환해준다.
		if (low <= high)
		{
			swap(vec[low], vec[high]);
			low++;
			high--;
		}
	}

	// 교차된 인덱스를 기준으로 분할하여 다시 재귀로 처리한다.
	quickSort(vec, start_index, high);
	quickSort(vec, low, end_index);
}
#pragma endregion

#pragma region List Sort
void selectionSort(list<int>& vec)
{
	list<int>::iterator iter;
	list<int>::iterator iterEnd = vec.end();
	for (iter = vec.begin(); iter != iterEnd; ++iter)
	{
		list<int>::iterator iter2;
		list<int>::iterator iterEnd2 = vec.end();

		list<int>::iterator minValueIndex = iter;

		for (iter2 = iter; iter2 != iterEnd2; ++iter2)
			minValueIndex = *iter2 < *minValueIndex ? iter2 : minValueIndex;

		swap(*iter, *minValueIndex);
	}
}
void insertionSort(list<int>& vec)
{
	list<int>::iterator iter;
	list<int>::iterator iterEnd = vec.end();

	// 첫번째 원소는 비교 대상이 없으니 두번쨰 원소부터 정렬을 수행한다.
	for (iter = ++vec.begin(); iter != iterEnd; ++iter)
	{
		list<int>::iterator iter2;
		list<int>::iterator iterEnd2 = vec.end();

		list<int>::iterator minValueIndex = iter;
		// 현재 비교하는 값은 i번째 값이다.
		int j; // 값이 들어가는 위치의 인덱스를 저장할 필요가 있으므로 선언울 따로한다.
		int key = vec[i];
		// 비교되는 원소의 인덱스가 첫번째 원소의 위치에 도달하거나,
		// key 값보다 클 경우에 반복문을 종료한다.
		// 인덱스를 거꾸로 진행한다. -> j--;
		for (iter2 = iter - 1; j >= 0 && key < vec[j]; j--)
		{
			// 반복문이 진행되는 동안 키 값의 인덱스부터 원소들을 차례대로 한칸씩 뒤로 밀어준다.
			vec[j + 1] = vec[j];
		}
		// 키 값을 최종적인 위치에 삽입해준다.
		vec[j + 1] = key;
	}

}
void bubbleSort(list<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec.size() - i - 1; j++)
		{
			if (vec[j] > vec[j + 1])
				swap(vec[j], vec[j + 1]);
		}
	}
}

void merge(list<int>& vec, int start_index, int mid_index, int end_index)
{
	vector<int> sorted;
	int left_index = start_index;
	int right_index = mid_index + 1;

	while (left_index <= mid_index && right_index <= end_index)
	{
		if (vec[left_index] < vec[right_index])
			sorted.push_back(vec[left_index++]);
		else
			sorted.push_back(vec[right_index++]);
	}

	if (left_index > mid_index) // 왼쪽 배열이 먼저 다 소진된 경우
	{
		// 오른쪽 배열 나머지를 전부 sorted 배열에 넣어야 한다.
		for (int i = right_index; i <= end_index; i++)
		{
			// 마지막인덱스까지 넣어준다.
			sorted.push_back(vec[i]);
		}
	}
	else // 오른쪽 배열이 먼저 다 소진된 경우
	{
		// 왼쪽 배열 나머지를 전부 sorted 배열에 넣어야 한다.
		for (int i = left_index; i <= mid_index; i++)
		{
			// 마지막인덱스까지 넣어준다.
			sorted.push_back(vec[i]);
		}
	}

	for (int i = start_index; i <= end_index; i++)
	{
		// sorted의 인덱스가 벡터의 인덱스와 같지 않기 때문에 i-start_index를 해줘야한다.
		vec[i] = sorted[i - start_index];
	}
}

void mergeSort(list<int>& vec, int start_index, int end_index)
{
	if (start_index == end_index) return;

	int mid_index = (start_index + end_index) / 2;

	mergeSort(vec, start_index, mid_index);
	mergeSort(vec, mid_index + 1, end_index);
	merge(vec, start_index, mid_index, end_index);
}
void quickSort(vector<int>& vec, int start_index, int end_index)
{
	// 시작 지점이 끝 지점과 같거나 더 클때, 즉 더이상 구역을 나눌 수 없을 때 반환한다.
	if (start_index >= end_index) return;

	// 중간 지점을 pivot으로 지정한다.
	int pivot = vec[(start_index + end_index) / 2];
	// 기존의 시작 지점 정보와 끝 지점 정보를 유지하기 위해 변수를 생성한다.
	int low = start_index;
	int high = end_index;

	// 아래 위로 탐색하면서 pivot을 기준으로 작은 값을 좌측에, 큰 값을 우측에 위치시킨다.
	while (low <= high)
	{
		// 각 인덱스가 조건에 부합할 때까지 찾아낸다.
		while (vec[low] < pivot) low++;
		while (vec[high] > pivot) high--;

		// 찾아낸 인덱스의 값이 교차되지 않았다면 각 인덱스의 원소를 교환해준다.
		if (low <= high)
		{
			swap(vec[low], vec[high]);
			low++;
			high--;
		}
	}

	// 교차된 인덱스를 기준으로 분할하여 다시 재귀로 처리한다.
	quickSort(vec, start_index, high);
	quickSort(vec, low, end_index);
}
#pragma endregion


// +a 벡터가 아니라 list로 정렬 시도
int main()
{
	srand((unsigned int)time(NULL));

	vector<int> selectionVector;	// 선택정렬 
	vector<int> insertionVector;	// 삽입정렬
	vector<int> bubbleVector;		// 버블정렬 
	vector<int> mergeVector;		// 합병정렬 
	vector<int> quickVector;		// 퀵 정렬  

	for (int i = 0; i < SIZE; i++)
	{
		int random = rand() % SIZE;

		selectionVector.push_back(random);
		insertionVector.push_back(random);
		bubbleVector.push_back(random);
		mergeVector.push_back(random);
		quickVector.push_back(random);
	}
	cout << "정렬 전   : ";
	printVector(selectionVector);

	selectionSort(selectionVector);
	cout << "선택 정렬 : ";
	printVector(selectionVector);

	insertionSort(insertionVector);
	cout << "삽입 정렬 : ";
	printVector(insertionVector);

	bubbleSort(bubbleVector);
	cout << "버블 정렬 : ";
	printVector(bubbleVector);

	mergeSort(mergeVector, 0, SIZE - 1);
	cout << "합병 정렬 : ";
	printVector(mergeVector);

	quickSort(quickVector, 0, SIZE - 1);
	cout << "퀵 정렬   : ";
	printVector(quickVector);
}