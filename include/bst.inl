#include "bst.h"


//Private insert
template < typename KeyType, typename ValueType, typename KeyTypeLess>
void BST< KeyType, ValueType, KeyTypeLess>::insert( BTNode * & root, const KeyType & key, const ValueType & value )
{
    if(root == nullptr){
        root = new BTNode(key, value);
        m_n_nodes++;
    }else{
        if(m_key_less(root->key, key)){
            insert(root->left, key, value);
        }else{
            insert(root->right, key, value);
        }
    }
}
//Public insert
template < typename KeyType, typename ValueType, typename KeyTypeLess>
void BST< KeyType, ValueType, KeyTypeLess >::insert( const KeyType & key , const ValueType & value )
{
    insert(m_root, key, value);
}
/*========================================================================================================*/
//Private contains
template < typename KeyType, typename ValueType, typename KeyTypeLess>
bool BST< KeyType, ValueType, KeyTypeLess >::contains( const BTNode * root , const KeyType & key ) const
{
    if (root != nullptr)
    {
        if (root->key == key)
        {
            return true;
        }else{
            if(m_key_less(root->key, key)){
                contains(root->left, key);
            }else{
                contains(root->right, key);
            }
        }
    }
    else{
        return false;        
    }

    //return false;
}
//Public contains
template < typename KeyType, typename ValueType, typename KeyTypeLess>
bool BST< KeyType, ValueType, KeyTypeLess >::contains(const KeyType & key ) const
{
    return contains(m_root, key);
}
/*========================================================================================================*/
//Private retrieve
template < typename KeyType, typename ValueType, typename KeyTypeLess>
bool BST< KeyType, ValueType, KeyTypeLess >::retrieve( const BTNode * root , const KeyType & key, ValueType & value ) const
{
    if (root != nullptr)
    {
        if (root->key == key)
        {
            value = root->data;
            return true;
        }else{
            if(m_key_less(root->key, key)){
                retrieve(root->left, key, value);
            }else{
                retrieve(root->right, key, value);
            }
        }
    }else
    {
        return false;    
    }    

    //return false;
}
//Public retrieve
template < typename KeyType, typename ValueType, typename KeyTypeLess>
bool BST< KeyType, ValueType, KeyTypeLess >::retrieve( const KeyType & key, ValueType & value ) const
{
    return retrieve(m_root, key, value);
}
/*========================================================================================================*/
//find_min
template < typename KeyType, typename ValueType, typename KeyTypeLess>
const ValueType & BST< KeyType, ValueType, KeyTypeLess >::find_min(void) const
{
    return get_smallest_leaf(root)->data;
}
//get_smallest_leaf
template < typename KeyType, typename ValueType, typename KeyTypeLess>
const typename BST< KeyType, ValueType, KeyTypeLess >::BTNode* BST< KeyType, ValueType, KeyTypeLess >::get_smallest_leaf(const BTNode * root) const
{
    if(root->left == nullptr)
    {
        return root;
    }else{
        return get_smallest_leaf(root->left);
    }
}
/*========================================================================================================*/
//find_max
template < typename KeyType, typename ValueType, typename KeyTypeLess>
const ValueType & BST< KeyType, ValueType, KeyTypeLess >::find_max(void) const
{
    return get_bigger_leaf(root)->data;
}
template < typename KeyType, typename ValueType, typename KeyTypeLess>
const typename BST< KeyType, ValueType, KeyTypeLess >::BTNode* BST< KeyType, ValueType, KeyTypeLess >::get_bigger_leaf(const BTNode * root) const
{
    if(root->right == nullptr)
    {
        return root;
    }else{
        return get_bigger_leaf(root->right);
    }
}
/*========================================================================================================*/
//Private remove
template < typename KeyType, typename ValueType, typename KeyTypeLess>
void BST< KeyType, ValueType, KeyTypeLess >::remove( BTNode * & root, const KeyType & key )
{
    //Tem dois filhos  
    //Tem um filho
    //É Folha
    
    if(root->key == key)
    {
        if(root->left != nullptr && root->right != nullptr)
        {
            const typename BST< KeyType, ValueType, KeyTypeLess >::BTNode* aux;
            aux = get_smallest_leaf(root->right);
            root->data = aux->data;
            root->key = aux->key;

            remove(root->right, aux->key);
        }else if(root->left != nullptr){
            root->data = root->left->data;
            root->key = root->left->key;

            remove(root->left, root->key);
        }else if(root->right != nullptr){
            root->data = root->right->data;
            root->key = root->right->key;

            remove(root->right, root->key);
        }else{
            delete(root);
            root = nullptr;
            m_n_nodes--;
        }
    }
}
//Public remove
template < typename KeyType, typename ValueType, typename KeyTypeLess>
void BST< KeyType, ValueType, KeyTypeLess >::remove(const KeyType & key )
{
    remove(m_root, key);
}
/*========================================================================================================*/
//Public inorder
template < typename KeyType, typename ValueType, typename KeyTypeLess>
template < typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::inorder( const BTNode * root, const UnaryFunction & visit ) const
{
    if(root == nullptr)
    {
        return;
    }else{
        inorder(root->left, visit);
        visit(root->data);
        inorder(root->right, visit);
    }
}
//Private inorder
template < typename KeyType, typename ValueType, typename KeyTypeLess>
template < typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::inorder(const UnaryFunction & visit ) const
{
    inorder(m_root, visit);
}
/*========================================================================================================*/
//Public preorder
template < typename KeyType, typename ValueType, typename KeyTypeLess>
template < typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::preorder( const BTNode * root, const UnaryFunction & visit ) const
{
    if(root == nullptr)
    {
        return;
    }else{
        visit(root->data);
        preorder(root->left, visit);
        preorder(root->right, visit);
    }
}
//Private preorder
template < typename KeyType, typename ValueType, typename KeyTypeLess>
template < typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::preorder(const UnaryFunction & visit ) const
{
    preorder(m_root, visit);
}
/*========================================================================================================*/
//Public postorder
template < typename KeyType, typename ValueType, typename KeyTypeLess>
template < typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::postorder( const BTNode * root, const UnaryFunction & visit ) const
{
    if(root == nullptr)
    {
        return;
    }else{
        postorder(root->left, visit);
        postorder(root->right, visit);
        visit(root->data);
    }
}
//Private postorder
template < typename KeyType, typename ValueType, typename KeyTypeLess>
template < typename UnaryFunction >
void BST< KeyType, ValueType, KeyTypeLess >::postorder(const UnaryFunction & visit ) const
{
    postorder(m_root, visit);
}
/*========================================================================================================*/
//Clone
template < typename KeyType, typename ValueType, typename KeyTypeLess>
typename BST< KeyType, ValueType, KeyTypeLess >::BTNode * BST< KeyType, ValueType, KeyTypeLess >::clone(const BTNode * root)   
{
    //Verifica o caso base, root é nulo
    //Cria um nó pra a nova árvore
    //Copia recursivamente cada nó seguindo a estrutura da árvore base
    //Retorna um ponteiro pra o nó da nova árvore

    if (root == nullptr)
    {
        return nullptr;
    }

    BTNode * newRoot = new BTNode(root->key, root->data);

    newRoot->left = clone(root->left);
    newRoot->right = clone(root->right);

    return newRoot; 
}
/*========================================================================================================*/
//Operator=
template<typename KeyType , typename ValueType, typename KeyTypeLess >
BST< KeyType, ValueType, KeyTypeLess > & BST< KeyType, ValueType, KeyTypeLess >::operator= (const BST< KeyType, ValueType, KeyTypeLess > & rhs)   
{
    m_key_less = rhs.m_key_less;
    delete(m_root);
    m_root = clone(rhs.m_root);
    m_n_nodes = rhs.m_n_nodes;

    return *this;
}
/*========================================================================================================*/
//Copy Constructor
 template<typename KeyType , typename ValueType, typename KeyTypeLess >
BST< KeyType, ValueType, KeyTypeLess >::BST  (const BST< KeyType, ValueType, KeyTypeLess > & other)   
{
    *this = other;
}
/*========================================================================================================*/
//Operator= List
template<typename KeyType , typename ValueType, typename KeyTypeLess >
BST< KeyType, ValueType, KeyTypeLess > ::BST(std::initializer_list< BST< KeyType, ValueType, KeyTypeLess >::node_content_type > ilist, const KeyTypeLess & comp) : m_key_less(comp)   
{
    m_n_nodes = 0;
    for( const auto & e : ilist )
    {
        //tree.insert( data[e].first, data[e].second );
        *this.insert(e.first, e.second);
    }

    //return *this;
}
/*========================================================================================================*/
 //Private Clear
template<typename KeyType , typename ValueType, typename KeyTypeLess >
void BST< KeyType, ValueType, KeyTypeLess >::clear(BTNode *& root)   
{
    //~BST();
    delete(root);
    m_n_nodes = 0;   
}
/*========================================================================================================*/
//Public Clear
template<typename KeyType , typename ValueType, typename KeyTypeLess >
void BST< KeyType, ValueType, KeyTypeLess >::clear( void )   
{
    return clear(m_root);
}
/*========================================================================================================*/