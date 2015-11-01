#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if (node==0) return 0;
    return (1+getSize(node->left)+getSize(node->right));
}

int calcNodeDepth(struct treeNode * node)
{
    struct treeNode *temp;
    int i=-1;
    temp=root;
    while(temp!=0){
        i++;
        if (temp->item==node->item) break;
        if (temp->item<node->item) temp=temp->left;
        else temp=temp->right;
    }
    if (temp==0) return FALSE_VALUE;
    else return i;
}


int calcDepth(int item)
{
    struct treeNode *temp;
    temp=searchItem(root,item);
    if (temp==0) return FALSE_VALUE;
    else return calcNodeDepth(temp);

}
struct treeNode* findSuccessor(struct treeNode * node, int item)
{
    struct treeNode * succ, * t;
    if( node->right != 0 )
    {
        succ = node->right ;
        while( succ->left!=0 )
        succ = succ->left ;
        return succ ;
    }
    else
    {
        succ = 0 ;
        t = root ;
        while( t!= 0 )
        {
            if (node->item == t->item ) return succ ;
            else if (node->item < t->item )
            {
                succ = t ;
                t = t->left ;
            }
            else t = t->right ;
        }
        return 0 ;
    }
}


int deleteItem(struct treeNode * node, int item)
{
    struct treeNode *parent=0,*del=0;
    int type;
    if (node==0) return 0;
    if (root->item==item && root==node){
      parent=0;
      del=root;
    }
    if (node->left!=0 && node->left->item==item ){
        parent=node;
        del=node->left;
        type=0;
    }
    if (node->right!=0 && node->right->item==item){
        parent=node;
        del=node->right;
        type=1;
    }
    if (parent==0 && del==0){
        int t=deleteItem(node->left,item);
        if(t==FALSE_VALUE)t=deleteItem(node->right,item);
        return t;
    }
    else {
        if (del->left==0 && del->right==0){
            free(del);
            if(parent==0) initializeTree();
            else if(type==0) parent->left=0;
            else parent->right=0;
        }
        else if (del->left==0){
            if (parent==0) root=del->right;
            else if (type==0) parent->left=del->right;
            else parent->right=del->right;
            free(del);
        }
        else if (del->right==0){
            if (parent==0) root=del->left;
            else if (type==0) parent->left=del->left;
            else parent->right=del->left;
            free(del);
        }
        else{
            struct treeNode *scc;
            scc=findSuccessor(del,del->item);
            int x;
            x=del->item;
            del->item=scc->item;
            scc->item=x;
            deleteItem(root,scc->item);
        }
        return TRUE_VALUE;
    }

}



int getMinItem()
{
    if (root==0) return FALSE_VALUE;
    struct treeNode *node;
    node=root;
    int m=node->item;
    while(node!=0){
        m=node->item;
        node=node->left;
    }
    return m;
}

int getMaxItem()
{
    if (root==0) return FALSE_VALUE;
    struct treeNode *node;
    node=root;
    int m=node->item;
    while(node!=0){
        m=node->item;
        node=node->left;
    }
    return m;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound)
{
    if (node==0) return 0;
    if (node->item>=leftBound && node->item<=rightBound)
        return (1+rangeSearch(node->left,leftBound,rightBound)+rangeSearch(node->right,leftBound,rightBound));
    if (node->item<leftBound) return rangeSearch(node->right,leftBound,rightBound);
    if (node->item>rightBound) return rangeSearch(node->left,leftBound,rightBound);

}





void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. Range Search.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",rangeSearch(root,l,r));
        }
    }

}
