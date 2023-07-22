#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
int N, L;
int Map[100][100] = { 0, };
int Ladder[100][100] = { 0 };

// 1 : true, 0 : false;
// determine whether or not a ladder can be placed.
int check(int rowOrCol, int num);

// dir : 0 -> go forward , 1-> backwark
int placeLadder(int y, int x, int rowOrCol, int dir);



int check(int rowOrCol, int num) {
	int pre_Height;
	//setting first value;
	if (rowOrCol == 0) pre_Height = Map[num][0];
	else pre_Height = Map[0][num];

	for (int i = 1; i < N; i++) {
		int now_Height;
		if (rowOrCol == 0) {// row
			now_Height = Map[num][i];
			if (now_Height != pre_Height) {
				if (abs(now_Height - pre_Height) > 1) return 0;//can't place ladder
				else if (now_Height > pre_Height) {
					if (!placeLadder(num, i-1, 0, 1)) {
						return 0;
					}
				}
				else {
					if (!placeLadder(num, i, 0, 0)) {
						return 0;
					}
				}

			}

		}
		else { // col
			now_Height = Map[i][num];
			if (now_Height != pre_Height) {
				if (abs(now_Height - pre_Height) > 1) return 0;//can't place ladder
				else if (now_Height > pre_Height) {
					if (!placeLadder(i-1, num, 1, 1)) {
						return 0;
					}
				}
				else {
					if (!placeLadder(i, num, 1, 0)) {
						return 0;
					}
				}

			}
		}
		pre_Height = now_Height;
	}

	return 1;
}

// (y,x) -> start position of ladder
// rowOrCol : 0 -> row , 1 -> col
int placeLadder(int y, int x, int rowOrCol, int dir) {
	//check can place ladder
	int Height = Map[y][x];
	if (rowOrCol == 0 && dir == 0) // row & forward
	{
		if (N - 1 < x + L - 1) return 0;
		for (int i = 0; i < L; i++) {
			if (Map[y][x + i] != Height || Ladder[y][x + i] == 1) return 0;
		}
	}
	else if (rowOrCol == 0 && dir == 1) {
		if (x - L+1 < 0) return 0;
		for (int i = 0; i < L; i++) {
			if (Map[y][x - i] != Height || Ladder[y][x - i] == 1) return 0;
		}
	}
	else if (rowOrCol == 1 && dir == 0) {
		if (N - 1 < y + L - 1) return 0;
		for (int i = 0; i < L; i++) {
			if (Map[y + i][x] != Height || Ladder[y + i][x] == 1) return 0;
		}
	}
	else {
		if (y - L + 1 < 0) return 0;
		for (int i = 0; i < L; i++) {
			if (Map[y - i][x] != Height || Ladder[y - i][x] == 1) return 0;
		}
	}



	//place ladder

	if (rowOrCol == 0)
	{
		if (dir == 0)
		{
			for (int i = 0; i < L; i++)
			{
				Ladder[y][x + i] = 1;
			}
		}
		else
		{
			for (int i = 0; i < L; i++)
			{
				Ladder[y][x - i] = 1;
			}
		}

	}
	else if (rowOrCol == 1)
	{
		if (dir == 0)
		{
			for (int j = 0; j < L; j++)
			{
				Ladder[y + j][x] = 1;
			}
		}
		else
		{
			for (int j = 0; j < L; j++)
			{
				Ladder[y - j][x] = 1;
			}

		}
	}


	return 1;
}


int main() {

	scanf(" %d %d", &N, &L);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf(" %d", &Map[i][j]);
		}
	}

	int ans = 0;
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < N; i++) {
			ans += check(k, i);
		} 
		memset(Ladder, 0, sizeof(Ladder));
	}
	printf("%d\n", ans);
	return 0;
}
