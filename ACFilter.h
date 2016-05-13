
/****************************************
 * 字典树AC自动机多模匹配过滤
 * *************************************/

#ifndef ACFILTER
#define ACFILTER

#include "stdint.h"
#include <tr1/unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <map>
//#include <unordered_map>
using namespace std;
class ACFilter
{
public:
  ACFilter();
  virtual ~ACFilter();

  virtual bool Init();
  virtual bool ReloadKeyFile(const std::string& keyFile);

  virtual bool addWord(const std::string& word);
  virtual bool addWord(const std::set<std::string>& words);
  virtual bool isFilter(const std::string& word,std::string &);

  virtual bool clear();
  virtual bool ReBuild();

private:
  typedef struct trieNode
  {
    typedef std::tr1::unordered_map<char, trieNode*> childs_t;

    char val;
    bool isWord;
    childs_t childs;
    trieNode* fail;
    string keyWord;
    trieNode()
    {
      fail = NULL;
      isWord = 0;
      childs.clear();
    }
  }node;

private:
  void destroy(node*);

private:
  node* root;
};

#endif
