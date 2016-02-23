#include <gatb/gatb_core.hpp>

/* Simple path iteration with nodes */

int main(int argc, char* argv[])
{
    try
    {
        size_t kmerSize = 11;
        cost char* seq = "AGGCGCTAGGGTAGAGGATGATGA";
        
        std::cout
            << "The initial sequence is '"
            << seq
            << "', kmer size is"
            << kmerSize
            << std::endl;
        
        // We create the graph from a given sequence, and for a given kmer size
        Graph graph = Graph::create(
            new BankStrings( seq, NULL),
            "-kmer-size %d -abundance-min 1 -verbose 0", kmerSize
        );
        
        // Get the first node
        Node node = graph.buildNode(seq);
        
        // Create a node iterator that iterates over all the simple nodes from 
        // the first node. Rememeber that a simple node has inDeg = outDeg = 1
        Graph::Iterator<Node> path = 
            graph.simplePath<Node> (node, DIR_OUTCOMING);
        
        // Iterate over the simple path:
        for (path.start(); !path.isDone(); path.next())
        {
            std::cout
                << "    ["
                << path.rank()
                << "] current item is "
                << graph.toString(path.item())
                << std::endl;
        }
        
        std::cout
            << "The simple path was "
            << path.rank()
            << " long"
            << std::endl;
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
