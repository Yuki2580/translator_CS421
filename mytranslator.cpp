#include<iostream>
#include<fstream>
#include<string>

using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: ** 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Yuki Tagawa
// RE:   **
bool word (string s)
{

  int state = 0;
  int charpos = 0;

  while(s[charpos] != '\0')
    {
      if(state==0 && (s[charpos]=='u'|| s[charpos]=='a'|| s[charpos]=='i'|| s[charpos]=='e'||s[charpos]=='o'||s[charpos]=='I'||s[charpos]=='E' || s[charpos]=='n'))
	state=0;
      else if(state==0 && (s[charpos]=='d'|| s[charpos]=='w'|| s[charpos]=='z'|| s[charpos]=='y'|| s[charpos]=='j'))
	state=2;
      else if(state==0 && (s[charpos]=='b'|| s[charpos]=='m'|| s[charpos]=='k'|| s[charpos]=='n'||s[charpos]=='h'||s[charpos]=='p'||s[charpos]=='r'||s[charpos]=='g'))
	state=3;
      else if(state==0 && s[charpos]=='t')
	state=4;
      else if(state==0 && s[charpos]=='s')
        state=5;
      else if(state==0 && s[charpos]=='c')
        state=6;
      else if(state==1 && (s[charpos]=='u'|| s[charpos]=='a'|| s[charpos]=='i'|| s[charpos]=='e'||s[charpos]=='o'||s[charpos]=='I'||s[charpos]=='E'))
	state=0;

      else if(state==1 && s[charpos]=='n')
	state=0;

      else if(state==2 && (s[charpos]=='u'|| s[charpos]=='a'|| s[charpos]=='i'|| s[charpos]=='e'||s[charpos]=='o'||s[charpos]=='I'||s[charpos]=='E'))
	{
	  state=1;
	  if(s[charpos+1]!='n')
	    state=0;
	}
      else if(state==3 && s[charpos]=='y')
	state=2;
      else if(state==3 && (s[charpos]=='u'|| s[charpos]=='a'|| s[charpos]=='i'|| s[charpos]=='e'||s[charpos]=='o'||s[charpos]=='I'||s[charpos]=='E'))
	{
          state=1;
          if(s[charpos+1]!='n')
            state=0;
	}

      else if(state==4 && s[charpos]=='s')
	state=2;
      else if(state==4 && (s[charpos]=='u'|| s[charpos]=='a'|| s[charpos]=='i'|| s[charpos]=='e'||s[charpos]=='o'||s[charpos]=='I'||s[charpos]=='E'))
	{
          state=1;
          if(s[charpos+1]!='n')
            state=0;
	}
      else if(state==5 && s[charpos]=='h')
        state=2;
      else if(state==5 && (s[charpos]=='u'|| s[charpos]=='a'|| s[charpos]=='i'|| s[charpos]=='e'||s[charpos]=='o'||s[charpos]=='I'||s[charpos]=='E'))
        {
          state=1;
          if(s[charpos+1]!='n')
            state=0;
	}
      else if(state==6 && s[charpos]=='h')
        state=1;
      else if(state==1 &&  (s[charpos]=='u'|| s[charpos]=='a'|| s[charpos]=='i'|| s[charpos]=='e'||s[charpos]=='o'||s[charpos]=='I'||s[charpos]=='E') && s[charpos+1]=='\0')
	state=0;
      else
	{
	  state=-1;
	  break;
	}


      charpos++;
    }
  cout<<endl;

  if(state==0)
    return true;
  else
    return false;
}

// PERIOD DFA 
// Done by: **
bool period (string s)
{  // complete this **
  if(s==".")
    return true;
  else
    return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Yuki Tagawa

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, ACTOR, DESCRIPTION, ACTION, TO, TENSE};     


// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "ACTOR", "DESCRIPTION", "ACTION", "TO", "TENSE"}; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
string reservetables[30] = {"masu", "masen", "mashita", "masendeshita", "desu", "deshita", "o", "wa", "ni", "watashi", "anata", "kare", "kanojo", "sore", "mata", "soshite", "shikashi", "dakara", "eofm"};


// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file
ofstream outFile;

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: 
int scanner(tokentype& tt, string& w)
{
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   
  ifstream inputFile;
  string a, b;
  bool check=false;
  int count=0;
  fin>>a;
  w=a;
  int index=w.size();
  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
  */
  if(period(w))
    {
      cout<<endl;
      tt=PERIOD;
      return tt;
    }

  if(w=="eofm")
    {
      tt=EOFM;
      return tt;
    }
  
  if(word(w)!=true && period(w)!=true)
    {
      cout<<"Lexical error: "<<w<<" is not a valid token"<<endl;
      tt=ERROR;
      return tt;
    }
  /*3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.*/
 
  for(int s=0; s<30; s++)
    {
      string compare=reservetables[s];
      int count=reservetables[s].size();
    
      if(count==index)
	{
	  for(int i=0, p=0; p<count && i<index; i++, p++)
	    {
	      if(w[i]!=compare[p])
		{
		  break;
		}
	      else
		{
		  if(w[count-1]==compare[count-1] && i==index-1 && p==count-1)
		    {
		      if(s==0)
			tt=VERB;
		      else if(s==1)
			tt=VERBNEG;
		      else if(s==2)
			tt=VERBPAST;
		      else if(s==3)
			tt=VERBPASTNEG;
		      else if(s==4)
			tt=IS;
		      else if(s==5)
			tt=WAS;
		      else if(s==6)
			tt=OBJECT;
		      else if(s==7)
			tt=SUBJECT;
		      else if(s==8)
			tt=DESTINATION;
		      else if(s==9 || s==10 || s==11 || s==12 || s==13)
			tt=PRONOUN;
		      else if(s==14 || s==15 || s==16 || s==17)
			tt=CONNECTOR;
		      check=true;
		    }
		}
	    }
	}
      
      if(check==true)
	{
	  break;
	}
    }

  if(check==false)
    {
      if(w[index-1]=='u'|| w[index-1]=='a'|| w[index-1]=='i'|| w[index-1]=='e'||w[index-1]=='o'||w[index-1]=='n')
	{
	  tt=WORD1;
	}
      else
	{
	  tt=WORD2;
	}
    }
      /*
  4. Return the token type & string  (pass by reference)
  */
  return tt;
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika
//int main()
//{
//  tokentype thetype;
//string theword; 
//string filename;

//cout << "Enter the input file name: ";
//cin >> filename;

//fin.open(filename.c_str());

  // the loop continues until eofm is returned.
  // while (true)
// {
//     scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
//     if (theword == "eofm") 
// break;  // stop now
//     cout << "Type is:" << tokenName[thetype] << endl;
//     cout << "Word is:" << theword << endl;   
	 
//   }
// cout << "End of file is encountered." << endl;
// fin.close();   

//}// end

//#include<iostream>
//#include<fstream>
//#include<string>
//using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  


// ----- Additions to the parser.cpp ---------------------                                                    

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt                             
// Make sure it is easy and fast to look up the translation.                                                  
// Do not change the format or content of lexicon.txt                                                         
//  Done by: **                                                                                               



// ** Need the updated match and next_token with 2 global vars                                                                          
// saved_token and saved_lexeme                                                                                                         
tokentype saved_token;
string saved_lexeme;
bool token_available;
bool N=false;


string lexicon[150];
string saved_E_word;

// ** Additions to parser.cpp here:                                                                          
// getEword() - using the current saved_lexeme, look up the English word                                      
// in Lexicon if it is there -- save the result                                                               
// in saved_E_word                                                                                            
//  Done by: **                                                                                               
void getEword()
{
  // outFile<<"lexeme: "<<saved_lexeme<<endl;
  bool flag=true;
  for(int i=0; i<150; i++)
    {
      
      if(saved_lexeme==lexicon[i])
	{
	  saved_E_word=lexicon[i+1];
	  //	  outFile<<"SAVE*****"<<saved_E_word<<endl;
	  flag=false;
	  break;
	}
    }
  if(tokenName[saved_token]=="WORD1" && flag==true)
    saved_E_word=saved_lexeme;
}

tokentype getToken(tokentype line_type)
{
  return line_type;
}


//    gen(line_type) - using the line type,                                                                   
//                     sends a line of an IR to translated.txt                                                
//                     (saved_E_word or saved_token is used)                                                  
//  Done by: **                                                                                               
void gen(tokentype line_type)
{
  //  cout<<tokenName[line_type]<<endl;

  switch(getToken(line_type))
    {
    case CONNECTOR:
      outFile<<"CONNECTOR: "<<saved_E_word<<endl;
      break;
    case ACTOR:
	outFile<<"ACTOR: "<<saved_E_word<<endl;
      break;    
    case ACTION:
      outFile<<"ACTION: "<<saved_E_word<<endl;
      break;  
    case TO:
      outFile<<"TO: "<<saved_E_word<<endl;
      break;
    case OBJECT:
      outFile<<"OBJECT: "<<saved_E_word<<endl;
      break;
    case TENSE:
      outFile<<"TENSE: "<<tokenName[saved_token]<<endl;
      outFile<<endl;
      break;
    case DESCRIPTION:
      outFile<<"DESCRIPTION: "<<saved_E_word<<endl;
    default:
      break;
    }
}



// Type of error: **
// Done by: ** 
ofstream outputFile;


void syntaxerror1(tokentype expected, string saved_lexeme)
{
  outputFile.open("errors.txt");
  
  char x;
  cout<<"SYNTAX ERROR: Expected "<<tokenName[expected]<<" but found "<<saved_lexeme<<endl;
  outputFile<<"SYNTAX ERROR: Expected "<<tokenName[expected]<<" but found "<<saved_lexeme<<endl;
  //cout<<"Skip or replace the token? (s or r)";
  //cin>>x;
  //if(x=='s')
  // else if(x=='r')
  
  outputFile.close();  
}


// Type of error: **
// Done by: ** 
void syntaxerror2(string fName, string saved_lexeme) 
{ 
  cout<<"SYNTAX ERROR: unexpected "<<saved_lexeme<<" found in "<<fName<<endl;
  exit(1);
}



// Purpose: **
// Done by: **
tokentype next_token()
{
  if(!token_available)
    {
      scanner(saved_token, saved_lexeme);
      token_available=true;
      cout<<"Scanner called using word: "<<saved_lexeme<<endl;
    }
  return saved_token;
}


// Purpose: **
// Done by: **
bool match(tokentype expected) 
{
  char x;
  if(next_token() != expected)  // mismatch has occurred with the next token
    { 
      // calls a syntax error function here to  generate a syntax error message here and do recovery      
      syntaxerror1(next_token(), saved_lexeme);
      cout<<"Skip or replace the token? (s or r)";
      cin>>x;
      if(x=='s')
	{
	  token_available=false;
	  next_token();
	  cout<<saved_lexeme<<endl;
	  return match(next_token());
	}
      else if(x=='r')
	{
	  token_available=false;
	  cout<<"Matched "<<tokenName[expected]<<endl;
	}
      return false;
    }
  else  // match has occurred
    {   
      cout<<"Matched "<<tokenName[expected]<<endl;
      token_available = false;  // eat up the token
      return true;              // say there was a match
    }  
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **
// Done by: **

void noun()
{
  cout<<"Processing <noun>"<<endl;
  switch(next_token())
    {
    case WORD1:
      match(WORD1);
      break;
    case PRONOUN:
      match(PRONOUN);
      break;
    default:
      syntaxerror2("noun", saved_lexeme);
    }
}


void verb()
{
  cout<<"Processing <verb>"<<endl;
  switch(next_token())
    {
    case WORD2:
      match(WORD2);
      getEword();
      break;
    default:
      syntaxerror2("verb", saved_lexeme);
    }
}

void tense()
{
  cout<<"Processing <tense>"<<endl;
  switch(next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      break;
    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;
    case VERB:
      match(VERB);
      break;
    case VERBNEG:
      match(VERBNEG);
      break;
    default:
      syntaxerror2("tense", saved_lexeme);
    }
}

void be()
{
  cout<<"Processing <be>"<<endl;
  switch(next_token())
    {
    case IS: 
      match(IS);
      gen(DESCRIPTION);
      gen(TENSE);
      break;
    case WAS: 
      match(WAS);
      gen(DESCRIPTION);
      gen(TENSE);
      break;
    default:
      syntaxerror2("be", saved_lexeme);
    }
}


void afterObject()
{
  cout<<"Processing <afterSubject>"<<endl;
  switch(next_token())
    {
    case WORD2:
      match(WORD2);
      getEword();
      gen(ACTION);
      tense();
      gen(TENSE);
      match(PERIOD);
      break;
    case WORD1:
      match(WORD1);
      getEword();
      match(DESTINATION);
      gen(TO);
      verb();
      getEword();
      gen(ACTION);
      tense();
      gen(TENSE);
      match(PERIOD);
      break;
    case PRONOUN:
      match(PRONOUN);
      getEword();
      match(DESTINATION);
      gen(TO);
      verb();
      getEword();
      tense();
      match(PERIOD);
      break;
    default:
      syntaxerror2("afterSubject", saved_lexeme);
    }
}

void afterNoun()
{
  cout<<"Processing <afrerNoun>"<<endl;
  switch(next_token())
    {
    case IS:
    case WAS:
      be();
      match(PERIOD);
      break;
    case DESTINATION:
      match(DESTINATION);
      gen(TO);
      verb();
      getEword();
      gen(ACTION);
      tense();
      gen(TENSE);
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      gen(OBJECT);
      afterObject();
      break;
    default:
      syntaxerror2("afterNoun", saved_lexeme);
    }
}


void afterSubject()
{
  cout<<"Processing <afterSubject>"<<endl;
  switch(next_token())
    {
    case WORD1:
    case PRONOUN:
      noun();
      getEword();
      afterNoun();
      break;
    case WORD2:
      verb();
      getEword();
      gen(ACTION);
      tense();
      gen(TENSE);
      match(PERIOD);
      break;
    default:
      syntaxerror2("afterSubject", saved_lexeme);
    }
}





void s()
{
  cout<<"Processing <s>"<<endl;

  switch(next_token())
    {
    case CONNECTOR:
      match(CONNECTOR);
      getEword();
      gen(CONNECTOR);
      noun();
      getEword();
      match(SUBJECT);
      gen(ACTOR);
      afterSubject();
      break;
    default:
      noun();
      getEword();
      match(SUBJECT);
      gen(ACTOR);
      afterSubject();
      break;
    }
}

void story()
{
  cout<<"Processing <story>"<<endl;
  s();
  while(true)
    {
      switch(next_token())
        {
        case CONNECTOR:
        case WORD1:
        case PRONOUN:
          s();
	  break;
	case EOFM:
	  cout<<"Successfully parsed <story>"<<endl;
	  cout<<endl;
	  N=true;
	  break;
        default:
          syntaxerror2("story", saved_lexeme);
        }
      if(N==true)
	break;
    }
}



//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **



//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

//#include<iostream>
//#include<fstream>
//#include<string>
//using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: **
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 


//string lexicon[100][2];
//string saved_E_word;

// ** Additions to parser.cpp here:                                                                          
// getEword() - using the current saved_lexeme, look up the English word                                  
// in Lexicon if it is there -- save the result                                             
// in saved_E_word                                                                          
//  Done by: **  
//void getEword()
//{
//  for(int i=0; i<100; i++)
//   {
//     if(saved_lexeme==lexicon[i][0])
//{
//  saved_E_word=lexicon[i][1];
//  break;
//}
//   }
//}


//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** 
//void gen(line_type)
//{
//  switch(line_type)
//  {
//  case CONNECTOR:
//    cout<<"CONNECTOR: "<<saved_E_word<<endl;
//  case ACTOR:
//    cout<<"ACTOR: "<<saved_E_word<<endl;
//  case ACTION:
//    cout<<"ACTION: "<<saved_E_word<<endl;
//  case TO:
//    cout<<"TO: "<<saved_E_word<<endl;
//  case OBJECT:
//    cout<<"OBJECT: "<<saved_E_word<<endl;
//  case ACTOR:
//    cout<<"ACTOR: "<<saved_E_word<<endl;
  // case TENSE:
   //   cout<<"TENSE: "<<saved_token<<endl;
//}
//}



// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  **
int main()
{
  string temp;
  int y=0;
  fin.open("lexicon.txt");
  outFile.open("translated.txt");
  while(fin >> temp)
    {
      lexicon[y]=temp;
      y++;
    }

  //  for(int i=0; i<150; i++)
  //  {
  //cout<<lexicon[i]<<endl;
  // }

  fin.close();
  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt 

  //** opens the output file translated.txt

  // outFile.open("translated.txt");
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file 
  //** closes traslated.txt
  fin.close();
  outFile.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

