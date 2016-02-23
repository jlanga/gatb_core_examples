#include <gatb/gatb_core.hpp>

/* Simple path (with edges) */

int main(int argc, char* argv[])
{
    try
    {
        size_t kmerSize = 11;
        char* seq = "AGGCGCTAGGGTAGAGGATGATGA";
        
        std::cout
            << "The initial sequence is "
            << seq
            << " and the kmer size is "
            << kmerSize
            << std::endl;
        
        // Create the graph from the sequence
        Graph graph = Graph::create(
            new BankStrings (seq, NULL),
            "-kmer-size %d -abundance-min 1 -verbose 0", kmerSize
        );
        
        // Make a node from the seq string
        Node node = graph.buildNode(seq);
        
        // Create an Edge iterator that iterates all the simple edges from the
        // first node. Note that inDeg = outDeg = 1
        Graph::Iterator<Edge> path =
            graph.simplePath<Edge> (node, DIR_OUTCOMING);
        
        // Iterate over that path:
        for (path.start(); !path.isDone(); path.next())
        {
            std::cout
                << "    ["
                << path.rank()
                << "] current item is "
                << graph.toString(path.item())
                << std::endl;
        }
        
        std::cout << "The simple path was " << path.rank() << " long" << std::endl;
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
