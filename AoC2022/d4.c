//
//  d4.c
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-25.
//

#include "d4.h"

void relString(void* str) {
    releaseString(str);
}

void Day4Part1(void) {
    const char* dataFile = "./Resources/input-d4.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    char line[BUFSIZE];
    memset(line, '\0', BUFSIZE);
    
    size_t containedPairs = 0;
    do {
        char* getReturn = fgets(line, BUFSIZE, f);
        if(getReturn == NULL)
            break;
        size_t lineLen = strnlen(getReturn, BUFSIZE); // If successful, will contain trailing newline
        
        struct string* str = initString(lineLen, line);
        const struct list* assignments = splitString(str, ',');
        
        assert(assignments != NULL);
        assert(countList(assignments) == 2);
        
        const struct list* asgElf1 = splitString(assignments->data, '-');
        const struct list* asgElf2 = splitString(assignments->next->data, '-');
        
        assert(asgElf1 != NULL);
        assert(countList(asgElf1) == 2);
        assert(asgElf2 != NULL);
        assert(countList(asgElf2) == 2);
        
        size_t a = 0, b = 0, c = 0, d = 0;
        a = strtoul(((struct string*)asgElf1->data)->c_str, NULL, 10);
        b = strtoul(((struct string*)asgElf1->next->data)->c_str, NULL, 10);
        c = strtoul(((struct string*)asgElf2->data)->c_str, NULL, 10);
        d = strtoul(((struct string*)asgElf2->next->data)->c_str, NULL, 10);
        
        bool contained = (a >= c && b <= d) || (c >= a && d <= b);
        if(contained)
            containedPairs++;
        
        releaseString(str);
        releaseAllDelegateList((struct list*)assignments, &relString);
    } while(!feof(f));
    
    printf("Contained pairs: %ld\n", containedPairs);
    
    fclose(f);
}

void Day4Part2(void) {
    const char* dataFile = "./Resources/input-d4.txt";
        
        FILE* f = fopen(dataFile, "r");
        assert(f != NULL);
        
        char line[BUFSIZE];
        memset(line, '\0', BUFSIZE);
        
        size_t overlappingPairs = 0;
        do {
            char* getReturn = fgets(line, BUFSIZE, f);
            if(getReturn == NULL)
                break;
            size_t lineLen = strnlen(getReturn, BUFSIZE); // If successful, will contain trailing newline
            
            struct string* str = initString(lineLen, line);
            const struct list* assignments = splitString(str, ',');
            
            assert(assignments != NULL);
            assert(countList(assignments) == 2);
            
            const struct list* asgElf1 = splitString(assignments->data, '-');
            const struct list* asgElf2 = splitString(assignments->next->data, '-');
            
            assert(asgElf1 != NULL);
            assert(countList(asgElf1) == 2);
            assert(asgElf2 != NULL);
            assert(countList(asgElf2) == 2);
            
            size_t a = 0, b = 0, c = 0, d = 0;
            a = strtoul(((struct string*)asgElf1->data)->c_str, NULL, 10);
            b = strtoul(((struct string*)asgElf1->next->data)->c_str, NULL, 10);
            c = strtoul(((struct string*)asgElf2->data)->c_str, NULL, 10);
            d = strtoul(((struct string*)asgElf2->next->data)->c_str, NULL, 10);
            
            bool overlaps = false;
            if(a < c) {
                if(b >= c)
                    overlaps = true;
            } else if(c < a) {
                if(d >= a)
                    overlaps = true;
            } else
                overlaps = true;
            
            if(overlaps)
                overlappingPairs++;
            
            releaseString(str);
            releaseAllDelegateList((struct list*)assignments, &relString);
        } while(!feof(f));
        
        printf("Overlapping pairs: %ld\n", overlappingPairs);
        
        fclose(f);
}

