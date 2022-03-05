#include <iostream>
#include <string>

using namespace std;

string decode(string coded_line)
{
	string result = "";
	int k = 0;
	for(int i = 0; i < coded_line.length(); i++)
	{
		if(coded_line[i] == '(')
		{
			string num = "";
			i++;
			while(coded_line[i] != ')')
			{
				num += coded_line[i];
				i++;
			}
			k = stoi(num);
			//currently we are on the ')' symbol, on the next loop it will see the letter
		}
		else
		{
			for(k; k > 0; k--)
			{
				result += coded_line[i];
			}
			if(k < 0)
			{
				result += coded_line[i];
			}
		}
	}
	return result;
}

int main()
{
	string input;
	cout << "insert the string" << endl;
	cin >> input;
	string answer = "";
	string difSymbols = "";
	int k = 1;
	int ind2 = 0;
	for(ind2 = 1; ind2 < input.size(); ind2++)
	{
		if(input[ind2] == input[ind2 - 1])
		{
			if(k == 1 || k == -1)
			{
				k = 2;
			}
			else if(k > 0)
			{
				k++;
			}
			else
			{
				k++; //k < 0 => abs will be lowered
				difSymbols.pop_back(); //remove last character
				answer += "(" + to_string(k) + ")" + difSymbols;
				k = 2;
				difSymbols = "";
			}
		}
		else
		{
			if(k == 1 || k == -1)
			{
				k = -2;
				difSymbols = "";
				difSymbols += input[ind2 - 1];
				difSymbols += input[ind2];
			}
			else if(k < 0)
			{
				k--;
				difSymbols += input[ind2];
			}
			else
			{
				answer += "(" + to_string(k) + ")" + input[ind2 - 1];
				k = 1;
			}
		}
	}
	if(difSymbols.size() == 0)
	{
		answer += "(" + to_string(k) + ")" + input[input.length() - 1];
	}
	else
	{
		answer += "(" + to_string(k) + ")" + difSymbols;
	}
	cout << answer << "    new length / old length = " << (double)answer.length() / (double)input.length() << endl;
	cout << decode(answer) << endl;
	return 0;
}