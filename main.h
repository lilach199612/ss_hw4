#define LETTERS 26
typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct node {
char letter;
long unsigned int countNode;
long unsigned int countChiledren;
long unsigned int countPrint;
struct node* children[LETTERS];
} node;
void add(node* ,char );
void release(node**);
long unsigned int print(node**);
long unsigned int printR(node**);