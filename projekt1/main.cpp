#include <iostream>

using namespace std;

int div(int arr_id[], int arr_v[], int start, int stop) {
	int p = arr_v[start];
	int i = start, j = stop, tmp, tmp2;
	for (;;) {
		while (arr_v[j] > p) { j--; }
		while (arr_v[i] < p) { i++; }
		if (i < j) {
			tmp = arr_v[i];
			tmp2 = arr_id[i];
			arr_v[i] = arr_v[j];
			arr_id[i] = arr_id[j];
			arr_v[j] = tmp;
			arr_id[j] = tmp2;
			i++;
			j--;
			continue;
		}
		return j;
	}
}
void qsort(int arr_id[], int arr_v[], int start, int stop) {
	int p;
	if (start < stop) {
		p = div(arr_id, arr_v, start, stop);
		qsort(arr_id, arr_v, start, p);
		qsort(arr_id, arr_v, p + 1, stop);
	}
}
void print(int** arr, int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << arr[0][i] << "\t" << arr[1][i] << endl;
	}
	cout << endl;
}


int main() {
	int n, p;
	cin >> n;
	cin >> p;

	int** arr = new int* [2];
	arr[0] = new int[n];
	arr[1] = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> arr[0][i];			// array[0] - id
		cin >> arr[1][i];			// array[1] - value
		//arr[1][i] = n - i;
		//arr[0][i] = n - i;
	}

	//print(arr, n);


	qsort(arr[0], arr[1], 0, n - 1);

	int sum = 0;
	int middle_id = -1;
	for (int i = 0; i < n; i++) {
		sum += arr[1][i];
		if (sum > p) { break; }
		middle_id++;
	}
	sum = 0;
	int last_id = middle_id;
	for (int i = middle_id + 1; i < n; i++) {
		sum += arr[1][i];
		if (sum > p) { break; }
		last_id++;
	}
	//cout << "last id: " << last_id << endl;
	//print(arr, n);

	qsort(arr[1], arr[0], 0, middle_id);
	qsort(arr[1], arr[0], middle_id + 1, last_id);

	//print(arr, n);

	cout << "1: ";
	for (int i = middle_id; i > -1; i--) {
		cout << arr[0][i] << " ";
	}
	cout << endl;
	cout << "2: ";
	for (int i = last_id; i > middle_id; i--) {
		cout << arr[0][i] << " ";
	}
	//cout << endl;
	delete arr;
	return 0;
}
