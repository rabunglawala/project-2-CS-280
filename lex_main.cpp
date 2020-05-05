/*
 * lex_main_rb46P2.cpp
 *
 * CS280
 * Spring 2020
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

#include "lex.h"

using namespace std;



int main(int argc,char *argv[])
{
    vector <string> flag;
    vector <string> file;
    vector <string> v_flag;
    vector <string> ids_flag;
    vector <string> identifires;
    ifstream fin;
    istream *in=&cin;
    
    
   /*collect all flags:
    for(int i=1; i<argc; i++)
    {
        string arg(argv[i]);
        if(arg.substr(0,1)=="-")
        {
            flag.push_back(arg);
        }
    }
    //collect file names:
    for(int i =1; i<argc; i++)
    {
        string fname(argv[i]);
        if(fname.substr(0,1) != "-")
        {
            file.push_back(fname);
        }
            
    }
    //chack valid flag name, and seaprate -id flags for identifires.
    for(int i=0; i<flag.size();i++)
    {
        string check(flag.at(i));
        if(check=="-v")
        {
            v_flag.push_back(check);
        }
        if(check == "-ids")
        {
            ids_flag.push_back(check);
        }
        if(check != "-v" && check != "-iconsts" && check != "-sconsts" && check != "-ids")
        {
            cout<<"UNRECOGNIZED FLAG "<<check<<endl;
            return -1;
        }
        
    }
    //check for extra file names.
    if(file.size()>1)
    {
        cout<<"ONLY ONE FILE NAME ALLOWED"<<endl;
        return -1;
    }*/
    //open file:
    //if(argc>=1)
   // {
        //for(int i=0; i<file.size();i++)
       // {
          //  string file_op(file.at(i));
            fin.open("good4.txt");
            in=&fin;
            
            if(!fin)
            {
                cout<<"CANNOT OPEN "<<endl;
                return -1;
            }
        //} 
    //}
    //Part 1 & Part 2 codes:
    string line;
    int LC=0;
    int tcounter=0;
    
    Tok t;
    while( (t=getNextToken(*in, LC)) != DONE && t != ERR ) 
    {
       tcounter++;
       //if(v_flag.size()>0)
      // {
        cout<<t<<endl;
      // }
       
      /* if(t==IDENT)
       {
           identifires.push_back(t.GetLexeme());
       }
       */
    }
    
    //print Error:
    if(t==ERR)
    {
        cout<<"Error on line "<<LC<<" ("<<t.GetLexeme()<<")"<<endl;
        return -1;
    }
    if(LC==0)
    {
        cout<<"Lines: "<<LC<<endl;
        return -1;
    }
    if(LC>0)
    {
      cout<<"Lines: "<<LC<<endl; 
      cout<<"Tokens: "<<tcounter<<endl;
    }
    
    /*print identifires:
    if(ids_flag.size()&&identifires.size()>0)
   	{
        sort(identifires.begin(),identifires.end());
        cout<<"IDENTIFIERS: ";
        for(int i=0; i<identifires.size()-1;i++)
        {
            cout<<identifires.at(i)<<", ";
        }
        cout<<identifires.back()<<endl;
   	} */
    return 0;
}
