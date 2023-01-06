//
//  list.h
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-26.
//

#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>

struct list {
    struct list* next;
    struct list* prev;
    
    size_t len;
    void* data;
};

/// Create first entry in new list. Entry will be empty
/// - Returns: new `struct list*` entry with no data and no linked entries..
struct list* initList(void);

/// Create first entry in new list, with supplied data of len size
/// - Parameter data: User-supplied data this `struct list*` entry shall point to
/// - Parameter len: Length of user-supplied data (in bytes)
/// - Returns: New `struct list*`
struct list* initWithList(void* data, size_t len);

/// Free memory for one list entry
/// - Parameter list: `struct list*` entry to release. `list->data` has to be freed by user.
/// - Returns: true if call succeeded
bool releaseList(struct list* list);

/// Release memory for all linked list entries
/// - Parameter list: `struct list*` to release. All linked entries will be released. `list->data` in each entry has to be freed by user.
/// - Returns: true if call succeeded
bool releaseAllList(struct list* list);

/// Free memory for one list entry, and call supplied function with data as parameter
/// - Parameter list: `struct list*` entry. Call `delegate` function with `list->data` as parameter, then free `list`,
/// - Parameter delegate: Delegate function, presumably to free/cleanup. Called before list entry is `free`´d
/// - Returns: true if call succeeded
bool releaseDelegateList(struct list* list, void (*delegate)(void* data));

/// Free memory for all linked list entries, and call supplied function with data for each one
/// - Parameter list: Call `delegate` function on each `struct list*` entry with `list->data` as parameter, then free `list`,
/// - Parameter delegate: Delegate function, presumably to free/cleanup. Called before list entry is `free`´d
/// - Returns: true if call succeeded for all entries
bool releaseAllDelegateList(struct list* list, void (*delegate)(void* data));

/// Add new entry at the end of list, with supplied data of len size
/// - Parameter list: `struct list*` to append new entry to
/// - Parameter data: User-supplied data this `struct list*` entry shall point to
/// - Parameter len: Length of `data`, in bytes
/// - Returns New `struct list*` appended to the end of `list`.
struct list* appendToList(struct list* list, void* data, size_t len);

/// Add new entry at the beginning of list, with supplied data of len size
/// - Parameter list: `struct list*` to prepend new entry to
/// - Parameter data: User-supplied data this `struct list*` entry shall point to
/// - Parameter len: Length of `data`, in bytes
/// - Returns New `struct list*` prepended before of `list`.
struct list* prependToList(struct list* list, void* data, size_t len);

/// Add new entry at the end of list, with supplied data of len size. An error will be asserted if list does not have an entry at index already.
/// - Parameter list: `struct list*` to insert new entry into
/// - Parameter data: User-supplied data this `struct list*` entry shall point to
/// - Parameter len: Length of `data`, in bytes
/// - Parameter index: Index where to insert new `struct list*` entry
/// - Returns New `struct list*` inserted into `list` at index `index`.
struct list* insertInList(struct list* list, void* data, size_t len, uint index);

/// Retrieve the last entry in the list
/// - Parameter list:`struct list*`
/// - Returns: Last entry in list containing `list`
const struct list* getLastList(const struct list* list);

/// Retrieve first entry in list
/// - Parameter list:`struct list*`
/// - Returns: First entry in list containing `list`
const struct list* getFirstList(const struct list* list);

/// Get entry at given index. List will always be traversed to start from the first entry.
/// - Parameter list: `struct list*` to search
/// - Parameter index: Index where to insert new `struct list*` entry
/// - Returns: Entry at index `index` counting from start of  `list`. If `index` is greater than the number of elements in the list plus one, NULL is returned.
const struct list* getAtIndexList(const struct list* list, uint index);

/// Get number of elements in list
/// - Parameter list: `struct list*`
/// - Returns: Number of linked entries
size_t countList(const struct list* list);

#endif /* list_h */
