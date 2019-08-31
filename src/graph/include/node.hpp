#pragma once

namespace graph
{

	template <typename Key>
	class Node
	{

	private:
		Key key;

	public:

		Node (Key key)
		: key(key)
		{}

		Key get_key () const
		{
			return key;
		}

	};

  template <typename Key>
  bool operator == (Node<Key> const & lhs, Node<Key> const & rhs)
  {
    return lhs.get_key() == rhs.get_key();
  }

  template <typename Key>
  bool operator != (Node<Key> const & lhs, Node<Key> const & rhs)
  {
    return !(lhs == rhs);
  }

  template <typename Key>
  bool operator < (Node<Key> const & lhs, Node<Key> const & rhs)
  {
    return lhs.get_key() < rhs.get_key();
  }

} // namespace graph
