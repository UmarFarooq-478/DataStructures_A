/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include "LinkedList.h"

#include <string.h>
#include <vector>
using namespace std;
//Main linked list i.e. TransactionLL
    MainList<string>TransactionLL;


void readInputFile(char* inputFilePath)
{
    //Creating fstream object and opening file
    ifstream obj;
    obj.open(inputFilePath);

    //string for reading values from file
    string file_word;
    
    //reading first line, i.e. Support Threshold and then storing it in a double variable
    getline(obj,file_word);
    double support_threshold=stof(file_word);
    TransactionLL.thresh_hold=support_threshold;
    //reading second line i.e. Number of transactions and storing it in a variable
    getline(obj,file_word);
    int n_transactions=stoi(file_word);
    TransactionLL.size=n_transactions;
    //Creating a string array of size n_transactions for storing all the transactions
    string transaction[n_transactions];
    
    //Temporary Vector that is used for tokenizing the string
    vector <string>items[n_transactions];
    
    
    
    //loop for iterating the file n_transactions times
    for(int i=0;i<n_transactions;i++)
    {
        getline(obj,transaction[i]);
        
        //Appends " " at start of every transaction string
        transaction[i]=" "+ transaction[i];
        
        //This divides the string into array of substrings separated by a ','
        tokenize(transaction[i],',',items[i]);
        
        //This is list of items i.e. an individual list in TransactionLL
        Linkedlist<string> list;
        
        //Inserting Tokenized strings into the individual list of items
        for(int j=0;j<items[i].size();j++){
              list.insert(items[i][j]);
        }
        
        //Inserting the list of items in main TransactionLL
        TransactionLL.insert(list);
    }
    
    //Displays the contents of TransactionLL
  //  TransactionLL.print();
}


void writingTransactionLLToFile (char* outputFilePath)
{
    ofstream obj;
    obj.open(outputFilePath);
    MainListNode<string>* temp=TransactionLL.head;
    while(temp!=NULL)
    {
       // temp->data.print();
        Node<string>* temp2 = temp->data.head;
    
    	while (temp2 != NULL) {
    		obj<<temp2->data;
    		    if(temp2->next!=NULL)
    		        obj<<",";
    		temp2 = temp2->next;
    	}
    	if(temp->next!=NULL)
        	obj<<endl;
        temp=temp->next;
    }
}
void generateFirstItemSet(char* LL_frequency){
    
    ofstream obj;
    obj.open(LL_frequency);
    double support_threshold=TransactionLL.size*TransactionLL.thresh_hold;
    vector<string> items;
    vector<int> items_count;
    int count=0;
    MainListNode<string>* temp=TransactionLL.head;
    while(temp!=NULL)
    {
       // temp->data.print();
        Node<string>* temp2 = temp->data.head;
    
    	while (temp2 != NULL) {
    		string obj=temp2->data;
    		bool found=0;
    		    for(int i=0;i<items.size();i++)
    		    {
    		        if(obj==items[i])
    		            {
    		             found=1;
    		             items_count[i]++;
    		            }
    		    }
    		    
    		    if(!found)
    		    {
    		        items_count.push_back(1);
    		        items.push_back(obj);
    		    }
    		temp2 = temp2->next;
    	}
        temp=temp->next;
    }
    for(int i=0;i<items.size();i++)
    {
        for(int j=0;j<items.size()-1;j++)
        {
            if(items_count[j]<items_count[j+1])
                {
                    int swap_vari=items_count[j];
                    items_count[j]=items_count[j+1];
                    items_count[j+1]=swap_vari;
                    
                    
                    string swap_var=items[j];
                    items[j]=items[j+1];
                    items[j+1]=swap_var;
                }
        }
    }
    bool written=0;
    for(int i=0;i<items.size();i++)
    {
      //  cout<<items[i]<<" "<<items_count[i]<<endl;
        if(items_count[i]>=support_threshold)
        {
            if(written)
            obj<<endl<<items[i]<<"("<<items_count[i]<<")";
            else{
                obj<<items[i]<<"("<<items_count[i]<<")";\
                written=1;
            }
        }
    }
    
    
    
    
    temp=TransactionLL.head;
    while(temp!=NULL)
    {
       // temp->data.print();
        Node<string>* temp2 = temp->data.head;
     Node<string>* prev = temp->data.head;
    	while (temp2 != NULL) {
    		string obj=temp2->data;
    		bool found=0;
    		    for(int i=0;i<items.size();i++)
    		    {
    		        if(obj==items[i] && items_count[i]<support_threshold)
    		            {
    		             prev->next=temp2->next;
    		            }
    		    }
    		    
    		    prev=temp2;
    		temp2 = temp2->next;
    	}
        temp=temp->next;
    }
}
//This function removes all punctuation marks from the TransactionLL
void removePunctuationMarks ()
{
    TransactionLL.removeMarks();
    
}

void convertUpperToLowerCase()
{
    TransactionLL.toLower();
}

class two_pair{
        
        public:
        string str[2];
        bool found(string s1="",string s2="")//returns true if value is found on any slot
        {
            if(s1=="" && s2=="")
            {
                cout<<"few arguments";
                return 0;
            }
            if(s2=="")
            return str[0]==s1 || str[1]==s1;
            else return (str[0]==s1 && str[1]==s2) || (str[1]==s1 && str[0]==s2);
        }
        two_pair()
        {
            str[0]="";
            str[1]="";
        }
        void additem(string s)//insert string on enmpty slot
        {
            if(str[0]=="")
                str[0]=s;
            else if(str[1]=="")
                str[1]=s;
        }
        bool isFull()
        {
            return str[0]!="" && str[1]!="";
        }
    };
void generateSecondItemSet(char* frequency_outputfile)
{
    ofstream obj;
    obj.open(frequency_outputfile);
    double support_threshold=TransactionLL.size*TransactionLL.thresh_hold;
 //   vector<two_pair> items;
    vector<int> items_count;
    int count=0;
    MainListNode<string>* temp=TransactionLL.head;
    vector<two_pair> items_main;
    while(temp!=NULL)
    {
       // temp->data.print();
        Node<string>* temp2 = temp->data.head;
        vector<two_pair> items;
        two_pair nobj;
        items.push_back(nobj);
    	while (temp2 != NULL) {
    		string obj=temp2->data;
    		bool found=0;
    		
    		    for(int i=0;i<items.size();i++)
    		    {
    		        //cout<<"here";
    		        if(!items[i].found(obj))
    		            {
    		               // cout<<"here";
        		             if(!items[i].isFull())
        		             {
        		                 items[i].additem(obj);
        		             }
        		             else
        		             {
        		                 two_pair new_obj;
        		                 new_obj.additem(items[i].str[0]);
        		                  new_obj.additem(obj);
        		                 items.push_back(new_obj);
        		                 
        		                 two_pair new_obj2;
        		                 new_obj2.additem(items[i].str[1]);
        		                 new_obj2.additem(obj);
        		                 items.push_back(new_obj2);
        		             }
    		            }
    		    }
    		    
    		  // if(!found)
    		  //  {
    		       // items_count.push_back(1);
    		      //  items.push_back(obj);
    		    //}
    		temp2 = temp2->next;
    	}
    	
    	
    	/*
    	cout<<"------------------------------"<<endl;
    	for(int i=0;i<items.size();i++)
    	{
    	    cout<<items[i].str[0]<<","<<items[i].str[1]<<endl;
    	}*/
    	
    	for(int i=0;i<items.size();i++)
    	{
    	    bool found=0;
    	    for(int j=0;j<items_main.size();j++)
    	        if(items_main[j].found(items[i].str[0],items[i].str[1]))
    	            {
    	                items_count[j]++;
    	                found=1;
    	            }
    	    if(!found)
    	    {
    	        items_main.push_back(items[i]);
    	        items_count.push_back(1);
    	    }       
    	    //cout<<items[i].str[0]<<","<<items[i].str[1]<<endl;
    	}
    	
    	
    	
    	
    //	cout<<"DOne"<<items.size();
        temp=temp->next;
    }
    
    
    for(int i=0;i<items_main.size();i++)
    {
        for(int j=0;j<items_main.size()-1;j++)
        {
            if(items_count[j]<items_count[j+1])
                {
                    int swap_vari=items_count[j];
                    items_count[j]=items_count[j+1];
                    items_count[j+1]=swap_vari;
                    
                    
                    two_pair swap_var=items_main[j];
                    items_main[j]=items_main[j+1];
                    items_main[j+1]=swap_var;
                }
        }
    }
    
    //cout<<"===================="<<endl;
    bool written=0;
    for(int i=0;i<items_main.size();i++)
    	{
    	    
    	   // cout<<items_main[i].str[0]<<","<<items_main[i].str[1]<<items_count[i]<<endl;
    	    if(items_count[i]>=support_threshold)
    	    {           
    	        if(written)
    	        {
    	           	    obj<<"\n"<<items_main[i].str[0]<<","<<items_main[i].str[1]<<"("<<items_count[i]<<")";
    	        }
    	        else
    	        {
    	            
    	                obj<<items_main[i].str[0]<<","<<items_main[i].str[1]<<"("<<items_count[i]<<")";
    	                written=1;
    	           
    	        }
    	    }
    	}
}














class three_set{
        
        public:
        string str[3];
        bool found(string s1="",string s2="",string s3="")//returns true if value is found on any slot
        {
            if(s1=="" && s2=="" && s3=="")
            {
                cout<<"few arguments";
                return 0;
            }
            if(s2=="" && s3=="")
            return str[0]==s1 || str[1]==s1;
            else if(s3=="")
            // To check if the strings exist in any arrangement
            return (str[0]==s1 && str[1]==s2) || (str[1]==s1 && str[0]==s2);    // s1,s2 or s2,s1
            else return (str[0]==s1 && str[1]==s2 && str[2]==s3) //s1,s2,s3
                     || (str[0]==s1 && str[2]==s2 && str[1]==s3) //s1,s3,s2
                     || (str[1]==s1 && str[0]==s2 && str[2]==s3) //s2,s1,s3
                     || (str[2]==s1 && str[0]==s2 && str[1]==s3) //s2,s3,s1
                     || (str[1]==s1 && str[2]==s2 && str[0]==s3) //s3,s1,s2
                     || (str[2]==s1 && str[1]==s2 && str[0]==s3);//s3,s2,s1
        }
        three_set()
        {
            str[0]="";
            str[1]="";
            str[2]="";
        }
        void additem(string s)//insert string on enmpty slot
        {
            if(str[0]=="")
                str[0]=s;
            else if(str[1]=="")
                str[1]=s;
            else if(str[2]=="")
                str[2]=s;    
        }
        bool isFull()
        {
            return str[0]!="" && str[1]!="" && str[2]!="";
        }
    };
void generateThirdItemSet(char* frequency_outputfile)
{
    ofstream obj;
    obj.open(frequency_outputfile);
    double support_threshold=TransactionLL.size*TransactionLL.thresh_hold;
 //   vector<three_set> items;
    vector<int> items_count;
    int count=0;
    MainListNode<string>* temp=TransactionLL.head;
    vector<three_set> items_main;
    while(temp!=NULL)
    {
       // temp->data.print();
        Node<string>* temp2 = temp->data.head;
        vector<three_set> items;
        three_set nobj;
        items.push_back(nobj);
    	while (temp2 != NULL) {
    		string obj=temp2->data;
    		bool found=0;
    		
    		    for(int i=0;i<items.size();i++)
    		    {
    		        //cout<<"here";
    		        if(!items[i].found(obj))
    		            {
    		               // cout<<"here";
        		             if(!items[i].isFull())
        		             {
        		                 items[i].additem(obj);
        		             }
        		             else
        		             {
        		                 three_set new_obj;
        		                 new_obj.additem(items[i].str[0]);
        		                  new_obj.additem(obj);
        		                 items.push_back(new_obj);
        		                 
        		                 three_set new_obj2;
        		                 new_obj2.additem(items[i].str[1]);
        		                 new_obj2.additem(obj);
        		                 items.push_back(new_obj2);
        		                 
        		                 three_set new_obj3;
        		                 new_obj3.additem(items[i].str[2]);
        		                 new_obj3.additem(obj);
        		                 items.push_back(new_obj2);
        		                 
        		             }
    		            }
    		    }
    		    
    		  // if(!found)
    		  //  {
    		       // items_count.push_back(1);
    		      //  items.push_back(obj);
    		    //}
    		temp2 = temp2->next;
    	}
    	
    	
    	
    /*	cout<<"------------------------------"<<endl;
    	for(int i=0;i<items.size();i++)
    	{
    	    cout<<items[i].str[0]<<","<<items[i].str[1]<<","<<items[i].str[2]<<endl;
    	}
    */	
    	for(int i=0;i<items.size();i++)
    	{
    	    bool found=0;
    	    for(int j=0;j<items_main.size();j++)
    	        if(items_main[j].found(items[i].str[0],items[i].str[1],items[i].str[2]))
    	            {
    	                items_count[j]++;
    	                found=1;
    	            }
    	    if(!found)
    	    {
    	        items_main.push_back(items[i]);
    	        items_count.push_back(1);
    	    }       
    	    //cout<<items[i].str[0]<<","<<items[i].str[1]<<endl;
    	}
    	
    	
    	
    	
    //	cout<<"DOne"<<items.size();
        temp=temp->next;
    }
    
    
    for(int i=0;i<items_main.size();i++)
    {
        for(int j=0;j<items_main.size()-1;j++)
        {
            if(items_count[j]<items_count[j+1])
                {
                    int swap_vari=items_count[j];
                    items_count[j]=items_count[j+1];
                    items_count[j+1]=swap_vari;
                    
                    
                    three_set swap_var=items_main[j];
                    items_main[j]=items_main[j+1];
                    items_main[j+1]=swap_var;
                }
        }
    }
    //cout<<"===================="<<endl;
    bool written=0;
    for(int i=0;i<items_main.size();i++)
    	{
    	    
    	   // cout<<items_main[i].str[0]<<","<<items_main[i].str[1]<<items_count[i]<<endl;
    	    if(items_count[i]>=support_threshold)
    	    {           
    	        if(written)
    	        {
    	           	    obj<<"\n"<<items_main[i].str[0]<<","<<items_main[i].str[1]<<","<<items_main[i].str[2]<<"("<<items_count[i]<<")";
    	        }
    	        else
    	        {
    	            
    	                obj<<items_main[i].str[0]<<","<<items_main[i].str[1]<<","<<items_main[i].str[2]<<"("<<items_count[i]<<")";
    	                written=1;
    	           
    	        }
    	    }
    	}
}

/*



int main()
{
    char* str="data.txt";
    readInputFile(str);
    removePunctuationMarks();
    writingTransactionLLToFile("AfterPunctuation.txt");
    cout<<"Removed Punctuation from original list and stored to \"AfterPunctuation.txt\""<<endl;
    
    convertUpperToLowerCase();
    writingTransactionLLToFile("AfterPunctuationUpperToLower.txt");
    cout<<"Converted Upper to lower case and stored to \"AfterPunctuationUpperToLower.txt\""<<endl;
    
    generateFirstItemSet("FrequencyItemSet.txt");
    cout<<"Generated First Item Set and stored to \"FrequencyItemSet.txt\""<<endl;
    
    writingTransactionLLToFile("afterFirstItemSet.txt");
    cout<<"After First Item set generation, TransactionLL stored to \"afterFirstItemSet.txt\""<<endl;
    
    generateSecondItemSet("FrequencyItemSet2.txt");
    cout<<"Generated Second Item Set and stored to \"FrequencyItemSe2.txt\""<<endl;
    
    generateThirdItemSet("FrequencyItemSet3.txt");
    cout<<"Generated Third Item Set and stored to \"FrequencyItemSet3.txt\""<<endl;
    return 0;
}
*/
