#ifndef MenuKbdHPP
#define MenuKbdHPP

#include <string>
#include <minwindef.h>

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
		WORD getForegroundColor();
		WORD getBackgroundColor();
		WORD getMixedColor();
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
		std::string getName();
		std::string getText();
		std::size_t getLenX();
		std::size_t getLenY();
		
		
	};

	class Button : public Text {

	};

	class Field : public Text {

	};

	class Table {

	};


	Text::Text() {
		name.clear(), text.clear();
		LenX = LenY = 0;
	}
	Text::~Text() {
		name.clear(), text.clear();
		LenX = LenY = 0;
	}

}

#endif
