#include <gatb/gatb_core.hpp>

/* Iterate over the graph nodes */

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "Please provide a HDF5 file." << std::endl;
        return EXIT_FAILURE;
    }
    
    try
    {
        // Load graph from file
        Graph graph = Graph::load(argv[1]);
        
        // Get an iterator for all nodes of the graph.
        Graph::Iterator<Node> it = graph.iterator<Node> ();
        
        // Loop over all nodes
        for(it.first(); !it.isDone(); it.next())
        {
            node = it.item();
            std::cout << graph.toString(node) << std::endl;
        }
    }
    catch (Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
