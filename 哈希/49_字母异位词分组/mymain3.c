/*
2026.04.08
*/

#include <stdint.h>
#include <stdlib.h>

typedef uint16_t Key[26];

typedef struct HashEntry{
    Key key;
    int groupIndex;
    int isused;
}HashEntry;

typedef struct HashTable{
    HashEntry *entry;
    int size;
    int capacity;
}HashTable;

typedef struct Group{
    char **str;
    int size;
    int capacity;
}Group;

unsigned int hashInt(Key key,int tableSize){
    unsigned int hash = 5381;
    const unsigned char* p = (const unsigned char*)key;
    for (int i = 0; i < 26 * sizeof(uint16_t); i++) {
        hash = ((hash << 5) + hash) ^ p[i];
    }
    return hash % tableSize;
}

void buildKey(Key key,const char *s){
    int count[26] = { 0 };
    while (*s) {
        count[*s - 'a']++;
        s++;
    }
    for (int i = 0; i < 26; i++) {
        key[i] = (uint16_t)count[i];
    }
}

int findGroup(HashTable *table,Key key){
    unsigned idx=hashInt(key,table->capacity);
    while(table->entry[idx].isused){
        if(memcmp(table->entry[idx].key,key,sizeof(Key))==0){
            return table->entry[idx].groupIndex;
        }
        idx=(idx+1)%table->capacity;
    }
    return -1;
}

void insertHash(HashTable *table,int groupIndex,Key key){
    unsigned idx=hashInt(key,table->capacity);
    while (table->entry[idx].isused) {
        idx = (idx + 1) % table->capacity;
    }
    memcpy(table->entry[idx].key, key, sizeof(Key));
    table->entry[idx].groupIndex = groupIndex;
    table->entry[idx].isused = 1;
    table->size++;
}

static HashTable* createHashTable(int capacity) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->capacity = capacity;
    ht->size = 0;
    ht->entry = (HashEntry*)calloc(capacity, sizeof(HashEntry));
    return ht;
}

void freeHash(HashTable *table){
    free(table->entry);
    free(table);
}

static void expandHashTable(HashTable** ht, int newCapacity){
    HashTable *old=*ht;
    HashTable *new=createHashTable(newCapacity);
    for (int i = 0; i < old->capacity; i++) {
        if (old->entry[i].isused) {
            insertHash(new, old->entry[i].groupIndex, old->entry[i].key);
        }
    }
    freeHash(old);
    *ht = new;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
     *returnSize = 0;
    if (strsSize == 0) {
        *returnColumnSizes = NULL;
        return NULL;
    }
    int initCapacity = strsSize * 2 + 1;
    HashTable* table = createHashTable(initCapacity);
    Group* groups = (Group*)malloc(sizeof(Group) * strsSize);
    int groupCount = 0; 

    for(int i=0;i<strsSize;i++){
        Key key;
        buildKey(key,strs[i]);
        int idx=findGroup(table,key);
        if(idx==-1){
            idx=groupCount++;
            groups[idx].size=0;
            groups[idx].capacity=4;
            groups[idx].str=(char**)malloc(sizeof(char*)*groups[idx].capacity);
             if (table->size * 4 > table->capacity * 3) { // 负载因子 > 0.75
                expandHashTable(&table, table->capacity * 2 + 1);
            }
            insertHash(table, idx, key);
        }
        Group* tmp=&groups[idx];
        if(tmp->capacity==tmp->size){
            tmp->capacity*=2;
            tmp->str=(char**)realloc(tmp->str,sizeof(char*)*tmp->capacity);
        }
        tmp->str[tmp->size++]=strs[i];
    }
    char***res=(char***)malloc(sizeof(char**)*groupCount);
    *returnColumnSizes = (int*)malloc(sizeof(int) * groupCount);
    for (int i = 0; i < groupCount; i++) {
        res[i] = groups[i].str;
        (*returnColumnSizes)[i] = groups[i].size;
    }

    *returnSize = groupCount;
    free(groups);
    freeHash(table);

    return res;
}