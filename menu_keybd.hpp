#ifndef MenuKbdHPP
#define MenuKbdHPP

#include <string>

namespace MenuKbd {

	class Text {
	protected:
		std::string name, text; // name: representation in code, text: charactors displayed
		std::size_t LenX, LenY; // limited length in x & y position, value "0" means "auto decide"
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

	class Script : public Text {

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
