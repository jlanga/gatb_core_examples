// We include what we need for the test
#include <gatb/gatb_core.hpp>

/*
Graph creation from the CL
*/

int main(int argc, char* argv[])
{
    // Get a command line parser with available options.
    IOptionsParser* parser = Graph::getOptionsParser();
    LOCAL (parser);
    
    // Use a try/catch block in case of problems when parsing
    try
    {
        //parse options
        parser->parse (argc, argv);
        
        // Create graph with the provided options
        Graph graph = Graph::create (parser->getProperties());
        
        // Dump info about the graph:
        std::cout << graph.getInfo() << std::endl;
    }
    catch (OptionFailure& e)
    {
        return e.displayErrors (std::cout);
    }
    catch (Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
