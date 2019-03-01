#define _CRT_SECURE_NO_WARNINGS
#include "tile.h"

void readMapTile() {
	FILE *fReadMapTile;
	int index = 0;
	char MapTile[INDEXSIZE][TILEYSIZE][TILEXSIZE + 1];
	char dummy[20];

	fReadMapTile = fopen("mapTiles.txt", "r");

	if (fread == NULL)
		printf("Map file does not Exists.");
	else {
		for (int i = 0; i < INDEXSIZE; i++) {
			for (int j = 0; j < TILEYSIZE; j++) {
				fscanf(fReadMapTile, "%s", MapTile[i][j]);
				MapTile[i][j][TILEXSIZE] = '\0';

				if (j == TILEYSIZE - 1) {
					fscanf(fReadMapTile, "%s", dummy);
				}
			}
		}
	}
	fclose(fReadMapTile);
}