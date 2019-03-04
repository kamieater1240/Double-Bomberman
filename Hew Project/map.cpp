#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "map.h"

char mapFull[(MAPLAYER * MAPHEIGHT * MAPWIDTH) + 1];
char mapFileRead[DECODELAYER][MAPHEIGHT / 8][(MAPWIDTH / 8) + 1];

//mapFullを戻る
const char * getMapFull(void) {
	return mapFull;
}

//ファイルからマップデータを読み込む
void readMap(void) {
	FILE *fReadMap;
	char mapRawFileRead[MAPHEIGHT / 8][MAPWIDTH / 8][DECODELAYER + 1];

	fReadMap = fopen("mapNew.txt", "r");

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

//読み込んだマップデータをデコードする
void mapDecoder() {

	static int incrementFrame = 0;
	incrementFrame %= 8;

	for (int h = 0; h < DECODELAYER; h++) {
		for (int i = 0; i < MAPHEIGHT / TILEYSIZE; i++) {

			char readMapFirstChar = '0';
			char readMapSecondChar = '0';
			for (int j = 0; j < MAPWIDTH / TILEXSIZE; j++) {

				if (h == 0) {							//アクションタイプ

					for (int k = 0; k < TILEYSIZE; k++)
					{
						for (int l = 0; l < TILEXSIZE; l++)
						{
							mapFull[(((0 * MAPHEIGHT * MAPWIDTH) + (((i * TILEYSIZE) + k) * MAPWIDTH) + ((j * TILEXSIZE) + l)) * MAPLAYER) + 0] = mapFileRead[h][i][j];
						}
					}
				}

				else if (h == 1) {						//背景色

					for (int k = 0; k < TILEYSIZE; k++)
					{
						for (int l = 0; l < TILEXSIZE; l++)
						{
							mapFull[(((0 * MAPHEIGHT * MAPWIDTH) + (((i * TILEYSIZE) + k) * MAPWIDTH) + ((j * TILEXSIZE) + l)) * MAPLAYER) + 1] = mapFileRead[h][i][j];
						}
					}
				}

				else if (h == 2) {						//マップタイル

					readMapFirstChar = mapFileRead[h][i][j];
					readMapSecondChar = mapFileRead[h + 1][i][j];

					int decodedMapFirstCharacter = decodeMapCharacters(readMapFirstChar);
					int decodedMapSecondCharacter = decodeMapCharacters(readMapSecondChar);

					int tileNumber = (decodedMapFirstCharacter * 16) + decodedMapSecondCharacter;

					if ((readMapFirstChar == '1') && (readMapSecondChar == '5')) {
						tileNumber += incrementFrame / 2;
					}

					char readMapTile[INDEXSIZE * TILEYSIZE * TILEXSIZE + 1];
					strcpy(readMapTile, getMapTile());
					readMapTile[INDEXSIZE * TILEYSIZE * TILEXSIZE] = '\0';

					for (int k = 0; k < TILEYSIZE; k++)
					{
						for (int l = 0; l < TILEXSIZE; l++)
						{
							mapFull[(((0 * MAPHEIGHT * MAPWIDTH) + (((i * TILEYSIZE) + k) * MAPWIDTH) + ((j * TILEXSIZE) + l)) * MAPLAYER) + 2] = readMapTile[(tileNumber * TILEYSIZE * TILEXSIZE) + (k * TILEYSIZE + l)];
						}
					}
				}

				else if (h == 4) {						//マップタイル　色シフト

					int shift = mapFileRead[h][i][j] - '0';
					if (shift > 16)
						shift -= 7;
					for (int k = 0; k < TILEYSIZE; k++) {
						for (int l = 0; l < TILEXSIZE; l++) {
							char currentChar = mapFull[(((0 * MAPHEIGHT * MAPWIDTH) + (((i * TILEYSIZE) + k) * MAPWIDTH) + ((j * TILEXSIZE) + l)) * MAPLAYER) + 2];
							int translateChar = currentChar - '0';
							if (currentChar != 'G') {
								if (translateChar > 16)
									translateChar = -7;

								int pixelShift = translateChar + shift;
								pixelShift %= 16;

								currentChar = pixelShift - '0';
								if (pixelShift >= 10)
									currentChar += 7;

								//mapFull[(((0 * MAPHEIGHT * MAPWIDTH) + (((i * TILEYSIZE) + k) * MAPWIDTH) + ((j * TILEXSIZE) + l)) * MAPLAYER) + 2] = currentChar;
							}
						}
					}
				}

				else if (h == 5) {						//アクションブロック

					readMapFirstChar = mapFileRead[h][i][j];
					readMapSecondChar = mapFileRead[h + 1][i][j];

					int decodedMapFirstCharacter = decodeMapCharacters(readMapFirstChar);
					int decodedMapSecondCharacter = decodeMapCharacters(readMapSecondChar);

					int tileNumber = (decodedMapFirstCharacter * 16) + decodedMapSecondCharacter;

					char readObjectTile[INDEXSIZE * TILEYSIZE * TILEXSIZE + 1];
					strcpy(readObjectTile, getObjectTile());
					readObjectTile[INDEXSIZE * TILEYSIZE * TILEXSIZE] = '\0';

					for (int k = 0; k < TILEYSIZE; k++)
					{
						for (int l = 0; l < TILEXSIZE; l++)
						{
							mapFull[(((0 * MAPHEIGHT * MAPWIDTH) + (((i * TILEYSIZE) + k) * MAPWIDTH) + ((j * TILEXSIZE) + l)) * MAPLAYER) + 3] = readObjectTile[(tileNumber * TILEYSIZE * TILEXSIZE) + (k * TILEYSIZE + l)];
						}
					}
				}

				else if (h == 7) {						//アクションブロック　色シフト

					int shift = mapFileRead[h][i][j] - '0';
					if (shift > 16)
						shift -= 7;
					for (int k = 0; k < TILEYSIZE; k++) {
						for (int l = 0; l < TILEXSIZE; l++) {

							char currentChar = mapFull[(((0 * MAPHEIGHT * MAPWIDTH) + (((i * TILEYSIZE) + k) * MAPWIDTH) + ((j * TILEXSIZE) + l)) * MAPLAYER) + 3];
							int translateChar = currentChar - '0';
							if (currentChar != 'G') {
								if (translateChar > 16)
									translateChar = -7;

								int pixelShift = translateChar + shift;
								pixelShift %= 16;

								currentChar = pixelShift - '0';
								if (pixelShift >= 10)
									currentChar += 7;

								//mapFull[(((0 * MAPHEIGHT * MAPWIDTH) + (((i * TILEYSIZE) + k) * MAPWIDTH) + ((j * TILEXSIZE) + l)) * MAPLAYER) + 3] = currentChar;
							}
						}
					}
				}

			}
		}
	}
	incrementFrame++;
}

int decodeMapCharacters(char encodedCharacter) {
	switch (encodedCharacter) {
	case('0'):
		return 0;
	case('1'):
		return 1;
	case('2'):
		return 2;
	case('3'):
		return 3;
	case('4'):
		return 4;
	case('5'):
		return 5;
	case('6'):
		return 6;
	case('7'):
		return 7;
	case('8'):
		return 8;
	case('9'):
		return 9;
	case('A'):
		return 10;
	case('B'):
		return 11;
	case('C'):
		return 12;
	case('D'):
		return 13;
	case('E'):
		return 14;
	case('F'):
		return 15;
	}
}

//マップをバッファする
void bufferMap() {

	mapDecoder();
	writeMapToBuffer(0, 0, mapFull);
}


char getcharMapFileRead(int layer, int playerX, int playerY) {

	return mapFileRead[layer][playerY][playerX];
}