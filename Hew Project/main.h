#pragma once

#define INDEXSIZE		256
#define DECODELAYER		8
#define MAPLAYER		4
#define MAPWIDTH		128
#define MAPHEIGHT		64
#define SCREENWIDTH		128
#define SCREENHEIGHT	64
#define PIXELSIZE		12
#define TILEXSIZE		8
#define TILEYSIZE		8

#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <string>

#include "map.h"
#include "buffer.h"
#include "tile.h"
#include "setting.h"
#include "color.h"

void Initiation();