//
//  d3.c
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-23.
//

#include "d3.h"

uint GetPriority(char ch) {
    if(isupper(ch))
        return ((int)ch) - UPPER_OFFSET;
    else if(islower(ch))
        return ((int)ch) - LOWER_OFFSET;
    
    assert(0);
}

void Day3Part1(void) {
    
    const char* dataFile = "./Resources/input-d3.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    char line[BUFSIZ] = "\0";
    uint sumPriorities = 0;
    
    do {
        memset(line, '\0', BUFSIZ);
        char* getReturn = fgets(line, BUFSIZ, f);
        if(getReturn == NULL)
            break;
        
        size_t lineLen = strnlen(line, BUFSIZ);
        assert(lineLen > 0);
        assert(line[lineLen - 1] == '\n');
        assert(lineLen % 2 == 1);
        
        size_t partLength = (lineLen - 1) / 2;
        char firstHalf[partLength + 1];
        char secondHalf[partLength + 1];
        
        strncpy(firstHalf, line, partLength);
        strncpy(secondHalf, line + partLength, partLength);
        firstHalf[partLength] = '\0';
        secondHalf[partLength] = '\0';
        
        uint priorities = 0;
        for(uint i = 0; i < partLength; i++) {
            char firstChar = firstHalf[i];
            if(firstChar == ' ')
                continue;
            
            if(strchr(secondHalf, firstChar) != NULL) {
                priorities += GetPriority(firstChar);
                
                firstHalf[i] = ' ';
            }
            
            char* occ = strchr(firstHalf, firstChar);
            while(occ != NULL) {
                *occ = ' ';
                occ = strchr(firstHalf, firstChar);
            }
        }
        
        sumPriorities += priorities;
    
    } while(!feof(f));
    
    printf("prios summed: %d\n", sumPriorities);
    
    fclose(f);
}

void Day3Part2(void) {
    
    const char* dataFile = "./Resources/input-d3.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    char line[BUFSIZ];
    char line2[BUFSIZ];
    char line3[BUFSIZ];
    memset(line, '\0', BUFSIZ);
    memset(line2, '\0', BUFSIZ);
    memset(line3, '\0', BUFSIZ);
    
    uint sumPriorities = 0;
    
    do {
        char* getReturn = fgets(line, BUFSIZ, f);
        if(getReturn == NULL)
            break;
        getReturn = fgets(line2, BUFSIZ, f);
        if(getReturn == NULL)
            break;
        getReturn = fgets(line3, BUFSIZ, f);
        if(getReturn == NULL)
            break;
        
        size_t lineLen = strnlen(line, BUFSIZ);
        assert(lineLen > 0);
        assert(line[lineLen - 1] == '\n');
        size_t line2Len = strnlen(line2, BUFSIZ);
        assert(line2Len > 0);
        assert(line2[line2Len - 1] == '\n');
        size_t line3Len = strnlen(line3, BUFSIZ);
        assert(line3Len > 0);
        assert(line3[line3Len - 1] == '\n');
        
        uint prio = 0;
        for(uint i = 0; i < lineLen - 1; i++) {
            char currentItem = line[i];
            
            // If currentItem occurs in *both* other rucksacks, get the priority
            if(strchr(line2, currentItem) != NULL && strchr(line3, currentItem) != NULL) {
                prio += GetPriority(currentItem);
                
                // Delete all occurrences of currentItem in line so we don't check this again
                char* occ = strchr(line, currentItem);
                while(occ != NULL) {
                    *occ = ' ';
                    occ = strchr(line, currentItem);
                }
            }
        }
        
        sumPriorities += prio;
        
        printf("prios: %d\n", prio);
    } while(!feof(f));
    
    printf("prios summed: %d\n", sumPriorities);
    
    fclose(f);
}
