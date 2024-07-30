#include<iostream>
using namespace std;

// định nghĩa cấu trúc một nút trong cây AVL
struct NODE
{
    int key;
    NODE* left;
    NODE* right;
    int height;
};

// Khởi tạo một nút
NODE* createNode(int data)
{
    NODE* temp = new NODE;
    temp->key = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

// Tính chiều cao của nút
int height(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return 0;
    }
    return pRoot->height;
}

// tính sự chênh lệch độ cao của cây con trái và cây con phaỉ
int getBalance(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return 0;
    }
    return height(pRoot->left) - height(pRoot->right);
}

// hàm xoay phải 
void rightRotate(NODE*& p)
{
    NODE* l = p->left;
    NODE* r = l->right;

    l->right = p;
    p->left = r;

    p->height = max(height(p->left), height(p->right)) + 1;
    l->height = max(height(l->left), height(l->right)) + 1;

    p = l;
}
// hàm xoay trái
void leftRotate(NODE*& p)
{
    NODE* r = p->right;
    NODE* l = r->left;

    r->left = p;
    p->right = l;

    p->height = max(height(p->left), height(p->right)) + 1;
    r->height = max(height(r->left), height(r->right)) + 1;
    
    p = r;
}

// chèn một nút có giá trị x vào cây
void Insert(NODE*& pRoot, int x)
{
    if(pRoot == NULL)
    {
        pRoot = createNode(x);
        return;
    }
    if(x < pRoot->key)
    {
        Insert(pRoot->left, x);
    }
    else
    {
        Insert(pRoot->right, x);
    }

    pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));

    int balance = getBalance(pRoot);


    // left left case
    if(balance > 1 && x < pRoot->left->key)
    {
        rightRotate(pRoot);
    }
    // right right case
    else if(balance < -1 && x > pRoot->right->key)
    {
        leftRotate(pRoot);
    }
    // Left Right Case
    else if (balance > 1 && x > pRoot->left->key) 
    {
        leftRotate(pRoot->left);
        rightRotate(pRoot);
    }
    // Right Left Case
    else if (balance < -1 && x < pRoot->right->key) 
    {
        rightRotate(pRoot->right);
        leftRotate(pRoot);
    }
}


// Xóa một nút trong cây với giá trị x
// hàm tìm nút thay thế
NODE* change(NODE* pRoot) 
{
	while (pRoot->left != NULL) 
	{
       	pRoot = pRoot->left;
    }
    return pRoot;
} 
// hàm xóa nút vơi giá trị x 
void Remove(NODE* &pRoot, int x)
{
	if(pRoot == NULL) return;
	if(x>pRoot->key)
	{
		Remove(pRoot->right,x);
	}
	else if(x<pRoot->key)
	{
		Remove(pRoot->left,x);
	}
	else 
	{
		if(pRoot->left==NULL&&pRoot->right==NULL)
		{
			delete pRoot;
			pRoot=NULL;	
		} 
		else if(pRoot->left==NULL)
		{
			NODE* temp = pRoot;
            pRoot = pRoot->right;
            delete temp;
		}
		else if(pRoot->right==NULL)
		{
			NODE*temp= pRoot;
			pRoot=pRoot->left;
			delete temp;
		}
		else
		{
			NODE*temp=change(pRoot->right);
			pRoot->key=temp->key;
			Remove(pRoot->right,temp->key);
		}
	}

    if (pRoot == NULL) return;


    pRoot->height = 1 + max(height(pRoot->left), height(pRoot->right));

    
    int balance = getBalance(pRoot);

    // Left Left Case
    if (balance > 1 && getBalance(pRoot->left) >= 0)
    {
        rightRotate(pRoot);
    }
    // Left Right Case
    else if (balance > 1 && getBalance(pRoot->left) < 0)
    {
        leftRotate(pRoot->left);
        rightRotate(pRoot);
    }
    // Right Right Case
    else if (balance < -1 && getBalance(pRoot->right) <= 0)
    {
        leftRotate(pRoot);
    }
    // Right Left Case
    else if (balance < -1 && getBalance(pRoot->right) > 0)
    {
        rightRotate(pRoot->right);
        leftRotate(pRoot);
    }
	
}

// Hàm kiểm tra một cây có phải là BST không
bool isBST(NODE* pRoot, NODE* &prev) 
{
	if (!pRoot) 
    {
        return true;
    }
	bool checkLeft = isBST(pRoot->left, prev);
	if (prev) 
    {
		if (prev->key >= pRoot->key) return false;
	}
	prev = pRoot;
	bool checkRight = isBST(pRoot->right, prev);
	return checkLeft && checkRight;
}
// hàm kiểm tra có phải là AVL tree hay không
bool isAVL(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return true;
    }
    NODE* tmp = NULL;
    if(isBST(pRoot, tmp) == false) return false;
    int l = height(pRoot->left);
    int r = height(pRoot->right);
    bool checkLeft = isAVL(pRoot->left);
    bool checkRight = isAVL(pRoot->right);

    if(abs(l - r) <= 1 && checkLeft && checkRight)
    {
        return true;
    }
    return false;
}

// Hàm duyệt cây Left Node Right
void preOrder(NODE* pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }
    cout << pRoot->key << " ";
    preOrder(pRoot->left);
    preOrder(pRoot->right);
}
