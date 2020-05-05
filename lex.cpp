/*
 * lex_cpp_rb46P2.cpp
 *
 * CS280
 * Spring 2020
 */

#include <iostream>
#include <map>
#include <fstream>
#include <iomanip>

#include "lex.h"

using namespace std;

map<Token,string> tok_Print =
{
    //Keywords:
    {PRINT,"PRINT"},
    {PRINTLN,"PRINTLN"},
    {REPEAT,"REPEAT"},
    {BEGIN,"BEGIN"},
    {END,"END"},

	//Identifiers:	
    {IDENT,"IDENT"},

	//Int & String Constant:	
    {ICONST,"ICONST"},
    {SCONST,"SCONST"},

	//Operator:
    {PLUS,"PLUS"}, 
    {MINUS,"MINUS"}, 
    {STAR,"STAR"}, 
    {SLASH,"SLASH"}, 
    {EQ,"EQ"},
    {LPAREN,"LPAREN"},
    {RPAREN,"RPAREN"},
    {SC,"SC"},
    
	//Error:
    {ERR,"ERR"},

	//Complete:	
    {DONE,"DONE"}
};
map<string,Token> Keywords =
{
    {"print",PRINT},
    {"println",PRINTLN},
    {"repeat",REPEAT}, 
    {"begin",BEGIN},
    {"end",END}
    
};
//checking for ICONST:
bool is_number(string s)
{
    
    for(char i:s)
    {
        if(!isdigit(s[i]))
            return false;
    }
			return true;

}
//checking for IDENT,ICONST,or KEYWORDS:
Tok ID_IC_KW(const string& lexeme, int LC)
{
  	Token t=IDENT;
    if(is_number(lexeme))
    {
        t=ICONST;
    }
   auto It = Keywords.find(lexeme);
   if( It != Keywords.end() )
       t = It->second;

   return Tok(t, lexeme, LC);
}
//output function:
ostream& operator<<(ostream& out, const Tok& tok)
{
    
    Token t=tok.GetToken();;
    out<<tok_Print[ t ];
    
    if(t == IDENT || t==ICONST)
        out<<"("<<tok.GetLexeme()<<")";
    
    return out;
}

//getting next token:
Tok getNextToken(istream& in, int& LC)
{
     enum TokState
    {
        BEGIN,
        INID,
        INSTRING,
        ININT,
        INCOMMENT
    };
    TokState lexstate= BEGIN;
    
    char ch;
    string lexeme;
    
    while(in.get(ch))
    {
      if(ch == '\n')
      {
           LC++;
      }
      switch(lexstate)
      {
          case BEGIN:
              if (isspace(ch))
                  continue;
             
             
              lexeme = ch;
              if(isalpha(ch))
              { 
                 lexstate = INID;
              }
              else if(ch == '"')
              {
                 lexstate = INSTRING;
              }
              else if (isdigit(ch))
              {
                 lexstate = ININT;
              }
              else if (ch == '/') 
              {
                  char peekch;
                  in.get(peekch);
                  if(peekch == ch)
                  {
                      lexstate = INCOMMENT;
                  }
                  else 
                  {
                     in.putback(peekch);
                     return Tok(SLASH,lexeme,LC);
                  }  
              }
              else if (ch=='!'||ch=='_'||ch=='$'||ch=='.')
            	{
               		 LC++;
                	return Tok(ERR,lexeme,LC);
            	}
              else {
               Token t = ERR;
               switch( ch )
               {
               case '+':
                   t = PLUS;
                   break;
               case '-':
                   t = MINUS;
                   break;
               case '*':
                   t = STAR;
                   break;
               case '(':
                   t = LPAREN;
                   break;
               case ')':
                   t = RPAREN;
                   break;
               case ';':
                   t = SC;
                   break;
                case '=':
                   t = EQ;
                   break;
                
               }
               return Tok(t, lexeme, LC);
           }
           break;

       case INID:
           if(isalpha(ch)|| isdigit(ch))
           {
               lexeme += ch;
           }
           else
           {
               if( ch == '\n' )
                   LC--;
               in.putback(ch);
               return ID_IC_KW(lexeme, LC);
           }  
           break;
      case INSTRING:
           lexeme += ch;
           char p;
           in.get(p);
           if(p != '\\')
           {
              in.putback(p);
           }
           if( ch=='\n' )
           {
              return Tok(ERR, lexeme, LC);
           }
           if(p=='\\')
           {
              in.get(ch);
           }
           if((p=='\\' && ch=='"')||ch=='\\')
               continue; 
           if( ch == '"' ) 
           {
               lexeme = lexeme.substr(1, lexeme.length()-2);
               return Tok(SCONST, lexeme, LC );
           }     
          break;
      case ININT:
           if(isdigit(ch))
           {
               lexeme += ch;
           }
           else if(isalpha(ch))
           {
               lexeme += ch;
               return Tok(ERR, lexeme, LC);
           }
           else
           {
               if( ch == '\n' )
                   LC--;
               in.putback(ch);
              return ID_IC_KW(lexeme, LC);
           }
           break;

       case INCOMMENT:
           	  if(ch=='\n')
              {
                 lexstate = BEGIN;    
              } 
           break;
       }       
      }
     if( in.eof() )
       return Tok(DONE, "", LC);
   return Tok(ERR, "Unknown Error", LC);
}
