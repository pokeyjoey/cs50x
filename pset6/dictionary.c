/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
} node;    

#define HASH_LENGTH 500
node* hashtable[HASH_LENGTH];

int dictionary_size = 0;

/**
 * hashfunction djb2 that works well with ASCII strings.
 * http://stackoverflow.com/questions/7700400/whats-a-good-hash-function-for-english-words
 */
unsigned long hashstring(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c; 
    }

    return hash % HASH_LENGTH;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int index, word_exists, word_length=0;
    node* bucket_node;
    char word_lowered[LENGTH+1];

    // if the word exists, then it can be found in the hash table.
    // The bucket the word would be in would be hashtable[hash(word)]

    // lower the word to get its hash
    for (int i = 0; word[i]!='\0'; i++)
    {
        word_lowered[i] = tolower(word[i]);
        word_length++;
    }
    word_lowered[word_length] = '\0';

    // Get the index of the linked list where the word would be 
    // stored in the hashtable
    index = hashstring((unsigned char *) word_lowered);

    // Get the address of the first element of the linked list.
    bucket_node = hashtable[index];

    // walk the linked list looking for the word.
    // - use strcasecmp to compare words - returns 0 if equal
    //   irrespective of case.
    while (bucket_node != NULL)
    {
        word_exists = strcasecmp(word, bucket_node->word);        
        if (word_exists == 0)
        {
            return true;
        }

        // word not found keep traversing the list
        bucket_node = bucket_node->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    int bucket;

    // try to open up the dictionary file
    FILE* file_pointer = fopen(dictionary, "r");
    if (file_pointer == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    bool words_to_read = true;

    // initialize the hashtable to NULL
    for (int i = 0; i < HASH_LENGTH; i++)
    {
        hashtable[i] = NULL;
    }

    // read all the words from the dictionary file
    while (words_to_read)
    {
        // make a node for a new word for the hash tables linked lists
        //node* new_node = malloc(sizeof(node));
        char temp_word[LENGTH+1];
       
        // if there are words to read
        //  - hash the word to find the bucket of the linked list to insert into.
        // else
        //  - stop reading the file
        if (fscanf(file_pointer, "%s", temp_word) == 1)
        {
            node* new_node = malloc(sizeof(node));
            strcpy(new_node->word, temp_word);
            dictionary_size++;

            // use the word to calculate the hash value
            // of the bucket in the array.
            bucket = hashstring((unsigned char *) new_node->word);

            // insert the word at the head of the linked list 
            // stored at the hashtable location.
            // - set new_node->next to the node* stored at the head 
            //   of the linked list stored at hashtable[bucket]
            // - set hashtable[bucket] to be the new_node node*.
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
        else
        {
            words_to_read = false;
        }
    }        

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //printf("dictionary_size: %i\n", dictionary_size); 
    return dictionary_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    int nodes_freed = 0;
    node* head;

    // iterate through each location in the hashtable.
    // - when hashtable[i] is not NULL:
    //   * set cursor equal to hashtable[i]
    //     - while cursor != NULL, walk the link list freeing its nodes
    for (int i = 0; i < HASH_LENGTH; i++)
    {
        if (hashtable[i] != NULL)
        {
            head = hashtable[i];
            node* cursor = head;

            while (cursor != NULL)
            {
                node* temp = cursor;
                cursor = cursor->next;
                free(temp);
                nodes_freed++;
            }
        }
    }

    if (nodes_freed == dictionary_size)
    {
        return true;
    }
    else
    {
        return false;
    }
}
