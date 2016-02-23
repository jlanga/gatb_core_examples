#include <gatb/gatb_core.hpp>

/* Create graph from command line string */

int main(int argc, char* argv[])
{
    // Check if at least 1 parameter is given from the command line
    if (argc < 2)
    {
        std::cerr << "You must provide a bank uri." << std::endl;
        return EXIT_FAILURE;
    }
    
    try
    {
        // Create the graph with the provided options:
        Graph graph = Graph::create ("-in %s", argv[1]);
        
        // Give some info on the graph on cout:
        std::cout << graph.getInfo() << std::endl;
    }
    catch (Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}

