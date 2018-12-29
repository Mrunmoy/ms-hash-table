#include <stdio.h>
#include <time.h>
#include "hash_table.h"

#define HASH_TABLE_SIZE (100)

static void test(void);

int main() {

    test();

    return 0;
}

static void test(void)
{
    time_t t;
    int key_list[HASH_TABLE_SIZE] = {0};
    do
    {
        hash_table_ptr pHashTable = create_new_hash_table(HASH_TABLE_SIZE);

        if (!pHashTable) break;

        /* Intializes random number generator */
        srand((unsigned) time(&t));

        // initialize
        for (int i= 0; i < HASH_TABLE_SIZE; i++)
        {
            key_list[i] = rand() % HASH_TABLE_SIZE;
            printf("%d. Inserting item %d with value %d into hash table!\n", i+1, i, key_list[i]);
            insert_into_hash_table(pHashTable, i, key_list[i]);
        }

        for (int i= 0; i < HASH_TABLE_SIZE; i++)
        {
            int val = rand();
            bool result = is_item_in_hash_table(pHashTable, i, &val);

            if (result && (key_list[i] == val))
            {
                printf("%d. Found item %d\n", i+1, i);
            }
            else
            {
                printf("%d. Item %d not found!\n", i+1, i);
            }
        }

        destroy_hash_table(pHashTable);
    } while (0);
}