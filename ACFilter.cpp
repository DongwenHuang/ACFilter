#include "ACFilter.h"

ACFilter::ACFilter()
{
  root = NULL;
}

ACFilter::~ACFilter()
{
if(root!=NULL)
  {
	this->clear();
  	destroy(root);
  	root = NULL;
  }
}

bool ACFilter::Init()
{
  if(root != NULL) return false;

  root = new node();
  root->val = 0;

  return true;
}

bool ACFilter::addWord(const std::string& word)
{

  node* p = root;
  std::string::const_iterator itWord = word.begin();

  while(itWord != word.end() )
  {
    node::childs_t& child = p->childs;
    node::childs_t::iterator it = child.find(*itWord);
    if(it != child.end())
    {
      p = it->second;
    }
    else
    {
      node* newNode = new node;
      newNode->fail = root;
      newNode->val  = *itWord;
      child[*itWord] = newNode;
      p = newNode;
    }
    ++itWord;
  }
  p->isWord = 1;
  p->keyWord=word;
  return true;
}

bool ACFilter::addWord(const std::set<std::string>& words)
{
}

bool ACFilter::isFilter(const std::string& word,std::string & keyWord)
{
  node* p = root;
  std::string::const_iterator it = word.begin();
  while(it != word.end())
  {
    node::childs_t& child = p->childs;
    if(child.find(*it) != child.end())
    {
      p = child[*it];
      node* tmp = p;
      while(tmp != root && tmp != NULL)
      {
        if(tmp->isWord)
        {
          keyWord=tmp->keyWord;
          return true;
        }
        tmp = tmp->fail;
      }
      ++it;
    }
    else
    {
      p = p->fail;
      if(p == NULL)
      {
        p = root;
        ++it;
      }
    }
  }
  return false;
}

bool ACFilter::ReBuild()
{
  std::queue<node*> que;
  que.push(root);

  while(!que.empty())
  {
    node* p = que.front();
    que.pop();

    node::childs_t &child = p->childs;
    node::childs_t::iterator it = child.begin();
    while(it != child.end())
    {
      node* tmp = p;
      while(tmp != NULL && tmp != root)
      {
        tmp = tmp->fail;
        if(tmp->childs.find(it->first) != tmp->childs.end())
        {
          it->second->fail = tmp->childs[it->first];
          break;
        }
      }
      que.push(it->second);
      ++it;
    }
  }

  return true;
}

bool ACFilter::ReloadKeyFile(const std::string& keyFile)
{
}

bool ACFilter::clear()
{
  for(node::childs_t::iterator it = root->childs.begin(); it!=root->childs.end(); ++it)
  {
    destroy(it->second);
  }
  root->childs.clear();
  return true;
}

void ACFilter::destroy(node* p)
{
  if(p == NULL)return;
  for(node::childs_t::iterator it = p->childs.begin(); it!=p->childs.end(); ++it)
  {
    destroy(it->second);
  }
  p->childs.clear();
  p->fail = NULL;

  delete p;
  p = NULL;
}

