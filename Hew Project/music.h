#pragma once
#include "main.h"

int openAudio(const char name[]);
void playAudio(int audio, BOOL isRepeatedly);
void stopAudio(int audio);