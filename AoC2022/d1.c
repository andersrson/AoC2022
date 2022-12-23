//
//  d1.c
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-23.
//

#include "d1.h"

void Day1Part1() {
    const char* dataFile = "./Resources/input-d1.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    size_t currentElfLoad = 0;
    size_t largestElfLoad = 0;
    char line[100] = "\0";
    
    do {
        char* getReturn = fgets(line, 100, f);
        
        char* endChar;
        long int lineLoad = strtol(line, &endChar, 10);
        
        if(lineLoad == 0 || getReturn == NULL) {
            if(currentElfLoad > largestElfLoad)
                largestElfLoad = currentElfLoad;
            currentElfLoad = 0;
        } else {
            currentElfLoad += lineLoad;
        }
        
        printf("Int value: %ld\n", lineLoad);
    } while(!feof(f));
    
    printf("Largest load: %ld\n", largestElfLoad);
    
    fclose(f);
}

void Day1Part2() {
    const char* dataFile = "./Resources/input-d1.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    size_t currentElfLoad = 0;
    size_t largestElfLoads[3] = { 0, 0, 0 };
    char line[100] = "\0";
    
    do {
        char* getReturn = fgets(line, 100, f);
        
        char* endChar;
        long int lineLoad = strtol(line, &endChar, 10);
        
        if(lineLoad == 0 || getReturn == NULL) {
            
            printf("Elf load: %ld\n", currentElfLoad);
            for(int i = 0; i < 3; i++) {
                if(currentElfLoad > largestElfLoads[i]) {
                    size_t tmp = largestElfLoads[i];
                    largestElfLoads[i] = currentElfLoad;
                    currentElfLoad = tmp;
                }
            }
            
            currentElfLoad = 0;
        } else {
            currentElfLoad += lineLoad;
        }
        
    } while(!feof(f));
    printf("Largest loads:\n");
    printf("%ld %ld %ld\n", largestElfLoads[0], largestElfLoads[1], largestElfLoads[2] );
    printf("Sum: %ld\n", largestElfLoads[0] + largestElfLoads[1] + largestElfLoads[2] );
    
    fclose(f);
}
