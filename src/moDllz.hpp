#include "rack.hpp"
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <list> // std::list
#include <algorithm> // std::find
#include <vector> // std::vector

#define FONT_FILE asset::plugin(pluginInstance, "res/bold_led_board-7.ttf")
#define mFONT_FILE asset::plugin(pluginInstance, "res/ShareTechMono-Regular.ttf")

using namespace rack;

extern Plugin *pluginInstance;

// Forward-declare each Model, defined in each module source file
extern Model *modelTwinGlider;
extern Model *modelXBender;
extern Model *modelMIDIdualCV;
extern Model *modelMIDI8MPE;
extern Model *modelMIDIpoly16;

///////////////////////
// custom components
///////////////////////

///knob44
struct moDllzKnobM : SvgKnob {
	moDllzKnobM() {
		// box.size = Vec(44, 44);
		minAngle = -0.83*M_PI;
		maxAngle = 0.83*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzKnobM.svg")));
		shadow->opacity = 0.f;
	}
};

///knob32
struct moDllzKnob32 : SvgKnob {
	moDllzKnob32() {
		// box.size = Vec(32, 32);
		minAngle = -0.83*M_PI;
		maxAngle = 0.83*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzKnob32.svg")));
		shadow->opacity = 0.f;
	}
};

struct moDllzKnob26 : SvgKnob {
	moDllzKnob26() {
		// box.size = Vec(32, 32);
		minAngle = -0.83*M_PI;
		maxAngle = 0.83*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzKnob26.svg")));
		shadow->opacity = 0.f;
	}
};

struct moDllzKnob22 : SvgKnob {
	moDllzKnob22() {
		//  box.size = Vec(32, 32);
		minAngle = -0.83*M_PI;
		maxAngle = 0.83*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzKnob22.svg")));
		shadow->opacity = 0.f;
	}
};

///TinyTrim
struct moDllzTTrim : SvgKnob {
	moDllzTTrim() {
		minAngle = -0.83*M_PI;
		maxAngle = 0.83*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzTTrim.svg")));
		shadow->opacity = 0.f;
	}
};

struct TTrimSnap : moDllzTTrim{
	TTrimSnap(){
		snap = true;
	}
};

///SnapSelector32
struct moDllzSelector32 : SvgKnob {
	moDllzSelector32() {
		// box.size = Vec(32, 32);
		minAngle = -0.85*M_PI;
		maxAngle = 0.85*M_PI;
		snap = true;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSnap32.svg")));
		shadow->opacity = 0.f;
	}
};

struct moDllzSmSelector : SvgKnob{
	moDllzSmSelector() {
	// box.size = Vec(36, 36);
		minAngle = -0.5*M_PI;
		maxAngle = 0.5*M_PI;
		snap = true;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSmSelector.svg")));
		shadow->opacity = 0.f;
	}
};

///switch
struct moDllzSwitch : SvgSwitch {
	moDllzSwitch() {
		// box.size = Vec(10, 20);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitch_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitch_1.svg")));
	}
};
///Horizontal switch
struct moDllzSwitchH : SvgSwitch {
	moDllzSwitchH() {
		// box.size = Vec(20, 10);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchH_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchH_1.svg")));
	}
};
///Switch with Led
struct moDllzSwitchLed : SvgSwitch {
	moDllzSwitchLed() {
		// box.size = Vec(10, 18);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchLed_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchLed_1.svg")));
	}
};
///Horizontal switch with Led
struct moDllzSwitchLedH : SvgSwitch {
	moDllzSwitchLedH() {
		// box.size = Vec(18, 10);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchLedH_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchLedH_1.svg")));
	}
};
///Horizontal switch Triple with Led
struct moDllzSwitchLedHT : SvgSwitch {
	moDllzSwitchLedHT() {
		// box.size = Vec(24, 10);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchLedHT_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchLedHT_1.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchLedHT_2.svg")));
	}
};

/// Transp Light over led switches
struct TranspOffRedLight : ModuleLightWidget {
	TranspOffRedLight() {
		box.size = Vec(10.f,10.f);
		addBaseColor(nvgRGBA(0xff, 0x00, 0x00, 0x88));//borderColor = nvgRGBA(0, 0, 0, 0x60);
	}
};
///switch TriState
struct moDllzSwitchT : SvgSwitch {
	moDllzSwitchT() {
		//   box.size = Vec(10, 30);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchT_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchT_1.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchT_2.svg")));
	}
};

///switch TriState Horizontal
struct moDllzSwitchTH : SvgSwitch {
	moDllzSwitchTH() {
		// box.size = Vec(30, 10);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchTH_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchTH_1.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzSwitchTH_2.svg")));
	}
};

///Momentary Button
struct moDllzMoButton : SvgSwitch {
	moDllzMoButton() {
		momentary = true;
		// box.size = Vec(48, 27);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzMoButton_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzMoButton_1.svg")));
	}
};

///Momentary Label Clear Button
struct moDllzClearButton : SvgSwitch {
	moDllzClearButton() {
		momentary = true;
		// box.size = Vec(38, 13);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzClearButton.svg")));
	}
};

///Momentary Round Button
struct moDllzRoundButton : SvgSwitch {
	moDllzRoundButton() {
		momentary = true;
		// box.size = Vec(14, 14);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzRoundButton.svg")));
	}
};

///Momentary PulseUp
struct moDllzPulseUp : SvgSwitch {
	moDllzPulseUp() {
		momentary = true;
		// box.size = Vec(12, 12);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzPulse2Up.svg")));
	}
};
///Momentary PulseDown
struct moDllzPulseDwn : SvgSwitch {
	moDllzPulseDwn() {
		momentary = true;
		// box.size = Vec(12, 12);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzPulse2Dwn.svg")));
	}
};

///MuteGate
struct moDllzMuteG : SvgSwitch {
	moDllzMuteG() {
		momentary = true;
		// box.size = Vec(67, 12);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzMuteG.svg")));
	}
};
///MuteGateP
struct moDllzMuteGP : SvgSwitch {
	moDllzMuteGP() {
		momentary = true;
		// box.size = Vec(26, 11);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzMuteGP.svg")));
	}
};
///MIDIPanic
struct moDllzMidiPanic : SvgSwitch {
	moDllzMidiPanic() {
		momentary = true;
		// box.size = Vec(38, 12);
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/midireset3812.svg")));
	}
};

/// Cursor  Buttons L R
struct moDllzcursorL : SvgSwitch {
	moDllzcursorL() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/cursorL_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/cursorL_1.svg")));
	}
};
struct moDllzcursorR : SvgSwitch {
	moDllzcursorR() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/cursorR_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/cursorR_1.svg")));
	}
};
/// UpDown + - Buttons
struct minusButton : SvgSwitch {
	minusButton() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/minusButton_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/minusButton_1.svg")));
	}
};
struct plusButton : SvgSwitch {
	plusButton() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/plusButton_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/plusButton_1.svg")));
	}
};

///Jacks
struct moDllzPort : SvgPort {
		moDllzPort() {
			setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzPort.svg")));
			shadow->opacity = 0.f;
		}
};
struct moDllzPortDark : SvgPort {
	moDllzPortDark() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/moDllzPortDark.svg")));
		shadow->opacity = 0.f;
	}
};
