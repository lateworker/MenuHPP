#include <bits/stdc++.h>
#include <windows.h>
#include "menu_keybd.hpp"

using namespace std;
using namespace MenuKbd;

int main() {
	ConsoleColor col;
	col.setForegroundColor(ColorCyan);
	Display scr;
	scr.set({2, 5}, display_t{"a", col});
	scr.refresh();
	system("pause > nul");
	return 0;
}
