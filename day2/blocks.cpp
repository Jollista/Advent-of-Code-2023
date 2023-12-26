#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
 * Replaces all instances of target in line with replacement
 * 
 * @returns the updated line
*/
string replaceAll(string line, string target, string replacement)
{
	//while there's more instances of target in line
	int found = line.find(target);
	while (found != -1)
	{
		cout << "line : " << line << endl;
		line = line.replace(found, target.length(), replacement);
		found = line.find(target);
	}

	return line;
}

/**
 * Parse a given block in the form
 * "3r"
 * or
 * "14b"
 * or
 * "102g"
*/
int* parseBlock(string block, int data[])
{
	cout << "parseBlock" << endl;
	//determine color
	int color = 0; //0=blue;1=red;2=green;
	if (block.find("r") != -1)
		color = 1;
	else if (block.find("g") != -1)
		color = 2;
	
	//trim color label and convert to int, assign to proper location in data
	data[color] = stoi(block.substr(block.length()-2, block.length()-1));
	return data;
}

/**
 * Parse a given round in a game in the form
 * "3 blue, 4 red, 6 green"
 * or
 * "2 red"
 * or
 * "9 green, 13 blue"
 * 
 * @returns an array of length 3 containing the
 * 	number of blues,
 * 	number of reds,
 * 	number of greens
*/
int* parseRound(string round)
{
	cout << "parseRound" << endl;
	int data[3];
	int* ptr;
	
	//make round more parseable
	//"3 blue, 4 red, 6 green" -> "3b,4r,6g"
	cout << "replacements" << endl;
	round = replaceAll(round, "blue", "b");
	cout << "replace blue" << endl;
	round = replaceAll(round, "red", "r");
	cout << "replace red" << endl;
	round = replaceAll(round, "green", "g");
	cout << "replace green" << endl;
	round = replaceAll(round, " ", "");
	cout << "replace whitespace" << endl;

	//while more blocks
	while (round.find(",") != -1)
	{
		cout << "round: " << round << endl;
		//parse block and update data
		ptr = parseBlock(round.substr(0, round.find(",")), data);
		for (int i = 0; i < 3; i++)
		{
			data[i] = ptr[i];
		}

		//trim parsed block
		round = round.substr(round.find(",")+1, round.length()-1);
	}

	//parse last block and update data
	ptr = parseBlock(round, data);
	for (int i = 0; i < 3; i++)
	{
		data[i] = ptr[i];
	}
	
	return data;
}

/**
 * Parse a given line in the form
 * "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
 * 
 * @returns an array of length 4, containing the 
 * 	gameid, 
 * 	max number of blue blocks, 
 * 	max number of red blocks, 
 * 	max number of green blocks
*/
int* parseGame(string game)
{
	cout << "parseGame" << endl;
	int data[4];

	//get game's id
	data[0] = stoi(game.substr(5, game.find(":")));

	//get the rest of the game data
	//e.g. "3 blue, 4 red; ..."
	string rounds = game.substr(game.find(": ")+1);
	int* roundData;

	//while there's more rounds
	while(rounds.find(";") != -1)
	{
		//get isolated round
		roundData = parseRound(rounds.substr(0, rounds.find(";")));
		data[1] = max(data[1], roundData[0]); //blue
		data[2] = max(data[2], roundData[1]); //red
		data[3] = max(data[3], roundData[2]); //green

		//trim parsed round
		rounds = rounds.substr(rounds.find("; ")+1, rounds.length()-1);
	}

	//get last round
	roundData = parseRound(rounds);
	data[1] = max(data[1], roundData[0]); //blue
	data[2] = max(data[2], roundData[1]); //red
	data[3] = max(data[3], roundData[2]); //green

	return data;
}

int main()
{
	//array of every game
	int games[100];

	//variables for reading input
	ifstream inputFile("input.txt");
	string line;

	if (inputFile.is_open())
	{
		//while more data
		while (inputFile.peek() != EOF)
		{
			getline(inputFile, line);
			cout << line << endl;
			int* arr = parseGame(line);
			cout << "Game id = " << arr[0] << endl;
			cout << "Max blu = " << arr[1] << endl;
			cout << "Max red = " << arr[2] << endl;
			cout << "Max grn = " << arr[3] << endl;
		}
	}
}