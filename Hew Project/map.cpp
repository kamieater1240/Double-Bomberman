#define _CRT_SECURE_NO_WARNINGS
#include "map.h"

char mapFull[(MAPHEIGHT * MAPWIDTH) + 1];
char mapFileRead[DECODELAYER][MAPHEIGHT / 8][(MAPWIDTH / 8) + 1];

//mapFullを戻る
const char * getMapFull(void) {
	return mapFull;
}

//ファイルからマップデータを読み込む
void readMap(void) {
	FILE *fReadMap;
	char mapRawFileRead[MAPHEIGHT / 8][MAPWIDTH / 8][DECODELAYER + 1];

	fReadMap = fopen("map.txt", "r");

	if (fread == NULL)
		printf("Map file does not Exists.");
	else {
		for (int i = 0; i < MAPHEIGHT / 8; i++) {
			for (int j = 0; j < MAPWIDTH / 8; j++) {
				fscanf(fReadMap, "%s", mapRawFileRead[i][j]);
				mapRawFileRead[i][j][DECODELAYER] = '\0';
			}
			printf("\n");
		}

		for (int k = 0; k < DECODELAYER; k++) {
			for (int i = 0; i < MAPHEIGHT / 8; i++) {
				for (int j = 0; j < MAPWIDTH / 8; j++) {
					mapFileRead[k][i][j] = mapRawFileRead[i][j][k];
				}
				mapFileRead[k][i][MAPWIDTH / 8] = '\0';
			}
		}
	}
	fclose(fReadMap);
}

//
char getcharMapFileRead(int MAP, int LAYER, int X, int Y) {
	return 'a';
}

int decodeMapCharacters(char CHARACTER) {
	return 0;
}

const char * getRawMapFull(void) {
	return '\0';
}

void mapDecoder(int ROOM) {

}

void updateMapFileRead(int ROOM, int DECODE_LAYER, int HEIGHT, int WIDTH, char CHANGE) {

}