#include <gatb/gatb_core.hpp>
#include <iostream>

/* Bank management 1 */

int main(int argc, char* argv[])
{
    // Get the file name from the argumenrs
    const char* filename = argc >= 2 ? argv[1] : "";
    
    // Declare a bank
    BankFasta b (filename);
    
    // Create an iterator over this bank
    BankFasta::Iterator it (b);
    
    // Loop over the sequences
    for(it.start(); !it.isDone(); it.next())
    {
        // Dump data size and comment
        std::cout
            << "["
            <<  it->getDataSize()
            << "] "
            << it->getComment()
            << std::endl;
       
        std::cout << it->toString() << std::endl;
            
    }
    
}
