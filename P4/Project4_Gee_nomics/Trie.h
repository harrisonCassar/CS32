#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
	Trie();
	~Trie();
	void reset();
	void insert(const std::string& key, const ValueType& value);
	std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

	// C++11 syntax for preventing copying and assignment
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;
private:
	struct ChildNodePtr;

	struct Node
	{
		//holds values
		//holds vector of children
		std::vector<ValueType> values;
		std::vector<ChildNodePtr> children;
	};

	struct ChildNodePtr
	{
		//holds label
		//holds pointer to Node
		char label;
		Node* child;
	};

	void destructAllChildren(Node* cur);
	Node* findChild(Node* parent, char label);
	std::vector<ValueType> findHelper(Node* child, const std::string& key, int index);

	Node* m_root;
};

template<typename ValueType>
Trie<ValueType>::Trie()
{
	m_root = new Node;
}

template<typename ValueType>
Trie<ValueType>::~Trie()
{
	destructAllChildren(m_root);
}

//auxiliary recursive function for destructor
template<typename ValueType>
void Trie<ValueType>::destructAllChildren(Node* cur)
{
	std::vector<ChildNodePtr>::iterator it = cur->children.begin();

	//if children vector is empty, it will skip these recursive calls
	while (it != cur->children.end())
	{
		destructAllChildren(it->child);
		it++;
	}

	delete cur;
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
	destructAllChildren(m_root);

	m_root = new Node;
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
	Node* cur = m_root;

	for (int i = 0; i < key.size(); i++)
	{
		Node* next = findChild(cur,key[i]);
		if (next != nullptr) //found child
		{
			cur = next;
		}
		else
		{
			ChildNodePtr temp;
			temp.label = key[i];
			temp.child = new Node;
			cur->children.push_back(temp);
			cur = cur->temp.child;
		}
	}

	cur->values.push_back(value);
}

template<typename ValueType>
Trie<ValueType>::Node* Trie<ValueType>::findChild(Node* parent, char label)
{
	if (parent->children.empty())
		return nullptr;

	std::vector<ChildNodePtr>::iterator it = parent->children.begin();

	while (it != parent->children.end())
	{
		if ((*it).label == label)
			return (*it).child;
	}

	return nullptr;
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
	return findHelper(m_root, key, 0);
}

template <typename ValueType>
std::vector<ValueType> Trie<ValueType>::findHelper(Node* cur, const std::string& key, int index)
{
	if (cur == nullptr)
	{
		std::vector<ValueType> temp;
		return temp;
	}

	if (index == key.size())
		return cur->values;

	Node* child = findChild(cur, key[index]);

	if (child == nullptr)
	{
		std::vector<ValueType> temp;
		return temp;
	}
	else
	{
		return findHelper(child, key, index + 1);
	}
}

#endif // TRIE_INCLUDED
