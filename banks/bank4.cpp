#include <gatb/gatb_core.hpp>
#include <iostream>

/* Bank 4 : Iterating with a progress bar */

// Define a functor that will be called during bank parsing
struct ProgressFunctor : public IteratorListener { void inc (u_int64_t current)
    {
        std::cout << ".";
    }
};


/******************************************************************************/

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        std::cerr << "ERROR: There isn't even an input file"
        return EXIT_FAILURE;
    }
    
    try
    {
        // Create an input bank
        IBank* inputBank = Bank::open (argv[1]);
        LOCAL (inputBank);
        
        // Create an iterator with SubjectIterator, which will write something 
        // every 10 iterations
        SubjectIterator<Sequence> iter (inputBank->iterator(), 10);
        
        // Create a listener to be notified each 10 iterations and attach it to 
        // iterator.
        iter.addObserver( new ProgressFunctor());
        
        // Loop over the sequences
        for (iter.first(); !iter.isDone(); iter.next())
        {
            // Note that we don't need to do anything in the loop about progress
            // management, and therefore we only focus on what it has to be done.
        }
        
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }

    return EXIT_SUCCESS;
}
