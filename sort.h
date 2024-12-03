#ifndef SORT_H
#define SORT_H
#include<iostream>

using namespace std;

template <class T>
void Insert(T temp, T* a, int i) {
	a[0] = temp;
	while (a[i] > temp) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = temp;
}
template <class T>
void InsertionSort(T* a, int n) {
	for (int j = 2; j <= n; j++) {
		T temp = a[j];
		Insert(temp, a, j - 1);
	}
}

template <class T>
void QuickSwap(T* a, const int left, const int right ,pair<int,int>* stack, int& top) {
	if (left < right) {
		int i = left, j = right + 1, pivot = a[left];
		do {
			do i++; while (a[i] < pivot);
			do j--; while (a[j] > pivot);
			if (i < j)swap(a[i], a[j]);
		} while (i < j);
		swap(a[left], a[j]);

		stack[++top]=make_pair(left, j - 1);
		stack[++top]=make_pair(j + 1, right);
	}
}

template <class T>
void QuickSort(T* a, int n) {
	
	pair<int, int>* s = new pair<int, int>[n + 1];
	s[1] = make_pair(1, n);
	int top = 1;
	while (top > 0) {
		int left = s[top].first;
		int right = s[top].second;
		top--;
		QuickSwap(a, left, right , s, top);
		
	}
	delete[]s;
}

template <class T>
void Merge(T* initList, T* resultList, int start, int mid, int end) {
	int p1, p2, p;
	for (p1 = start, p2 = mid + 1, p = start; p1 <= mid && p2 <= end; p++) {
		if (initList[p1] < initList[p2]) {
			resultList[p] = initList[p1];
			p1++;
		}
		else {
			resultList[p] = initList[p2];
			p2++;
		}
	}
	copy(initList + p1, initList + mid + 1, resultList + p);
	copy(initList + p2, initList + end + 1, resultList + p);
}

template <class T>
void NaturalMergeSort(T* a, const int n) {

	int* ascend = new int[n + 1];
	ascend[1] = 1;
	int count = 1; //오름차순의 갯수
	for (int i = 2; i <= n; i++) {
		if (a[i] < a[i - 1]) ascend[++count] = i; //오름차순의 시작점 인덱스 저장
	}

	int* tempList = new int[n + 1];

	while (count > 1) {
		int i;
		for (i = 1; i <= count - 2; i += 2) {
			Merge(a, tempList, ascend[i], ascend[i + 1] - 1, ascend[i + 2] - 1);
		}
		if (count - i == 1) {
			Merge(a, tempList, ascend[i], ascend[i + 1] - 1, n);
			copy(tempList + 1, tempList + n + 1, a + 1);
		}
		else copy(tempList + 1, tempList + ascend[i], a + 1);
		

		int precount = count;
		count = 0;
		for (int i = 1; i <= precount; i += 2) {
			ascend[++count] = ascend[i];
		}
	}

	delete[]ascend;
	delete[]tempList;
}

template <class T>
void Adjust(T* a, const int i, const int n) {
	T root = a[i];

	int j;
	for (j = 2 * i; j <= n; j *= 2) {
		if (j < n && a[j + 1] > a[j]) j++;
		if (a[j] < root) break;
		else a[j / 2] = a[j];
	}
	a[j / 2] = root;
}

template <class T>
void HeapSort(T* a, const int n) {
	for (int i = n / 2; i >= 1; i--) Adjust(a, i, n);
	for (int i = n - 1; i >= 1; i--) {
		swap(a[1], a[i + 1]);
		Adjust(a, 1, i);
	}
}
#endif