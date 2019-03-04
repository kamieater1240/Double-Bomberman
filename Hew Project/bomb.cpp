#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "bomb.h"

BOMB bombs[MAXBOMB];

//爆弾を初期化する
void initBomb() {

	for (int i = 0; i < MAXBOMB; i++) {
		bombs[i].posX = 0;
		bombs[i].posY = 0;
		bombs[i].power = 1;
		bombs[i].explodeCnt = 0;
		bombs[i].isUsed = false;
	}
}

//爆弾をセットする
void setBomb(int posX, int posY, int power, PLAYER* player) {

	for (int i = 0; i < MAXBOMB; i++) {
		if (!bombs[i].isUsed) {
			bombs[i].posX = posX;
			bombs[i].posY = posY;
			bombs[i].power = power;
			bombs[i].explodeCnt = 0;
			bombs[i].isUsed = true;
			bombs[i].fromWho = player;
			break;
		}
	}
}

//爆弾のステータスをアップデートする
void UpdateBomb() {
	for (int i = 0; i < MAXBOMB; i++) {
		if (bombs[i].isUsed) {
			if (bombs[i].explodeCnt == 60) {
				explode();
				bombs[i].isUsed = false;
				bombs[i].fromWho->bombPlantedNum--;
			}
			else {
				bombs[i].explodeCnt++;
			}
		}
	}
}

//爆弾が爆発する時の処理
void explode() {

}

//爆弾をバッファする
void bufferBombs() {
	char readObjectTile[INDEXSIZE * TILEYSIZE * TILEXSIZE + 1];
	strcpy(readObjectTile, getObjectTile());

	for (int i = 0; i < MAXBOMB; i++) {
		if (bombs[i].isUsed) {
			writeBombToBuffer(5, bombs[i].posX, bombs[i].posY, readObjectTile);
		}
	}
}

//爆弾の火をバッファする
void bufferFires() {

}