/*  ____________________________________________________________________________________________

    @author Amber Higgins, 13327954
    Assignment 3: Trees and Search
    Date: 29th November 2016
    
    The following code implements the required functions for a Binary Search Tree (BST):
    	- void tree_insert(Node* root, char data)
	  This function will add a new node to the tree containing the character 'data', provided that it is not a duplicate.
    	- Node* tree_search(Node* root, char data)
    	  This function will search for a node containing 'data' in the tree, and return it if found.
    	- void tree_print_sorted(Node* root)
    	  This function will print out the contents of the BST in alphabetical order.
    	- void tree_delete(Node* root, char data)
    	  This function will delete the node (if it exists) in the tree with 'data' as its parameter. This takes into account all of the different cases that can be encountered.
    	- void construct_balanced_tree(Node* root, int start, int end)
    	  This function aims to construct a new, balanced BST given a sorted array of data - it works by recursively splitting the given array in half, and adding the midpoint of the sublist at each
 	  splitting stage as the next node in the tree.
    
    NOTES:
    1) There are some issues in the implementation of the final function (construct_balanced_tree())due to issues with memory allocation, which have been pin-pointed to be down to the root->left and 
       root->right pointers respectively (these do not seem to have any memory allocated to them). However due to time constraints this could not be fully investigated/resolved.
       However the implementation itself is founded on strong logic and I believe it would operate correctly, had there been no memory allocation issues.
    
    2) This implementation assumes that the input characters to the BST are all lowercase alphabetric characters, which are the only values that can be given as input at runtime.
    The implementation also does not allow user input, but generates input characters itself which may be restrictive. If there was more time, it should be implented to allow user input.
    
    ____________________________________________________________________________________________
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 26                     					//max num of nodes in the tree: corresponds to the number of characters in the alphabet

typedef struct Node{
    char data;
    struct Node* left;
    struct Node* right;
} Node;

/**************************
*	GLOBAL VARIABLES  *
***************************/
Node* Root=NULL;
Node* root_new=NULL;
char sorted_array[SIZE];                				//array to store the sorted elements in for re-adding to our balanced tree
char data_to_delete, char_to_insert, search_char;      		 	//temp variables used in main
int counter=0;                         					//counter used in sorting of elements in the tree
int num_elements_added=0;                				//a counter which tracks how many elements were ACTUALLY added to tree (taking duplicates into account)

/**************************
*	FUNCTIONS         *
***************************/
char generate_random_character();                			//function to generate random lowercase alphabetic characters
Node* make_node(char data);                				//function to create a new node instance, and assign it a character ('data')
int compare(char x, char curr);                				//function which compares two characters and returns their difference as an integer (used in tree-sorting)
Node* find_minimum_node(Node* n);                 			//function to find the minimum element in the tree (used in tree_delete function)
void tree_insert(Node* root, char data);        			//function to add a new node to the tree with 'data' as its data parameter
Node* tree_delete(Node* root, char data);        			//function (recursive) to remove a node from the tree (if it exists), given its data parameter
Node* tree_search(Node* root, char data);        			//function which searches the tree for a node containing 'node_data', and returns it if found
void sort_tree_elements(Node *n);                				//function to sort the elements of a tree alphabetically and store them in a list
void tree_print_sorted(Node* root);            				//function which prints out the elements of the tree in alphabetical order
void delete_tree(Node* n);                				//function to delete all of the existing nodes in a tree
void construct_balanced_tree(Node* root, int start, int end);		//function (recursive) to create a balanced tree




int main(){

    //generate a random array, and add the elements to the tree as they are generated
    srand(time(NULL));
    char array[SIZE];
    for(int i=0; i<SIZE;i++){
        array[i]=generate_random_character();				//generate a random alphabetic character and add to array
        tree_insert(Root, array[i]); 					//also add it to the tree using tree_insert()
        printf("---\n %c \n---\n", array[i]);				//print it out as its generated
    }
    printf("\n-----------\nPRINTING THE INITIAL TREE...\n----------\nRoot: %c\n", Root->data);
    tree_print_sorted(Root);						//print the tree contents in alphabetical order

 
    //search for a character in the tree
    search_char=generate_random_character();
    Node* result = tree_search(Root, search_char);
    if(result==NULL){
        printf("Character doesn't exist in the tree");
    }
    else printf("\nFound node %c \n", result->data);
 
 
    //insert a new node
    char_to_insert=generate_random_character();        			//may or may not already be in tree: will not add duplicate
    printf("\nTrying to insert random node %c\n",char_to_insert);
    tree_insert(Root, char_to_insert);					//try to insert this new node
    printf("\n-----------\nPRINTING THE UPDATED TREE...\n----------\n", char_to_insert);
    tree_print_sorted(Root);						//print out the updated tree to the console window
    printf("\n");
   
   
     //delete a node: demonstrate root deletion first
    data_to_delete = Root->data;					//get the character belonging to the root node
    printf("\nSearching for root %c to delete...\n", data_to_delete);
    Node* r =tree_delete(Root,data_to_delete);				//remove this node
    printf("\n-----------\nPRINTING THE UPDATED TREE...\n----------\n");
    tree_print_sorted(Root);						//print the updated tree to the console window
    printf("\n");
   
    //delete a random node
    data_to_delete = generate_random_character();        		//may or may not be in the tree: will not remove any nodes if not found
    printf("\nSearching for %c to delete...\n", data_to_delete);
    r =tree_delete(Root,data_to_delete);				//attempt to remove the node with this character
    printf("\n-----------\nPRINTING THE UPDATED TREE...\n----------\n");
    tree_print_sorted(Root);						//print the updated tree to the console window
    printf("\n");
   
   
    //make balanced tree from the elements generated earlier
    printf("\n------------------\n...BEGINNING THE BALANCING PROCESS...\n-----------------");
    printf("\n-----------\nSORTING THE ARRAY\n----------\n");
    sort_tree_elements(Root);                    			//sort the existing tree into an array of characters		
    for(int j=0;j<num_elements_added;j++){
        printf(" %c", sorted_array[j]);					//print out the characters as they are sorted in order
    }
    printf("\n-----------\nDELETING THE ORIGINAL TREE\n----------\n");
    delete_tree(Root);							//delete the existing tree
    int num_list_elements = num_elements_added;	
    num_elements_added=0;						//reset	
    printf("\n-----------\nMAKING A BALANCED TREE\n----------\n");
    construct_balanced_tree(root_new, 0, num_list_elements-1);	//make a new balanced tree (root_new is a new root for the new tree)
    tree_print_sorted(root_new);                 			//print out the resulting balanced tree
   
    return 0;
}



//function to generate random lowercase alphabetic characters
char generate_random_character(){
    int randNum = 26 * (rand() / (RAND_MAX + 1.0));
    randNum = randNum + 97;
    char randChar = (char) randNum;
 
    return randChar;
}


//function to create a new node instance, and assign it a character ('data')
Node* make_node(char data){
    //allocate memory for the node
    Node* newNode = (Node*)malloc(sizeof(Node*));

    //set properties
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
 
    return newNode;
}



//function which compares two characters and returns their difference as an integer (used in tree-sorting)
int compare(char x, char curr){
    return x-curr;
}


//function to find the minimum element in the tree (used in tree_delete function)
Node* find_minimum_node(Node* n){
    if(n==NULL){
        return NULL;
    }
    if(n->left){
        //min element will be in the left subtree: recurse left
        return find_minimum_node(n->left);
    }
    else{
        return n;
    }
}


//function to add a new node to the tree with 'data' as its data parameter
void tree_insert(Node* root, char data){
    bool went_left=false, exit=false;
   
    if(root==Root && root==NULL){
        //theres nothing in the tree yet: this is the root of the tree
        printf("There was nothing in the list: this node is the root: %c\n", data);
        Root =make_node(data);
        num_elements_added++;
        return;
    } else if (root==root_new && root==NULL){
        printf("There was nothing in the list: this node is the root: %c\n", data);
        root_new = make_node(data);
        num_elements_added++;
        return;
    }
   
    Node* curr=root;								//start iterating from the first node
    Node* prev = NULL;
   
    while(curr!=NULL&&exit==false){
        //we keep looking
        int result = compare(data, curr->data);
        printf("Result: %i \n", result);
        prev = curr; 								//preserve curr
     
        if(result<0){
            //go left
            printf("Went left of '%c' \n", curr->data);
            went_left=true;
            curr=curr->left;

        } else if (result>0){
            //go right
            printf("Went right of '%c' \n", curr->data);
            went_left=false;
            curr=curr->right;
        } else{ 
            //already exists - don't add a duplicate!
            exit=true;
            printf("Node %c was already in tree\n", data);
            return;
        }
    }
    //we get to here whenever we are at end of the current branch
   
    if(went_left==true){
        //this is the last branch we took - add to left
        printf("Adding to left. \n");
        prev->left=make_node(data);
        num_elements_added++;
    } else{
        //last branch we took was to right - add to right
        printf("Adding to right. \n");
        prev->right = make_node(data);
        num_elements_added++;
    } 
}




//function (recursive) to remove a node from the tree (if it exists), given its data parameter
Node* tree_delete(Node* root, char data){
    /* Considered 3 cases in this approach:
        -leaf node (just delete)
        -parent with 1 child (Replace it with its child node)
        -parent with 2 children (Replace by its "successor")
       The root is also accurately deletable.
    */ 
    Node* temp;									//temp Node* variable
 
    if(root==NULL){
        printf("\nElement not in tree\n");
    }
    else if(data < root->data){
        //keep looking
        printf("Going left\n");
        root->left = tree_delete(root->left, data);
    }
    else if(data > root->data){
        //keep looking
        printf("Going right\n");
        root->right=tree_delete(root->right, data);
    }
    else{
        if(root->right && root->left){
            //two children: find the smallest one of the two
            temp = find_minimum_node(root->right);
            root->data = temp->data;
            root->right=tree_delete(root->right, temp->data);
        }
        else{
            temp = root;
            //must check whether root is the root of the tree
            if(root->left==NULL){
                root=root->right;
            } else if(root->right==NULL){
                root=root->left;
            }
            free(temp);
            temp->data=NULL;
            temp=NULL;
            printf("\nDeleted successfully.\n");
            num_elements_added--;
        }
    }
    return root;
}


//function which searches the tree for a node containing 'node_data', and returns it if found
Node* tree_search(Node* root, char data){
    bool found=false;
   
    printf("\n Searching for char %c \n", data);
   
    if(Root==NULL){
        printf("Can't search - tree is empty!\n");
        return NULL;
    }
    else{
        Node* curr=root;
     
        while(curr!=NULL && found==false){
            int result=compare(data, curr->data);
            if(result<0){
                curr=curr->left;
            } else if(result>0){
                curr=curr->right;
            } else{ 
                //we have found it!
                return curr;
            }
        }
    }
    //we only end up here if we didn't find the node
    return NULL;
}




//function to sort the elements of a tree alphabetically and store them in a list
void sort_tree_elements(Node* n){
    if(n!=NULL){
        //recurse left
        sort_tree_elements(n->left);
        sorted_array[counter] = n->data;
        counter++;
        //recurse right
        sort_tree_elements(n->right);
    }
}


//function which prints out the elements of the tree in alphabetical order
void tree_print_sorted(Node* root){

    if(root==NULL) return; 							//the tree is empty
 
    //recursively iterate through from bottom-left node to bottom-right node
    tree_print_sorted(root->left);
    printf("%c ", root->data);
    tree_print_sorted(root->right); 
}


//function to delete all of the existing nodes in a tree
void delete_tree(Node* node){
    if(node==NULL) return;                					//i.e. if the tree is already empty, exit
   
    //recurse through left branch
    if(node->left!=NULL)
        delete_tree(node->left);
    //recurse through right branch
    if(node->right!=NULL)
        delete_tree(node->right);
    
    //nullify all the parameters of each node in the tree                   
    node->data=NULL;
    node->left=NULL;
    node->right=NULL;
    node=NULL;
    //deallocate the memory associated with the node
    free(node);    
}



//function (recursive) to create a balanced tree
void construct_balanced_tree(Node* root, int start, int end){ 
    int midpoint, sum=start+end+1;

    if(start==end){
        printf("Start==end - edge case detected\n");
        return root;
    }
    //to add in balanced order, must add the mid-value of the sublists each time to their respective sides of their parent
    midpoint = sum/2;
    printf("Sum = %i, Midpoint = %i, sorted_array[midpoint]= %c\n", sum, midpoint, sorted_array[midpoint]);

    //insert mid-element of current sublist (left/right) into the tree
    tree_insert(root, sorted_array[midpoint]);
    printf("We got back out of the insert function\n");
    construct_balanced_tree(root->left, start, midpoint);    			//traverse left sublist
    construct_balanced_tree(root->right, midpoint+1, end);    			//traverse right sublist    
}
