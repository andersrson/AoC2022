//
//  d2.c
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-23.
//

#include "d2.h"

void Day2Part1() {
    
    const char* dataFile = "./Resources/input-d2.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    char line[10] = "\0";
    
    uint runningTotal = 0;
    
    do {
        char* getReturn = fgets(line, 10, f);
        if(getReturn == NULL)
            break;
        
        assert(isalpha(line[0]) && isalpha(line[2]));
        
        char opp = line[0];
        char my = line[2];
        
        uint score = 0;
        
        if(my == MY_ROCK)
            score = POINTS_ROCK;
        if(my == MY_PAPER)
            score = POINTS_PAPER;
        if(my == MY_SCISSORS)
            score = POINTS_SCISSORS;
        
        if(opp == OPP_ROCK) {
            if(my == MY_ROCK)
                score += POINTS_DRAW;
            else if(my == MY_PAPER)
                score += POINTS_WIN;
        } else if(opp == OPP_PAPER) {
            if(my == MY_PAPER)
                score += POINTS_DRAW;
            else if(my == MY_SCISSORS)
                score += POINTS_WIN;
        } else if(opp == OPP_SCISSORS) {
            if(my == MY_SCISSORS)
                score += POINTS_DRAW;
            else if(my == MY_ROCK)
                score += POINTS_WIN;
        }
        
        runningTotal += score;
        
        printf("Round score: %d, total: %d\n", score, runningTotal);
        
    } while(!feof(f));
    
    printf("Total score: %d\n", runningTotal);
    
    fclose(f);
}

void Day2Part2() {
    const char* dataFile = "./Resources/input-d2.txt";
        
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    char line[10] = "\0";
    
    uint runningTotal = 0;
    
    do {
        char* getReturn = fgets(line, 10, f);
        if(getReturn == NULL)
            break;
        
        assert(isalpha(line[0]) && isalpha(line[2]));
        
        char opp = line[0];
        char play = line[2];
        char my = '\0';
        
        uint score = 0;
        
        if(opp == OPP_ROCK) {
            if(play == PLAY_WIN) {
                my = MY_PAPER;
                score += POINTS_WIN;
            } else if(play == PLAY_DRAW){
                my = MY_ROCK;
                score += POINTS_DRAW;
            } else if(play == PLAY_LOSE) {
                my = MY_SCISSORS;
                score += POINTS_LOST;
            }
        } else if(opp == OPP_PAPER) {
            if(play == PLAY_WIN) {
                my = MY_SCISSORS;
                score += POINTS_WIN;
            } else if(play == PLAY_DRAW){
                my = MY_PAPER;
                score += POINTS_DRAW;
            } else if(play == PLAY_LOSE) {
                my = MY_ROCK;
                score += POINTS_LOST;
            }
        } else if(opp == OPP_SCISSORS) {
            if(play == PLAY_WIN) {
                my = MY_ROCK;
                score += POINTS_WIN;
            } else if(play == PLAY_DRAW){
                my = MY_SCISSORS;
                score += POINTS_DRAW;
            } else if(play == PLAY_LOSE) {
                my = MY_PAPER;
                score += POINTS_LOST;
            }
        }
        
        if(my == MY_ROCK)
            score += POINTS_ROCK;
        if(my == MY_PAPER)
            score += POINTS_PAPER;
        if(my == MY_SCISSORS)
            score += POINTS_SCISSORS;
        
        runningTotal += score;
        
        printf("Round score: %d, total: %d\n", score, runningTotal);
        
    } while(!feof(f));
    
    printf("Total score: %d\n", runningTotal);
    
    fclose(f);
}
