#ifndef MenuKbdHPP
#define MenuKbdHPP

#include <bits/stdc++.h>
#include <windows.h>

COORD operator + (const COORD& a, const COORD& b) { return {(SHORT)(a.X + b.X), (SHORT)(a.Y + b.Y)}; }
COORD operator - (const COORD& a, const COORD& b) { return {(SHORT)(a.X - b.X), (SHORT)(a.Y - b.Y)}; }
COORD operator * (const COORD& a, const SHORT& b) { return {(SHORT)(a.X * b), (SHORT)(a.Y * b)}; }
COORD operator / (const COORD& a, const SHORT& b) { return {(SHORT)(a.X / b), (SHORT)(a.Y / b)}; }
COORD operator % (const COORD& a, const SHORT& b) { return {(SHORT)(a.X % b), (SHORT)(a.Y % b)}; }
void operator += (COORD& a, const COORD& b) { a = a + b; }
void operator -= (COORD& a, const COORD& b) { a = a - b; }
void operator *= (COORD& a, const SHORT& b) { a = a * b; }
void operator /= (COORD& a, const SHORT& b) { a = a / b; }
void operator %= (COORD& a, const SHORT& b) { a = a % b; }
std::strong_ordering operator <=> (const COORD& a, const COORD& b) { return std::make_pair(a.X, a.Y) <=> std::make_pair(b.X, b.Y); }
bool operator == (const COORD &a, const COORD &b) { return std::make_pair(a.X, a.Y) == std::make_pair(b.X, b.Y); }
std::istream &operator >> (std::istream &pin, COORD &x) { pin >> x.X >> x.Y; return pin; }
std::ostream &operator << (std::ostream &pout, const COORD x) { pout << x.X << ' ' << x.Y; return pout; }

namespace MenuKbd {

#define ColorBlack				0
#define ColorBlue				1
#define ColorGreen				2
#define ColorCyan				3
#define ColorRed				4
#define ColorPurple				5
#define ColorYellow				6
#define ColorWhite				7
#define ColorBrightBlack		8
#define ColorBrightBlue			9
#define ColorBrightGreen		10
#define ColorBrightCyan			11
#define ColorBrightRed			12
#define ColorBrightPurple	 	13
#define ColorBrightYellow	 	14
#define ColorBrightWhite		15
	
	class ConsoleColor {
		WORD color;
	public:
		ConsoleColor(); ~ConsoleColor();
		ConsoleColor(WORD mixedColor);
		
		void setForegroundColor(WORD col);
		void setBackgroundColor(WORD col);
		WORD getForegroundColor() const;
		WORD getBackgroundColor() const;
		WORD getMixedColor() const;
		
		bool operator == (const ConsoleColor& b) const;
	};
	
	using display_t = std::tuple<std::string, ConsoleColor>;
	class Basic {
	public:
		static bool getCursorPosition(COORD &cursorPosition);
		static bool setCursorPosition(COORD cursorPosition = {0, 0});
		static bool getConsoleColor(ConsoleColor& color);
		static bool setConsoleColor(const ConsoleColor& color);
		static bool printText(COORD position, const display_t& data);
	};
	
	class Text {
	protected:
		std::string name, text; // name: representation in code, text: charactors displayed
		std::size_t LenX, LenY; // limited length in x & y position, value "0" means "auto decide"
		ConsoleColor defaultColor; // public ??
	public:
		Text(); ~Text();

		void setName();
		void setText();
		void setLenX();
		void setLenY();
		std::string getName() const;
		std::string getText() const;
		std::size_t getLenX() const;
		std::size_t getLenY() const;
		
		
	};

	class Button : public Text {

	};

	class Field : public Text {

	};

	class Table {

	};

	class Display {
		std::map<COORD, std::pair<display_t, bool> > buffer;
	public:
		Display(); ~Display();
		
		void refresh();
		void set(COORD position, const display_t& data);
		display_t get(COORD position) const;
	};
	
// ConsoleColor
	ConsoleColor::ConsoleColor() {
		color = ColorWhite;
	} 
	ConsoleColor::~ConsoleColor() {
		color = 0;
	}
	ConsoleColor::ConsoleColor(WORD mixedColor) {
		color = mixedColor;
	}
	void ConsoleColor::setForegroundColor(WORD col) {
		color = getBackgroundColor() << 4 | col;
	}
	void ConsoleColor::setBackgroundColor(WORD col) {
		color = col << 4 | getForegroundColor();
	}
	WORD ConsoleColor::getForegroundColor() const {
		return color & 0b1111;
	}
	WORD ConsoleColor::getBackgroundColor() const {
		return color >> 4;
	}
	WORD ConsoleColor::getMixedColor() const {
		return color;
	}
	bool ConsoleColor::operator == (const ConsoleColor& b) const {
		return color == b.color;
	}
	
// Basic
	bool Basic::getCursorPosition(COORD &cursorPosition) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); bool ret = false;
		CONSOLE_SCREEN_BUFFER_INFO info;
		ret |= GetConsoleScreenBufferInfo(hConsole, &info);
		cursorPosition = info.dwCursorPosition;
		return ret;
	}
	bool Basic::setCursorPosition(COORD cursorPosition) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		return SetConsoleCursorPosition(hConsole, cursorPosition);
	}
	bool Basic::getConsoleColor(ConsoleColor& color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); bool ret = false;
		CONSOLE_SCREEN_BUFFER_INFO info;
		ret |= GetConsoleScreenBufferInfo(hConsole, &info);
		color = ConsoleColor(info.wAttributes);
		return ret;
	}
	bool Basic::setConsoleColor(const ConsoleColor& color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		return SetConsoleTextAttribute(hConsole, color.getMixedColor());
	}
	bool Basic::printText(COORD position, const display_t& data) {
		bool ret = false;
		const auto& [text, color] = data;
		COORD position_now; ConsoleColor color_now;
//		ret |= getCursorPosition(position_now) 	|| getConsoleColor(color_now);
		ret |= setCursorPosition(position)		|| setConsoleColor(color);
		std::cout << text;
//		ret |= setCursorPosition(position_now)	|| setConsoleColor(color_now);
		return ret;
	}
	
// Text
	Text::Text() {
		name.clear(), text.clear();
		LenX = LenY = 0;
	}
	Text::~Text() {
		name.clear(), text.clear();
		LenX = LenY = 0;
	}
	
// Display
	Display::Display() {
		buffer.clear();
	}
	Display::~Display() {
		buffer.clear();
	}
	void Display::refresh() {
		for (const auto& [position, bufferdata] : buffer) {
			if (!bufferdata.second) continue; // if theres no changes, then continue
			Basic::printText(position, bufferdata.first);
		}
	}
	void Display::set(COORD position, const display_t& data) {
		if (buffer[position].first == data) return; // if its the same, bypass
		buffer[position] = std::make_pair(data, true);
	}
	display_t Display::get(COORD position) const {
		return buffer.at(position).first; // cannot use [] to visit because of "const"
	}

}

#endif
