#include "Element.h"

Element::Element(unsigned short p, unsigned short n, std::string name, int dName, BF100 time, bool stable)
{
	Protons = p;
	Nutrons = n;
	elementName = name;
	decayName = dName;
	if (!stable)
	{
		BF100 a = 1/time;
		a = boost::multiprecision::pow(a, BF100(.5));
		short d = 0;
		while (a <= BF100(10) && d < 100)
		{
			d++;
			a *= 10;
		}
		decayChance = a.convert_to<LINT>();
		tDecayChance = boost::multiprecision::pow(BF50(10), d).convert_to<LINT>();
	}
	else
	{
		decayChance = 0;
		tDecayChance = 1;
	}
	boost::random::mt19937 foo(clock());
	gen = foo;
}

bool Element::testDecay(Element Elements[])
{
	if ((n > 0) && (n > ns))
	{
		if (genLargeNum(0, tDecayChance.convert_to<int>()) < decayChance.convert_to<int>())
		{
			n--;
			Elements[decayName].n++;
			return true;
		}
		else
		{
			ns++;
			return false;
		}

	}
	else
	{
		return false;
	}
}

LINT Element::genLargeNum(int min, int max)
{
	boost::random::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}