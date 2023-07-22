#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
uint8_t saw[4];
/*
i 번째의 5번비트와 i+1 번째의 1번비트가 맞닿아 있음
*/

void select_saw(int num, int dir, int is_rotate[]) {
	
	int ndir;
	if (dir == -1) ndir = 1;
	else ndir = -1;

	if (num != 0 && is_rotate[num-1] == 0 && (((saw[num] & (0x02))>>1)^((saw[num-1] & (0x20)) >> 5))) {
		is_rotate[num - 1] = ndir;
		select_rotate_saw(num - 1, ndir, is_rotate);
	}
	if (num != 3 && is_rotate[num + 1] == 0 && (((saw[num + 1] & (0x02)) >> 1) ^ ((saw[num] & (0x20)) >> 5))) {
		is_rotate[num + 1] = ndir;
		select_rotate_saw(num + 1, ndir, is_rotate);
	}
	
}

void rotate_saw(int is_rotate[]) {
	for (int i = 0; i < 4; i++) {
		if (is_rotate[i] == 1) {
			uint8_t saw_temp = 0;
			for (int j = 1; j < 8; j++) {
				saw_temp |= ((saw[i] & (0x01 << j)) >> 1);
			}
			saw_temp |= ((saw[i] & (0x01)) << 7);
			saw[i] = saw_temp;
		}
		else if (is_rotate[i] == -1) {

			uint8_t saw_temp = 0;
			for (int j = 6; j >= 0; j--) {
				saw_temp |= ((saw[i] & (0x01 << j)) << 1);
			}
			saw_temp |= ((saw[i] & (0x80)) >> 7);
			saw[i] = saw_temp;
		}
	}
}

int main() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			char bit;
			scanf(" %c", &bit);
			if (bit == '1') {
				saw[i] |= (0x01 << (7 - j));//LSB : 12 -> 시계방향
			}
		}
	}
	int K;
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		int saw_num, direction;
		int is_rotate[4] = { 0 };
		scanf("%d %d", &saw_num, &direction);
		is_rotate[saw_num-1] = direction;
		select_saw(saw_num-1, direction, is_rotate);
		rotate_saw(is_rotate);
		//int de=1;
	}

	uint8_t score = 0;
	for (int i = 0; i < 4; i++) {
		score += ((saw[i] & 0x80) >> (7-i));
	}
	printf("%d", score);

	return 0;
}