## A Simple Hash Table

A simple hash implementation of hash table data structure in C.
[Reference](http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29)

### Folder Layout

    .
    ├── build                   # Compiled files (alternatively `dist`)
    ├── inc                     # Interface Header file for using hash-table library
    ├── src                     # Hash table implementation C file 
    ├── tests                   # Automated tests 
    ├── tests                   
        ├── dependencies        # CppUTest dependent submodule
    ├── scripts                 # Useful scripts for this project
    ├── .buildkite              # Buildkite Pipeline settings                   
    ├── docker                  # Dockerfile source
    ├── LICENSE                 # MIT Licence
    └── README.md

### Library
The following functions are available in the library:

#### Create a dynamically allocated hash table
```- hash_table_ptr create_new_hash_table(size_t hash_table_size);```

#### Release hash table and all it's item's memory after use
```- void destroy_hash_table(hash_table_ptr p_hash_table);```

#### Add a new element to the table
```- bool insert_into_hash_table(hash_table_ptr p_hash_table, int key, int value);```

#### Search for an existing element in the table
```- bool is_item_in_hash_table(hash_table_ptr p_hash_table, const int key, int *p_value);```

#### Remove an existing element from the table
```- bool delete_from_hash_table(hash_table_ptr p_hash_table, int key);```

#### HashTableTester Class
This implements the tester wrapper class which is used in file ```TestHashTable.cpp``` for implementing the unit-tests.

Have a look at the [Project Page](https://github.com/Mrunmoy/ms-hash-table/projects) for upcoming enhancement/bugfixes
