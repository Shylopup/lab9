#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

// Fill out this structure
struct HashType
{
    struct RecordType *record;
    int occupied; // flag to check if index is occupied
};

// Compute the hash function
int hash(int x, int hashSz)
{
    // Simple hash function example: modulus
    return x % hashSz;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
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

// prints the records
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

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    for (i=0;i<hashSz;++i)
    {
        if (pHashArray[i].occupied)
        {
            printf("Index %d -> %d, %c, %d\n", i, pHashArray[i].record->id, pHashArray[i].record->name, pHashArray[i].record->order);
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Your hash implementation
    int hashSz = recordSz; // assuming hash size same as record size for simplicity
    struct HashType *hashTable = (struct HashType*)malloc(sizeof(struct HashType) * hashSz);

    // Initialize hash table
    for (int i = 0; i < hashSz; ++i)
    {
        hashTable[i].record = NULL;
        hashTable[i].occupied = 0;
    }

    // Hash records and store them in the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        int hashedIndex = hash(pRecords[i].id, hashSz);
        hashTable[hashedIndex].record = &pRecords[i];
        hashTable[hashedIndex].occupied = 1;
    }

    // Display records in the hash table
    printf("\nRecords in Hash Table:\n");
    displayRecordsInHash(hashTable, hashSz);

    // Free memory
    free(pRecords);
    free(hashTable);

    return 0;
}
