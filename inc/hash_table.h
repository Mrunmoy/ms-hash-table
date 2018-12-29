/*
 * @file hash_table.h
 * @author Mrunmoy Samal
 * @date 28 Dec 2018
 * @brief This is the interface file for simple hash table implementaiton.
 *
 *  LICENSE:-
 *  The MIT License (MIT)
 *  Copyright (c) 2016 Mrunmoy Samal
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom
 *  the Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall
 *  be included in all copies or substantial portions of the
 *  Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 *  OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif


/*************************************************************************
*   Include Files
*************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*************************************************************************
*   Public Defines
*************************************************************************/


/*************************************************************************
*   Public Macros
*************************************************************************/


/*************************************************************************
*   Public Data Types
*************************************************************************/

/**
 * @brief hash_item_t.
 * Structure definition for hash item.
 *
 * It contains
 * - key (integer).
 * - value (integer).
 * - pointer to next hash item in the list (for collision resolution)
 */
typedef struct hash_item_t
{
    int key;
    int value;
    struct hash_item_t * p_next;
}hash_item_t, * hash_item_ptr;


/**
 * @brief hash_table_t.
 * Structure definition for hash table.
 *
 * It contains the
 * - total size of this hash table.
 * - number of elements inserted in the table.
 * - list of arrays of hash items (for collision resolution.)
 */
typedef struct hash_table_t
{
    int size;                       /**< size. total size of hash table. hash_table_t#size. */
    int num_items;                  /**< num_items. totall number of elements present in the hash table.
                                      *  hash_table_t#num_items. */
    hash_item_ptr * pp_item_list;   /**< pp_item_list. pointer to array of hash_items pointers.
                                      *  hash_table_t#pp_item_list. */
}hash_table_t, * hash_table_ptr;


/*************************************************************************
*   Public Function Prototypes
*************************************************************************/

/// \brief create_new_hash_table.
///                         Creates a new hash table.
/// \param hash_table_size. size of hash table to be created.
/// \return                 newly allocated hash table.
hash_table_ptr create_new_hash_table(size_t hash_table_size);

/// \brief destroy_hash_table.
///                         Releases memory for a hash table and all it's items.
/// \param p_hash_table.    hash table to be deleted.
void destroy_hash_table(hash_table_ptr p_hash_table);

/// \brief insert_into_hash_table.
///                         Inserts a key-value pair into hash table
/// \param p_hash_table.    hash table to insert into
/// \param key.             key of item
/// \param value.           value of item
/// \return                 true if successfully inserted. false if failed.
bool insert_into_hash_table(hash_table_ptr p_hash_table, int key, int value);

/// \brief is_item_in_hash_table.
///                         search key in hash table.
/// \param p_hash_table.    pointer to hash table to search.
/// \param key.             key to search
/// \param p_value.         pointer to return value in.
/// \return                 true if successful, false if not found.
bool is_item_in_hash_table(hash_table_ptr p_hash_table, const int key, int *p_value);

/// \brief delete_from_hash_table.
///                         delete a key-value pair from the hash table.
/// \param p_hash_table.    pointer to hash table.
/// \param key.             key to delete.
/// \return                 true if successfully deleted, false if fails
bool delete_from_hash_table(hash_table_ptr p_hash_table, int key);


#ifdef __cplusplus
}
#endif


#endif //HASH_TABLE_H
