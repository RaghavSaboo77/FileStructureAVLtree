//with having to create a file of that number
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

// An AVL tree node
struct Node
{
    char key[30];
    struct Node *left;
    struct Node *right;
    int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(char *key)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    strcpy(node->key ,key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, char *key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (strcmpi(key , node->key)<0)
        node->left  = insert(node->left, key);
    else if (strcmpi(key , node->key)>0)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmpi(key , node->left->key)<0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmpi(key , node->right->key)>0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmpi(key , node->left->key)>0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmpi(key , node->right->key)<0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// A utility function to print preorder traversal
// of the tree.
void preOrder(struct Node *root)
{
    if(root != NULL)
    {

        printf("%s ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int f=0;
#define COUNT 10

int display2D(struct Node *root, int space,char *ele)
{

    if (root == NULL) return 0;

    space += COUNT;

    display2D(root->right, space,ele);


    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    if(strcmpi(root->key,ele)==0)
      { printf("{|%s|}\n", root->key);f=1; }

       else
    {printf("%s\n", root->key);    }

    display2D(root->left, space,ele);
    return f;
}
int checkinavl(struct Node *root,char *x)
{
    struct Node *curr,*prev;
    curr=root;
    prev=NULL;
    if(root==NULL)
        return 1;
    while(curr!=NULL)
    {
        prev=curr;
        if(strcmpi(curr->key,x)==0)
            return 0;
        else if(strcmpi(x,curr->key)<0)
            curr=curr->left;
        else
            curr=curr->right;
    }
    return 1;
}
void del_file()
{
    char num[30];
    int n;
    FILE *fp=fopen("integers.txt","r");
    while ( fscanf(fp,"%s",num)!=EOF )
    {
        n=remove(num);
    }
    fclose(fp);
}

/* Drier program to test above function*/
int main()
{ FILE *fptr;
  struct Node *root = NULL;
  int cho;
  //where the integers file is the prototype of the folder
  while(1)
  {
      system("cls");
      printf("1.Create your own set of new file\n");
      printf("2.Use the old ones from the folder\n");
      printf("Enter your choice 1 or 2 : ");
      scanf("%d",&cho);
      printf("\n");
      if(cho==1)
      {int s;
      del_file();
      fptr = fopen("integers.txt", "w");
      printf("Enter the no. of files to be stored  : ");
      scanf("%d",&s);
      char n[30];
      for(int i=1;i<=s;i++)
        {
            printf("Enter The name of file no. %d:-",i);
            scanf("%s",n);
            if(checkinavl(root,n)==0)
            {
                printf("\nThe File already exists , Please re-enter \n\n");
                i--;
                continue;
            }
            root=insert(root,n);
            int len=strlen(n);
            FILE *fp=fopen(n,"w");
            fclose(fp);
            n[len]='\n';
            n[len+1]='\0';
            fprintf(fptr,n);

        }
       fclose(fptr);
       break;
       }
       else if(cho==2)
       {
        char num[30];

        fptr = fopen("integers.txt", "r");

        while ( fscanf(fptr,"%s",num)!=EOF ) {

                root=insert(root,num);
            }
        printf("The AVL tree has been created \n\n  ");
        fclose(fptr);
        break;
       }
       else
       {
           printf("Invalid Choice \n\n");
           printf("Press any key to continue : ");
           getch();

        }
  }
    printf("\nPress any key to continue : ");
    getch();
    fptr = fopen("integers.txt", "a");

   while(1)
   {
    int k=0;
    system("cls");
    printf("1.Search For a File \n");
    printf("2.Insert a File \n");
    printf("3.Display current avl tree \n");
    printf("4.Exit \n");
    printf("Enter your choice : ");
    scanf("%d",&k);
    char el[30];
    switch(k)
        {
            case 1:
            printf("Enter the file name that you want to search :");
            scanf("%s",el);
            if(display2D(root,0,el))
                printf("\nFile  found\n");
            else
                printf("\nFile not found\n");
            break;
            case 2:
            printf("Enter the file name that you want to insert : ");
            scanf("%s",el);
            if(checkinavl(root,el)==0)
            {
                printf("The File Already exists \n\n");
                break;
            }
            root=insert(root,el);
            int len=strlen(el);
            FILE *fp=fopen(el,"w");
            fclose(fp);
            el[len]='\n';
            el[len+1]='\0';
            fprintf(fptr,el);
                    break;
            case 3:
            display2D(root,0,"0");

             break;

            default:exit(0);
        }
    printf("Press any key to continue : ");getch();
   }

  fclose(fptr);
  return 0;
}

