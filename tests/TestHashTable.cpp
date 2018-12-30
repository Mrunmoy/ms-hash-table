/* @file TestHashTable.cpp
 * @author Mrunmoy Samal
 * @date 29 12 2018
 * @brief Unit Test definitions for hash table.
 *
 *  LICENSE:-
 *  The MIT License (MIT)
 *  Copyright (c) 2018 Mrunmoy Samal
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
 */


/*************************************************************************
*   Include Files
*************************************************************************/
#include <string.h>
#include <time.h>
#include "CppUTest/TestHarness.h"
#include "hash_table.h"
#include "HashTableTester.h"


/*************************************************************************
*   Private Defines
*************************************************************************/
#define HASH_TABLE_SIZE (100)

/*************************************************************************
*   Private  Macros
*************************************************************************/


/*************************************************************************
*   Private Data Types
*************************************************************************/


/*************************************************************************
*   Private Function Prototypes
*************************************************************************/


/*************************************************************************
*   Private Function Definitions
*************************************************************************/
HashTableTester::HashTableTester(size_t size)
{
    pHashTable = create_new_hash_table(size);
}

HashTableTester::~HashTableTester()
{
    if (pHashTable)
    {
        destroy_hash_table(pHashTable);
    }
}

bool HashTableTester::add(int key, int value)
{
    return insert_into_hash_table(pHashTable, key, value);
}

bool HashTableTester::exists(const int key, int *p_value)
{
    return is_item_in_hash_table(pHashTable, key, p_value);
}

bool HashTableTester::remove(int key)
{
    return delete_from_hash_table(pHashTable, key);
}


/*************************************************************************
*   Private Variable Definitions
*************************************************************************/

TEST_GROUP(PositiveTestCases)
{
    void setup()
    {
        time_t t;

        /* Initializes random number generator */
        srand((unsigned) time(&t));
    }
};


/*************************************************************************
*   Public Function Definitions
*************************************************************************/

TEST(PositiveTestCases, CreateHashTable)
{
    HashTableTester * pTester = new HashTableTester(HASH_TABLE_SIZE);
    CHECK(NULL != pTester);
    delete pTester;
}

TEST(PositiveTestCases, AddOneItem)
{
    HashTableTester * pTester = new HashTableTester(HASH_TABLE_SIZE);
    CHECK((NULL != pTester));

    CHECK((true == pTester->add(1, 12)));
    delete pTester;
}

TEST(PositiveTestCases, AddTwoItems)
{
    HashTableTester * pTester = new HashTableTester(HASH_TABLE_SIZE);
    CHECK(NULL != pTester);

    CHECK((true == pTester->add(1, 12)));
    CHECK((true == pTester->add(2, 22)));

    delete pTester;
}

TEST(PositiveTestCases, AddMaxItems)
{
    HashTableTester * pTester = new HashTableTester(HASH_TABLE_SIZE);
    CHECK(NULL != pTester);

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        CHECK((true == pTester->add(i + 1, rand() % HASH_TABLE_SIZE)));
    }

    delete pTester;
}

TEST(PositiveTestCases, AddOneItemAndDelete)
{
    HashTableTester * pTester = new HashTableTester(HASH_TABLE_SIZE);
    CHECK(NULL != pTester);

    CHECK((true == pTester->add(1, rand() % HASH_TABLE_SIZE)));
    CHECK((true == pTester->remove(1)));

    delete pTester;
}

TEST(PositiveTestCases, AddMaxItemAndDeleteAll)
{
    HashTableTester * pTester = new HashTableTester(HASH_TABLE_SIZE);
    CHECK(NULL != pTester);

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        CHECK((true == pTester->add(i + 1, rand() % HASH_TABLE_SIZE)));
    }

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        CHECK((true == pTester->remove(i + 1)));
    }

    delete pTester;
}

TEST(PositiveTestCases, AddMaxItemsAndLookup)
{
    int key_list[HASH_TABLE_SIZE] = {0};
    HashTableTester * pTester = new HashTableTester(HASH_TABLE_SIZE);
    CHECK(NULL != pTester);

    // Add N items
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        key_list[i] = rand() % HASH_TABLE_SIZE;
        pTester->add(i + 1, key_list[i]);
    }

    // Lookup added items to see if they exists
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        pTester->add(i + 1, rand() % HASH_TABLE_SIZE);
    }

    delete pTester;
}

