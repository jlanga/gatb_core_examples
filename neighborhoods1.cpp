#include <gatb/gatb_core.hpp>

#undef NDEBUG
#include <cassert>

// Node neighbors management with nodes

int main(int argc, char* argv[])
{
    try
    {
        // Create a fake bank with a 5 letter sequences and kmer length of 4
        Graph graph = Graph::create (
            new BankStrings ("AATGC", NULL),
            "-kmer-size 4 -abundance-min 1 -verbose 0"
        );
        
        // Get an iterator
        Graph::Iterator<Node> it = graph.iterator<Node>();
        
        // Check that there are two nodes
        assert(it.size() == 2);
        
        // Loop through the nodes
        for (it.first(); !it.isDone(); it.next())
        {
            Node& current = it.item();
            
            // Get the string of the node
            std::string s = graph.toString(current);
            
            // Check that it is one of both possible nodes
            assert(s == "AATG" || s == "ATGC");
            
            if(s == "AATG")
            {
                // Get the neighbors of this node current
                Graph::Vector<Node> neighbors = graph.successors<Node> (current);
                
                // Check that there is only a successor
                assert(neighbors.size() == 1);
                
                // Other way to check that
                assert(graph.outdegree(current) == 1);
                
                // Check it is the correct neighbor
                assert(graph.toString(neighbors[0]) == "ATGC");
            }
            
        }
        
        std::out << "Test OK" << std::endl;
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }


    return EXIT_SUCCESS;
}
