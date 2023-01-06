//
//  string.c
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-25.
//

#include "string.h"

struct string* allocString(size_t len) {
    
    assert(len > 0);
    
    struct string* str = malloc(sizeof(struct string));
    assert(str != NULL);
    
    str->len = len;
    str->c_str = malloc(len);
    
    memset(str->c_str, '\0', len);
    
    return str;
}

struct string* initString(size_t len, const char* data) {
    assert(data != NULL);
    assert(len > 0);
    
    struct string* str = allocString(len);
    
    size_t idx = 0;
    do {
        str->c_str[idx] = data[idx];
    } while(data[idx] != '\0' && ++idx < len - 1);
    str->c_str[len - 1] = '\0';
    
    return str;
}

void releaseString(struct string* str) {
    assert(str != NULL);
    free(str);
}

struct string* replaceInString(const struct string* str, char find, char replaceWith) {
    assert(str != NULL);
    
    int idx = findIndexInString(str, find);
    
    struct string* newStr = initString(str->len, str->c_str);
        
    while(idx != -1) {
        newStr->c_str[idx] = replaceWith;
        idx = findIndexInString(newStr, find);
    }
    
    return newStr;
}

char* findCharInString(const struct string* str, char c) {
    return strchr(str->c_str, (int)(str->len));
}

int findIndexInString(const struct string* str, char c) {
    assert(str != NULL);
    
    for(uint i = 0; i < str->len; i++) {
        if(str->c_str[i] == c)
            return i;
    }

    return -1;
}

const struct list* splitString(const struct string* inputStr, char separator) {
    assert(inputStr != NULL);
    
    struct string* localStr = (struct string*) inputStr;
    
    if(localStr->len == 0)
        return initList();
    
    if(localStr->len == 1) {
        if(findCharInString(localStr, separator) == NULL)
            return initWithList(localStr, STRING_LEN(localStr));
        else
            return initWithList(allocString(1), STRING_LEN(localStr));
    }
    
    if(findIndexInString(localStr, separator) == -1)
        return initWithList(localStr, STRING_LEN(localStr));
    
    struct list* list = NULL;
    uint i = 0;
    uint lastIdx = 0;
    _Bool hasReadNonSeparators = false;
    
    for(i = 0; i < localStr->len; i++) {
        if(localStr->c_str[i] == separator) {
            if(hasReadNonSeparators) {
                struct string* s = initString(i - lastIdx + 1, &localStr->c_str[lastIdx]);
                list = appendToList(list, s, STRING_LEN(s));
                lastIdx = i + 1;
                hasReadNonSeparators = false;
            }
        } else {
            if(!hasReadNonSeparators)
                lastIdx = i;
            hasReadNonSeparators = true;
        }
    }
    
    if(hasReadNonSeparators) {
        struct string* s = initString(i - lastIdx, &localStr->c_str[lastIdx]);
        list = appendToList(list, s, STRING_LEN(s));
    }
    
    return getFirstList(list);
}

