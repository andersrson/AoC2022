//
//  list.c
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-26.
//

#include "list.h"

struct list* initList(void) {
    struct list* l = malloc(sizeof(struct list));
    
    assert(l != NULL);
    
    l->data = NULL;
    l->len = 0;
    l->next = NULL;
    l->prev = NULL;
    
    return l;
}

struct list* initWithList(void* data, size_t len) {
    struct list* l = initList();
    
    assert(l != NULL);
    
    l->data = data;
    l->len = len;
    
    return l;
}

bool releaseList(struct list* list) {
    assert(list != NULL);
    
    free(list);
    
    return true;
}

bool releaseAllList(struct list* list) {
    assert(list != NULL);
    
    struct list* tmp = list;
    do {
        tmp = list->next;
        releaseList(list);
        list = tmp;
    } while(list != NULL);
    
    return true;
}

bool releaseDelegateList(struct list* list, void (*delegate)(void* data)) {
    assert(list != NULL);
    assert(delegate != NULL);
    
    delegate(list->data);
    releaseList(list);
    
    return true;
}

bool releaseAllDelegateList(struct list* list, void (*delegate)(void* data)) {
    assert(list != NULL);
    assert(delegate != NULL);
    
    bool result = true;
    
    struct list* tmp = list;
    do {
        tmp = list->next;
        delegate(list->data);
        
        releaseList(list);
        list = tmp;
        
    } while(list != NULL);
    
    return result;
}

struct list* appendToList(struct list* list, void* data, size_t len){
    if(list == NULL)
        return initWithList(data, len);
    
    struct list* entry = initWithList(data, len);
    struct list* last = (struct list*) getLastList(list);
    last->next = entry;
    entry->prev = last;
    
    return entry;
}

struct list* appendEntryToList(struct list* list, struct list* entry) {
    assert(entry != NULL);
    assert(entry->prev == NULL);
    
    if(list == NULL)
        return entry;
    
    struct list* last = (struct list*) getLastList(list);
    assert(last->next == NULL);
    
    last->next = entry;
    entry->prev = last;
    
    return entry;
}

struct list* prependToList(struct list* list, void* data, size_t len) {
    if(list == NULL)
        return initWithList(data, len);
    
    struct list* entry = initWithList(data, len);
    struct list* first = (struct list*) getFirstList(list);
    first->prev = entry;
    entry->next = first;
    
    return entry;
}

struct list* prependEntryToList(struct list* list, struct list* entry) {
    assert(entry != NULL);
    assert(entry->next == NULL);
    
    if(list == NULL)
        return entry;
    
    struct list* first = (struct list*) getFirstList(list);
    assert(first->prev == NULL);
    
    first->prev = entry;
    entry->next = first;
    
    return entry;
}

struct list* insertInList(struct list* list, void* data, size_t len, uint index) {
    assert(list != NULL);
    
    struct list* atIndex = (struct list*) getAtIndexList(list, index);
    
    assert(atIndex != NULL);
    
    struct list* entry = initWithList(data, len);
    
    entry->next = atIndex;
    entry->prev = atIndex->prev;
    
    if(atIndex->prev != NULL) {
        entry->prev->next = entry;
    }
    
    atIndex->prev = entry;
    
    return entry;
}

struct list* insertEntryInList(struct list* list, struct list* entry, uint index) {
    assert(list != NULL);
    assert(entry->prev == NULL);
    assert(entry->next == NULL);
    
    struct list* atIndex = (struct list*) getAtIndexList(list, index);
    
    assert(atIndex != NULL);
    
    entry->next = atIndex;
    entry->prev = atIndex->prev;
    
    if(atIndex->prev != NULL) {
        entry->prev->next = entry;
    }
    
    atIndex->prev = entry;
    
    return entry;
}

struct list* removeEntryFromList(struct list* entry) {
    assert(entry != NULL);
    
    if(entry->prev != NULL)
        entry->prev->next = entry->next;
    if(entry->next != NULL)
        entry->next->prev = entry->prev;
    
    entry->prev = NULL;
    entry->next = NULL;
    
    return entry;
}

struct list* takeList(struct list* list, size_t count) {
    assert(list != NULL);
    
    size_t listCount = countList(list);
    
    assert(listCount >= count);
    
    if(listCount == count)
        return list;
    
    struct list* cut = getAtIndexList(list, (uint)count);
    
    assert(cut->prev != NULL);
    assert(cut->prev->next == cut);
    
    cut->prev->next = NULL;
    cut->prev = NULL;
    
    return cut;
}

struct list* takeTailList(struct list* list, size_t count) {
    assert(list != NULL);
    
    size_t listCount = countList(list);
    
    assert(listCount >= count);
    
    if(listCount == count)
        return list;
    
    struct list* cut = getAtIndexList(list, (uint)(listCount - count));
    
    assert(cut->prev != NULL);
    assert(cut->prev->next == cut);
    
    cut->prev->next = NULL;
    cut->prev = NULL;
    
    return cut;
}

struct list* getLastList(const struct list* list) {
    assert(list != NULL);
    
    struct list* last = (struct list*) list;
    while(last->next != NULL)
        last = last->next;
    
    return last;
}

struct list* getFirstList(const struct list* list) {
    assert(list != NULL);
    
    struct list* first = (struct list*) list;
    while(first->prev != NULL)
        first = first->prev;
    
    return first;
}

struct list* getAtIndexList(const struct list* list, uint index) {
    assert(list != NULL);
    
    struct list* current = getFirstList(list);
    uint idx = 0;
    while(current != NULL) {
        if(idx == index)
            return current;
        current = current->next;
        idx++;
    }
    
    return NULL;
}

size_t countList(const struct list* list) {
    assert(list != NULL);
    
    if(list->prev != NULL)
        list = getFirstList(list);
    
    size_t count = 0;
    do {
        count++;
        list = list->next;
    } while(list != NULL);
    
    return count;
}
