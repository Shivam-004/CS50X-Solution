#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#define TABLE_SIZE 200000
typedef struct node
{
  char word[LENGTH + 1];
  struct node *next;
} node;
unsigned long hash(char *str);
unsigned int word_count = 0;
node *table[TABLE_SIZE];
bool check(const char *word)
{
  int len = strlen(word);
  char s[len + 1];
  s[len] = '\0';

  for (int i = 0; i < len; i++)
    s[i] = tolower(word[i]);

  int index = hash(s) % TABLE_SIZE;
  node *n = table[index];

  while (n != NULL) {
    if (strcmp(s, n -> word) == 0)
      return true;
    n = n -> next;
  }

  return false;
}
bool load(const char *dictionary)
{
  word_count = 0;
  FILE *fp = fopen(dictionary, "rb");
  if (fp == NULL)
    return false;
  char buffer[LENGTH + 1];
  int lim = LENGTH + 2;
  while (fgets(buffer, lim, fp) != NULL) {
    int len = strlen(buffer);
    if (buffer[len - 1] == '\n')
      buffer[--len] = '\0';
    int index = hash(buffer) % TABLE_SIZE;
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
      fclose(fp);
      return false;
    }
    strcpy(new_node -> word, buffer);
    new_node -> next = table[index];
    table[index] = new_node;
    word_count++;
  }
  return true;
}
unsigned int size(void)
{
  return word_count;
}

bool unload(void)
{
  for (int i = 0; i < TABLE_SIZE; i++) {
    node *next = table[i];
    while (next != NULL) {
      node *t = next;
      next = next -> next;
      free(t);
    }
  }

  word_count = 0;
  return true;
}

unsigned long hash(char *str)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}
