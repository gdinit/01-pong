/* globals.h */

#ifndef GLOBALS_H
#define GLOBALS_H

struct Settings {
	bool inGameOverlay = false;
	bool debugPrintToConsole = false;
	bool debugPrintToConsoleFPS = false;
	float paddleIndent = -1.f;
	float playAreaTopLine = 0.f;
	float playAreaBottomLine = 0.f;
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
	//
	float paddleRightTop;
	float paddleRightBottom;
	float paddleRightLeft;
	float paddleRightRight;
	//
	float paddleLeftTop;
	float paddleLeftBottom;
	float paddleLeftLeft;
	float paddleLeftRight;
	//
	signed long int	scoreLeftSide = 0;
	signed long int	scoreRightSide = 0;
};

#endif	// GLOBALS_H

/* EOF */

