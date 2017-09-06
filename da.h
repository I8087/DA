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

 /* Make sure we don't redfine everything. */
 #ifndef DA_H
 #define DA_H

 /* Dynamic array structure. */
 typedef struct DA {
     int *heap;
     size_t size;
     size_t inc;
     size_t len;
 } DA;

/* Main dynamic array functions. */
void DA_init(DA *list, size_t size);
void DA_deinit(DA *list);
void DA_check(DA *list);
int DA_append(DA *list, int element);
int DA_get(DA *list, int index);
int DA_insert(DA *list, int index, int element);
int DA_delete(DA *list, int index);
void DA_remove(DA *list, int element);
int DA_pop(DA *list);
int DA_count(DA *list, int element);
void DA_copy(DA *list1, DA *list2);
int DA_compare(DA *list1, DA *list2);
void DA_reverse(DA *list);
void DA_sort(DA *list);
void DA_sortback(DA *list);
int DA_find(DA* list, int element);
int DA_findlast(DA *list, int element);
void DA_extend(DA *list1, DA *list2);
void DA_merge(DA *list1, DA *list2);
void DA_split(DA *list1, DA *list2, int index);
void DA_print(DA *list);

/* Lazily initialize a dynamic array without giving an initial size. */
static inline DA_qinit(DA *list) {
    DA_init(list, 5);
}

/* Checks to make sure the index is accessable.*/
static inline int DA_outofbounds(DA *list, int index) {
    if (list->len < index) return 1;
    return 0;
}

/* Returns the number of elements in the dynamic array. */
static inline int DA_len(DA *list) {
    return list->len;
}

#endif
