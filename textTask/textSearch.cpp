//i guess i got the idea of the algorithm... thx to https://habr.com/ru/post/307220/
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

vector<int> prefixFunc(string s){
	int n = s.length();
	vector<int> prefixSuffixs(n); //storing length of equal prefix and suffix, not entirely equal
	prefixSuffixs[0] = 0;
	for(int i = 1; i < n; ++i){
		int j = prefixSuffixs[i-1]; //previous pref-suf
		while((j > 0) && (s[i] != s[j])){ //we can't enlarge this one
			j = prefixSuffixs[j-1];  //previous to previous by the order of the pref-suf array
		}
		if(s[i] == s[j]) ++j; //we enlarge the one that we found
		prefixSuffixs[i] = j;
	}
	return prefixSuffixs;
}

int findSubStr(string text, string searched){
	string tmp = searched + "@" + text; //need a symbol that is not in any of the strings
	vector<int> prefSuf = prefixFunc(tmp);
	int n = tmp.length();
	int foundSize = searched.length();
	for(int i = foundSize + 1; i < n; i++){ //we skip searched and @
		if(prefSuf[i] == foundSize){ //ladies n gentlemen       we got em
			//we found the last symbol
			return (i - (foundSize - 1) - foundSize - 1); //i is last (-(foundSize - 1) we find the first index, then we subtract searched.length and 1 for the special symbol)
		}
	}
	return -1;
}

int howMuchInText(string text, string searched){
	string tmp = searched + "@" + text; //need a symbol that is not in any of the strings
	vector<int> prefSuf = prefixFunc(tmp);
	int n = tmp.length();
	int foundSize = searched.length();
	int sum = 0;
	for(int i = foundSize + 1; i < n; i++){ //we skip searched and @
		if(prefSuf[i] == foundSize){ //ladies n gentlemen       we got em
			//we found the last symbol
			++sum; //i is last (-(foundSize - 1) we find the first index, then we subtract searched.length and 1 for the special symbol)
		}
	}
	return sum;
}

int main(){
	cout << "about medical center" <<endl;
	string text, patient;
	getline(cin, text);
	getline(cin, patient);
	cout << howMuchInText(text, patient) << endl;

	// cout << findSubStr(text, word);
	cout << "about html" << endl;
	getline(cin, text);
	int n = text.length();
	int k = 0; //number of #
	regex colorPattern = regex("#([0-9a-fA-F]{6}[^[:alnum:]])|#([0-9a-fA-F]{3}[^[:alnum:]])"); //whanted to do space or ; but end of line breaks everything ($ does nothing)
	for(int i = 0; i < n; ++i) if(text[i] == '#') ++k;
	smatch m;
	text += " "; //yeeeaaasss  a crutch (eol breaking the pattern, i've no idea)
	while(regex_search(text, m, colorPattern)){
		//cout << m[0] << endl;
		--k; // we found a good one
		text = m.suffix();
	}
	cout << "bad colors " << k << endl; //we print those with # but not being a good color 
	return 0;
}