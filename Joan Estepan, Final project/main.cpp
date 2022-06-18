#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <stdexcept>
#include <limits>
#include<fstream>
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
	char* procname = new char[pName.length() + 1];
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
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
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
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
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
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
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

//display multiple characters function from project one. most useful function i've had so far
string nCharString(size_t n, char c) {
	string deco;
	deco = string(n, c); //assign variable with string. c will be output by n number of times
	return deco; //return deco string 
}

//create function to print menu
void printMenu() {
	cout << nCharString(56, '*') <<endl;    //display decoration
	cout << nCharString(15, '*') <<  " Grocery Tracking Program " << nCharString(15, '*') << endl;
	cout << " 1. Count All Items" << endl;
	cout << " 2. Count Single Item" << endl;
	cout << " 3. Create Items Frequency Diagram File" << endl;
	cout << " 4. Exit" << endl;
	cout << " Enter Your Selection as a Number 1, 2, 3, or 4." << endl;
	cout << endl;
	cout << nCharString(55, '*') << endl;
}

//bool function to validate input  
bool validateString(const string& s)
{
	//returns true when the input is not a number
	for (const char c : s) {
		if (!isalpha(c) && !isspace(c))
			return false;
	}

	return true;
}

//function to validate integer input
bool validateInt(int number) {
	if (number < 0 || number > 4) {
		return true;
	}
	return false;
}
//create histogram function to display frequency of word
void histogram() {
		//ifstream file to read through the file
		ifstream file;
		//open file 
		file.open("frequency.dat");
		if (!file.is_open()) return; //check that the file is not already open

		//declare variable for the item and for the number of times it appears
		int number;
		string word;

		//loop through file
		while (file >> word)
		{
			//first prints item
			cout << " * " << word<<" ";
			if (file >> word)
			{	//converts the string number to an int so we can run our function
				int num = stoi(word);
				cout <<  nCharString(num, '*') << '\n';
			}
		}
	}



int main()
{
	//declare variable for inputs
	string item;
	int input = 0;
	//Loop intil user selects option 4
	while (input != 4) {
		system("Color 7");		
		system("cls");		//clear screen to keep it nice
		printMenu();

		//get input for switch case selection
		cin >> input;

		//INput validation
		while (cin.fail() || validateInt(input))
		{
			system("cls");
			cout << " * Invalid Input! Try again: * \n";
			cout << endl;
			cin.clear();
			cin.ignore();
			//get input again after ignoring and clearing
			printMenu();
			cin >> input;
			continue;
		}


		//clear console to keep it nice
		system("cls");

		//Swich case for options

		switch (input) {
		case 1:
			CallProcedure("countAllWords");
			system("pause");
			break;
		case 2:
			cout << "Please Enter the Item you Would Like to Count. " << endl;
			cin.ignore();		//clear and ignore old inputs
			cin.clear();		
			cin >> item;
			while (!validateString(item)) {			//Call bool function to validate input in while loop
				cout << "Invalid Input! Please Enter an item not a number. " << endl;
				cin.clear();
				cin.ignore();
				cin >> item;			//get input again
			}
			cout << callIntFunc("countSingleWord", item);		//print item and frequency
			cout << " Times" << endl;
			system("pause");
			break;
		case 3:
			cout << "Creating New File frequency.dat... " << endl;
			CallProcedure("createFile");
			cout << "Success! " << endl;
			cout << endl;
			histogram();				//display histogram
			system("pause");
			break;
		case 4:
			cout << "Exiting Program... " << endl;
			exit(0);		//exit


		}
	}

		return 0;
	
}