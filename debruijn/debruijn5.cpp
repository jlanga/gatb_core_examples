#include <gatb/gatb_core.hpp>

// Load graph from HDF5 file

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        std::cerr << "You must provide a HDF5 file." << std::endl;
        return EXIT_FAILURE;
    }
    
    try
    {
        Graph graph = Graph::load (argv[1]);
    }
    catch (Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
