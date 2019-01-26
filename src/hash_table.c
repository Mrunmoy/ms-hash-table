/*
 * @file hash_table.c
 * @author Mrunmoy Samal
 * @date 28 Dec 2018
 * @brief This is the implementation file for simple hash table.
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
 * Source of inspiration:
 *  \ref http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
 */


/*************************************************************************
*   Include Files
*************************************************************************/

#include <limits.h>
#include <stdio.h>
#include "hash_table.h"


/*************************************************************************
*   Private Defines
*************************************************************************/
#define MULTIPLIER (97)


/*************************************************************************
*   Private Macros
*************************************************************************/


/*************************************************************************
*   Private Data Types
*************************************************************************/


/*************************************************************************
*   Private Function Prototypes
*************************************************************************/
static hash_item_ptr create_new_hash_item(int key, int value);
static void destroy_hash_item(hash_item_ptr p_hash_item);
static unsigned long get_hash(int key);


/*************************************************************************
*   Private Function Definition
*************************************************************************/

/// \brief get_hash.
///        This function calculates a hash using a integer key
/// \param key. Integer key on which has is to be calculated
/// \return calculated integer hash
static unsigned long get_hash(int key)
{
    unsigned const char *us;
    unsigned long h;
    h = 0;

    for(;key;) {
        h = h * MULTIPLIER + ((key >> 1) & 0xFF);
        key >>= 1;
    }
    return h;
}

/// \brief create_new_hash_item.
///                 This function creates a new hash_item.
/// \param key.     item's key.
/// \param value.   items's value
/// \return         dynamically allocated hash item.
static hash_item_ptr create_new_hash_item(int key, int value)
{
    hash_item_ptr p_hash_item = (hash_item_ptr) malloc(sizeof(hash_item_t));
    if (p_hash_item)
    {
        p_hash_item->key    = key;
        p_hash_item->value  = value;
    }

    return p_hash_item;
}

/// \brief destroy_hash_item.
///        Deallocates memory for hash item
/// \param p_hash_item. item to be released.
static void destroy_hash_item(hash_item_ptr p_hash_item)
{
    if (p_hash_item)
    {
        free(p_hash_item);
    }
}


/*************************************************************************
*   Public Function Definition
*************************************************************************/

/// \brief create_new_hash_table.
///                         Creates a new hash table.
/// \param hash_table_size. size of hash table to be created.
/// \return                 newly allocated hash table.
hash_table_ptr create_new_hash_table(size_t hash_table_size)
{
    hash_table_ptr p_hash_table = (hash_table_ptr) malloc(sizeof(hash_table_t));

    if (p_hash_table)
    {
        p_hash_table->size        = (int)hash_table_size;
        p_hash_table->num_items   = 0;
        p_hash_table->pp_item_list = calloc(hash_table_size, sizeof(hash_item_ptr));
    }

    return p_hash_table;
}

/// \brief destroy_hash_table.
///                         Releases memory for a hash table and all it's items.
/// \param p_hash_table.    hash table to be deleted.
void destroy_hash_table(hash_table_ptr p_hash_table)
{
    if (p_hash_table)
    {
        for (int i = 0; i < p_hash_table->size; i++) {
            if (p_hash_table->pp_item_list[i]) {
                destroy_hash_item(p_hash_table->pp_item_list[i]);
            }
        }
    }
    // release item list memory
    free(p_hash_table->pp_item_list);

    // release hash table memory
    free(p_hash_table);
}

/// \brief insert_into_hash_table.
///                         Inserts a key-value pair into hash table
/// \param p_hash_table.    hash table to insert into
/// \param key.             key of item
/// \param value.           value of item
/// \return                 true if successfully inserted. false if failed.
bool insert_into_hash_table(hash_table_ptr p_hash_table, int key, int value)
{
    bool result = false;
    do
    {
        hash_item_ptr p_new_item = NULL;
        int hash_index = INT_MAX;

        if (!p_hash_table) break;

        p_new_item = create_new_hash_item(key, value);
        if (!p_new_item) break;

        hash_index = get_hash(key) % p_hash_table->size;

        //printf("Inserting into hash index %d\n", hash_index);

        // add to the beginning of list at index hash_index
        p_new_item->p_next                     = p_hash_table->pp_item_list[hash_index];
        p_hash_table->pp_item_list[hash_index] = p_new_item;

        p_hash_table->num_items++;

        result = true;
    } while(0);

    return result;
}

/// \brief is_item_in_hash_table.
///                         search key in hash table.
/// \param p_hash_table.    pointer to hash table to search.
/// \param key.             key to search
/// \param p_value.         pointer to return value in.
/// \return                 true if successful, false if not found.
bool is_item_in_hash_table(hash_table_ptr p_hash_table, const int key, int *p_value)
{
    bool result = false;

    do
    {
        if (!p_hash_table) break;

        hash_item_ptr p_item = NULL;

        for (p_item = p_hash_table->pp_item_list[get_hash(key) % p_hash_table->size]; p_item != NULL; p_item = p_item->p_next)
        {
            if (key == p_item->key)
            {
                /* got it */
                *p_value = p_item->value;
                result = true;
                break;
            }
        }
    } while(0);

    return result;
}

/// \brief delete_from_hash_table.
///                         delete a key-value pair from the hash table.
/// \param p_hash_table.    pointer to hash table.
/// \param key.             key to delete.
/// \return                 true if successfully deleted, false if fails
bool delete_from_hash_table(hash_table_ptr p_hash_table, int key)
{
    bool result = false;

    do
    {
        if (!p_hash_table) break;

        hash_item_ptr * p_prev = NULL;
        hash_item_ptr p_curr = NULL;

        for (p_prev = &(p_hash_table->pp_item_list[get_hash(key) % p_hash_table->size]);
             *p_prev != NULL;
             p_prev = &((*p_prev)->p_next))
        {
            if ( key == (*p_prev)->key)
            {
                /* got it */
                p_curr = *p_prev;
                *p_prev = p_curr->p_next;

                destroy_hash_item(p_curr);
                result = true;
                break;
            }
        }

    } while(0);

    return result;
}




