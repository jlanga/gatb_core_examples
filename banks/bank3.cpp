#include <gatb/gatb_core.hpp>
#include <iostream>

/* Bank 3: Iterating with functors */

// Why functors?
//  - multithreading
//  - reusing

struct Functor { void operator () (Sequence& s) const
{
    // dump data size and comment
    std::cout << "[" << s.getDataSize() << "]" << s.getComment() << std:endl;
    
    // Dump the data
    std::cout << s.toString () << std::endl;

}};

/******************************************************************************/

int main (int argc, char* argv)
{
    if (argc < 2)
    {
        std::cerr << "ERROR: Provide at least one argument" << std::endl;
        return EXIT_FAILURE;
    }

    // Declare an input bank and use it locally
    IBank* inputBank = Bank::open(argv[1]);
    LOCAL (inputBank);
    
    // create an iterator of this bank
    Iterator<Sequence>* it = inputBank->iterator();
    LOCAL (it);
    
    // Loop over the sequences in a "push" fashion (one functor call per seq)
    Functor fct;
    it->iterate (fct);

    return EXIT_SUCCESS;
}
