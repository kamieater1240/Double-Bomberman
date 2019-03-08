#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "player.h"
#include "bomb.h"

PLAYER player1, player2;

//�v���C���[������������
void InitPlayer(PLAYER* player, COORD pos) {
	player->posX = pos.X;
	player->posY = pos.Y;
	player->isAlive = true;
	player->canPlantBombNum = 1;
	player->bombPlantedNum = 0;
	player->bombPower = 1;
	player->settingBomb = false;
}

//�v���[���[1�X�e�[�^�X���A�b�v�f�[�g����
void UpdatePlayer1(PLAYER* player1) {

	if (inport(PK_W)) {
		if (getcharMapFileRead(0, (player1->posX) / 8, (player1->posY - 8) / 8) == '0' || getcharMapFileRead(0, (player1->posX) / 8, (player1->posY - 8) / 8) == '4' || getcharMapFileRead(0, (player1->posX) / 8, (player1->posY - 8) / 8) == '5') {
			playAudio(footstepSE, 0);

			if (getcharMapFileRead(0, (player1->posX) / 8, (player1->posY - 8) / 8) == '5') {
				playAudio(takeItemSE, 0);

				if (getcharMapFileRead(6, (player1->posX) / 8, (player1->posY - 8) / 8) == '7') {
					if (player1->canPlantBombNum < 4)
						player1->canPlantBombNum *= 2;
				}
				else if (getcharMapFileRead(6, (player1->posX) / 8, (player1->posY - 8) / 8) == '8') {
					if (player1->bombPower < 8)
						player1->bombPower *= 2;
				}

				clearItem(player1->posX, player1->posY - 8);
			}

			player1->posY -= 8;
			if (player1->posY < 0)
				player1->posY = 0;
		}
	}
	if (inport(PK_S)) {
		if (getcharMapFileRead(0, (player1->posX) / 8, (player1->posY + 8) / 8) == '0' || getcharMapFileRead(0, (player1->posX) / 8, (player1->posY + 8) / 8) == '4' || getcharMapFileRead(0, (player1->posX) / 8, (player1->posY + 8) / 8) == '5') {
			playAudio(footstepSE, 0);

			if (getcharMapFileRead(0, (player1->posX) / 8, (player1->posY + 8) / 8) == '5') {
				playAudio(takeItemSE, 0);

				if (getcharMapFileRead(6, (player1->posX) / 8, (player1->posY + 8) / 8) == '7') {
					if (player1->canPlantBombNum < 4)
						player1->canPlantBombNum *= 2;
				}
				else if (getcharMapFileRead(6, (player1->posX) / 8, (player1->posY + 8) / 8) == '8') {
					if (player1->bombPower < 8)
						player1->bombPower *= 2;
				}

				clearItem(player1->posX, player1->posY + 8);
			}

			player1->posY += 8;
			if (player1->posY > 80)
				player1->posY = 80;
		}
	}
	if (inport(PK_A)) {
		if (getcharMapFileRead(0, (player1->posX - 8) / 8, (player1->posY) / 8) == '0' || getcharMapFileRead(0, (player1->posX - 8) / 8, (player1->posY) / 8) == '4' || getcharMapFileRead(0, (player1->posX - 8) / 8, (player1->posY) / 8) == '5') {
			playAudio(footstepSE, 0);

			if (getcharMapFileRead(0, (player1->posX - 8) / 8, (player1->posY) / 8) == '5') {
				playAudio(takeItemSE, 0);

				if (getcharMapFileRead(6, (player1->posX - 8) / 8, (player1->posY) / 8) == '7') {
					if (player1->canPlantBombNum < 4)
						player1->canPlantBombNum *= 2;
				}
				else if (getcharMapFileRead(6, (player1->posX - 8) / 8, (player1->posY) / 8) == '8') {
					if (player1->bombPower < 8)
						player1->bombPower *= 2;
				}

				clearItem(player1->posX - 8, player1->posY);
			}

			player1->posX -= 8;
			if (player1->posX < 0)
				player1->posX = 0;
		}
	}
	if (inport(PK_D)) {
		if (getcharMapFileRead(0, (player1->posX + 8) / 8, (player1->posY) / 8) == '0' || getcharMapFileRead(0, (player1->posX + 8) / 8, (player1->posY) / 8) == '4' || getcharMapFileRead(0, (player1->posX + 8) / 8, (player1->posY) / 8) == '5') {
			playAudio(footstepSE, 0);

			if (getcharMapFileRead(0, (player1->posX + 8) / 8, (player1->posY) / 8) == '5') {
				playAudio(takeItemSE, 0);

				if (getcharMapFileRead(6, (player1->posX + 8) / 8, (player1->posY) / 8) == '7') {
					if (player1->canPlantBombNum < 4)
						player1->canPlantBombNum *= 2;
				}
				else if (getcharMapFileRead(6, (player1->posX + 8) / 8, (player1->posY) / 8) == '8') {
					if (player1->bombPower < 8)
						player1->bombPower *= 2;
				}

				clearItem(player1->posX + 8, player1->posY);
			}

			player1->posX += 8;
			if (player1->posX > 128)
				player1->posX = 128;
		}
	}

	//���e��u��
	if (GetAsyncKeyState(VK_TAB) & 0x8000) {
		if (!player1->settingBomb) {
			if (player1->bombPlantedNum < player1->canPlantBombNum) {
				if (checkMapEmpty(player1->posX / 8, player1->posY / 8)) {
					playAudio(putBombSE, 0);
					player1->bombPlantedNum++;
					setBomb(player1->posX, player1->posY, player1->bombPower, player1);
					bombsToMap();
					player1->settingBomb = true;
					setMapEmpty(player1->posX / 8, player1->posY / 8, false);
					setRandomBomb(player1->bombPower);
					bombsToMap();
				}
			}
		}
	}
	else {
		player1->settingBomb = false;
	}

	player1->isAlive = !isGameOver(player1);
}

//�v���[���[2�X�e�[�^�X���A�b�v�f�[�g����
void UpdatePlayer2(PLAYER* player2) {

	//�ړ�
	if (inport(PK_UP)) {
		if (getcharMapFileRead(0, (player2->posX) / 8, (player2->posY - 8) / 8) == '0' || getcharMapFileRead(0, (player2->posX) / 8, (player2->posY - 8) / 8) == '4' || getcharMapFileRead(0, (player2->posX) / 8, (player2->posY - 8) / 8) == '5') {
			playAudio(footstepSE, 0);

			if (getcharMapFileRead(0, (player2->posX) / 8, (player2->posY - 8) / 8) == '5') {
				playAudio(takeItemSE, 0);

				if (getcharMapFileRead(6, (player2->posX) / 8, (player2->posY - 8) / 8) == '7') {
					if (player2->canPlantBombNum < 4)
						player2->canPlantBombNum *= 2;
				}
				else if (getcharMapFileRead(6, (player2->posX) / 8, (player2->posY - 8) / 8) == '8') {
					if (player2->bombPower < 8)
						player2->bombPower *= 2;
				}

				clearItem(player2->posX, player2->posY - 8);
			}

			player2->posY -= 8;
			if (player2->posY < 0)
				player2->posY = 0;
		}
	}
	if (inport(PK_DOWN)) {
		if (getcharMapFileRead(0, (player2->posX) / 8, (player2->posY + 8) / 8) == '0' || getcharMapFileRead(0, (player2->posX) / 8, (player2->posY + 8) / 8) == '4' || getcharMapFileRead(0, (player2->posX) / 8, (player2->posY + 8) / 8) == '5') {
			playAudio(footstepSE, 0);

			if (getcharMapFileRead(0, (player2->posX) / 8, (player2->posY + 8) / 8) == '5') {
				playAudio(takeItemSE, 0);

				if (getcharMapFileRead(6, (player2->posX) / 8, (player2->posY + 8) / 8) == '7') {
					if (player2->canPlantBombNum < 4)
						player2->canPlantBombNum *= 2;
				}
				else if (getcharMapFileRead(6, (player2->posX) / 8, (player2->posY + 8) / 8) == '8') {
					if (player2->bombPower < 8)
						player2->bombPower *= 2;
				}

				clearItem(player2->posX, player2->posY + 8);
			}

			player2->posY += 8;
			if (player2->posY > 80)
				player2->posY = 80;
		}
	}
	if (inport(PK_LEFT)) {
		if (getcharMapFileRead(0, (player2->posX - 8) / 8, (player2->posY) / 8) == '0' || getcharMapFileRead(0, (player2->posX - 8) / 8, (player2->posY) / 8) == '4' || getcharMapFileRead(0, (player2->posX - 8) / 8, (player2->posY) / 8) == '5') {
			playAudio(footstepSE, 0);

			if (getcharMapFileRead(0, (player2->posX - 8) / 8, (player2->posY) / 8) == '5') {
				playAudio(takeItemSE, 0);

				if (getcharMapFileRead(6, (player2->posX - 8) / 8, (player2->posY) / 8) == '7') {
					if (player2->canPlantBombNum < 4)
						player2->canPlantBombNum *= 2;
				}
				else if (getcharMapFileRead(6, (player2->posX - 8) / 8, (player2->posY) / 8) == '8') {
					if (player2->bombPower < 8)
						player2->bombPower *= 2;
				}

				clearItem(player2->posX - 8, player2->posY);
			}

			player2->posX -= 8;
			if (player2->posX < 0)
				player2->posX = 0;
		}
	}
	if (inport(PK_RIGHT)) {
		if (getcharMapFileRead(0, (player2->posX + 8) / 8, (player2->posY) / 8) == '0' || getcharMapFileRead(0, (player2->posX + 8) / 8, (player2->posY) / 8) == '4' || getcharMapFileRead(0, (player2->posX + 8) / 8, (player2->posY) / 8) == '5') {
			playAudio(footstepSE, 0);

			if (getcharMapFileRead(0, (player2->posX + 8) / 8, (player2->posY) / 8) == '5') {
				playAudio(takeItemSE, 0);

				if (getcharMapFileRead(6, (player2->posX + 8) / 8, (player2->posY) / 8) == '7') {
					if (player2->canPlantBombNum < 4)
						player2->canPlantBombNum *= 2;
				}
				else if (getcharMapFileRead(6, (player2->posX + 8) / 8, (player2->posY) / 8) == '8') {
					if (player2->bombPower < 8)
						player2->bombPower *= 2;
				}

				clearItem(player2->posX + 8, player2->posY);
			}

			player2->posX += 8;
			if (player2->posX > 128)
				player2->posX = 128;
		}
	}

	//���e��u��
	if (GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) {
		if (!player2->settingBomb) {
			if (player2->bombPlantedNum < player2->canPlantBombNum) {
				if (checkMapEmpty(player2->posX / 8, player2->posY / 8)) {
					playAudio(putBombSE, 0);
					player2->bombPlantedNum++;
					setBomb(player2->posX, player2->posY, player2->bombPower, player2);
					bombsToMap();
					player2->settingBomb = true;
					setMapEmpty(player2->posX / 8, player2->posY / 8, false);
					setRandomBomb(player2->bombPower);
					bombsToMap();
				}
			}
		}
	}
	else {
		player2->settingBomb = false;
	}

	player2->isAlive = !isGameOver(player2);
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

//�v���C���[�͔����Ɋ������܂ꂽ
bool isGameOver(PLAYER* player) {
	if (getcharMapFileRead(0, (player->posX) / 8, (player->posY) / 8) == '4') {
		return true;
	}
	else
		return false;
}