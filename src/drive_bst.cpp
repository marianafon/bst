#include <iostream>   // cout, cin, endl
#include <utility>    // std::pair<>
#include <random>     // radom_device, mt19937, std::shuffle.
#include <iomanip>    // std::setw()
#include <string>     // std::string
#include <cassert>
#include <vector>
#include <algorithm>

#include "../include/bst.h"

/*
template<class T>
void print(const T &no)
{
    std::cout << no << std::endl;
}
*/
/*
struct IsOdd : public std::unary_function<std::string,void> {
  void operator() (std::string number) {std::cout << number << " - ";}
};
*/

void Print (std::string x) { std::cout << "-" << x; }

/*
template<class T>
struct print : public std::unary_function<T> {
    void operator() (const T &number) {std::cout << number << " - ";}
};
*/   

int main()
{
    auto n_unit{0}; // unit test count.

    // Our BST will store strings with integer keys.
    typedef std::pair< size_t,std::string > test_type;

    // Input data
    test_type data[] = {
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
        { 10, "ten" }
    };

    /*
    std::initializer_list<test_type> dataList[] = {
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
        { 10, "ten" }
    };
    */

    // Print the input
    {
        size_t insertion_order[] = { 5, 1, 7, 0, 3, 2 };
        // The tree declaration.
#define USE_FUNCTOR
#ifdef USE_FUNCTOR
        struct CompareKey {
            bool operator()( const size_t & a, const size_t & b )
            {
                return a > b ;
            }
        };
        BST< size_t, std::string, CompareKey > tree;
#else // Use lambda
        auto compare_keys = []( const size_t &a, const size_t &b )->bool
        {
            return a > b ;
        };
        //BST< size_t, std::string, decltype( compare_keys ) > tree( compare_keys );
#endif
        std::cout << ">>> Empty: " << tree.empty();
        std::cout << ">>> Size: " << tree.size() << std::endl;

        std::cout << ">>> Inserting data:\n";
        for( const auto & e : insertion_order )
        {
            std::cout << "< " << std::setw(3) << data[e].first << " , \"" << data[e].second << "\" >\n";
            tree.insert( data[e].first, data[e].second );
        }
        
        std::cout << "\n>>> Initial Tree:\n" << tree << std::endl;

        //BST< size_t, std::string, CompareKey > copyTree(tree);
        //std::cout << "\n>>> Copy Tree:\n" << copyTree << std::endl;
        //BST< size_t, std::string, CompareKey > copyTree(data, CompareKey);

        std::cout << ">>> Empty: " << tree.empty();        
        std::cout << ">>> Size: " << tree.size() << std::endl;;

        tree.remove(data[5].first);
        std::cout << "\n>>> Remove:\n" << tree << std::endl;
        std::cout << std::endl;

        std::cout << ">>> Size: " << tree.size() << std::endl;

        std::cout << ">>> Inorder:"<<std::endl;
        tree.inorder(Print);
        std::cout << std::endl;

        std::cout << ">>> Preorder:"<<std::endl;
        tree.preorder(Print);
        std::cout << std::endl;

        std::cout << ">>> Postorder:"<<std::endl;
        tree.postorder(Print);
        std::cout << std::endl;


        std::cout << ">>> Retrieve: 3 "<<std::endl;
        std::string value = "-";

        std::cout <<  "Valor antes: " << value;
        if (tree.retrieve(3, value)){
            std::cout <<  " Valor depois: " << value << std::endl;
        }else{
            std::cout <<  " Valor depois: " << value << " Não encontrado" << std::endl;
        }
         
        std::cout << ">>> Retrieve: 5 "<<std::endl;
        value = "-";
        std::cout <<  "Valor antes: " << value;        
        if (tree.retrieve(5, value)){
            std::cout <<  " Valor depois: " << value << std::endl;
        }else{
            std::cout <<  " Valor depois: " << value << " Não encontrado" << std::endl;
        }        
    
        std::cout << ">>> Contains: 7 ";
        if (tree.contains(7)){
            std::cout <<  "True" << std::endl;
        }else{
            std::cout <<  "False" << std::endl;
        }
         
        std::cout << ">>> Contains: 5 ";
        if (tree.contains(5)){
            std::cout <<  "True" << std::endl;
        }else{
            std::cout <<  "False" << std::endl;
        }        
    }

    return EXIT_SUCCESS;
}
