
#include <stdio.h>
#include <stdlib.h>

/*
*   @author Amber Higgins
*   @date   21st October 2016
*/

#define NUM_TEST_KEYS 7   //num of strings
#define MAX_KEY_LENGTH 16
#define HASH_TABLE_SIZE 17
char hashtable[HASH_TABLE_SIZE][MAX_KEY_LENGTH];

int hash(const char* s, int tableSize);  //"pet" hash function

int main()
{
    char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH] = {"prince adam", "orko", "cringer", "teela", "aleet", "princess adora", "orko"};
    int probe=0, cumul_probe=0, i, index;

    printf("            key      index       probe\n--------------------------------------\n" );
    for ( i = 0; i < NUM_TEST_KEYS; i++ ) {
        probe=1;
        //get our index
	index = hash( test_strings[i], HASH_TABLE_SIZE );

        if(hashtable[index][MAX_KEY_LENGTH]==NULL)
            hashtable[index][MAX_KEY_LENGTH]=test_strings[i];
        else{
            while(hashtable[index][MAX_KEY_LENGTH]!=NULL){
                index++;
                probe++;
            }
            hashtable[index][MAX_KEY_LENGTH]=test_strings[i];
            cumul_probe+=probe;
        }
        printf( "%16s   %6i     %6i \n", test_strings[i], index, probe);
    }
    cumul_probe=0;

    return 0;
}


//this implementation seems to be very commonly used
int hash( const char* s, int tableSize){
    int index = 0;
    index = strlen(s)%tableSize;
    return index;
}
