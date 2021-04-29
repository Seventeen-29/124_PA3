#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <climits>
#include <time.h>
#include <chrono>
#include <stdlib.h> 

using namespace std;

int main(int argc, char* argv[]) {

	//INPUT NUMBERS TO BE PARTITIONED
	vector<int> A = { 100, 52, 13, 27, 62, 19, 5 };

	int b = 0;
	for (int elt : A) {
		b += elt;
	}
	int n = A.size();

	vector<vector<bool>> X(2 * b + 1, vector<bool>(n, false));
	vector<vector<int>> Y(2 * b + 1, vector<int>(n, 0));

	X[-A[0] + b][0] = true;
	X[A[0] + b][0] = true;
	Y[-A[0] + b][0] = -1;
	Y[A[0] + b][0] = 1;

	for (int j = 1; j < n; j++) {
		for (int i = 0; i < 2 * b + 1; i++) {
			int r1 = i - A[j];
			int r2 = i + A[j];
			bool val1 = false;
			bool val2 = false;
			if (0 <= r1 && r1 < 2 * b + 1) {
				val1 = X[r1][j - 1];
			}
			if (0 <= r2 && r2 < 2 * b + 1) {
				val2 = X[r2][j - 1];
			}

			X[i][j] = val1 || val2;

			if (!X[i][j]) {
				Y[i][j] = NULL;
			}
			else {
				if (val1) {
					Y[i][j] = 1;
				}
				else {
					Y[i][j] = -1;
				}
			}
		}

	}

	int finalRes = 0;
	if (X[b][n - 1]) {
		finalRes = 0;
	}
	else {
		for (int m = 1; m <= b; m++) {
			if (X[b - m][n - 1] || X[b + m][n - 1]) {
				finalRes = m;
				break;
			}
		}
	}

	vector<int> signs(n, 0);

	int index = n - 1;
	int res = finalRes + b;
	while (index >= 0) {
		signs[index] = Y[res][index];
		res = res - signs[index] * A[index];
		index = index - 1;
	}

	cout << "input: ";
	for (int i = 0; i < A.size(); i++) {
		cout << " " << A[i] << " ";
	}
	cout << endl << "signs: ";
	for (int i = 0; i < signs.size(); i++) {
		cout << " " << signs[i] << " ";
	}
	cout << endl;
	int calculatedResidue = 0;
	for (int i = 0; i < n; i++) {
		calculatedResidue += signs[i] * A[i];
	}
	if (abs(calculatedResidue) != finalRes) {
		cout << "Something's wrong!" << endl;
		exit(1);
	}
	else {
		cout << "residue: " << finalRes << endl;
	}
}