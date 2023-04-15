#include <stdio.h>
#include <stdlib.h>

#define hashTableSize 11

// RecordType
struct RecordType
{
    
    int id;
    char name;
    int order;
    struct RecordType* next; //Next Pointer
};

// Fill out this structure
struct HashType
{
    //Pointer to a RecordType Struct
    struct RecordType* data;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    // hash function is x % tableSize
    return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
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
            pRecord->next = NULL;
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

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize);// call the hash function to get the index
    
    if (hashTable[index].data == NULL){
        hashTable[index].data = record;
    }
    else{

        struct RecordType* temp = hashTable[index].data;
        while (temp->next != NULL){
            temp = temp->next;
            }
        temp->next = record;

        }


    
}

void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    for (int i = 0; i < tableSize; i++)
    {
        struct RecordType* curr = hashTable[i].data;
        if (curr != NULL)
        {
            printf("Index %d -> ", i);
            while (curr != NULL)
            {
                printf("%d, %c, %d -> ", curr->id, curr->name, curr->order);
                curr = curr->next;
            }
            printf("NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);


    struct HashType* hashTable = (struct HashType*) malloc(sizeof(struct HashType) * hashTableSize);
    if (hashTable == NULL)
    {
        printf("Cannot allocate memory\n");
        exit(-1);
    }
    for (int i = 0; i < hashTableSize; i++)
    {
        hashTable[i].data = NULL;
    }

    
    for (int i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

    
    displayRecordsInHash(hashTable, hashTableSize);

    free(pRecords);
    free(hashTable);
    
}
