#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

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

	~List(){ 
		delete next; 
	}

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
		//List* tmp = this;
		if(next) next->print();
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

	List* killLast(){ //caution delete does not make previous pointers into nullptr
		if(!this) return nullptr;
		if (this->size() == 1) {
			this->data = 0; //inthis variant size cannot go lower than 1
		}
		else if (this->size() == 2) {
			delete this->next;
			this->next = nullptr;
		}
		else {
			List* pretmp = this;
			while (pretmp->next->next) {
				pretmp = pretmp->next; //pretmp will be the obj before last
			}
			delete pretmp->next;
			pretmp->next = nullptr;
		}
		return this;
	}
};


string addBracket(string s,  string *buildStr, int pos = 0) {
	if (s.size() % 2 == 0) { // a(b(cd)e)f
		if (pos != s.size() / 2 - 1) { //not the left central element
			*buildStr = buildStr->substr(0, buildStr->size() / 2) + s[pos] + "(" + ")" + s[s.size() - pos - 1] + buildStr->substr(buildStr->size() / 2);
		}
		else {
			*buildStr = buildStr->substr(0, buildStr->size() / 2) + s[pos] + s[s.size() - pos - 1] + buildStr->substr(buildStr->size() / 2);
			return(*buildStr);
		}
	}
	else { // a(b(c)d)e
		if (pos != s.size() / 2) { //not the central element
			*buildStr = buildStr->substr(0, buildStr->size() / 2) + s[pos] + "(" + ")" + s[s.size() - pos - 1] + buildStr->substr(buildStr->size() / 2);
		}
		else {
			*buildStr = buildStr->substr(0, buildStr->size() / 2) + s[pos] + buildStr->substr(buildStr->size() / 2);
			return(*buildStr);
		}
	}
	pos++;
	return (addBracket(s, buildStr, pos));
}

string strBracket(string s) {
	if (s.size() <= 0) return("");
	string* sptr = new string("");
	string ans = addBracket(s, sptr);
	delete(sptr);
	return(ans);
}

void deleteNLast(List* list, int n) {
	for(int i =0; i < n; i++){
		list = list->killLast();
	}
}

void deleteLast(List* list) {
	List* tmp = list;
	while (tmp->getNext()) tmp = tmp->getNext();
	delete tmp;
}

int main() {
	cout << "insert the string" << endl;
	string s = "";
	cin >> s;
	cout << strBracket(s) << endl;
	
	int n = 0;
	cout << "insert n - the number of consecutive inputs, then n times insert number - data for the list member" << endl;
	cin >> n;
	List* list = nullptr;
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		list = list->addFront(tmp);
	}
	cout << endl;
	cout << "insert d - number of deaths" << endl;
	cin >> n;
	list->print();
	cout << endl;

	//deleteLast(list);
	deleteNLast(list, n);
	//list = list->killLast();
	list->print();
	//delete list;
	cout << endl;
	return 0;
}