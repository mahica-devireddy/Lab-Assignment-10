#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct Trie {

  int count; 
  struct Trie *children[26]; 

}; 

struct Trie* createNode() {
  struct Trie* newNode = (struct Trie*) malloc (sizeof(struct Trie));
  newNode->count = 0;
  for (int i = 0; i < 26; i++) {
    newNode->children[i] = NULL;
  }
  return newNode;
}

void insert(struct Trie **ppTrie, char *word){

  if (*ppTrie == NULL) {
    *ppTrie = (struct Trie*) malloc (sizeof(struct Trie)); 
    (*ppTrie)->count = 0; 
    
    for (int i = 0; i < 26; i++) {
      (*ppTrie)->children[i] = NULL;
    }
  }

  struct Trie* curr = *ppTrie; 
  char *pChar = word; 
  while (*pChar != '\0'){
    int index = *pChar - 'a'; 
    if (curr->children[index] == NULL) {
      curr->children[index] = createNode(); 
      
    }
    curr = curr->children[index]; 
    pChar++; 
  } 
  
    curr->count++; 
    
}


int numberOfOccurances(struct Trie *pTrie, char *word) {
  
  struct Trie* curr = pTrie; 
  char* pChar = word; 
  
  while (*pChar != '\0' && curr != NULL) {
    int index = *pChar - 'a';
    curr = curr->children[index];
    pChar++;
  }

  if (curr == NULL) {
    
    return 0;
    
  } else {
    
    return curr->count;
    
  }
}

struct Trie *deallocateTree(struct Trie *pTrie){
  
  if (pTrie == NULL) {
    return NULL; 
  }
  
  for (int i = 0; i < 26; i++) {
    deallocateTree(pTrie->children[i]); 
  }
  
  free(pTrie); 
  return NULL; 
  
}

int main(void) {
  
  int i, n;
  FILE* ifp = fopen("dictionary.txt", "r");
  fscanf(ifp, "%d", &n);
  
  struct Trie* myDictionary = createNode(); 
  for (i = 0; i < n; i++) {
    char word[SIZE]; 
    fscanf(ifp, "%s", word);
    insert(&myDictionary, word); 
  }
  
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++) {
    printf("\t%s : %d\n",pWords[i], numberOfOccurances(myDictionary, pWords[i]));
  }
  
  myDictionary = deallocateTree(myDictionary);

  fclose(ifp); 
  
  if (myDictionary != NULL) {
    printf("There is an error in this program\n");
    return 0;
  } else {
    printf("\nCODE WORKED");
    return 0; 
  }
 
}
