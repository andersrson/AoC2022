//
//  d6.c
//  AoC2022
//
//  Created by Anders Runesson on 2023-01-09.
//

#include "d6.h"

void Day6Part1(size_t MARKER_LEN) {
    const char* dataFile = "./Resources/input-d6.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    rewind(f);
    
    struct list* inputLines = NULL;
    char* fullLine = malloc(filesize);
    do {
        char* getReturn = fgets(fullLine, (int)filesize, f);
        if(getReturn == fullLine && !isspace(getReturn[0])) {
            size_t len = strnlen(fullLine, filesize);
            struct string* line = initString(len, fullLine);
            inputLines = appendToList(inputLines, line, len);
        }
    } while(!feof(f));
    free(fullLine);
    fclose(f);
    
    for(int i = 0; i < countList(inputLines); i++) {
        struct list* entry = getAtIndexList(inputLines, i);
        struct string* str = (struct string*)entry->data;
        char* txt = str->c_str;
        size_t len = strnlen(txt, str->len);
        
        assert(len > 3);
        int floor = 0;
        
        for(int j = 1; j < len; j++) {
            uint nonDupes = 1;
            char now = txt[j];
            for(int k = 1; k < MARKER_LEN; k++) {
                int checkIdx = j - k;
                if(checkIdx < floor)
                    break;
                
                char check = txt[checkIdx];
                if(check != now) {
                    nonDupes++;
                } else {
                    floor = checkIdx + 1;
                    break;
                }
            }
            if(nonDupes >= MARKER_LEN) {
                printf("Marker found ending at %d\n", j + 1);
                break;
            }
        }
    }
    
    releaseAllDelegateList(inputLines, (void(*)(void*))releaseString);
}

void Day6Part2(size_t MARKER_LEN) {
    const char* dataFile = "./Resources/input-d6.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    rewind(f);
    
    struct list* inputLines = NULL;
    char* fullLine = malloc(filesize);
    do {
        char* getReturn = fgets(fullLine, (int)filesize, f);
        if(getReturn == fullLine && !isspace(getReturn[0])) {
            size_t len = strnlen(fullLine, filesize);
            struct string* line = initString(len, fullLine);
            inputLines = appendToList(inputLines, line, len);
        }
    } while(!feof(f));
    free(fullLine);
    fclose(f);
    
    for(int i = 0; i < countList(inputLines); i++) {
        struct list* entry = getAtIndexList(inputLines, i);
        struct string* str = (struct string*)entry->data;
        char* txt = str->c_str;
        size_t len = strnlen(txt, str->len);
        
        assert(len > 3);
        int floor = 0;
        
        for(int j = 1; j < len; j++) {
            uint nonDupes = 1;
            char now = txt[j];
            for(int k = 1; k < MARKER_LEN; k++) {
                int checkIdx = j - k;
                if(checkIdx < floor)
                    break;
                
                char check = txt[checkIdx];
                if(check != now) {
                    nonDupes++;
                } else {
                    floor = checkIdx + 1;
                    break;
                }
            }
            if(nonDupes >= MARKER_LEN) {
                printf("Marker found ending at %d\n", j + 1);
                break;
            }
        }
    }
    
    releaseAllDelegateList(inputLines, (void(*)(void*))releaseString);
}
