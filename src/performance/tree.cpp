#include "tree.hpp"

using std::deque;
using std::pair;
using std::string;
using std::unique_ptr;

void Tree::add (deque<string> keys, string const & value)
{
  // If we have reached the end of the path, store the value
  // and update the node's state
  if (keys.empty())
  {
    m_value_type = STRING;
    m_value = value;
    m_children.clear();
    return;
  }

  m_value_type = SUBTREE;
  std::string & subtree_key = keys.front();

  // child does not exist
  if (m_children.find(subtree_key) == m_children.end())
    m_children.emplace(subtree_key, new Tree());

  deque<string> new_keys(keys.begin() + 1, keys.end()); 
  m_children.at(subtree_key)->add(new_keys, value);
}

pair<bool, string> Tree::get (deque<string> keys)
{
  switch (m_value_type)
  {
    case NONE:
      return {false, ""};

    case STRING:
      if (keys.empty())
        return {true, m_value};
      return {false, ""};

    case SUBTREE:
      if (keys.empty())
        return {false, ""};
      std::string & key = keys.front();
      deque<string> new_keys(keys.begin() + 1, keys.end()); 
      return m_children.at(key)->get(new_keys);
  }
}

void Tree::write (std::ostream & out_stream) const
{
  // if no children, just print the value
  if (m_children.empty())
  {
    out_stream << '\"' << m_value << '\"';
    return;
  }

  // print the children
  out_stream << "{ ";
  for (auto child = m_children.begin(); child != m_children.end(); ++child)
  {
    if (child != m_children.begin())
      out_stream << ", ";
    out_stream << '\"' << child->first << "\" : ";
    child->second->write(out_stream);
  }
  out_stream << " }"; 
}