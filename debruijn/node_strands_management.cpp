#include <gatb/gatb_core.hpp>

#undef NDEBUG
#include <cassert>

/* Node strand management */

int main (int argc, char* argv[])
{
    try
    {
    // Create a graph through a sequence
        Graph graph = Graph::create(
            new BankStrings("AATGC", NULL),
            "-kmer-size 5 -abundance-min 1 -verbose 0"
        );
        
        // Make a node iterator
        Graph::Iterator<Node> it = graph.iterator<Node>();
        
        // Check that there's only a node
        assert(it.size() == 1);
        
        // Get the node
        it.first(); Node& current = it.item();
        
        // Get the representation in characters
        std::string s = graph.toString(current);
        
        // Check that it is indeed that string
        assert(s == "AATGC");
        
        // Reverse the node
        Node other = graph.reverse(current);
        
        // Chech that it is the rc of the initial string
        assert( graph.toString(other) == "GCATT");
        
        // Check that both nodes are represented by the same kmer
        assert (current.kmer == other.kmer);
        
        std::cout << "Test Ok" << std:endl;
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
