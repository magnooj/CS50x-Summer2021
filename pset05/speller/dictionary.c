// Implements a dictionary's functionality
// I used this youtube video for getting help to solve this pset:
// https://www.youtube.com/watch?v=sz5XOuxy4GM

#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
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
const unsigned int N = 26;

// Number of loaded words
int wordCount = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Creating temporary key and node for comparison
    int key = hash(word);
    node *nnode = table[key];

    while (nnode != NULL)
    {
        if (strcasecmp(nnode->word, word) == 0)
        {
            return true;
        }
        nnode = nnode->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int val = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        val += tolower(word[i]);
    }
    return val % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Need a table to store values
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // loading the words  from the file
    char tmp_word[LENGTH + 1];

    while (fscanf(file, "%s\n", tmp_word) != EOF)
    {
        // Create new node
        node *tmp_node = malloc(sizeof(node));

        // Copying new word in memory
        strcpy(tmp_node->word, tmp_word);

        // Finding hash node
        int index = hash(tmp_word);
        if (table[index] == NULL)
        {
            tmp_node->next = NULL;
            table[index] = tmp_node;
        }
        else
        {
            tmp_node->next = table[index];
            table[index] = tmp_node;
        }

        wordCount ++;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Returning word counts
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *nnode = table[i];
        while (nnode != NULL)
        {
            node *tmpnode = nnode;
            nnode = nnode->next;
            free(tmpnode);
        }
        table[i] = NULL;
    }
    return true;
}
