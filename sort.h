#ifndef SORT_H
#define SORT_H
#include<iostream>
#include<vector>
#include<stack>

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
void QuickSwap(T* a, const int left, const int right ,stack<int>& s) {
	if (left < right) {
		int i = left, j = right + 1, pivot = a[left];
		do {
			do i++; while (a[i] < pivot);
			do j--; while (a[j] > pivot);
			if (i < j)swap(a[i], a[j]);
		} while (i < j);
		swap(a[left], a[j]);

		s.push(left);
		s.push(j - 1);
		s.push(j + 1);
		s.push(right);
	}
}

template <class T>
void QuickSort(T* a, int n) {
	
	stack< int> s;
	s.push(1);
	s.push(n);
	while (!s.empty()) {
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();
		QuickSwap(a, left, right , s);
		
	}
}

//template <class T>
//void QuickSort(T* a, const int left, const int right) {
//	if (left < right) {
//		int i = left, j = right + 1, pivot = a[left];
//		do {
//			do i++; while (a[i] < pivot);
//			do j--; while (a[j] > pivot);
//			if (i < j)swap(a[i], a[j]);
//		} while (i < j);
//		swap(a[left], a[j]);
//
//		QuickSort(a, left, j - 1);
//		QuickSort(a, j + 1, right);
//	}
//	else return;
//}

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

	vector<int> order;
	int s = 1, m = 1, e = 2;
	while (s <= n) {
		m = s;
		while (m != n&& a[m] <= a[m + 1]) {
			m++;
		}
		if (m == n) {
			order.push_back(s);
			order.push_back(m);
			break;
		}
		else { 
			e = m + 1;
			
			while (e != n && a[e] <= a[e + 1]) {
				e++;
				
			}
			

			order.push_back(s);
			order.push_back(m);
			order.push_back(e);
			s = e + 1;
		}

	}

	T* tempList = new T[n + 1];
	
	bool toggle = true;
	int i;
	for (i = 3; i <= order.size(); i *= 2) {
		int j;
		for (j = 0; order.size() - j >= i; j += i) {
			s = order[j];
			m = order[j + (i - 1) / 2];	
			e = order[j + i - 1];
			if (toggle) Merge(a, tempList, s, m, e);
			else Merge(tempList, a, s, m, e);
		}
		if ((order.size() - j <= i/2) && order.size() - j > 0) {
			if (toggle)copy(a + order[j], a + n + 1, tempList + order[j]);
			else copy(tempList + order[j], tempList + n + 1, a + order[j]);
		}
		else if (order.size() - j > i/2) {
			s = order[j];
			m = order[j + (i - 1) / 2];
			e = n;
			if (toggle)Merge(a, tempList, s, m, e);
			else Merge(tempList, a, s, m, e);
		}
		
		toggle = !toggle;

	}

	if (i > order.size()) {
		s = 1;
		m = order[(i - 1) / 2];
		e = n;
		if (toggle)Merge(a, tempList, s, m, e);
		else Merge(tempList, a, s, m, e);
		
		toggle = !toggle;
	}

	if (!toggle)copy(tempList + 1, tempList + n + 1, a + 1);

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