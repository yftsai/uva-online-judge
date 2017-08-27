// #trivial
#include <iostream>
using namespace std;

int main()
{
	int case_count;
	for (cin >> case_count; case_count > 0; case_count--){
	    int rectangles[2][4];
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
				cin >> rectangles[i][j];

        rectangles[0][0] = max(rectangles[0][0], rectangles[1][0]);
        rectangles[0][1] = max(rectangles[0][1], rectangles[1][1]);
        rectangles[0][2] = min(rectangles[0][2], rectangles[1][2]);
        rectangles[0][3] = min(rectangles[0][3], rectangles[1][3]);

		if (rectangles[0][0] < rectangles[0][2] && rectangles[0][1] < rectangles[0][3])
            cout << rectangles[0][0] << " " << rectangles[0][1] << " " << rectangles[0][2] << " " << rectangles[0][3] << endl;
		else
			cout << "No Overlap" << endl;
        if (case_count > 1)
		    cout << endl;
	}
	return 0;
}
