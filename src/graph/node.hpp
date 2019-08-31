#pragma once

namespace graph
{

	template <typename Key_t>
	class Node
	{
	private:
		Key_t key;
	public:
		Node (Key_t key) : key(key) {}
		Key_t get_key () const { return key; }
	};

  template <typename Key_t>
  bool operator == (Node<Key_t> const & lhs, Node<Key_t> const & rhs)
  {
    return lhs.get_key() == rhs.get_key();
  }

  template <typename Key_t>
  bool operator != (Node<Key_t> const & lhs, Node<Key_t> const & rhs)
  {
    return !(lhs == rhs);
  }

  template <typename Key_t>
  bool operator < (Node<Key_t> const & lhs, Node<Key_t> const & rhs)
  {
    return lhs.get_key() < rhs.get_key();
  }

} // namespace graph
