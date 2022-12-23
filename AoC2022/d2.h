//
//  d2.h
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-23.
//

#ifndef d2_h
#define d2_h

#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#define POINTS_WIN 6
#define POINTS_DRAW 3
#define POINTS_LOST 0

#define POINTS_ROCK 1
#define POINTS_PAPER 2
#define POINTS_SCISSORS 3

#define OPP_ROCK 'A'
#define OPP_PAPER 'B'
#define OPP_SCISSORS 'C'

#define MY_ROCK 'X'
#define MY_PAPER 'Y'
#define MY_SCISSORS 'Z'

#define PLAY_LOSE 'X'
#define PLAY_DRAW 'Y'
#define PLAY_WIN 'Z'

void Day2Part1(void);
void Day2Part2(void);

#endif /* d2_h */
