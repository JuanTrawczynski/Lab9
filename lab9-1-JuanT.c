#include <stdio.h>
#include <stdlib.h> // for malloc, free

#define HASH_TABLE_SIZE 23

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order;
};

// Node for chaining
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// HashType - Hash Table
struct HashType
{
    struct Node* head; // Head of the linked list for chaining
};

// Compute the hash function
int hash(int x)
{
    return x % HASH_TABLE_SIZE;
}

// Function to initialize the hash table
void initializeHashTable(struct HashType hashTable[])
{
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        hashTable[i].head = NULL;
    }
}

// Function to insert a record into the hash table
void insertRecord(struct HashType hashTable[], struct RecordType record)
{
    int index = hash(record.id);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = record;
    newNode->next = hashTable[index].head;
    hashTable[index].head = newNode;
}

// Function to display records in the hash structure
void displayRecordsInHash(struct HashType hashTable[])
{
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        printf("Index %d -> ", i);
        struct Node* current = hashTable[i].head;
        while (current != NULL)
        {
            printf("(%d, %c, %d) -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Function to parse input file to an array of records
int parseData(char* input_lab_9, struct RecordType** ppData)
{
    FILE* inFile = fopen(input_lab_9, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// Function to print records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    // Parse input data
    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize hash table
    struct HashType hashTable[HASH_TABLE_SIZE];
    initializeHashTable(hashTable);

    // Insert records into hash table
    int i;
    for (i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, pRecords[i]);
    }

    // Display records in hash structure
    displayRecordsInHash(hashTable);

    // Free allocated memory
    free(pRecords);

    return 0;
}