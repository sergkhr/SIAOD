#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <chrono>


using namespace std;

void randomizeArray(vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = rand() % 101;
	}
}

void bubbleSort(vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		bool flag = false;
		for (int j = 0; j < arr.size() - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = true;
			}
		}
		if (!flag)return; //Aiverson stuff )))
	}
}

void arrOut(const vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	srand(time(0));

	int n;
	cin >> n;

	vector<int> arr(n);
	randomizeArray(arr);
	//arrOut(arr);

	auto start = std::chrono::steady_clock::now();

	bubbleSort(arr);

	auto end = std::chrono::steady_clock::now();
	auto elapsedMilliseconds = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

	//arrOut(arr);
	cout << "in " << elapsedMilliseconds << "ms" << endl;

	return 0;
}