#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <vector>
// these are the nodes that the map points to for each element
// the keytype represents the key, the valuetype represents the value its assigned to
template <typename KeyType, typename ValueType>
struct Node
{
    KeyType key;
    // values is declared as a vector so a key can have mulitple values
    std::vector<ValueType> values;
    Node* left, * right;
    Node(const KeyType k, const ValueType v)
    {
        key = k;
        values.push_back(v);
        left = right = nullptr;
    }
};

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
        }
        // constructor for iterator with specified index for where to point at for the values vector
        Iterator(int i)
            : index(i)
        {
        }
        // constructor for iterator with specified node assigned to it
        Iterator(Node<KeyType, ValueType>* n)
            : node(n)
        {
        }
        // return the value at index from node's value vector
        ValueType& get_value() const
        {
            return node->values[index];
        }
        // check if the current index is valid
        // if it's less than 0 or greater than the node's value vector's size, then it's invalid
        bool is_valid() const
        {
            if (index < 0)
                return false;
            if (index >= node->values.size())
                return false;
            return true;
        }
        // increment index by one to advance iterator to the next value
        void advance()
        {
            index++;
        }

      private:
          // an iterator just needs a node to watch and an index for which value to watch
          Node<KeyType, ValueType>* node;
          int index = 0;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        // deallocate every Node in the tree
        freeTree(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        // if there's no root, the tree is empty so immediately set it equal to current key/value
        if (m_root == nullptr)
        {
            m_root = new Node<KeyType, ValueType>(key, value);
            return;
        }
        // iterative implementation:
        // keep looping through the map, keeping track of which node is currently being pointed to
        // start it at root node and keep looping until either we find the key/value pair or insert one ourselves
        Node<KeyType, ValueType>* cur = m_root;
        while (true)
        {
            // if current node key watches input key, then add the value to the node's value vector
            if (key == cur->key)
            {
                cur->values.push_back(value);
                return;
            }
            // if key is less than current node, we need to go to the left of the map
            if (key < cur->key)
            {
                // if the current node has a left child, assign current to that child
                if (cur->left != nullptr)
                {
                    cur = cur->left;
                }
                // otherwise insert the key/value as current node's left child and exit the loop
                else
                {
                    cur->left = new Node<KeyType, ValueType>(key, value);
                    return;
                }
            }
            // if key is greater than current node, we need to go the the right of the map
            else if (key > cur->key)
            {
                // if the current node has a right child, assign current to that child
                if (cur->right != nullptr)
                    cur = cur->right;
                // otherwise insert the key/value as current node's right child and exit the loop
                else
                {
                    cur->right = new Node<KeyType, ValueType>(key, value);
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        // if root is nullptr the tree is empty, so return an invalid iterator
        if (m_root == nullptr)
        {
            return Iterator(-1);
        }
        // otherwise iteratively search through the tree until we find the key, keeping track of the current node we're looking at
        Node<KeyType, ValueType>* cur = m_root;
        while (true)
        {
            // if key equals current node's key, we've found the value so we can return an iterator assigned to this node
            if (key == cur->key)
            {
                return Iterator(cur);
            }
            // otherwise if key is less than current node's key, we need to go left
            if (key < cur->key)
            {
                // if there is a left child, assign current to that node
                if (cur->left != nullptr)
                {
                    cur = cur->left;
                }
                // otherwise the key is not in the tree, return invalid iterator
                else
                {
                    return Iterator(-1);
                }
            }
            // if key is greater than current node's key we need to go right
            else if (key > cur->key)
            {
                // if current node has a right child, assign current to that child
                if (cur->right != nullptr)
                    cur = cur->right;
                // otherwise the key is not in the tree, return invalid iterator
                else
                {
                    return Iterator(-1);
                }
            }
        }
    }
    

  private:
      Node<KeyType, ValueType>* m_root;
      void freeTree(Node<KeyType, ValueType>* cur)
      {
          // if the current node is null, immediatley return
          if (cur == nullptr)
              return;
          // recursively call delete on the left and right children
          freeTree(cur->left);
          freeTree(cur->right);
          // delete the dynamically allocated memory that points to Node
          delete cur;
      }
};

#endif // TREEMULTIMAP_INCLUDED
