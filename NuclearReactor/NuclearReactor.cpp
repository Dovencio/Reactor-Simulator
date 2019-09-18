// NuclearReactor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "NuclearReactor.h"

using namespace std;

int main()
{
	srand(clock());
	system("title Decay simulator");
	short longboi = 21;
	const LINT mol("6022140761000000000000000");
	unsigned long long tries = 0;
	LINT NumOfTests = 0;
	cout << "How many grams of U238?: ";
	string GU238;
	cin >> GU238;
	cout << "How many grams of U235?: ";
	string GU235;
	cin >> GU235;
	cout << "Update screen every ms?:";
	string SUpdate;
	cin >> SUpdate;
	Elements[0].n = (BF50(GU238) / BF50(238) * BF50(mol)).convert_to<LINT>();
	Elements[16].n = (BF50(GU235) / BF50(235) * BF50(mol)).convert_to<LINT>();
	system("CLS");
	LINT particles = 0;
	intOutputData(Elements, *(&Elements + 1) - Elements);
	while (Elements[0].n > 0)
	{
		for (short i = 0; i < *(&Elements + 1) - Elements; i++)
		{
			Elements[i].ns = 0;
		}
		GETTP(start)
		tries++;
		LINT n = getMostAtoms();
		for (LINT i = 0; i < n; i++)
		{
			for (short i = 0; i < *(&Elements + 1) - Elements; i++)
			{
				if (Elements[i].testDecay(Elements))
				{
					particles++;
				}
			}
			GETTP(stop)
			GETUS(t, stop, start)
			LINT tc = t.count();
			if ((tc % stoi(SUpdate) == 0) || Elements[0].n == 0)
			{
				thread dout(outputData, longboi, tries, n, i, particles/tries*60, Elements, *(&Elements + 1) - Elements, start);
				if (Elements[1].n > 0)
					dout.detach();
				else
					dout.join();
			}
		}
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

