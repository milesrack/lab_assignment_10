#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie *children[26];
    int count;
};

void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int len = strlen(word);

    for (int i = 0; i < len; i++){
        char c = word[i];

        if (pTrie->children[c - 'a'] == NULL){
            pTrie->children[c - 'a'] = createTrie();
        }

        pTrie = pTrie->children[c - 'a'];
    }

    pTrie->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int len = strlen(word);

    for (int i = 0; i < len; i++){
        char c = word[i];

        if (pTrie->children[c - 'a'] == NULL){
            return 0;
        }

        pTrie = pTrie->children[c - 'a'];
    }

    return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL){
        return NULL;
    }

    for (int i = 0; i < 26; i++){
        if (pTrie->children[i] != NULL){
            deallocateTrie(pTrie->children[i]);
        }
    }

    free(pTrie);

    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *root = (struct Trie *) malloc(sizeof(struct Trie));

    for (int i = 0; i < 26; i++){
        root->children[i] = NULL;
    }

    root->count = 0;

    return root;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int n = 0;
    char word[50];

    FILE *fp = fopen(filename, "r");

    if (fp == NULL){
        return 0;
    }

    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++){
        fscanf(fp, "%s", word);
        pInWords[i] = (char *) malloc(sizeof(char) * (strlen(word) + 1));
        strcpy(pInWords[i], word);
    }

    fclose(fp);

    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
    return 0;
}