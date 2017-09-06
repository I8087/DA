/**
 * A small, portable, and powerful C library for dynamic arrays.
 *
 * Copyright (c) 2017, Nathaniel Yodock
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdlib.h>
#include "da.h"

/* Initializes a dynamic array. */
void DA_init(DA *list, size_t size) {
    list->heap = (int*) malloc(size * sizeof(int));
    list->size = size;
    list->inc = size;
    list->len = 0;
}

/* Deinitializes a dynamic array. */
void DA_deinit(DA *list) {
    free(list->heap);
    list->heap = NULL;
    list->size = 0;
    list->inc = 0;
    list->len = 0;
}

/**
 * Checks to see if the dynamic array is too large or too small for its
 * respective memory allocation and changes it, if neccesary.
 */
void DA_check(DA *list) {
    if (list->size == list->len) {
        list->size += list->inc;
        list->heap = (int *) realloc(list->heap, list->size * sizeof(int));
    } else if ((list->len + list->inc) < list->size) {
        list->size -= list->inc;
        list->heap = (int *) realloc(list->heap, list->size * sizeof(int));
    }
}

/* Appends an element to the end of a dynamic array. */
int DA_append(DA *list, int element) {
    DA_check(list);
    list->heap[list->len++] = element;
    return list->len-1;
}

/* Safely gets an element, returns -1 if the index is out of bounds. */
int DA_get(DA *list, int index) {
    if (DA_outofbounds(list, index)) return -1;
    return list->heap[index];
}

/* Insert an element into the dynamic array at a given point. */
int DA_insert(DA *list, int index, int element) {
    if (DA_outofbounds(list, index)) return -1;
    list->len++;
    DA_check(list);
    for (int i = list->len; i > index; i--) list->heap[i] = list->heap[i-1];
    list->heap[index] = element;
    return 0;
}

/* Removes an element from the dynamic array at a given index. */
int DA_delete(DA *list, int index) {
    if (DA_outofbounds(list, index)) return -1;
    for (int i = index; i < list->len; i++) list->heap[i] = list->heap[i+1];
    list->len--;
    DA_check(list);
    return 0;
}

/* Removes an element and its duplicates from the dynamic array, if they exist. */
void DA_remove(DA *list, int element) {
    for (int i = 0; i < list->len; i++) {
        if (list->heap[i] == element) {
            DA_delete(list, i);
            i--;
        }
    }
}

/**
 * Gets the top most element, removes it from the dynamic array,
 * and then returns it.
 */
int DA_pop(DA *list) {
    if (!list->len) return -1;
    int ret = DA_get(list, --list->len);
    DA_check(list);
    return ret;
}

/* Returns the number of times an element is in the dynamic array. */
int DA_count(DA *list, int element) {
    int count = 0;
    for (int i = 0; i < list->len; i++) if (list->heap[i] == element) count++;
    return count;
}

/* Copies list1 into list2. Lists are independent of each other after creation. */
void DA_copy(DA *list1, DA *list2) {
    if (list2->len) DA_deinit(list2);
    DA_init(list2, list1->size);
    for (int i = 0; i < list1->len; i++) DA_append(list2, list1->heap[i]);
}

/* Compares two dynamic arrays and returns a boolean of their elements. */
int DA_compare(DA *list1, DA *list2) {
    if (list1->len != list2->len) return 0;
    for (int i = 0; i < list1->len; i++) if (list1->heap[i] != list2->heap[i]) return 0;
    return 1;
}

/* Reverses the elements in a dynamic array. */
void DA_reverse(DA *list) {
    int holder;
    int halfway = list->len/2;
    for (int i = 0; i < halfway; i++) {
        holder = list->heap[i];
        list->heap[i] = list->heap[list->len-1-i];
        list->heap[list->len-1-i] = holder;
    }
}

/* Sorts all of the elements in a dynamic array from least to greatest. */
void DA_sort(DA *list) {
    int i = 1;
    int r = 0;
    int holder;
    for (;;) {
        if (i > list->len-1) {
            if (r) {
                r = 0;
                i = 1;
            } else {
                return;
            }
        }

        if (list->heap[i] < list->heap[i-1]) {
            r = 1;
            holder = list->heap[i];
            list->heap[i] = list->heap[i-1];
            list->heap[i-1] = holder;
            i--;
        }
        i++;
    }
}

/* Sorts all of the elements in a dynamic array from greatest to least. */
void DA_sortback(DA *list) {
    DA_sort(list);
    DA_reverse(list);
}

/* Finds the first instance of an element and returns its index. */
int DA_find(DA* list, int element) {
    for (int i = 0; i < list->len; i++) if (list->heap[i] == element) return i;
    return -1;
}

/* Finds the last instance of an element and returns its index. */
int DA_findlast(DA *list, int element) {
    int index = -1;
    for (int i = 0; i < list->len; i++) if (list->heap[i] == element) index = i;
    return index;
}

/* Copys list2 and appends all of its elements to list1. */
void DA_extend(DA *list1, DA *list2) {
    for (int i = 0; i < list2->len; i++) DA_append(list1, list2->heap[i]);
}

/**
 * Copys list2 and appends all of its elements to list1,
 * then deinitializes list2.
 */
void DA_merge(DA *list1, DA *list2) {
    DA_extend(list1, list2);
    DA_deinit(list2);
}

/**
 * Splits list1 at the given index, putting the first half of elements into
 * list1 and the other half of elements into list2.
 */
void DA_split(DA *list1, DA *list2, int index) {
    DA_deinit(list2);
    if (index > list1->len) index = list1->len;
    DA_init(list2, list1->len-index);

    while (index < list1->len) {
        DA_append(list2, list1->heap[index]);
        DA_delete(list1, index);
    }
}

/* Displays the dynamic array via stdout. */
void DA_print(DA *list) {
    putchar('{');
    for (int i=0; i<list->len; i++) {
        printf("%d", DA_get(list, i));
        if (i != list->len-1) printf(", ");
    }
    printf("}\n");
}
