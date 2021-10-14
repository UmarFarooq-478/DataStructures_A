/***
   *  This file contains the utility functions for accomplishing different tasks like string tokenizing , lower to uppercase etc.
   * 
   ***/
#include <vector>

void tokenize(string &str, char delim, vector<string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

string removePunctuationMarks(string str)
{
    string str2="";
    int str2_ind=0;
    for(int i=0;i<str.length();i++)
    {
        if(str[i]<'A')
            continue;
        str2.push_back(str[i]);
    }
//    for(int i=str2_ind;i<=str2.length();i++)
//        str2[i]='\n';
        
    return str2;
}


string uppertoLower(string str)
{
 
    string str2=str;
      
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>'A' && str[i]<'Z')
        str2[i]=tolower(str[i]);
    }
    return str2;
}