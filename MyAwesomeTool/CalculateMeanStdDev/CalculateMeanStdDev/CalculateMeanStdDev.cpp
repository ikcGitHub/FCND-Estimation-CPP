// CalculateMeanStdDev.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <numeric>

using namespace std;

tuple<vector<float>, vector<float>, int> read_csv_data(string fpath);
tuple<float, float> calculateMeanStdDev(vector<float> data);

int main()
{
	//cout << "Hello World" << endl;
	
	// Initialize data file paths
	vector<string> fpath;
	fpath.push_back("../../../config/log/Graph1.txt");
	fpath.push_back("../../../config/log/Graph2.txt");
	
	for (int i = 0; i < fpath.size(); i++) {
		// Initialize value
		vector<float> time, X;
		int size_vec;

		// Read the data from CSV
		tie(time, X, size_vec) = read_csv_data(fpath[i]);

		// Initialize value
		float X_Mean = 0;
		float X_StdDev = 0;

		// Calculate the mean and standard deviation
		tie(X_Mean, X_StdDev) = calculateMeanStdDev(X);
		cout << "Current file path is:" << fpath[i] << endl;
		cout << "Mean is:" << X_Mean << endl;
		cout << "Standard Deviation is:" << X_StdDev << endl;
	}

	

    return 0;
}

tuple<vector<float>, vector<float>, int> read_csv_data(string fpath) {
	//cout << "read_csv_data" << endl;

	ifstream file (fpath);
	// Check file existence
	if (!file.good()) {
		cout << "ERROR: File does not exist" << endl;		
	}
	
	// Checke if file is opened
	if (!file.is_open()) {
		cout << "ERROR: File Open" << '\n';
	}

	// Initialize parameter
	string str_t, str_x;
	vector<float> t, x;
	int size_vec = 0;
	
	// Read first row then throw it away
	getline(file, str_x, '\n');

	// Read data
	while (!file.eof()) {
		// Read time
		getline(file, str_t, ',');
		t.push_back(stof(str_t));
		//cout << t[size_vec] << endl;
		// Read x data
		getline(file, str_x, '\n');
		x.push_back(stof(str_x));
		//cout << x[size_vec] << endl;
		// Count up
		size_vec++;
		//cout << size_vec << endl;
		// TODO: Need to handle if the last line is empty
	}

	// Close file
	file.close();

	return make_tuple(t, x, size_vec);
}

tuple<float, float> calculateMeanStdDev(vector<float> data) {
	//cout << "calculateMeanStdDev" << endl;
	
	// Initialize
	float sum = 0.0, mean = 0.0, var = 0.0, std_dev = 0.0;
	float size = data.size();
	float sum1 = 0.0;

	// Calculate sum, average, standard deviation
	sum = accumulate(data.begin(), data.end(), 0.0);
	/*cout << "sum is" << sum << endl;
	for (int n = 0; n < size; n++) {
		sum1 += data[n];
	}
	cout << "sum1 is" << sum1 << endl;*/
	mean = sum / size;
	
	for (int i = 0; i < size; i++) {
		var += pow(data[i] - mean, 2);
	}

	std_dev = sqrt(var / size);

	return make_tuple(mean, std_dev);
}