#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <string>

#include "conioex.h"
#include "map.h"
#include "buffer.h"
#include "tile.h"
#include "setting.h"
#include "color.h"
#include "item.h"
#include "startandend.h"
#include "music.h"
using namespace std;

#define INDEXSIZE		256
#define DECODELAYER		8
#define MAPLAYER		4

#define MAPWIDTH		136
#define MAPHEIGHT		88

#define SCREENWIDTH		136
#define SCREENHEIGHT	88

#define PIXELSIZE		12
#define TILEXSIZE		8
#define TILEYSIZE		8

#define MAX_BOMB		50
#define MAX_ITEM		100

#define GAME_X    8
#define GAME_Y    1

enum State {
	TITLE,
	GAME,
	RESULT
};

extern int titleMusic, themeMusic, selectSE, takeItemSE, putBombSE, footstepSE, gameoverSE, explosionSE, endMusic;

#ifdef _DEBUG
void DispDebug(void);
#endif // _DEBUG

void Initiation();
void InitMusic();
void Update();
void Draw();

#endif // !_MAIN_H_