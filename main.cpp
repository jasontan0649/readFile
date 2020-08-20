#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include <sstream>
using namespace std;

//common function
bool isNum(string s);

//print vector function for ease of debug
void printV(vector<double>);
void printV(vector<string>);

//load file
void loadFile(vector<string>&, vector<vector<double>>&, int&, int&);
string getFileName();
bool getColTitleRow(ifstream&, int&, vector<string>&, int&);
bool getTitleRow(ifstream&, vector<string>&);
bool getData(ifstream&, vector<vector<double>>&);
bool isColRowMatch(vector<vector<double>>, int, int);

//transpose vector
void transposeV(vector<vector<double>>, vector<vector<double>>&);


int main() {
	vector<string> title;
	vector<vector<double>> data;
	int col = 0, row = 0;

	loadFile(title, data, col, row);

	vector<vector<double>> dataTp;

	transposeV(data, dataTp);

	//debug see output
	for (auto item : dataTp) {
		printV(item);
		cout << endl;
	}


}
//load file

bool isNum(string s) {
	for (char c : s)
		if (!isdigit(c) && c != '.') //check if a char is num or dot
			return false;

	return true; //check completed
}

void loadFile(vector<string>& title, vector<vector<double>>& data, int& col, int& row) {
	while (1) {
		string file; ifstream f;
		data.clear(); // vector clear prior run to clean old data
		title.clear(); // vector clear prior run to clean old data
		file = getFileName(); //debug purpose
		f.open(file);

		if (!f) { //check file exist && can open
			cout << file << " not found\nPlease try again" << endl;
			continue;
		}

		if (!getColTitleRow(f, col, title, row))//get column,title,row from file,check format
			continue;

		if (!getData(f, data)) //get data from file, check format
			continue;

		if (!isColRowMatch(data, col, row))//check format
			continue;

		break;
	}
}

string getFileName() {
	string file;
	cout << "Please enter a CSV file name: ";
	cin >> file;
	return file + ".csv";
}

bool getColTitleRow(ifstream& f, int& col, vector<string>& title, int& row) {
	if (!(f >> col)) { //check column value, false if 0 or not int
		cout << "Unsupported format/Empty data\nPlease try again" << endl;
		return false;
	}

	if (!getTitleRow(f, title) || title.size() != col) { //get title from 
		cout << "Columns do not match\nPlease try again" << endl;
		return false;
	}

	if (!(f >> row)) { //check row value, false if 0 or not int
		cout << "Empty data\nPlease try again" << endl;
		return false;
	}

	return true;
}

bool getTitleRow(ifstream& f, vector<string>& title) {
	string line;
	f >> line;

	if (line.empty()) //empty data
		return false;

	//retrieve value by string streaming
	string val;
	istringstream titleStream(line + ",");
	while (getline(titleStream, val, ',')) {
		title.push_back(val);
	}

	return true;
}

bool getData(ifstream& f, vector<vector<double>>& data) {
	string line, val;

	while (f >> line) {
		istringstream  lineStream(line + ",");
		data.emplace_back(); //append new vector if line not end
		while (getline(lineStream, val, ',')) {
			if (!isNum(val)) {
				cout << "Data contain non numeric value.\nPlease try again" << endl;
				return false;
			}
			data.back().push_back(stoi(val)); //append data 
		}
	}

	return true; //append successful
}

bool isColRowMatch(vector<vector<double>> data, int col, int row) {
	if (row != data.size()) {
		cout << "Data row does not match with given input\nPlease try again" << endl;
		return false;
	}

	for (auto item : data)
		if (item.size() != col) {
			cout << "Data column does not match with given input\nPlease try again" << endl;
			return false;
		}

	return true;
}

//print vector
void printV(vector<double> arr) {
	cout << "[ ";
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << "]";
}

void printV(vector<string> arr) {
	cout << "[ ";
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << "]";
}


//tranpose vector
void transposeV(vector<vector<double>> vect, vector<vector<double>>& res) {
	const int row = vect.size();
	const int col = vect[0].size();

	res.resize(col, vector<double>(row));

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			res[j][i] = vect[i][j];
		}
	}
}