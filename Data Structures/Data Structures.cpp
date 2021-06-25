/*********Implementation of Singly Link List************/

#include <iostream>

using namespace std;
// link list methods and node structure
struct Node {
    int value;
    Node* next;
};
Node* head;
int sizeNodeList = 0;
void insertion(int newvalue);
void updation(int newvalue, int position);
void deletion(int removevalue);
void print();
Node* sort(Node* a);
Node* merge(Node* a, Node* b);
void search(int a);

// Binary search tree methods and node structure
struct bstnode {
    int value;
    bstnode* left;
    bstnode* right;
};

void bstInsertion(bstnode** root, int newValue);
void balanceBST(bstnode** pproot);
void inorder(bstnode* proot);


int main()
{
    bstnode* proot = nullptr;
    int opr, subopr, x, i, position;//operation , sub operation to be performed.
    bool exit = false;
    cout << "1. LinkList 2. BST" << endl;
    cin >> opr;
    switch (opr)
    { 
    case 1: //link list case
        while(!exit) {
            cout << "1. Insertion 2. Updation 3. Deletion 4. Traversal 5. Searching 6. Sorting 7. EXIT" << endl;
            cin >> subopr;
            switch (subopr)
            {
            case 1:
                cout << "How many numbers do you want to insert";
                cin >> i;
                while (i) {
                    cout << "Enter the number to be inserted" << endl;
                    cin >> x;
                    insertion(x);
                    i--;
                }
                cout << endl;
                break;
            case 2:
                cout << "Enter the number and the position at which it is to be updated"<<endl;
                cin >> x >> position;
                updation(x,position);
                break;
            case 3:
                cout << "Enter the number you want to be deleted"<<endl;
                cin >> x;
                deletion(x);
                break;
            case 4:
                print();
                break;
            case 5:
                cout << "Enter the number you want to search : ";
                cin >> x;
                search(x);
                break;
            case 6:
                head = sort(head);
                print();
                break;
            default:
                exit = true;
                break;
            }
        }
        exit = false;        
        break;
    case 2: // binary search tree case
        while (!exit) {
            cout << "1. Insertion 2. Updation 3. Deletion 4. Inorder 5. Searching 6. Sorting 7. EXIT" << endl;
            cin >> subopr;
            switch (subopr)
            {
            case 1:
                cout << "How many tree nodes do you want to insert";
                cin >> i;
                while (i) {
                    cout << "Enter the node to be inserted" << endl;
                    cin >> x;
                    cout << "root node " << &proot;
                    bstInsertion(&proot, x);
                    i--;
                }
                cout << endl;
                break;
            case 2:
                cout << "Enter the number and the position at which it is to be updated" << endl;
                cin >> x >> position;
                updation(x, position);
                break;
            case 3:
                cout << "Enter the number you want to be deleted" << endl;
                cin >> x;
                deletion(x);
                break;
            case 4:
                inorder(proot);
                break;
            case 5:
                cout << "Enter the number you want to search : ";
                cin >> x;
                search(x);
                break;
            case 6:
                head = sort(head);
                print();
                break;
            default:
                exit = true;
                break;
            }
        }
    
   
    default:
        break;
    }
    return 0;
}

void insertion(int newvalue) {
    
    Node* n =(Node*) malloc(sizeof(Node));
    if (n) {
        n->value = newvalue;
        n->next = head;
        head = n;
    }
    else cout << "memory could not be allocated";
    cout << "head "<<head;
   
}
void print() {
    cout << "Printing list"<<endl;
    Node* current;
    current = head;
    while (current != NULL) {
        cout << current->value << " -> ";
        current = current->next;
    }
    cout << "\n";
}
void updation(int newvalue, int position) {
    Node* current = head;
    int counter = 1;
    while (counter < position) {
        if (!current->next)
            break;
        current = current->next;
        counter++;
    }
    current->value = newvalue;
    cout << "value has been updated at location " << position << endl;
}
void deletion(int removevalue) {
    Node* current = head;
    Node* previous = NULL;
    if (head->value == removevalue) {
        head = head->next;
        free(current);
        previous = head;
        current = previous->next;
    }
    previous = current;
    current = current->next;
    while (current) {
        if (current->value == removevalue) {
            previous->next = current->next;
            free(current);
            current = previous->next;
        }
        previous = previous->next;
        current = current->next;

    }
}
Node* sort(Node* a) {
    if (a == NULL || a->next == NULL) {
        return a; 
    }
    
    Node* fast = a->next;
    Node* slow = a;
    Node* b;
       
    while (fast) {
        fast = fast->next;
        if (fast) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    b = slow->next;
    slow->next = NULL;
    Node* newa = sort(a);
    Node* newb = sort(b);
    Node* headref = merge(newa,newb);
    return headref;
    
}
Node* merge(Node* a, Node* b) {
    Node* s;
    Node* headref = NULL;
    if (a == NULL)return b;
    if (b == NULL)return a;

    if (a->value <= b->value) {
        s = a;
        a = a->next;
    }
    else {
        s = b;
        b = b->next;
    }
    headref = s;

    while (a && b) {
        if (a->value <= b->value) {
            s->next = a;
            s = a;
            a = s->next;
        }
        else {
            s->next = b;
            s = b;
            b = s->next;
        }
    }
    if (a == NULL)s->next = b;
    if (b == NULL)s->next = a;
    return headref;
}
void search(int a) {
    int position=1;
    int flag = 0;
    Node* current = head;
    while (current->next) {
        if (a == current->value) {
            cout << "Your node is at location : " << position<<endl;
            flag = 1;
            return;
        }
        position++;
        current = current->next;
    }
    if (flag == 0) {
        cout << "Value not found"<<endl;
    }
}

void bstInsertion(bstnode** pproot, int newValue) {
    bstnode* newNode = new bstnode;
    newNode->value = newValue;
    newNode->left = newNode->right = NULL;
    //cout << "new node created at address" <<newNode<< " with value "<<newNode->value<<endl;
    if (*pproot == NULL) {
        *pproot = newNode;
        //cout << "*pproot return" << *pproot;
        return;
    }
    else if (newValue <= (*pproot)->value) {
            bstInsertion(&((*pproot)->left), newValue);
    }
    else {
            bstInsertion(&((*pproot)->right), newValue);
    }
    
}
void balanceBST(bstnode** pproot) {

}
void inorder(bstnode* proot) {
    //print left child, root and then right child
    if (proot->left)
        inorder(proot->left);
    cout << proot->value << " ";
    if (proot->right)
        inorder(proot->right);
}
void preorder(bstnode* proot) {
    // print root, left child and then right child
    cout << proot->value << " ";
    if (proot->left)
        preorder(proot->left);
    if (proot->right)
        preorder(proot->right);
}

