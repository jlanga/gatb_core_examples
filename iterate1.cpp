#include <gatb/gatb_core.hpp>

/* Iterate over the nodes */

int main (int argc, char* argv[])
{
    // Check if there is at least one argument
    if ( argc < 2)
    {
        std::cerr << "You must provide a HDF5 file." << std::endl;
        return EXIT_FAILURE;
    }
    
    try
    {
        // Load the graph
        Graph graph = Graph::load (argv[1]);
        
        // Create an iterator
        Graph::Iterator<Node> it = graph.iterator<Node> ();
        
        // Loop over each node in it
        for (it.first(); !it.isDone(); it.next())
        {
            node = it.item();
            std::cout << graph.toString(node) << std::endl;
        }
    }
    catch (Exception& e)
    {
        std::err << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
