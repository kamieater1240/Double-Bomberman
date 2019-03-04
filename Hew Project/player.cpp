#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "player.h"

PLAYER player1, player2;

//�v���C���[������������
void InitPlayer(PLAYER* player, COORD pos) {
	player->posX = pos.X;
	player->posY = pos.Y;
	player->isAlive = true;
	player->canPlantBombNum = 1;
	player->bombPlantedNum = 0;
	player->bombPower = 1;
}

//�v���[���[1�X�e�[�^�X���A�b�v�f�[�g����
void UpdatePlayer1(PLAYER* player1) {

	if (inport(PK_W)) {
		if (getcharMapFileRead(0, (player1->posX) / 8, (player1->posY - 8) / 8) == '0' || getcharMapFileRead(0, (player1->posX) / 8, (player1->posY - 8) / 8) == '4' || getcharMapFileRead(0, (player1->posX) / 8, (player1->posY - 8) / 8) == '5') {
			player1->posY -= 8;
			if (player1->posY < 0)
				player1->posY = 0;
		}
	}
	if (inport(PK_S)) {
		if (getcharMapFileRead(0, (player1->posX) / 8, (player1->posY + 8) / 8) == '0' || getcharMapFileRead(0, (player1->posX) / 8, (player1->posY + 8) / 8) == '4' || getcharMapFileRead(0, (player1->posX) / 8, (player1->posY + 8) / 8) == '5') {
			player1->posY += 8;
			if (player1->posY > 80)
				player1->posY = 80;
		}
	}
	if (inport(PK_A)) {
		if (getcharMapFileRead(0, (player1->posX - 8) / 8, (player1->posY) / 8) == '0' || getcharMapFileRead(0, (player1->posX - 8) / 8, (player1->posY) / 8) == '4' || getcharMapFileRead(0, (player1->posX - 8) / 8, (player1->posY) / 8) == '5') {
			player1->posX -= 8;
			if (player1->posX < 0)
				player1->posX = 0;
		}
	}
	if (inport(PK_D)) {
		if (getcharMapFileRead(0, (player1->posX + 8) / 8, (player1->posY) / 8) == '0' || getcharMapFileRead(0, (player1->posX + 8) / 8, (player1->posY) / 8) == '4' || getcharMapFileRead(0, (player1->posX + 8) / 8, (player1->posY) / 8) == '5') {
			player1->posX += 8;
			if (player1->posX > 128)
				player1->posX = 128;
		}
	}


}

//�v���[���[2�X�e�[�^�X���A�b�v�f�[�g����
void UpdatePlayer2(PLAYER* player2) {

	//�ړ�
	if (inport(PK_UP)) {
		if (getcharMapFileRead(0, (player2->posX) / 8, (player2->posY - 8) / 8) == '0' || getcharMapFileRead(0, (player2->posX) / 8, (player2->posY - 8) / 8) == '4' || getcharMapFileRead(0, (player2->posX) / 8, (player2->posY - 8) / 8) == '5') {
			player2->posY -= 8;
			if (player2->posY < 0)
				player2->posY = 0;
		}
	}
	if (inport(PK_DOWN)) {
		if (getcharMapFileRead(0, (player2->posX) / 8, (player2->posY + 8) / 8) == '0' || getcharMapFileRead(0, (player2->posX) / 8, (player2->posY + 8) / 8) == '4' || getcharMapFileRead(0, (player2->posX) / 8, (player2->posY + 8) / 8) == '5') {
			player2->posY += 8;
			if (player2->posY > 80)
				player2->posY = 80;
		}
	}
	if (inport(PK_LEFT)) {
		if (getcharMapFileRead(0, (player2->posX - 8) / 8, (player2->posY) / 8) == '0' || getcharMapFileRead(0, (player2->posX - 8) / 8, (player2->posY) / 8) == '4' || getcharMapFileRead(0, (player2->posX - 8) / 8, (player2->posY) / 8) == '5') {
			player2->posX -= 8;
			if (player2->posX < 0)
				player2->posX = 0;
		}
	}
	if (inport(PK_RIGHT)) {
		if (getcharMapFileRead(0, (player2->posX + 8) / 8, (player2->posY) / 8) == '0' || getcharMapFileRead(0, (player2->posX + 8) / 8, (player2->posY) / 8) == '4' || getcharMapFileRead(0, (player2->posX + 8) / 8, (player2->posY) / 8) == '5') {
			player2->posX += 8;
			if (player2->posX > 128)
				player2->posX = 128;
		}
	}

	//���e��u��
	if (inport(PK_GT)) {
		if (player2->bombPlantedNum < player2->canPlantBombNum) {
			player2->bombPlantedNum++;
			setBomb(player2->posX, player2->posY, player2->bombPower, player2);
		}
	}
}

//�v���C���[���o�b�t�@����
void bufferPlayers() {
	char readObjectTile[INDEXSIZE * TILEYSIZE * TILEXSIZE + 1];
	strcpy(readObjectTile, getObjectTile());

	//buffer player1
	writePlayerToBuffer(2, player1.posX, player1.posY, readObjectTile);
	//buffer player2
	writePlayerToBuffer(3, player2.posX, player2.posY, readObjectTile);
}

//�v���[���[1���擾����
PLAYER* getPlayer1() {
	return &player1;
}

//�v���[���[2���擾����
PLAYER* getPlayer2() {
	return &player2;
}