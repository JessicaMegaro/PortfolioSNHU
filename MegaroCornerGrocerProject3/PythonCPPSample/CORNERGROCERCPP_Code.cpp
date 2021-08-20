/* Jessica Megaro
 * 8/13/2021
 * This program will use C++ and python to itemize and count items fed from a text file of the corner grocer.
 * It will display how many items are purchased in one day to increase efficiency of layout of business.
 */

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char *procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();	
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen: 
		You sent me: Test
Return:
	100 is returned to the C++	
*/
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
//Reads integer from user, if no number is entered, continue to prompt.
int getIntFromUser() {
	int input = 0;
	while (!(cin >> input)) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Invalid number." << endl;
	}
	return input;
}

//Prompt user for choice in display menu. 
char getUserChoice() {
	int input = 0;
	cout << string(60, '*') << endl;
	cout << "* " << setw(57) << left << "1: Calculate Item Counts " << "*" << endl;
	cout << "* " << setw(57) << left << "2: Search For Item " << "*" << endl;
	cout << "* " << setw(57) << left << "3: Display Histogram" << "*" << endl;
	cout << "* " << setw(57) << left << "4: Exit Program " << "*" << endl;
	cout << string(60, '*') << endl;
	cout << "Enter your selection as a number 1, 2, 3 or 4." << endl;
	cout << "> ";

	input = getIntFromUser();
	while (input < 1 || input > 4) {
		cout << "Invalid option, please enter 1, 2, 3 or 4." << endl;
		cout << "> ";
		input = getIntFromUser();
	}
	return input;
}
/*Opens frequency.dat fileand reads in the item counts for each word, displays with asterisks or
 *states unable to open file if file is not open.
 */
void displayHistogram(string path) {
	ifstream file(path);

	if (!file.is_open()) {
		cout << "Unable to open file: " << path << endl;
	}
	else {
		string word;
		int count = 0;
		while (!file.eof()) {
			if (file >> word >> count) {
				cout << setw(15) << left << word << ": " << string(count, '*') << endl;
			}
		}
		file.close();
	}
}

/*Function to answer user, case 1 prints item counts from file, case 2 allows user to search with a word
 * to return a count of a specific item, case 3 prints the histogram with asterisks to see the most
 * frequent items and case 4 allows to exit the program.
 */
void main() {
	int choice = 0;
	while ((choice = getUserChoice()) != 4) {
		switch (choice) {
		case 1:
			CallProcedure("PrintCounts");
			break;
		case 2: {
			string word;
			cout << "Enter item: ";
			cin >> word;
			int count = callIntFunc("GetCountForWord", word);
			cout << "Count: " << count << endl;
			break;
		}
		case 3:
			CallProcedure("StoreFrequencyData");
			displayHistogram("frequency.dat");
		}
	}
	cout << "Goodbye." << endl;
}