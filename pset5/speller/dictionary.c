// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *hashtable[N];

//Word counter
int word_counter = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *n = calloc(1, sizeof(node));
        if (n == NULL)
        {
            //unload();
            return NULL;
        }

        strcpy(n -> word, word);

        //calculate hash index of word with hash function
        int index = hash(n -> word);

        //create pointer to beginning of the hashtable's indexed list
        node *head = hashtable[index];

        //check if that index has a list already, if not create it, and increase word count
        if (head == NULL)
        {
            hashtable[index] = n;
            word_counter++;
        }
        else
        {
            n -> next = hashtable[index];
            hashtable[index] = n;
            word_counter++;
        }
    }

    fclose(dict);
    return true;
}



////////////////////////////////////////////////////////////////////
// Hashes word to a number
// Using the djb2 hash function, can be found on GitHub and Reddit
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % N;
}

////////////////////////////////////////////////////////////////////



// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //make copy of word to be case insensitive
    char copy[LENGTH + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        copy[i] = tolower(word[i]);
    }
    copy[strlen(word)] = '\0';
    
    //get hash index from copy of word
    int index = hash(copy);
    
    //create cursor variable to go through linked list 
    node *cursor = hashtable[index];
    
    while (cursor != NULL)
    {
        if (strcasecmp(cursor -> word, copy) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }
    
    return false;
}



// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
