#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include "sort.h"
using namespace std;
int main(int argc, char* argv[]) {
	int T = atoi(argv[1]); // num of test case
	cout << "T=" << T << endl;
	int N; // �� �׽�Ʈ���̽� �� ���ڵ��� ����
	int i; // iterator
	double result[4]; // result �迭�� �� �˰��� ���� ����ð��� �����ϰ� �˴ϴ�.
	/*
	* result[0]: insertion sort
	* result[1]: quick sort
	* result[2]: natural merge sort
	* result[3]: heap sort
	* */
	
	chrono::system_clock::time_point start_t, end_t;
	double diff_t;
	if (argc < 3) {
		cerr << "wrong argument count" << endl;
		return 1;
	}
	cout << "--INS--|--QUICK--|--NATMG--|--HEAP--|" << endl;
	for (i = 2; i < T + 2; i++) {
		// i��° ������ ������ �н��ϴ�.
		fstream fin(argv[i]);
		// �� ���� �˰��� �ʿ��� �ڷᱸ���� �����ϰ� �����͸� ����ϴ�.
		fin >> N;
		int* arr = new int[N+1];
		for (int i = 1; i <= N; i++) {
			fin >> arr[i];
		}
		// ������� ���� �ð� ������ �����մϴ�.
		/* example
		gettimeofday(&start_t, NULL);
		�������� ����
		gettimeofday(&end_t, NULL);
		 diff_t = (double)(end_t.tv_sec-start_t.tv_sec)+((double)(end_t.tv_usec-start_t.tv_usec)/1000000);
		result[0] = diff_t;
		*/
		//�ð����⵵ �ڼ��� ����
		int* temp = new int[N + 1];

		copy(arr + 1, arr + N + 1, temp + 1);
		start_t = chrono::system_clock::now();
		InsertionSort(temp, N );
		end_t = chrono::system_clock::now();
		diff_t = (double)chrono::duration_cast<chrono::microseconds>(end_t - start_t).count() / 1000000;
		result[0] = diff_t;
		
		copy(arr + 1, arr + N + 1, temp + 1);
		start_t = chrono::system_clock::now();
		QuickSort(temp, 1, N);
		end_t = chrono::system_clock::now();
		diff_t = (double)chrono::duration_cast<chrono::microseconds>(end_t - start_t).count() / 1000000;
		result[1] = diff_t;

		
		copy(arr + 1, arr + N + 1, temp + 1);
		start_t = chrono::system_clock::now();
		NaturalMergeSort(temp, N);
		end_t = chrono::system_clock::now();
		diff_t = (double)chrono::duration_cast<chrono::microseconds>(end_t - start_t).count() / 1000000;
		result[2] = diff_t;

		copy(arr + 1, arr + N + 1, temp + 1);
		start_t = chrono::system_clock::now();
		HeapSort(temp, N);
		end_t = chrono::system_clock::now();
		diff_t = (double)chrono::duration_cast<chrono::microseconds>(end_t - start_t).count() / 1000000;
		result[3] = diff_t;

		delete[]arr;
		delete[]temp;
		
		/* ����� ����մϴ�. (�� �κ��� �������� �ʽ��ϴ�) */
		cout.precision(5);
		cout << fixed;
		for (int j = 0; j < 4; j++) {
			cout << result[j] << " ";
		}
		cout  << N << endl;
	}
}