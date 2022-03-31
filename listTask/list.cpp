#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class List
{
private:
	int data;
	List* next;
public:
	List(List* nextObj = nullptr, int data = 0){
		this->data = data;
		next = nextObj;
	}

	~List(){ if(next) delete next; }

	void setData(int data){
		this->data = data;
	}
	int getData(){
		return data;
	}
	int operator[](int i){
		if(i < 0) throw out_of_range("out of range");
		List* zeroObj = this;
		while(i > 0){
			if(zeroObj->next){
				i--;
				zeroObj = zeroObj->next;
			}
			else throw out_of_range("out of range");
		}
		return (zeroObj->data);
	}
	void setNext(List* next){
		if(this->next) delete (this->next);
		this->next = next;
	}
	List* getNext(){
		return next;
	}

	List* addFront(List* newObj = new List(nullptr, 0)){
		if(newObj->next) delete newObj->next; //lazy variant
		newObj->next = this;
		return newObj;
	}
	List* addFront(int data = 0, List* newObj = new List(nullptr, 0)){ //don't know how to make without returning List*
		newObj->data = data;
		newObj->next = this;
		return newObj;
	}

	void add(List* newObj = new List(nullptr, 0)){
		List* tmp = this;
		while(tmp->next) tmp = tmp->next;
		tmp->next = newObj;
	}
	void add(int data = 0, List* newObj = new List(nullptr, 0)){
		List* tmp = this;
		while(tmp->next) tmp = tmp->next;
		newObj->data = data;
		tmp->next = newObj;
	}

	void print(){
		cout << this->data << endl;
		List* tmp = this;
		if(tmp->next) tmp->next->print();
	}

	void splitByX(int x, vector<int>& lessX, vector<int>& moreX){
		List* tmp = this;
		lessX.clear();
		moreX.clear();
		if(tmp->data <= x) lessX.push_back(tmp->data);
		else moreX.push_back(tmp->data);
		while(tmp->next){
			tmp = tmp->next;
			if(tmp->data <= x) lessX.push_back(tmp->data);
			else moreX.push_back(tmp->data);
		}
		lessX.shrink_to_fit();
		moreX.shrink_to_fit();
	}

	int find(int x){
		int i = 0;
		List* tmp = this;
		if(tmp->data == x) return i;
		while(tmp->next){
			tmp = tmp->next;
			if(tmp->data == x) return i;
		}
		return -1;
	}

	void killClones(){ // O(n^2)
		List* iptr = this;
		if(iptr->next){
			List* preJptr = iptr;
			List* jptr;
			while(preJptr->next){
				jptr = preJptr->next;
				if(jptr->data == iptr->data){

					if(jptr->next) preJptr->next = jptr->next; //deleting a list member
					else preJptr->next = nullptr;
					jptr->next = nullptr;
					delete jptr;
				}
				else{
					preJptr = jptr;
				}
			}
		}
		while(iptr->next){
			iptr = iptr->next;
			List* preJptr = iptr;
			List* jptr;
			while(preJptr->next){
				jptr = preJptr->next;
				if(jptr->data == iptr->data){
					if(jptr->next) preJptr->next = jptr->next; //deleting a list member
					else preJptr->next = nullptr;
					jptr->next = nullptr;
					delete jptr;
				}
				else{
					preJptr = jptr;
				}
			}
		}
	}

	int size(){
		int s = 1;
		List* tmp = this;
		while(tmp->next){
			tmp = tmp->next;
			s++;
		}
		return s;
	}

	void killLast(){
		List* tmp = this;
		while(tmp->next){
			tmp = tmp->next;
		}
		delete tmp;
	}
};

List* addFrontSeveral(List* list){
	cout << "insert number of inputs, then the input stuff" << endl;
	int n = 0;
	cin >> n;
	for(int i = 0;i < n; i++){
		int tmp;
		cin >> tmp;
		list = list->addFront(tmp);
	}
	return list;
}

int main(){
	int n = 0;
	cout << "insert n - the number of consecutive inputs, then n times insert number - data for the list member" << endl;
	cin >> n;
	List* list = nullptr;	
	for(int i = 0; i < n; i++){
		int tmp;
		cin >> tmp;
		list = list->addFront(tmp);
	}
	cout << endl;
	list->print();
	cout << endl;
	cout << (*list)[n-1] << endl;
	cout << endl;
	vector<int> lx;
	vector<int> mx;
	cout << "insert x, which will split the list" << endl;
	cin >> n;
	cout << endl;
	list->splitByX(n, lx, mx);
	for(int i = 0; i < lx.size(); i++){
		cout << lx[i] << " ";
	}
	cout << endl;
	for(int i = 0; i < mx.size(); i++){
		cout << mx[i] << " ";
	}
	cout << endl;
	list->killClones();
	cout << endl;
	list->print();
	cout << endl;
	list = addFrontSeveral(list);
	cout << endl;
	list->print();
	delete list;
	return 0;
}