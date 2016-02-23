#include <gatb/gatb_core.hpp>
#include <iostream>

/* Bank 5: Usage of the Progress Iterator */

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "ERROR: Provide a file!" << std::endl;
        return EXIT_FAILURE;
    }
    
    try
    {
        // Declare an input bank and use locally
        IBank* inputBank = Bank::open(argv[1]);
        LOCAL (inputBank);
        
        // Iterator with progress messages
        ProgressIterator<Sequence> iter (*inputBank, "Iterating sequences");
        
        // Loop over the sequences
        for(it.start(); !it.isDone(); it.next())
        {
            // Do nothing
        }
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }

    return EXIT_SUCCESS;
}
