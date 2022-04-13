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

void arrOut(const vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
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

void shellSort(vector<int>& arr) {
	vector<int> steps = {1, 4, 10, 23, 57, 132, 301, 501, 1750}; //best for n < 4000 according to wiki
	for(int stInd = steps.size()-1; stInd >= 0; stInd--){
		for(int i = steps[stInd]; i < arr.size(); i++){
			for(int j = i - steps[stInd]; j >= 0 && arr[j] > arr[j + steps[stInd]]; j -= steps[stInd]){
				swap(arr[j], arr[j + steps[stInd]]);
			}
		}
	}
	
}

void mergeSort(vector<int>& arr, int left = 0, int right = -1) {
	if(right == -1) right = arr.size() - 1;
	if(right - left == 1){ //two-block array
		if(arr[left] > arr[right]) swap(arr[left], arr[right]);
		//arrOut(arr);
		//cout << arr[left] << " " << arr[right] << endl;
		return;
	}
	int middle = left + (right - left) / 2;
	if(left != right){ // have to split
		mergeSort(arr, left, middle);
		mergeSort(arr, middle+1, right);
	}
	else return; //single block array
	//now we merge
	vector<int> tmp1;
	vector<int> tmp2;
	for(int i = left; i <= middle; i++) tmp1.push_back(arr[i]); //copying into temporary arrays
	for(int i = middle+1; i <= right; i++) tmp2.push_back(arr[i]);
	int ind1 = 0, ind2 = 0;
	for(int i = left; i <= right; i++){
		if(ind1 > tmp1.size()-1){ // first array all done
			arr[i] = tmp2[ind2];
			ind2++;
		}
		else if(ind2 > tmp2.size()-1){ // second array all done
			arr[i] = tmp1[ind1];
			ind1++;
		}
		else{
			if(tmp1[ind1] < tmp2[ind2]){
				arr[i] = tmp1[ind1];
				ind1++;
			}
			else{
				arr[i] = tmp2[ind2];
				ind2++;
			} 
		}
	}

}



int main() {
	srand(time(0));

	int n;
	cin >> n;

	vector<int> arr(n);
	randomizeArray(arr);
	//arrOut(arr);

	auto start = std::chrono::steady_clock::now();

	//bubbleSort(arr);
	//shellSort(arr);
	mergeSort(arr);

	auto end = std::chrono::steady_clock::now();
	auto elapsedMilliseconds = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

	//arrOut(arr);
	cout << "in " << elapsedMilliseconds << "ms" << endl;

	return 0;
}