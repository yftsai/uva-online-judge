#include <iostream>
using namespace std;

int main()
{
	int num, den, table[1000], nch, i, j;

	for (; (cin >> num >> den) && !(num==0 && den==0); ){
		cout << ".";
		for (i=0, nch=1; num>0; i++, nch++){
			num*=10;
			// record
			table[i]=num;
			// search for the pattern
			for (j=0; j<i && table[j]!=table[i]; j++)
				;
			
			if (j<i)
				break;		// find the pattern
			else {
				if (nch%50==0)
					cout << endl;
				cout << num/den;
				num%=den;
			}
		}
		cout << endl;
		
		if (num==0)
			cout << "This expansion terminates." << endl;
		else
			cout << "The last " << i-j << " digits repeat forever." << endl;
		cout << endl;
	}

	return 0;
}
