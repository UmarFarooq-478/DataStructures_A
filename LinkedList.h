#include <iostream>
using namespace std;
#include "Utility_Functions.h"







template <class T>
class Node {
public:
	T data;
	Node<T>* next;
	Node()
	{
	    next = NULL;
	}
	Node(T data)
	{
		this->data = data;
		this->next = NULL;
	}
};
template <class T>
class Linkedlist {
    public:
	Node<T>* head;
public:
	Linkedlist() {
	    head = NULL; 
	}
	bool isEmpty(){
        return !head;	    
	}
	void insert(T data)
{
    	Node<T>* newNode = new Node<T>(data);
    	if (head == NULL) {
    		head = newNode;
    		return;
    	}
    	Node<T>* temp = head;
    	while (temp->next != NULL) {
    		temp = temp->next;
    	}
    	temp->next = newNode;
    	
}

	void remove(T nodeOffset)
{
    if(!isEmpty())
    {
    	Node<T> *temp1 = head, *temp2 = NULL;
    	int ListLen = 0;
    
    	if (head == NULL) {
    		cout<<"List empty."<<endl;
    		return;
    	}
    	while (temp1 != NULL) {
    		temp1 = temp1->next;
    		ListLen++;
    	}
    	if (ListLen < nodeOffset) {
    		cout<<"Index out of range"<< endl;
    		return;
    	}
    	temp1 = head;
    	if (nodeOffset == 1) {
    		head = head->next;
    		delete temp1;
    		return;
    	}
    	while (nodeOffset-- > 1) {
    		temp2 = temp1;
    		temp1 = temp1->next;
    	}
    	temp2->next = temp1->next;
    	delete temp1;
    	
    }
    else
    {
        cout<<"List is empty"<<endl;
    }
}
void print()
{
	Node<T>* temp = head;
	if (head == NULL) {
		cout<<"List empty"<<endl;
		return;
	}
	while (temp != NULL) {
		cout<<temp->data<<" ";
		temp = temp->next;
	}
}

void removeMarks()
{
	Node<T>* temp = head;
	if (head == NULL) {
		cout<<"List empty"<<endl;
		return;
	}
	while (temp != NULL) {
		temp->data=removePunctuationMarks(temp->data);
		temp = temp->next;
	}
}

void toLower()
{
	Node<T>* temp = head;
	if (head == NULL) {
		cout<<"List empty"<<endl;
		return;
	}
	while (temp != NULL) {
		temp->data=uppertoLower(temp->data);
		temp = temp->next;
	}
}

int search(T data)
{
    if(!isEmpty())
    {
        int i=0;
        Node<T>* temp=head;
        while(temp!=NULL)
        {
            if(temp->data==data)
                return i;
            temp=temp->next;
            i++;
        }
        cout<<"Not Found";
        return -1;
    }
    return -1;
}
};

template<class T>
class MainListNode{
    public:
    Linkedlist<T> data;
    MainListNode<T> *next;
    MainListNode(){
        data=NULL;
    }
    MainListNode(Linkedlist<T> data)
    {
        this->data=data;
    }
};
template <class T>
class MainList{
    
public:
    MainListNode<T>* head;
    int size;
    double thresh_hold;
    	void insert(Linkedlist<T> data)
{
    	MainListNode<T>* newNode = new MainListNode<T>(data);
    	if (head == NULL) {
    		head = newNode;
    		return;
    	}
    	MainListNode<T>* temp = head;
    	while (temp->next != NULL) {
    		temp = temp->next;
    	}
    	temp->next = newNode;
    	
}

void print()
{
    MainListNode<T>* temp=head;
    int i=0;
    while(temp!=NULL)
    {
        cout<<"-----";
        temp->data.print();
        if(temp->next!=NULL)
            cout<<endl<<"|"<<endl;
        temp=temp->next;
        i++;
        
    }
}

void removeMarks()
{
    MainListNode<T>* temp=head;
    while(temp!=NULL)
    {
        temp->data.removeMarks();      
        temp=temp->next;
        
    }
}
void toLower()
{
    MainListNode<T>* temp=head;
    while(temp!=NULL)
    {
        temp->data.toLower();      
        temp=temp->next;
        
    }
}

};


