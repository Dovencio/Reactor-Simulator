#include "Element.h"

Element::Element(unsigned short p, unsigned short n, std::string name, int dName, LINT decChance, LINT tDecChance)
{
	Protons = p;
	Nutrons = n;
	elementName = name;
	decayName = dName;
	decayChance = decChance;
	tDecayChance = tDecChance;
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