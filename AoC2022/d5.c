//
//  d5.c
//  AoC2022
//
//  Created by Anders Runesson on 2023-01-07.
//

#include "d5.h"

void relString2(void* str) {
    releaseString(str);
}

void printStacks(struct list* stacks[], size_t stackCount) {
    
    for(int i = 0; i < stackCount; i++) {
        printf("Stack %d: ", i + 1);
        struct list* stack = stacks[i];
        
        if(stack == NULL) {
            printf("(empty stack) \n");
            continue;
        }
        
        for(int k = 0; k < countList(stack); k++) {
            struct list* crateListEntry = getAtIndexList(stack, k);
            struct string* crateLabel = (struct string*) crateListEntry->data;
            printf(" [%s] ", crateLabel->c_str);
        }
        printf("\n");
    }
}

void Day5Part1(void) {
    const char* dataFile = "./Resources/input-d5.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    char line[BUFSIZE];
    memset(line, '\0', BUFSIZE);
    
    struct list* stackStrings = NULL;
    struct list* opStrings = NULL;
    
    size_t stackCount = 0;
    do {
        char* getReturn = fgets(line, BUFSIZE, f);
        if(getReturn == NULL)
            break;
        size_t lineLen = strnlen(getReturn, BUFSIZE); // If successful, will contain trailing newline
        
        struct string* str = NULL;
        if(strchr(getReturn, '[') != NULL) {
            str = initString(lineLen, getReturn);
            stackStrings = appendToList(stackStrings, str, STRING_LEN(str));
        } else if(strstr(getReturn, "move") != NULL) {
            str = initString(lineLen, getReturn);
            opStrings = appendToList(opStrings, str, STRING_LEN(str));
        } else if(strchr(getReturn, '1') != NULL) {
            str = initString(lineLen, getReturn);
            const struct list* stackLabels = splitString(str, ' ');
            const struct list* lastStack = getLastList(stackLabels);
            const struct string* lastStackNo = (const struct string*) lastStack->data;
            stackCount = strtoul(lastStackNo->c_str, NULL, 10);
            
            if(str != NULL) {
                releaseString(str);
                str = NULL;
            }
        }
    } while(!feof(f));
    
    stackStrings = getFirstList(stackStrings);
    opStrings = getFirstList(opStrings);
    
    struct list* stacks[stackCount];
    for(int i = 0; i < stackCount; i++)
        stacks[i] = NULL;
    
    struct list* currentStackLayer = stackStrings;
    do {
        int bracket = 0;
        struct string* csl = (struct string*) currentStackLayer->data;
        bracket = findIndexOffsetInString(csl, '[', bracket);
        while(bracket != -1) {
            struct string* crateLabel = initString(2, &csl->c_str[bracket + 1]);
            struct list* stack = stacks[bracket / 4];
            
            stacks[bracket / 4] = prependToList(stack, crateLabel, STRING_LEN(crateLabel));
            
            bracket = findIndexOffsetInString(csl, '[', ++bracket);
        }
        currentStackLayer = currentStackLayer->next;
    } while(currentStackLayer != NULL);
    
    printf("Found %ld stacks: \n", stackCount);
    printStacks(stacks, stackCount);
    
    for(int i = 0; i < countList(opStrings); i++) {
        struct list* cmdEntry = getAtIndexList(opStrings, i);
        struct string* commandString = cmdEntry->data;
        
        uint moveCount = 0, sourceStack = 0, targetStack = 0;
        struct list* splits = splitString(commandString, ' ');
        uint foundNums = 0;
        for(uint k = 0; k < countList(splits); k++) {
            struct list* tokenEntry = getAtIndexList(splits, k);
            struct string* token = tokenEntry->data;
            if(isnumber(token->c_str[0])) {
                switch(foundNums++) {
                    case 0:
                        moveCount = (uint)strtoul(token->c_str, NULL, 10);
                        break;
                    case 1:
                        sourceStack = (uint)strtoul(token->c_str, NULL, 10);
                        break;
                    case 2:
                        targetStack = (uint)strtoul(token->c_str, NULL, 10);
                        break;

                }
            }
        }
        
        releaseAllDelegateList(splits, &relString2);
        
        //printf("Command data: count: %d, from: %d, to: %d\n", moveCount, sourceStack, targetStack);
        
        struct list* stackFrom = stacks[sourceStack - 1];
        struct list* stackTo = stacks[targetStack - 1];
        
        for(int i = 0; i < moveCount; i++) {
            struct list* targetCrate = getLastList(stackFrom);
            assert(targetCrate->next == NULL);
            
            if(countList(stackFrom) == 1) {
                stacks[sourceStack - 1] = NULL;
                stackFrom = NULL;
            } else
                removeEntryFromList(targetCrate);
            
            if(stackTo == NULL) {
                stacks[targetStack - 1] = targetCrate;
                stackTo = targetCrate;
            } else {
                struct list* newPrev = getLastList(stackTo);
                assert(newPrev->next == NULL);
                
                appendEntryToList(stackTo, targetCrate);
            }
        }
    }
    
    printf("After rearranging: \n");
    printStacks(stacks, stackCount);
    
    printf("Top crate labels: ");
    for(int i = 0; i < stackCount; i++) {
        struct list* top = getLastList(stacks[i]);
        struct string* label = top->data;
        printf("%s", label->c_str);
    }
    printf("\n");
    
    for(int i = 0; i < stackCount; i++)
        if(stacks[i] != NULL)
            releaseAllDelegateList(stacks[i], &relString2);
    
    releaseAllDelegateList((struct list*)stackStrings, &relString2);
    releaseAllDelegateList((struct list*)opStrings, &relString2);
    
    fclose(f);
}

void Day5Part2(void) {
    const char* dataFile = "./Resources/input-d5.txt";
    
    FILE* f = fopen(dataFile, "r");
    assert(f != NULL);
    
    char line[BUFSIZE];
    memset(line, '\0', BUFSIZE);
    
    struct list* stackStrings = NULL;
    struct list* opStrings = NULL;
    
    size_t stackCount = 0;
    do {
        char* getReturn = fgets(line, BUFSIZE, f);
        if(getReturn == NULL)
            break;
        size_t lineLen = strnlen(getReturn, BUFSIZE); // If successful, will contain trailing newline
        
        struct string* str = NULL;
        if(strchr(getReturn, '[') != NULL) {
            str = initString(lineLen, getReturn);
            stackStrings = appendToList(stackStrings, str, STRING_LEN(str));
        } else if(strstr(getReturn, "move") != NULL) {
            str = initString(lineLen, getReturn);
            opStrings = appendToList(opStrings, str, STRING_LEN(str));
        } else if(strchr(getReturn, '1') != NULL) {
            str = initString(lineLen, getReturn);
            const struct list* stackLabels = splitString(str, ' ');
            const struct list* lastStack = getLastList(stackLabels);
            const struct string* lastStackNo = (const struct string*) lastStack->data;
            stackCount = strtoul(lastStackNo->c_str, NULL, 10);
            
            if(str != NULL) {
                releaseString(str);
                str = NULL;
            }
        }
    } while(!feof(f));
    
    stackStrings = getFirstList(stackStrings);
    opStrings = getFirstList(opStrings);
    
    struct list* stacks[stackCount];
    for(int i = 0; i < stackCount; i++)
        stacks[i] = NULL;
    
    struct list* currentStackLayer = stackStrings;
    do {
        int bracket = 0;
        struct string* csl = (struct string*) currentStackLayer->data;
        bracket = findIndexOffsetInString(csl, '[', bracket);
        while(bracket != -1) {
            struct string* crateLabel = initString(2, &csl->c_str[bracket + 1]);
            struct list* stack = stacks[bracket / 4];
            
            stacks[bracket / 4] = prependToList(stack, crateLabel, STRING_LEN(crateLabel));
            
            bracket = findIndexOffsetInString(csl, '[', ++bracket);
        }
        currentStackLayer = currentStackLayer->next;
    } while(currentStackLayer != NULL);
    
    printf("Found %ld stacks\n", stackCount);
    
    for(int i = 0; i < countList(opStrings); i++) {
        struct list* cmdEntry = getAtIndexList(opStrings, i);
        struct string* commandString = cmdEntry->data;
        
        uint moveCount = 0, sourceStack = 0, targetStack = 0;
        struct list* splits = splitString(commandString, ' ');
        uint foundNums = 0;
        for(uint k = 0; k < countList(splits); k++) {
            struct list* tokenEntry = getAtIndexList(splits, k);
            struct string* token = tokenEntry->data;
            if(isnumber(token->c_str[0])) {
                switch(foundNums++) {
                    case 0:
                        moveCount = (uint)strtoul(token->c_str, NULL, 10);
                        break;
                    case 1:
                        sourceStack = (uint)strtoul(token->c_str, NULL, 10);
                        break;
                    case 2:
                        targetStack = (uint)strtoul(token->c_str, NULL, 10);
                        break;

                }
            }
        }
        
        releaseAllDelegateList(splits, &relString2);
        
        struct list* stackFrom = stacks[sourceStack - 1];
        struct list* stackTo = stacks[targetStack - 1];
        
        assert(stackFrom != NULL);
        
        size_t stackFromCount = countList(stackFrom);
        
        struct list* targetCrate = takeTailList(stackFrom, moveCount);
        if(moveCount == stackFromCount)
            stacks[sourceStack - 1] = NULL;
        
        if(stackTo == NULL)
            stacks[targetStack - 1] = targetCrate;
        else
            appendEntryToList(stackTo, targetCrate);
    }
    
    printf("After rearranging: \n");
    printStacks(stacks, stackCount);
    
    printf("Top crate labels: ");
    for(int i = 0; i < stackCount; i++) {
        struct list* top = getLastList(stacks[i]);
        struct string* label = top->data;
        printf("%s", label->c_str);
    }
    printf("\n");
    
    for(int i = 0; i < stackCount; i++)
        if(stacks[i] != NULL)
            releaseAllDelegateList(stacks[i], &relString2);
    
    releaseAllDelegateList((struct list*)stackStrings, &relString2);
    releaseAllDelegateList((struct list*)opStrings, &relString2);
    
    fclose(f);
}
