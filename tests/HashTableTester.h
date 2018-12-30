/* @file HashTableTester.h
 * @author Mrunmoy Samal
 * @date 29 12 2018
 * @brief Tester Data structure definition.
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

#ifndef HASH_TABLE_HASHTABLETESTER_H
#define HASH_TABLE_HASHTABLETESTER_H

/*************************************************************************
*   Include Files
*************************************************************************/
#include <CppUTest/TestHarness.h>
#include "CppUTest/TestHarness_c.h"
#include "CppUTestExt/MockSupport.h"
#include "hash_table.h"

/*************************************************************************
*   Public Defines
*************************************************************************/


/*************************************************************************
*   Public Macros
*************************************************************************/


/*************************************************************************
*   Public Data Types
*************************************************************************/
class HashTableTester
{
    hash_table_ptr pHashTable = NULL;

public:
    HashTableTester(size_t size);
    ~HashTableTester();

    bool add(int key, int value);
    bool exists(const int key, int *p_value);
    bool remove(int key);
};

/*************************************************************************
*   Public Function Prototypes
*************************************************************************/




#endif //HASH_TABLE_HASHTABLETESTER_H
