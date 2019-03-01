#define _CRT_SECURE_NO_WARNINGS
#include "tile.h"

char mapTile[INDEXSIZE * TILEYSIZE * TILEXSIZE + 1];
char objectTile[(INDEXSIZE * TILEYSIZE * TILEXSIZE) + 1];

const char * getMapTile(void) {
	return mapTile;
}

const char * getObjectTile(void) {
	return objectTile;
}

//マップタイルを読み込む
void readMapTile() {
	FILE *fReadMapTile;
	int index = 0;
	char readMapTile[INDEXSIZE][TILEYSIZE][TILEXSIZE + 1];
	char dummy[20];

	fReadMapTile = fopen("mapTiles.txt", "r");

	if (fread == NULL)
		printf("MapTiles file does not Exists.");
	else {
		for (int i = 0; i < INDEXSIZE; i++) {
			for (int j = 0; j < TILEYSIZE; j++) {
				fscanf(fReadMapTile, "%s", readMapTile[i][j]);
				readMapTile[i][j][TILEXSIZE] = '\0';

				for (int k = 0; k < TILEXSIZE; k++) {
					mapTile[(i * TILEYSIZE * TILEXSIZE) + (j * TILEYSIZE) + k] = readMapTile[i][j][k];
				}

				if (j == TILEYSIZE - 1) {
					fscanf(fReadMapTile, "%s", dummy);
				}

			}
		}
		mapTile[INDEXSIZE * TILEYSIZE * TILEXSIZE] = '\0';
	}
	fclose(fReadMapTile);
}

//オブジェクトタイルを読み込む
void readObjectTile() {
	FILE *fReadObjectTile;
	int index = 0;
	char readObjectTile[INDEXSIZE][TILEYSIZE][TILEXSIZE + 1];
	char dummy[20];

	fReadObjectTile = fopen("objectTiles.txt", "r");
	if (fread == NULL)
		printf("ObjectTiles file does not Exists.");
	else {
		for (int i = 0; fscanf(fReadObjectTile, "%s", readObjectTile[index][i]) != EOF; i++) {
			readObjectTile[index][i][TILEXSIZE] = '\0';

			for (int j = 0; j < TILEXSIZE; j++) {
				if (i >= TILEYSIZE - 1) {
					i = -1;
					index++;
					fscanf(fReadObjectTile, "%s", dummy);
				}
				objectTile[(index*TILEYSIZE*TILEXSIZE) + (i * TILEYSIZE) + j] = readObjectTile[index][i][j];
			}
		}
		objectTile[INDEXSIZE * TILEYSIZE * TILEXSIZE] = '\0';
	}
	fclose(fReadObjectTile);
}