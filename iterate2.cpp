#include <gatb/gatb_core.hpp>

// Iterate in parallel

int main(int argc, char* argv[])
{
    // Check number of inputs
    if(argc < 2)
    {
        std::err << "You must provide a HDF5 file." << std::endl;
        return EXIT_FAILURE;
    }
    
    try
    {
        // Create a graph
        Graph graph = Graph::load(argv[1]);
        
        // Create an iterator from the graph
        Graph::Iterator<Node> it = graph.iterator<Node> ();
        
        // Set the number of cores
        size_t nbCores = 4;
        
        // Create a dispatcher object and use it to send jobs to the threads
        IDispatcher::Status status = 
            Dispacher(nbCores).iterate (it, [&graph] (const Node& node)
            {
                // This is the place where you should see what to do with each 
                // node
                // Remember to close the parenthesis!
            });
        std::cout 
            << "we used " 
            << status.nbCores 
            << " cores, elapsed time is "
            << status.time
            << " msec"
            << std::endl
    }
    catch(Exception& e)
    {
        std::err << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
