#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include "bomb.h"

BOMB bombs[MAX_BOMB];

//���e������������
void initBomb() {

	for (int i = 0; i < MAX_BOMB; i++) {
		bombs[i].posX = 0;
		bombs[i].posY = 0;
		bombs[i].power = 1;
		bombs[i].explodeCnt = 0;
		bombs[i].isUsed = false;
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
			break;
		}
	}
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

	writeMapFileRead(mapReceiveFile);
	firesToMap(bomb);
}

//���e���}�b�v�ɕ`��
void bombsToMap() {

	static char mapReceiveFile[(DECODELAYER * (MAPHEIGHT / 8) * (MAPWIDTH / 8)) + 1];
	strcpy(mapReceiveFile, getMapFileRead());	//��{�}�b�v�f�[�^���R�s�[

	//���e���g�̃}�X�̉΂�`��
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
					
					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 50) {
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

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 50) {
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

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 50) {
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

					int createItem = rand() % (100 - 1 + 1) + 1;
					//Create item
					if (createItem < 50) {
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