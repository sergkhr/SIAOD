#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <list>

using namespace std;

class Product{
	private:
		int id_;
		string name_;
		string name2_; // really two names in the task
		string units_;
		int price_;
	public:
		Product(int id = -1, string name = "name", string name2 = "name2", string units = "cu", int price = 10) : id_(id), name_(name), name2_(name2), units_(units), price_(price){};
		
		int getId() const { return id_; }
		void setId(int id) { id_ = id; }
		string getName() const { return name_; }
		void setName(string name) { name_ = name;}
		string getName2() const { return name2_;}
		void setName2(string name2) { name2_ = name2;}
		string getUnits() const { return units_;}
		void setUnits(string units) { units_ = units;}
		int getPrice() const { return price_; }
		void setPrice(int price) { price_ = price;}
};

class HashTable{
	private:
		int size_; // size of the hash table also we'll devide by that number
		vector<list<vector<int>>> table_; //we're storing indexes of original array here  int[0] - is id; int[1] is index
	public:
		int size() const { return size_; }
		HashTable(const vector<Product>& arr, int size = 1000){
			size_ = size;
			list<vector<int>> temp = {}; //this helped... for some reason
			for(int i = 0; i < size_; i++) table_.push_back(temp); //table_.push_back(list<vector<int>()>()); did a ton of errors
			for(int i = 0; i < arr.size(); i++){
				vector<int> tmp = {arr[i].getId(), i};
				table_[toHash(arr[i].getId())].push_back(tmp); //we placed index of a certain product into the hash table on the pos determined by toHash function
			}
		}

		int toHash(int id) const {return(id % size_);}

		int findIndex(int id) const {
			for(auto it = table_[toHash(id)].begin(); it != table_[toHash(id)].end(); ++it){ //linear search inside blocks of same hash value
				if((*it)[0] == id) return (*it)[1];
			}
			return -1;
		}
};

void randomizeArray(vector<Product>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		int id = rand() % 1000 + (rand() % 1000 * 1000);
		arr[i] = Product(id, "name" + to_string(id));
	}
}

int main(){
	srand(time(0));
	int n;
	cin >> n;
	vector<Product> arr(n);
	randomizeArray(arr);
	for(int i = 0; i < arr.size(); i++) cout << arr[i].getId() << " " << arr[i].getName() << endl;
	HashTable ht(arr);
	cin >> n; //insert the id of searched
	int index = ht.findIndex(n);
	if(index != -1) cout << arr[ht.findIndex(n)].getName() << endl;
	else cout << "not found" << endl;
	

	return 0;
}