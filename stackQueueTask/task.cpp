#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
	vector<int> stack;
	//stack.push_back(1); these are for a vector to be a stack
	//stack.back();
	//stack.pop_back();
	string s;
	cin >> s;
	//postfinx form numbers are only one character long
	for(int i = 0; i < s.size(); i++){
		if(s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/'){ //it's a number
			//cout << int(s[i]) << endl;
			stack.push_back(int(s[i])-48);
		}
		else{ //it's an action
			if(stack.size() >= 2){ // we have what to work with
				int tmp1 = stack.back();
				stack.pop_back();
				int tmp2 = stack.back();
				stack.pop_back();
				switch(s[i]){
					case '+':
						stack.push_back(tmp2 + tmp1);
						break;
					case '-':
						stack.push_back(tmp2 - tmp1);
						break;
					case '*':
						stack.push_back(tmp2 * tmp1);
						break;
					case '/':
						stack.push_back(tmp2 / tmp1); //cd/ = c / d
						break;
				}
			}
			else{
				cout << "you have problems in postfix form" << endl;
				break;
			}
		}
	}

	if(stack.size() == 1) cout << stack.back() << endl;
	else cout << "you have problems in postfix form, not enough actions";

	//couple of tests
	// ab+cd-* = (a+b)*(c-d)
	// abc+d/* = a*((b+c)/d)
	// ab-c*d- = (a-b)*c-d

	return 0;
}