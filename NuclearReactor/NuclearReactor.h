#pragma once

#include <iostream>
#include <chrono>
#include <math.h>
#include <thread>
#include <windows.h>
#include <thread>
#include <sstream>
#include <string>
#include <time.h>
#include <mutex>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/mpl/modulus.hpp>
#include "Element.h"

using namespace std;

#define LINT boost::multiprecision::cpp_int
#define STMP chrono::steady_clock::time_point
#define BF50 boost::multiprecision::cpp_dec_float_50
#define GETTP(x) STMP x = chrono::high_resolution_clock::now();
#define NOW chrono::high_resolution_clock::now()
#define GETUS(x, y, z) chrono::milliseconds x = chrono::duration_cast<chrono::milliseconds>( y - z );

mutex ThreadLock;

const LINT mol("6022140761000000000000000");
STMP start;
const short longboi = 21;
LINT particles = 0;
unsigned long long tries = 0;
LINT ni = 0;
LINT in = 0;
bool finished = false;
string SUpdate;

void secToYDHMS(BF50 x, BF50 foo[])
{
	short i = 0;
	for (BF50 denom : {
		BF50("31557600"), BF50("86400"), BF50("3600"),
		BF50("60"), BF50("1")
	})
	{
		BF50 count = x / denom;

		if (count >= 1)
		{
			count = trunc(count);
			foo[i] = count;
			x -= denom * count;
		}
		i++;
	}
}

BF50 toSeconds(float time, string type)
{
	if (type == "y")
	{
		return time * 365.0 * 24.0 * 60.0 * 60.0;
	}
	else if (type == "d")
	{
		return time * 24.0 * 60.0 * 60.0;
	}
	else if (type == "h")
	{
		return time * 60.0 * 60.0;
	}
	else if (type == "m")
	{
		return time * 60.0;
	}
	else
	{
		return time;
	}
}

Element Elements[] = {
	Element::Element(92, 146, "U238", 1, toSeconds(4.47 * pow(10, 9), "y"), false), //0
	Element::Element(90, 144, "TH234", 2, toSeconds(24.1, "d"), false), //1
	Element::Element(90, 145, "TH233", 3, toSeconds(22.33, "m"), false), //2
	Element::Element(90, 144, "TH232", 4, toSeconds(1.405 * pow(10, 10), "y"), false), //3
	Element::Element(88, 142, "RA228", 5, toSeconds(5.74, "y"), false), //4
	Element::Element(88, 141, "RA227", 6, toSeconds(24.17, "m"), false),//5
	Element::Element(88, 140, "RA226", 7, toSeconds(1.6 * pow(10, 3), "y"), false),//6
	Element::Element(86, 138, "RN222", 8, toSeconds(3.8235, "d"), false),//7
	Element::Element(84, 136, "PO218", 9, toSeconds(3.17, "m"), false),//8
	Element::Element(82, 134, "PB214", 10, toSeconds(26.83, "m"), false),//9
	Element::Element(82, 133, "PB213", 11, toSeconds(10.2, "m"), false),//10
	Element::Element(82, 132, "PB212", 12, toSeconds(10.6, "h"), false),//11
	Element::Element(82, 131, "PB211", 13, toSeconds(36.17, "m"), false),//12
	Element::Element(82, 130, "PB210", 14, toSeconds(22.2, "y"), false),//13
	Element::Element(82, 129, "PB209", 15, toSeconds(3.2528, "h"), false),//14
	Element::Element(82, 128, "PB208", 15, 0, true),//15
	Element::Element(92, 143, "U235", 3, pow(10, 9), false)//16
}

const short EleLeng = *(&Elements + 1) - Elements;

void displayElementDecayChances(Element Elements[], short len)
{
	for (short i = 0; i < len; i++)
	{
		cout << Elements[i].elementName << ": " << Elements[i].decayChance << "/" << Elements[i].tDecayChance << endl;
	}
	system("pause");
}

void collectElementN(Element Elements[], short len)
{
	cout << "Grams [1], Mols[2], or Atoms [3]: ";
	string choice;
	cin >> choice;
	switch (stoi(choice))
	{
	case 1:
		for (short i = 0; i < len; i++)
		{
			string d;
			cout << "How many grams of " << Elements[i].elementName << "?: ";
			cin >> d;
			Elements[i].n = (BF50(d) / BF50(Elements[i].Protons + Elements[i].Nutrons) * mol.convert_to<BF50>()).convert_to<LINT>();
		}
		break;
	case 2:
		for (short i = 0; i < len; i++)
		{
			string d;
			cout << "How many Mols of " << Elements[i].elementName << "?: ";
			cin >> d;
			Elements[i].n = (BF50(d) * mol.convert_to<BF50>()).convert_to<LINT>();
		}
		break;
	case 3:
		for (short i = 0; i < len; i++)
		{
			string d;
			cout << "How many atoms of " << Elements[i].elementName << "?: ";
			cin >> d;
			Elements[i].n = LINT(d);
		}
		break;
	default:
		for (short i = 0; i < len; i++)
		{
			string d;
			cout << "How many grams of " << Elements[i].elementName << "?: ";
			cin >> d;
			Elements[i].n = (BF50(d) / BF50(Elements[i].Protons + Elements[i].Nutrons) * mol.convert_to<BF50>()).convert_to<LINT>();
		}
		break;
	}
}

LINT getMostAtoms(bool incS)
{
	LINT r = 0;
	for (short i = 0; i < *(&Elements + 1) - Elements; i++)
	{
		if (Elements[i].decayChance > 0 || incS)
		{
			if (r < Elements[i].n)
			{
				r = Elements[i].n;
			}
		}
	}
	return r;
}

void MoveCursor(int x, int y)
{
	COORD foo;
	foo.X = x;
	foo.Y = y;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, foo);
}

void dataChange(short l, short xStart, int y, string newData)
{
	MoveCursor(xStart, y);
	for (short i = 0; i < l; i++)
	{
		cout << " ";
	}
	MoveCursor(xStart, y);
	cout << newData << endl;
}

void dataChange(short l, short xStart, int y, LINT newData)
{
	MoveCursor(xStart, y);
	for (short i = 0; i < l; i++)
	{
		cout << " ";
	}
	MoveCursor(xStart, y);
	cout << newData << endl;
}

void dataChange(short l, short xStart, int y, long long newData)
{
	MoveCursor(xStart, y);
	for (short i = 0; i < l; i++)
	{
		cout << " ";
	}
	MoveCursor(xStart, y);
	cout << newData << endl;
}

void dataChange(short l, short xStart, int y, float newData)
{
	MoveCursor(xStart, y);
	for (short i = 0; i < l; i++)
	{
		cout << " ";
	}
	MoveCursor(xStart, y);
	cout << newData << endl;
}

void dataChange(short l, short xStart, int y, BF50 newData)
{
	MoveCursor(xStart, y);
	for (short i = 0; i < l; i++)
	{
		cout << " ";
	}
	MoveCursor(xStart, y);
	cout << newData << endl;
}

void intOutputData(Element Elements[], int len)
{
	cout << "Ionizing Radiation:" << endl;
	cout << "Time taken:" << endl;
	cout << "Sim. seconds passed:" << endl;
	cout << "Ops per sec:" << endl;
	cout << "ETA (for this sec):" << endl;
	for (short i = 0; i < len; i++)
	{
		cout << Elements[i].elementName << ":" << endl;
	}
}

void outputData()
{
	while (!finished)
	{
		GETTP(stop)
		GETUS(t, stop, start)
		LINT tc = t.count();
		if (tc % LINT(SUpdate) == 0)
		{
			dataChange(24, longboi, 0, (particles.convert_to<BF50>() / BF50(tries) * BF50(60)).convert_to<LINT>().convert_to<string>() + " CPM");
			BF50 nii[5] = { 0,0,0,0,0 };
			secToYDHMS(tc.convert_to<BF50>() / 1000.0, nii);
			dataChange(45, longboi, 1,
				nii[0].convert_to<string>() + " y " +
				nii[1].convert_to<string>() + " d " +
				nii[2].convert_to<string>() + " h " +
				nii[3].convert_to<string>() + " m " +
				nii[4].convert_to<string>() + " s"
			);

			dataChange(to_string(ULONG_MAX).length(), longboi, 2, to_string(tries));
			BF50 d = ni.convert_to<BF50>() / (tc.convert_to<BF50>() / 1000.0);
			dataChange(11, longboi, 3, d);
			BF50 x = (in - ni).convert_to<BF50>() / d;
			BF50 foo[5] = { 0,0,0,0,0 };
			secToYDHMS(x, foo);
			dataChange(45, longboi, 4,
				foo[0].convert_to<string>() + " y " +
				foo[1].convert_to<string>() + " d " +
				foo[2].convert_to<string>() + " h " +
				foo[3].convert_to<string>() + " m " +
				foo[4].convert_to<string>() + " s " +
				to_string((BF50(ni) / BF50(in) * BF50(100)).convert_to<float>()) + "%"
			);
			for (short i = 0; i < EleLeng; i++)
			{
				dataChange(24, longboi, i + 5, Elements[i].n);
			}

		}
	}
}
