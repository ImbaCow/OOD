#include "pch.h"
#include <algorithm>
#include <cctype>
using namespace std;

int main()
{
	string str = "";
	cout << all_of(str.begin(), str.end(), isdigit);
}
