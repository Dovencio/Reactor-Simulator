// NuclearReactor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "NuclearReactor.h"

using namespace std;

int main()
{
	_mkdir("saves");
	srand(clock());
	system("title Decay simulator");
	//displayElementDecayChances(Elements, EleLeng);
	collectElementN(Elements, EleLeng);
	cout << "Update screen every ms?:";
	cin >> SUpdate;
	system("CLS");
	intOutputData(Elements, EleLeng);
	LINT NumOfTests = 0;
	start = NOW;
	thread d(outputData);
	bool Locked = true;
	while (getMostAtoms(false) > LINT(0) && Locked)
	{
		for (short i = 0; i < *(&Elements + 1) - Elements; i++)
		{
			Elements[i].ns = 0;
		}
		start = NOW;
		tries++;
		in = getMostAtoms(false);
		for (ni = 0; ni < in; ni++)
		{
			for (short i = 0; i < *(&Elements + 1) - Elements; i++)
			{
				if (Elements[i].testDecay(Elements))
				{
					particles++;
				}
			}
		}
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			Locked = false;
		}
	}
	finished = true;
	d.join();
	cout << "Would you like to make a save?[y/n]: ";
	string ans;
	cin >> ans;
	if (ans == "y")
	{
		cout << "Name?: ";
		cin >> ans;
		fstream save("saves/" + ans + ".samp", fstream::out);
		save << particles << endl;
		save << tries << endl;
		for (short i = 0; i < EleLeng; i++)
		{
			save << Elements[i].n << endl;
		}
		save.close();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

