#include <iostream>

using namespace std;

struct elem
{
    int key;
    elem *left, *right;
};

void add(int n, elem* &t)
{
    if (t == NULL)
    {
        t = new elem;
        t->key = n;
        t->left = t->right = NULL;
    }
    else
    {
        if (t->key < n)
            add(n, t->right);
        else
            add(n, t->left);
    }
}

void pre(elem* t)
{
    if (t)
    {
        cout << t->key << " ";
        pre(t->left);
        pre(t->right);
    }
}

void post(elem* t)
{
    if (t)
    {
        post(t->left);
        post(t->right);
        cout << t->key << " ";
    }
}

void inf(elem* t)
{
    if (t)
    {
        inf(t->left);
        cout << t->key << " ";
        inf(t->right);
    }
}

elem* search(int n, elem* t)
{
    if (t->key < n)
        return search(n, t->right);
    else if(t->key > n)
        return search(n, t->left);
    else
        return t;
}

elem* parent(int n, elem* t)
{
    elem* left = t->left;
    elem* right = t->right;
    
    if (t->key == n) return NULL;
    
    if (t->key < n)
    {
        if(right -> key == n)
            return t;
        return parent(n, t->right);
    }
    else
    {
        if(left ->key == n)
            return t;
        return parent(n, t->left);
    }
}

elem* par(elem* child, elem* t)
{
    elem* left = t->left;
    elem* right = t->right;
    if (t ->key < child->key)
    {
        if(right->key == child->key)
            return t;
        return par(child, t->right);
    }
    else
    {
        if(left->key == child->key)
            return t;
        return par(child, t->left);
    }
}

void swap(elem* a, elem* b)
{
    int temp = a -> key;
    a -> key = b -> key;
    b -> key = temp;
}

void del(int n, elem* t)
{
    
    elem* point = search(n, t);
    elem* p = parent(n, t);
    
    if(!point->left && !point->right)
    {
        if(p->right == point)
            p->right = NULL;
        else
            p->left = NULL;
    
        delete point;
    }
    else if(point->left && point->right)
    {
        elem* child = point -> left;
        int counter = 0;
        while(child->right)
        {
            child = child->right;
            counter ++;
        }
        
        elem* pa = par(child, t);
        
        if(child->left)
        {
            swap(child, child -> left);
            swap(child ->left, point);
            child ->left = NULL;
            delete child ->left;
        }
        else if(counter == 0)
        {
            swap(point, child);
            point ->left = NULL;
            delete point ->left;
        }
        else
        {
            swap(point, child);
            pa -> right = NULL;
            delete pa -> right;
        }
    }
    else
    {
        if(point->left)
        {
            swap(point, point->left);
            point->left = NULL;
            delete point->left;
        }
        else
        {
            swap(point, point->right);
            point->right = NULL;
            delete point->right;
        }
    }
    
    
    cout << "pre: ";
    pre(t);
    cout << endl << "post: ";
    post(t);
    cout << endl << "inf: ";
    inf(t);
    cout << endl;
}

int main() 
{
    elem *start = NULL;
    add(17, start);
    add(11, start);
    add(23, start);
    add(7, start);
    add(13, start);
    add(19, start);
    add(35, start);
    add(16, start);
    
    
    cout << "pre: ";
    pre(start);
    cout << endl << "post: ";
    post(start);
    cout << endl << "inf: ";
    inf(start);
    cout << "\nAfter: " << endl;
    del(17, start);
}
