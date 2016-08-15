#include "pch.h"
#include "Source.h"

void Source::FireEvent(int n)
{
	theEvent_(this, n);
}