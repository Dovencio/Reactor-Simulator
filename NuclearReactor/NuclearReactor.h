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

mutex ThreadLock;

#define LINT boost::multiprecision::cpp_int
#define STMP chrono::steady_clock::time_point
#define BF50 boost::multiprecision::cpp_dec_float_50
#define GETTP(x) STMP x = chrono::high_resolution_clock::now();
#define GETUS(x, y, z) chrono::milliseconds x = chrono::duration_cast<chrono::milliseconds>( y - z );

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

Element Elements[] = {
	Element::Element(92, 146, "U238", 1, LINT("49"), LINT("10000000000000000000")), //0
	Element::Element(90, 144, "TH234", 2, LINT("33"),  LINT("100000000")), //1
	Element::Element(90, 145, "TH233", 3, LINT("51"), LINT("100000")), //2
	Element::Element(90, 144, "TH232", 4, LINT("15"), LINT("10000000000000000000")), //3
	Element::Element(88, 142, "RA228", 5, LINT("57"), LINT("10000000000")), //4
	Element::Element(88, 141, "RA227", 6, LINT("39"), LINT("10000")),//5
	Element::Element(88, 140, "RA226", 7, LINT("19"), LINT("1000000000000")),//6
	Element::Element(86, 138, "RN222", 8, LINT("3"), LINT("1000000")),//7
	Element::Element(84, 136, "PO218", 9, LINT("5"), LINT("100")),//8
	Element::Element(82, 134, "PB214", 10, LINT("62"), LINT("10000")),//9
	Element::Element(82, 133, "PB213", 11, LINT("16"), LINT("1000")),//10
	Element::Element(82, 132, "PB212", 12, LINT("26"), LINT("1000000")),//11
	Element::Element(82, 131, "PB211", 13, LINT("46"), LINT("10000")),//12
	Element::Element(82, 130, "PB210", 14, LINT("98"), LINT("10000000000")),//13
	Element::Element(82, 129, "PB209", 15, LINT("85"), LINT("1000000")),//14
	Element::Element(82, 128, "PB208", 15, LINT("0"), LINT("1")),//15
	Element::Element(92, 143, "U235", 3, LINT("31"), LINT("100000000000000000"))//16
};

LINT getMostAtoms()
{
	LINT r = 0;
	for (short i = 0; i < *(&Elements + 1) - Elements; i++)
	{
		if (r < Elements[i].n)
		{
			r = Elements[i].n;
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

void outputData(int longboi, int tries, LINT n, LINT i, LINT particles, Element Elements[], int len, STMP start)
{
	ThreadLock.lock();
	GETTP(stop)
	GETUS(t, stop, start)
	LINT tc = t.count();

	dataChange(24, longboi, 0, particles.convert_to<string>() + " CPM");
	BF50 nii[5] = { 0,0,0,0,0 };
	secToYDHMS(tc.convert_to<BF50>() / 1000.0, nii);
	dataChange(to_string(ULONG_MAX).length(), longboi, 1, 
		nii[0].convert_to<string>() + " y " +
		nii[1].convert_to<string>() + " d " +
		nii[2].convert_to<string>() + " h " +
		nii[3].convert_to<string>() + " m " +
		nii[4].convert_to<string>() + " s"
	);

	dataChange(to_string(ULONG_MAX).length(), longboi, 2, to_string(tries));
	BF50 d = i.convert_to<BF50>() / (tc.convert_to<BF50>() / 1000.0);
	dataChange(11, longboi, 3, d);
	BF50 x = (n - i).convert_to<BF50>() / d;
	BF50 foo[5] = { 0,0,0,0,0 };
	secToYDHMS(x, foo);
	dataChange(45, longboi, 4,
		foo[0].convert_to<string>() + " y " +
		foo[1].convert_to<string>() + " d " +
		foo[2].convert_to<string>() + " h " +
		foo[3].convert_to<string>() + " m " +
		foo[4].convert_to<string>() + " s " +
		to_string((BF50(i) / BF50(n) * BF50(100)).convert_to<float>()) + "%"
	);
	for (short i = 0; i < len; i++)
	{
		dataChange(24, longboi, i + 5, Elements[i].n);
	}
	ThreadLock.unlock();
}
