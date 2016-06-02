//Meeshaan Shah
//CPSC 406
//Knuth–Morris–Pratt Algorithm

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

//creates partial match table base on pattern
void partialMatchTable(string p, int pi[])
{
	int m = p.length();
	int q;
	pi[0] = -1;
	
	for (int i = 1; i < m; ++i)
	{
		q = pi[i-1];
		while (q >= 0)
		{
			if (p[q] == p[i-1])
				break;
			else
				q = pi[q];
		}
		pi[i] = q + 1;
	}
	
	//print partial match table
	cout << "PMT: ";
	for (int i = 0; i < m; ++i)
	{
		cout << pi[i] <<  " ";
	}
	cout << endl;
}

//runs KMP algorithm pattern p on target t, returns a boolean if or not in target
bool KMP(string p, string t)
{
	int n = t.length();
	int m = p.length();
	int pi[m];
	
	partialMatchTable(p, pi);
	
	int i = 0;
	int q = 0;
	
	while (i < n)
	{
		if (q == -1)
		{
			++i;
			q = 0;
		}
		else if (t[i] == p[q])
		{
			++i;
			++q;
			if (q == m)
				return true;
		}
		else
			q = pi[q];
	}
	return false;
}

int main(int argc, char *argv[])
{
	//shows how program needs to run if command line entry was wrong
	if (argc != 2)
	{
		cout << "usage: "<< argv[0] << "</../nameOfText.txt>" << endl;
	}
	//actual program
	else
	{		
		string fileName = argv[1];
		ifstream file(fileName);
		
		string line;
		char answer;
		int lineCount = 0;
		int start;
		int end;
		string target = "";
		string pattern;
		
		//check if did not open
		if (!file.is_open())
		{
     		cout<< "Could not open file" << endl;
		}
		else
		{
			//read target from file
			while (!file.eof())
			{
				getline(file, line);
				target += line;
				++lineCount;
				cout << lineCount << endl;
			}
			file.close();
			
			//kmp continue to ask until user says no
			cout << "Run kmp on target? (y/n) "; cin >> answer;
			cin.ignore();
			while (answer == 'y' || answer == 'Y')
			{
				cout << "Enter pattern:" << endl;
				getline(cin, pattern);
				
				//start clock
				start = clock();
				
				//KMP
				if (KMP(pattern, target))
					cout << "Match" << endl;
				else
					cout << "No match" << endl;
				
				//stop clock	
				end = clock();
				
				//prints clock test
				cout <<  "Clock Test: " << ((float)end - start)/CLOCKS_PER_SEC << " seconds" << endl;
				cout << "---------------------------------" << endl;
				cout << "Run again? (y/n) "; cin >> answer;
				cin.ignore();
			}
		}
	}	
	return 0;
}