#define _CRT_SECURE_NO_WARNINGS
#include "player.h"

PLAYER player1, player2;

//プレイヤーを初期化する
void InitPlayer(PLAYER player, COORD pos) {
	player.posX = pos.X;
	player.posY = pos.Y;
	player.isAlive = true;
}

//プレーヤー1ステータスをアップデートする
void UpdatePlayer1(PLAYER player1) {

}

//プレーヤー2ステータスをアップデートする
void UpdatePlayer2(PLAYER player2) {

}

//プレーヤー1を取得する
PLAYER* getPlayer1() {
	return &player1;
}

//プレーヤー2を取得する
PLAYER* getPlayer2() {
	return &player2;
}