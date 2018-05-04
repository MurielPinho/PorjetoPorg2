#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>

#include "cwcreator.h"

using namespace std;


void          beginProgram();
int           options();
void          CreateDictionary();
void          puzzleCreator();
bool          VerifyWord(string word);
vector<string>searchWord(string word);
string        strFix(string s);
string        strLower(string s);


void          Dictionary::CreateDictionary()
{
  string   file4read, file4write, line, key, synonym;
  ifstream infile, outfile;
  regex    reg("[A-Za-z: ,]+");
  char    *tok = NULL, *write = NULL;
  bool     FirstWord;

  getline(cin, file4read);

  infile.open(file4read);


  if (infile.fail())
  {
    cerr << "Error opening file: " << file4read << endl;
    exit(1);
  }


  while (!infile.eof())
  {
    // Conversao para char* com o objetivo de utilizar strtok
    getline(infile, line);
    write = new char[line.length() + 1];
    strcpy(write, line.c_str());
    FirstWord = true;


    // Separação de palavras simples
    if (regex_match(line, reg))
    {
      tok = strtok(write, ":,");

      while (tok != NULL)
      {
        if (tok[0] == ' ') tok = &tok[1];

        if (tok[strlen(tok) - 1] == ' ') tok[strlen(tok) - 1] = '\0';

        if (FirstWord)
        {
          key = strFix(tok);
          inGameDictionary.push_back(key);
          FirstWord = false;
        }
        else
        {
          synonym = strLower(tok);
          Synonyms[key].push_back(synonym);
        }
        tok = strtok(NULL, ":,");
      }
    }
  }

  infile.close();
}

void Dictionary::showDictionary()
{
  for (size_t i = 0; i < inGameDictionary.size(); i++)
  {
    cout << inGameDictionary.at(i) << endl;
  }
}

bool Dictionary::VerifyWord(string word)

{
  string temp;

  word = strFix(word);

  for (size_t i = 0; i < inGameDictionary.size(); i++) {
    temp = inGameDictionary.at(i);

    if (word == temp)
    {
      return true;
    }
  }
  return false;
}

string Dictionary::strFix(string s)
{
  bool first = true;

  for (size_t i = 0; i < s.size(); i++)
  {
    if (first) {
      if (islower(s.at(i)))
      {
        s.at(i) = toupper(s.at(i));
      }
      first = false;
    }
    else
    {
      if (isupper(s.at(i)))
      {
        s.at(i) = tolower(s.at(i));
      }
    }
  }
  return s;
}

string Dictionary::strLower(string s)
{
  for (size_t i = 0; i < s.size(); i++)
  {
    if (isupper(s.at(i)))
    {
      s.at(i) = tolower(s.at(i));
    }
  }
  return s;
}

vector<string>Dictionary::searchWord(string word)
{
  vector<string> words;
  int flag = 0;

  for (size_t i = 0; i < inGameDictionary.size(); i++)
  {
    if (inGameDictionary.at(i).size() >= word.size())
    {
      for (size_t j = 0; j < word.size(); j++)
      {
        for (size_t k = 0; k < inGameDictionary.at(i).size(); k++)
        {
          if (tolower(word.at(j)) == tolower(inGameDictionary.at(i).at(k)))
          {
            flag = 1;
            k    = inGameDictionary.at(i).size();
          }
          else
          {
            flag = 0;
          }
        }

        if (flag == 0)
        {
          j = word.size();
        }
      }

      if (flag != 0)
      {
        words.push_back(inGameDictionary.at(i));
      }
    }
  }

  for (size_t i = 0; i < words.size(); i++)
  {
    cout << words.at(i) << endl;
  }
  return words;
}

Board::Board()
{
  int lin, col;

  cin >> lin;
  cin >> col;
  cin.ignore();
  vector<vector<char> > words(lin, vector<char>(col, '.'));
  system("clear");
  cout << "   ";

  for (int i = 97; i < col + 97; i++)
  {
    cout << char(i) << " ";
  }
  cout << endl;

  for (int i = 0; i < lin; i++)
  {
    cout << char(i + 65) << " ";

    for (size_t j = 0; j < col; j++)
    {
      cout << " " << words.at(i).at(j);
    }
    cout << endl;
  }
}

void Board::showBoard()
{}
