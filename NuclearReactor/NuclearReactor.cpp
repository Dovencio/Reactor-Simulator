// NuclearReactor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "NuclearReactor.h"

using namespace std;

int main()
{
	_mkdir("saves");
	srand(clock());
	system("title Decay simulator");
	displayElementDecayChances(Elements, EleLeng);
	collectElementN(Elements, EleLeng);
	cout << "Update screen every ms?:";
	cin >> SUpdate;
	system("CLS");
	intOutputData(Elements, EleLeng);
	LINT NumOfTests = 0;
	start = NOW;
	thread d(outputData);
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
					//PlaySound(TEXT("click.wav"), NULL, SND_FILENAME);
				}
			}
		}
		if (recording)
		{
			fstream rec("saves/rec.srec", fstream::out|fstream::app);
			rec << tries << '\t' << particles.convert_to<BF50>() / BF50(tries) * BF50(60) << '\t';
			for (short i = 0; i < EleLeng; i++)
			{
				rec << Elements[i].n;
				if (!(i == EleLeng - 1))
				{
					rec << '\t';
				}
			}
			rec << endl;
			rec.close();
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
	return 0;
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

