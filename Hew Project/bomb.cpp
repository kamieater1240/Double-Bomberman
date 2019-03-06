#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "bomb.h"

BOMB bombs[MAX_BOMB];
bool mapEmpty[MAPHEIGHT / 8][MAPWIDTH / 8];

//���e������������
void initBomb() {

	for (int i = 0; i < MAX_BOMB; i++) {
		bombs[i].posX = 0;
		bombs[i].posY = 0;
		bombs[i].power = 1;
		bombs[i].explodeCnt = 0;
		bombs[i].isUsed = false;
		bombs[i].fireTimeCnt = 0;
		bombs[i].hasFire = false;
		bombs[i].fromWho = NULL;
		bombs[i].type = BOMBTYPE_NONE;
	}
}

//���e���Z�b�g����
void setBomb(int posX, int posY, int power, PLAYER* player) {

	for (int i = 0; i < MAX_BOMB; i++) {
		if (!bombs[i].isUsed && !bombs[i].hasFire) {
			bombs[i].posX = posX;
			bombs[i].posY = posY;
			bombs[i].power = power;
			bombs[i].explodeCnt = 0;
			bombs[i].isUsed = true;
			bombs[i].fireTimeCnt = 0;
			bombs[i].hasFire = false;
			bombs[i].fromWho = player;
			bombs[i].type = BOMBTYPE_NORMAL;
			break;
		}
	}
}

//�}�b�v��ɔ��e�������_���ɃZ�b�g����
void setRandomBomb(int power) {

	srand(time(NULL));
	int temp, x, y;
	temp = rand() % (186 - 0 + 1) + 0;
	x = temp % 17;
	y = temp / 17;

	while (!checkMapEmpty(x, y)) {
		temp = rand() % (186 - 0 + 1) + 0;
		x = temp % 17;
		y = temp / 17;
	}

	for (int i = 0; i < MAX_BOMB; i++) {
		if (!bombs[i].isUsed && !bombs[i].hasFire) {
			bombs[i].posX = x * 8;
			bombs[i].posY = y * 8;
			bombs[i].power = power;
			bombs[i].explodeCnt = 0;
			bombs[i].isUsed = true;
			bombs[i].fireTimeCnt = 0;
			bombs[i].hasFire = false;
			bombs[i].fromWho = NULL;
			bombs[i].type = BOMBTYPE_ICE;
			break;
		}
	}

	setMapEmpty(x, y, false);
}

//���e�̃X�e�[�^�X���A�b�v�f�[�g����
void UpdateBomb() {
	//bombsToMap();
	for (int i = 0; i < MAX_BOMB; i++) {
		if (bombs[i].isUsed) {
			//�����ɂ���
			if (bombs[i].explodeCnt == 45 && bombs[i].hasFire != true) {
				explode(bombs[i]);
				bombs[i].hasFire = true;
				bombs[i].isUsed = false;
				if (bombs[i].fromWho != NULL)
					bombs[i].fromWho->bombPlantedNum--;
			}
			else if (bombs[i].explodeCnt < 45 && bombs[i].hasFire != true) {
				bombs[i].explodeCnt++;
			}

		}
		else {
			if (bombs[i].hasFire) {
				//������̉΂ɂ���
				if (bombs[i].hasFire && bombs[i].fireTimeCnt == 15) {
					bombs[i].hasFire = false;
					clearFires(bombs[i]);
					itemsToMap();
				}
				else if (bombs[i].hasFire && bombs[i].fireTimeCnt < 15) {
					bombs[i].fireTimeCnt++;
					explode(bombs[i]);	//draw one more time, else if two bombs are too close, when clearing the fire of the first bomb, second's fire will be cleared too
				}
			}
		}
	}
}

//���e���������鎞�̏���
void explode(BOMB bomb) {
	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//��{�}�b�v�f�[�^���R�s�[

	//bomb���g�̃}�X��fire
	for (int j = 0; j < DECODELAYER; j++) {
		if (j == 0)
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '4';
		else if (j == 1)
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
		else if (j == 6)
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '6';
		else
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
	}

	setMapEmpty(bomb.posX / 8, bomb.posY / 8, true);

	writeMapFileRead(mapReceiveFile);

	if (bomb.type == BOMBTYPE_NORMAL)
		firesToMap(bomb);
	else if (bomb.type == BOMBTYPE_ICE)
		firesToMap(bomb);
}

//���e���}�b�v�ɕ`��
void bombsToMap() {

	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//��{�}�b�v�f�[�^���R�s�[

	//���e��`��
	for (int i = 0; i < MAX_BOMB; i++) {
		if (bombs[i].isUsed) {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 0)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bombs[i].posY / 8)*(MAPWIDTH / 8)) + (bombs[i].posX / 8)) = '3';
				else if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bombs[i].posY / 8)*(MAPWIDTH / 8)) + (bombs[i].posX / 8)) = '2';
				else if (j == 6)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bombs[i].posY / 8)*(MAPWIDTH / 8)) + (bombs[i].posX / 8)) = '5';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bombs[i].posY / 8)*(MAPWIDTH / 8)) + (bombs[i].posX / 8)) = '0';
			}
		}
	}

	writeMapFileRead(mapReceiveFile);
}

//���e�̉΂��}�b�v�ɕ`��
void firesToMap(BOMB bomb) {
	bool topStop = false, downStop = false, leftStop = false, rightStop = false;
	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//��{�}�b�v�f�[�^���R�s�[

	srand(time(NULL));

	//�����͈͂̉΂�`��
	for (int i = 1; i <= bomb.power; i++) {

		//Check bomb up
		if (!topStop) {
			if (*(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '0' || *(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '2'
				|| *(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '5') {
				if (*(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '2') {

					setMapEmpty(bomb.posX / 8, (bomb.posY - 8 * i) / 8, true);

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 30) {
						int whichKind = rand() % (100 - 1 + 1) + 1;
						if (whichKind > 50)
							setItem(bomb.posX, bomb.posY - 8 * i, ITEMTYPETYPE_DBBOMB);
						else
							setItem(bomb.posX, bomb.posY - 8 * i, ITEMTYPETYPE_DBPOWER);
					}

					topStop = true;
				}

				for (int j = 0; j < DECODELAYER; j++) {
					if (j == 0)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '4';
					else if (j == 1)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
					else if (j == 6)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '6';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
				}
			}
			else
				topStop = true;
		}
		//Check bomb down
		if (!downStop) {
			if (*(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '0' || *(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '2'
				|| *(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '5') {
				if (*(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '2') {

					setMapEmpty(bomb.posX / 8, (bomb.posY + 8 * i) / 8, true);

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 30) {
						int whichKind = rand() % (100 - 1 + 1) + 1;
						if (whichKind > 50)
							setItem(bomb.posX, bomb.posY + 8 * i, ITEMTYPETYPE_DBBOMB);
						else
							setItem(bomb.posX, bomb.posY + 8 * i, ITEMTYPETYPE_DBPOWER);
					}

					downStop = true;
				}

				for (int j = 0; j < DECODELAYER; j++) {
					if (j == 0)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '4';
					else if (j == 1)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
					else if (j == 6)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '6';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
				}
			}
			else
				downStop = true;
		}
		//Check bomb right
		if (!leftStop) {
			if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '0' || *(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '2'
				|| *(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '5') {
				if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '2') {

					setMapEmpty((bomb.posX + 8 * i) / 8, bomb.posY / 8, true);

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 30) {
						int whichKind = rand() % (100 - 1 + 1) + 1;
						if (whichKind > 50)
							setItem(bomb.posX + 8 * i, bomb.posY, ITEMTYPETYPE_DBBOMB);
						else
							setItem(bomb.posX + 8 * i, bomb.posY, ITEMTYPETYPE_DBPOWER);
					}

					leftStop = true;
				}

				for (int j = 0; j < DECODELAYER; j++) {
					if (j == 0)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '4';
					else if (j == 1)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '2';
					else if (j == 6)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '6';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '0';
				}
			}
			else
				leftStop = true;
		}
		//Check bomb left
		if (!rightStop) {
			if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '0' || *(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '2'
				|| *(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '5') {
				if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '2') {

					setMapEmpty((bomb.posX - 8 * i) / 8, bomb.posY / 8, true);

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 30) {
						int whichKind = rand() % (100 - 1 + 1) + 1;
						if (whichKind > 50)
							setItem(bomb.posX - 8 * i, bomb.posY, ITEMTYPETYPE_DBBOMB);
						else
							setItem(bomb.posX - 8 * i, bomb.posY, ITEMTYPETYPE_DBPOWER);
					}

					rightStop = true;
				}

				for (int j = 0; j < DECODELAYER; j++) {
					if (j == 0)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '4';
					else if (j == 1)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '2';
					else if (j == 6)
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '6';
					else
						*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '0';
				}
			}
			else
				rightStop = true;
		}
	}

	writeMapFileRead(mapReceiveFile);
}

//���e�̕X���}�b�v�ɕ`��
void iceToMap(BOMB bomb) {

}

//���e�̉΂��}�b�v�������
void clearFires(BOMB bomb) {
	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//��{�}�b�v�f�[�^���R�s�[

	//���e���g�̃}�X�̉΂�����
	for (int j = 0; j < DECODELAYER; j++) {
		if (j == 1)
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
		else
			*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
	}

	//�����͈͂̉΂�����
	for (int i = 1; i <= bomb.power; i++) {

		//Check bomb up
		if (*(mapReceiveFile + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '4') {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY - 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
			}
		}
		//Check bomb down
		if (*(mapReceiveFile + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) == '4') {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '2';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + (((bomb.posY + 8 * i) / 8)*(MAPWIDTH / 8)) + (bomb.posX / 8)) = '0';
			}
		}
		//Check bomb right
		if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) == '4') {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '2';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX + 8 * i) / 8)) = '0';
			}
		}
		//Check bomb left
		if (*(mapReceiveFile + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) == '4') {
			for (int j = 0; j < DECODELAYER; j++) {
				if (j == 1)
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '2';
				else
					*(mapReceiveFile + (j*(MAPHEIGHT / 8)*(MAPWIDTH / 8)) + ((bomb.posY / 8)*(MAPWIDTH / 8)) + ((bomb.posX - 8 * i) / 8)) = '0';
			}
		}
	}

	writeMapFileRead(mapReceiveFile);
}

//mapEmpty������������
void initMapEmpty() {

	for (int i = 0; i < MAPHEIGHT / 8; i++) {
		for (int j = 0; j < MAPWIDTH / 8; j++) {
			if (getcharMapFileRead(0, j, i) != '1' && getcharMapFileRead(0, j, i) != '2' && getcharMapFileRead(0, j, i) != '3')
				mapEmpty[i][j] = true;
			else
				mapEmpty[i][j] = false;
		}
	}
}

void setMapEmpty(int posX, int posY, bool value) {
	mapEmpty[posY][posX] = value;
}

bool checkMapEmpty(int posX, int posY) {
	return mapEmpty[posY][posX];
}