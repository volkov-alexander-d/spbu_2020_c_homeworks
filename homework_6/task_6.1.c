#include "../library/fileProcessing/fileProcessing.h"
#include "../library/hashTable/hashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTheNecessaryInformation(HashTable* words)
{
    printf("load factor: %f\n", getLoadFactor(words));
    printf("average number of probes: %f\n", getAverageNumberOfProbes(words));
    int maximumNumberOfProbes = getMaximumNumberOfProbes(words);
    printf("maximum number of probes: %d\n", maximumNumberOfProbes);
    printf("elements with maximum number of probes: ");
    printAllElementsWithCertainNumberOfProbes(words, maximumNumberOfProbes);
    printf("\n");
    printf("number of different added words: %d\n", getElementCount(words));
    printf("number of empty buckets: %d\n", getBucketCount(words) - getElementCount(words));
    printElementsWithBiggestValues(words, 10);
}

int getIndex(int hash, int module, int numberOfProbes)
{
    return (hash + ((numberOfProbes - 1) * numberOfProbes) / 2) % module;
}

int getHash(char* key, int module)
{
    int size = (int)strlen(key);
    int currentHash = 0;
    for (int i = 0; i < size; ++i) {
        currentHash = ((currentHash * 2) + (key[i] - 'a')) % module;
    }
    return currentHash;
}

int main()
{
    FILE* input = NULL;
    input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("file \"input.txt\"not found");
        return 0;
    }
    HashTable* words = createHashTable(&getHash, &getIndex);
    char* currentWord = readWordFromFile(input);
    while (currentWord != NULL) {
        {
            addElement(words, currentWord, 1);
            free(currentWord);
            currentWord = readWordFromFile(input);
        }
    }

    printTheNecessaryInformation(words);

    destroyHashTable(words);
    free(currentWord);
    fclose(input);
    return 0;
}
