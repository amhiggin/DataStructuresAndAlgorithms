#include <stdio.h>
#include <stdlib.h>

/*
*   @author Amber Higgins
*   @date   21st October 2016
*/

#define NUM_TEST_KEYS 7     //num of strings
#define MAX_KEY_LENGTH 2500
#define HASH_TABLE_SIZE 2500
char hashtable[HASH_TABLE_SIZE][MAX_KEY_LENGTH];

int rehash(const char* s, int tableSize);	//double hash if we need to
unsigned int RSHash(char* str, unsigned int len);//hashtable from literature

int main()
{
    char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH] = {"prince adam", "orko", "cringer", "teela", "aleet", "princess adora", "orko"};
    int probe=0, cumul_probe=0, i, index;

	printf("            key      index       probe\n--------------------------------------\n" );
	for(i=0; i<NUM_TEST_KEYS;i++){
           probe=1;
           index = RSHash(test_strings[i], strlen(test_strings[i]));
           if(hashtable[index][MAX_KEY_LENGTH]==NULL)
              hashtable[index][MAX_KEY_LENGTH]=test_strings[i];
           else{
              while(hashtable[index][MAX_KEY_LENGTH]!=NULL){
                 index=rehash(test_strings[i], HASH_TABLE_SIZE);
                 probe++;
              }
           hashtable[index][MAX_KEY_LENGTH]=test_strings[i];
           cumul_probe+=probe;
        }
        printf( "%16s   %6i     %6i \n", test_strings[i], index, probe);
      }
      return 0;
}


//double hash if we need to 
int rehash(const char* s, int tableSize){
    int index=0;
    for(int i=0; i<strlen(s);i++){
        index = strlen(s)*2;;
    }
    return index%tableSize;

}

//hashtable from literature - originally from Algorithms in C, Robert Sedgewick
unsigned int RSHash(char* str, unsigned int len)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }
   //take modulus to keep index relatively small - custom step
   return hash%HASH_TABLE_SIZE;
}

