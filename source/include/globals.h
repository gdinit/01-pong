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
	float ballSpeed = -1.f;
	float paddleSpeedComputer = -1.f;
	float paddleSpeedHuman = -1.f;
	float paddleVelocityPosStep = 1.f;
	float paddleVelocityNegStep = -1.f;
	bool sideRightIsComputer = true;
	bool sideLeftIsComputer = true;
	float sideRightSpawnX = -1.f;
	float sideRightSpawnY = -1.f;
	float sideLeftSpawnX = -1.f;
	float sideLeftSpawnY = -1.f;
};

struct Globals {
	bool moveUpRequestActive = false;
	bool moveDownRequestActive = false;
};

#endif	// GLOBALS_H

/* EOF */

