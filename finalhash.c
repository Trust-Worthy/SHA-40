#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIGEST_SIZE 5 //Size of SHA_40 has in bytes
#define BLOCK_SIZE sizeof(struct Block) //Block size in bytes
#define BYTE unsigned char //Allows using BYTE in place of unsigned char


typedef struct Digest{
	BYTE hash0;
	BYTE hash1;
	BYTE hash2;
	BYTE hash3;
	BYTE hash4;
}Digest;

//unsigned char* SHA_40(const unsigned char* msg, size_t length); //SHA_40 hash function
void print_hash(struct Digest* digest); //prints hash
int digest_equal(struct Digest* digest1, struct Digest* digest2); //Returns 1 (true) or 0 (false)

//Decided to make my SHA_40 return a digest instead of an unsigned char
Digest* SHA_40(const unsigned char* msg, size_t length){
	//Step 1: Set the Seed in unsigned char array. array will change after every iteration of for loop
	//Step 1.5: Create a ptr to the seed array so the values in the seed can change
	unsigned char seed[] = {11,22,33,44,55}; // remover 'unsigned'
		////////////////A ,B ,C	,D, E
	//unsigned char *ptrseed = &seed;
	//printf("Legnth = %d\n", length);
	//Step 2:Create a ptr that points to a digest. This will point to the output of the hash function
	Digest *ptrdigest = (Digest*)malloc(40);

	//Step 3: Populate an empty digest and assign the 'ptrdigest' to the address of the 'digest'
	Digest digest = {0,0,0,0,0};
	ptrdigest = &digest;
	//printf("Seed before %d\n",seed[2]);	
	//Step 4: Initiate for loop. The for loop will run for every byte in the message
	for(int i =0; i <length;i++){
		//printf("I = %d\n", i);
		unsigned char a,b,c,d,e; //Step 5: Create placeholder values for the original seed array
		a = seed[0];
		b = seed[1];
		c = seed[2];
		d = seed[3];
		e = seed[4];
		//printf("a = %d, b = %d, c = %d, d = %d, e = %d\n", a,b,c,d,e);
		//Step 6: Do bitwise & of B and C. The Xor result
		unsigned char box1 = (b&c) ^ d; // bitwise & of b and c. then xor with d
		//Step 7: Bitshift A three to the right.
		unsigned char tempA = seed[0];
		unsigned char box2 = tempA >> 3;
		//Step 8: Get the ith byte of the msg and place it in box 3
		//unsigned char box3 = *(msg+i);
		unsigned char box3 = msg[i];	
		//Step 9: Add all the boxes together and place them in 0th index or A 'starting cycle again'
		seed[0] = box1 + box2 + box3; 

		//Step 10: Index B(1) comes original index A. Index C(2) is index B shifted once to the left
		seed[1] = a; 
		seed[2] = b << 1;

		//Step 11: Index D(3) is original C(2). Index E(4) becomes original D(3)
		seed[3] = c; 
		seed[4] = d;

	}
	
	digest.hash0 = seed[0];
	digest.hash1 = seed[1];
	digest.hash2 = seed[2];
	digest.hash3 = seed[3];
	digest.hash4 = seed[4];

	//printf("Seed after %d\n", seed[2]);
	//free(digest);
	return ptrdigest;
}

int digest_equal(struct Digest* digest1, struct Digest* digest2){
	int hash_equality = memcmp(digest1,digest2,5);
	
	if(hash_equality == 0){
		return 1;
	}
	else{
		return 0;
	}
}

void print_hash(struct Digest* digest){
	//digest = (Digest*) malloc(5);
	BYTE completed_hash0 = digest->hash0;
	BYTE completed_hash1 = digest->hash1;
	BYTE completed_hash2 = digest->hash2;
	BYTE completed_hash3 = digest->hash3;
	BYTE completed_hash4 = digest->hash4;
	//Digest dig = *digest;
	//BYTE completed_hash = dig.hash4;

	printf("The hash value is shown below: \n");
	printf("Hash value: %d %d %d %d %d\n", completed_hash0,completed_hash1,completed_hash2,completed_hash3,completed_hash4);
}
		

int main(){

	
	//Assignment Code
	//Step 1: Create unsig char array and ask user for input
	unsigned char msg[20]; //Message can be 20 bytes long
	unsigned char msg2[20]; 
	printf("Please enter a message you would like hashed: \n");
	scanf("%s",msg);
	printf("Please enter ANOTHER message you would like hashed: \n");
	scanf("%s",msg2);
	//Step 2: Create pointer with allocated memory. Size of ptr is same size as msg entered from user.
	unsigned char *ptrmsg = (unsigned char*)malloc(sizeof(msg));   
	unsigned char *ptrmsg2 = (unsigned char*)malloc(sizeof(msg));   
	//Step 3: Make the ptr point to the memory address of the msg and get length of message
	ptrmsg = msg; //char arrays are pointers 'first element'
	size_t length = strlen(msg);
	ptrmsg2 = msg2; //char arrays are pointers 'first element'
	size_t length2 = strlen(msg2);
	//Step 4: Verify that correct msg was received
	printf("Your message was: %s\n",msg);
	printf("Your SECond message was: %s\n",msg2);
	//Step 5: Send ptrmsg and length to the hash funtion and create ptr that can point to hashed digest
	Digest *ptrdigest = (Digest*)malloc(sizeof(msg));
	ptrdigest = SHA_40(ptrmsg,length); //ptrdigest is pointing to the pointer return by func which is pointing to the hashed digest
	Digest *ptrdigest2 = (Digest*)malloc(sizeof(msg2));
	ptrdigest2 = SHA_40(ptrmsg2,length2); //ptrdigest is pointing to the pointer return by func which is pointing to the hashed digest
	//Step 6:Print the hash and the original message
	print_hash(ptrdigest);
	printf("Original message: %s\n",msg);
	print_hash(ptrdigest2);
	printf("2nd Original message: %s\n",msg2);

	//Step 7: Compare two hashes
	int equality = digest_equal(ptrdigest,ptrdigest2);
	printf("1 = Equal while 0 = Not equal\n");
	printf("These two hashes are %d\n",equality);

}
	



