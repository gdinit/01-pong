/* globals.h */

#ifndef GLOBALS_H
#define GLOBALS_H

struct Settings {
	bool inGameOverlay = false;
	bool debugPrintToConsole = false;
	bool debugPrintToConsoleFPS = false;
	float paddleIndent = -1.f;
	float playAreaTopLine = -1.f;
	float playAreaBottomLine = -1.f;
	unsigned short int currentScreenSizeWidth = 0;
	unsigned short int currentScreenSizeHeight = 0;
	float ballSlower = -1.f;
	float paddleSlowerComputer = -1.f;
	float paddleSlowerHuman = -1.f;
	float paddleVelocityPosStep = 1.f;
	float paddleVelocityNegStep = -1.f;
	bool sideRightIsComputer = true;
	bool sideLeftIsComputer = true;
};

struct Globals {
	bool moveUpRequestActive = false;
	bool moveDownRequestActive = false;
};

#endif	// GLOBALS_H

/* EOF */

