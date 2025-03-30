#ifndef MenuKbdHPP
#define MenuKbdHPP

//#include <string>
//#include <vector>
//#include <tuple>
#include <bits/stdc++.h>
#include <windows.h>

namespace MenuKbd {

#define CONSOLE_BLACK			0
#define CONSOLE_BLUE			1
#define CONSOLE_GREEN			2
#define CONSOLE_CYAN			3
#define CONSOLE_RED				4
#define CONSOLE_PURPLE			5
#define CONSOLE_YELLOW			6
#define CONSOLE_WHITE			7
#define CONSOLE_BRIGHTBLACK 	8
#define CONSOLE_BRIGHTBLUE 		9
#define CONSOLE_BRIGHTGREEN 	10
#define CONSOLE_BRIGHTCYAN 		11
#define CONSOLE_BRIGHTRED 		12
#define CONSOLE_BRIGHTPURPLE 	13
#define CONSOLE_BRIGHTYELLOW 	14
#define CONSOLE_BRIGHTWHITE 	15
	
	class ConsoleColor {
		WORD color;
	public:
		ConsoleColor(); ~ConsoleColor();
		
		void setForegroundColor(WORD col);
		void setBackgroundColor(WORD col);
		WORD getForegroundColor() const;
		WORD getBackgroundColor() const;
		WORD getMixedColor() const;
	};

	using display_t = std::tuple<std::string, ConsoleColor>;
	class Basic {
	public:
		static bool getCursorPosition(COORD &cursorPosition);
		static bool setCursorPosition(COORD cursorPosition = {0, 0});
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

	Text::Text() {
		name.clear(), text.clear();
		LenX = LenY = 0;
	}
	Text::~Text() {
		name.clear(), text.clear();
		LenX = LenY = 0;
	}
	
	Display::Display() {
		buffer.clear();
	}
	Display::~Display() {
		buffer.clear();
	}
	
	bool Basic::getCursorPosition(COORD &cursorPosition) {
		bool ret = false;
		CONSOLE_SCREEN_BUFFER_INFO temp;
		ret |= GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp);
		cursorPosition = temp.dwCursorPosition;
		return ret;
	}
	bool Basic::setCursorPosition(COORD cursorPosition) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		return SetConsoleCursorPosition(hConsole, cursorPosition);
	}
	bool Basic::setConsoleColor(const ConsoleColor& color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		return SetConsoleTextAttribute(hConsole, color.getMixedColor());
	}
	bool Basic::printText(COORD position, const display_t& data) {
		const auto& [text, color] = data;
		COORD position_now;
		getCursorPosition(position_now);
		setCursorPosition(position);
		std::cout << text;
		setCursorPosition(position_now);
	}
	
	void Display::refresh() {
		for (const auto& [position, bufferdata] : buffer) {
			if (!bufferdata.second) continue; // if theres no changes, then continue
			
		}
	}
	void Display::set(COORD position, const display_t& data) {
//		buffer[position] = data;
	}
	display_t Display::get(COORD position) {
//		return buffer[position];
	}

}

#endif
