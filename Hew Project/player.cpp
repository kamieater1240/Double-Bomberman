#define _CRT_SECURE_NO_WARNINGS
#include "player.h"

PLAYER player1, player2;

//�v���C���[������������
void InitPlayer(PLAYER player, COORD pos) {
	player.posX = pos.X;
	player.posY = pos.Y;
	player.isAlive = true;
}

//�v���[���[1�X�e�[�^�X���A�b�v�f�[�g����
void UpdatePlayer1(PLAYER player1) {

}

//�v���[���[2�X�e�[�^�X���A�b�v�f�[�g����
void UpdatePlayer2(PLAYER player2) {

}

//�v���[���[1���擾����
PLAYER* getPlayer1() {
	return &player1;
}

//�v���[���[2���擾����
PLAYER* getPlayer2() {
	return &player2;
}