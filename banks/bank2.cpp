#include <gatb/gatb_core.cpp>
#include <iostream>

/* Bank 2: bank with exception management */

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "You must provide a bank" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Try & catch
    try
    {
        // Declare an input bank and use it locally
        IBank* inputBank = Bank::open (argv[1]);
        LOCAL (inputBank);
        
        // Create an iterator over this bank
        Iterator<Sequences>* it = inputBank->iterator();
        LOCAL (it);
        
        // Loop over the sequences
        for (it->first(); !it->isDone(); it->next())
        {
            // Get the sequence
            Sequence& seq = it->item();
            
            // Dump the data size and the comment
            std::cout << "[" << seq.getDataSize() << "]" << seq.getComment() << std::endl;
            
            // Dump the data
            std::cout << seq.toString() << std::endl;
        }
        
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
