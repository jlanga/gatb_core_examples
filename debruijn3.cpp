#include <gatb/gatb_core.hpp>

/* Graph creation from a bank and command line options*/

int main(int argc, char* argv[])
{
    // Check that there is at least one options
    if (argc < 2)
    {
        std::cerr << "You must provide a FASTA file uri." << std::endl;
        return EXIT_FAILURE;
    }
    
    try
    {
        // Create graph with the bank options
        Graph graph = Graph::create (Bakn::open(argv[1], "-abundance-min %d", 5));
        
        // Dump info on the graph
        std::cout << graph.getInfo() << std::endl;
        
        // Graph::create will take care about the bank object and will delete
        // it if nobody else needs it.
        // In other words: there is no need here to call delete on bank here.
    }
    catch (Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
