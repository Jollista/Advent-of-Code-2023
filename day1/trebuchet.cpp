#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//reverse a string
string reverse(string str)
{
	string toReturn = "";

	for (int i = str.length()-1; i >= 0; i--)
	{
		toReturn += str[i];
	}

	return toReturn;
}

//convert a character to a single digit positive integer
//if character is not a number, returns -1
int getNum(char c)
{
	if (c >= '0' && c <= '9')
	{
		return c - '0';
	}
	return -1;
}

//get the first digit in a string
int firstDigit(string line)
{
	int num = -1;
	for (int i = 0; i < line.length(); i++)
	{
		num = getNum(line[i]);
		if (num != -1)
			return num;
	}
	return 0;
}

int lastDigit(string line)
{
	return firstDigit(reverse(line));
}

/**
 * Gets first and last digits in a given string as a single two-digit number 
*/
int getCalibrationValue(string line)
{
	return firstDigit(line) * 10 + lastDigit(line);
}

string replace(string line, string target, string replacement)
{
	//while there's more instances of target in line
	int found = line.find(target);
	if (found != -1)
	{
		line.replace(found, 1, replacement);
	}

	return line;
}

/**
 * returns equivalent digit to a written number
*/
string digit(string number)
{
	if (number.compare("one") == 0)
		return "1";
	if (number.compare("two") == 0)
		return "2";
	if (number.compare("three") == 0)
		return "3";
	if (number.compare("four") == 0)
		return "4";
	if (number.compare("five") == 0)
		return "5";
	if (number.compare("six") == 0)
		return "6";
	if (number.compare("seven") == 0)
		return "7";
	if (number.compare("eight") == 0)
		return "8";
	if (number.compare("nine") == 0)
		return "9";
	
}

/**
 * Returns the index of the smallest value in the array
*/
int minimum(int arr[], int size)
{
	int smallest = arr[0];
	int index = 0;

	for (int i = 1; i < size; i++)
	{
		if (arr[i] < smallest)
		{
			smallest = arr[i];
			index = i;
		}
	}

	return index;
}

/**
 * returns the earliest written number substring in a given line
*/
string earliestNum(string line)
{
	string num = "";
	int positions[9];
	string numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	
	//get first positions of each text number
	for (int i = 0; i < sizeof(positions)/sizeof(int); i++)
	{
		positions[i] = line.find(numbers[i]);
		if (positions[i] < 0)
			positions[i] = line.length()+1;
	}

	//get index of earliest num
	int minIndex = minimum(positions, sizeof(positions)/sizeof(int));

	//if minIndex is invalid, no more text numbers to replace, return ""
	if (positions[minIndex] >= line.length()+1)
		return "";
	
	//else, return text number at minIndex
	return numbers[minIndex];
}

/**
 * Replace instances of spelled out numbers (e.g. "one", "nine", etc.)
 * with their digit
*/
string enumerate(string line)
{
	//while there's still more written numbers
	string num = earliestNum(line);
	while (num.compare("") != 0)
	{
		line = replace(line, num, digit(num));
		num = earliestNum(line);
	}
	return line;
}

int main()
{
	//variables for reading input
	ifstream inputFile("input.txt");
	string line;

	//sum total of calibration values
	int sum = 0;

	cout << "Hello world | " + reverse("Hello world") << endl;

	if (inputFile.is_open())
	{
		//while more data
		while (inputFile.peek() != EOF)
		{
			//get line
			getline(inputFile, line);
			cout << line << " -> " << enumerate(line) << " | " << firstDigit(enumerate(line)) << lastDigit(enumerate(line)) << endl;
			sum += getCalibrationValue(enumerate(line));
		}

		cout << "Sum = " << sum << endl;
	}
}