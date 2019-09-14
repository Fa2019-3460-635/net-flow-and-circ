#pragma once

#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <string>

/**
 * Tree is a data structure for storing nested maps of strings, and it supports
 * outputing the data to a stream using a subset of JSON.
 */
class Tree
{
public:

	/**
	 * Adds a new leaf node to the tree, storing the given value inside.
	 *
	 * @param keys A list of keys representing a path from the root of the tree
	 *             to a leaf node.
	 *
	 * @param value The string to store at the leaf node.
	 */
	void
	add (std::deque<std::string> keys, std::string const & value);

	/**
	 * Retrieves the value that has been stored at the given key.
	 *
	 * @param keys A list of keys representing a path from the root of the tree
	 *             to a leaf node.
	 *
	 * @returns Returns a pair in which the first element is a boolean value and
	 *          the second element is a string.  The boolean value is true iff
	 *          the given key was found in the tree and it referred to a leaf node.
	 *          If the boolean value is true, then the string contains the value
	 *          at the leaf node.  Otherwise, the value of the string is
	 *          undefined.
	 */
	std::pair<bool, std::string>
	get (std::deque<std::string> keys);

	/**
	 * Outputs the contents of the tree structure using a subset of the JSON
	 * format.
	 */
	void
	write (std::ostream & out_stream) const;

private:
	enum ValueType {
		NONE,
		STRING,
		SUBTREE
	} m_value_type = NONE;
	std::string m_value;
	std::map<std::string, std::unique_ptr<Tree>> m_children;
};