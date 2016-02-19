#include <gatb/gatb_core.hpp>

/* Iteration through branching nodes */

int main(int argc, char* argv[])
{
    // Check that at least an HDF5 file is given
    if(argc < 2)
    {
        std::err << "Provide an HDF5 file" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        // Load the graph
        Graph graph = Graph::load(argv[1]);
        // Get an iterator made for branching nodes
        Graph::Iterator it = graph.iterator<BranchingNode> ();
        // Loop
        for(it.start(); !it.isDone(); it.next())
        {
            // Print rank and the node
            std::cout
                << "[" << it.rank() << "] " 
                << graph.toString(it.item()) << std::endl;
        }
    }
    catch(Exception& e)
    {
        std::err << "EXCEPTION: " << e.getMessage() << std::endl;    
    }

    return EXIT_SUCCESS;
}
