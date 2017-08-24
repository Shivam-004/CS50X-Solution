#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"
typedef struct node
{
  struct node *children[27];
  bool is_leaf;
} node;
int index_char(char c);
node *create_node();
void unload_node(node *n);
unsigned int word_count = 0;
node *root;
bool check(const char *word)
{
  node *current_node = root;
  for (int i = 0, len = strlen(word); i < len; i++)
  {
    int index = index_char(word[i]);
    if (current_node -> children[index] == NULL)
      return false;
    current_node = current_node -> children[index];
  }

  return current_node -> is_leaf;
}

bool load(const char *dictionary)
{
  word_count = 0;
  FILE *fp = fopen(dictionary, "rb");
  if (fp == NULL)
    return false;
  fseek(fp, 0, SEEK_END);
  unsigned int fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *buffer = malloc(fsize + 1);
  if (buffer == NULL) 
  {
    fclose(fp);
    return false;
  }
  fread(buffer, fsize, 1, fp);
  fclose(fp);
  buffer[fsize] = '\0';
  root = create_node();
  if (root == NULL) 
  {
    free(buffer);
    return false;
  }
  node *current_node = root;
  for (int i = 0; i < fsize; i++)
  {
    if (buffer[i] == '\n')
    {
      current_node -> is_leaf = true;
      current_node = root;
      word_count++;
      continue;
    }
    int index = index_char(buffer[i]);
    if (current_node -> children[index] == NULL)
    {
      current_node -> children[index] = create_node();
      if (current_node -> children[index] == NULL) 
	  {
        free(buffer);
        return false;
      }
    }

    current_node = current_node -> children[index];
  }

  free(buffer);
  return true;
}
unsigned int size(void)
{
  return word_count;
}

bool unload(void)
{
  unload_node(root);
  return true;
}

int index_char(char c) {
  if (c == '\'')
    return 26;
  else if (c >= 'A' && c <= 'Z')
    return c - 65;
  else
    return c - 97;
}

node *create_node()
{
  node *n = malloc(sizeof(node));
  if (n == NULL)
    return NULL;

  for (int i = 0; i < 27; i++)
    n -> children[i] = NULL;

  n -> is_leaf = false;

  return n;
}

void unload_node(node *n)
{
  for (int i = 0; i < 27; i++)
  {
    if (n -> children[i] != NULL)
      unload_node(n -> children[i]);
  }
  free(n);
}
