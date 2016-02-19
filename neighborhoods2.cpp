#include <gatb/gatb_core.hpp>

#undef NDEBUG
#include <cassert>

/* Node neighbors management with edges 2*/

int main(int argc, char* argv[])
{
    try
    {
        // Create a graph from a fake bank with one sequence
        Graph graph = Graph::create(
            new BankStrings ("AATGC", NULL),
            "-kmer-size 4 -abundance-min 1 -verbose0"
        );
        
        // Create an iterator
        Graph::Iterator<Node> it = graph.iterator<Node>();
        
        assert(it.size() == 2);
        
        // Loop
        for(it.start(); !it.isDone(); it.next())
        {
            // Get the node that we are using right now
            Node node = it.item();
            
            // Convert it to a string
            std::string s = graph.toString(node);
            
            // We check that it is correct
            assert(s == "AATG" || s ==  "ATGC");
            
            if(s == "AATG")
            {
                // Get the successors of the current node (they are edges)
                Graph::Vector<Edge> neighbors = graph.successors<Edge> (current);
                
                // Check that there's only one
                assert(neighbors.size() == 1);
                
                // Check that it is the node we are looking for
                assert(graph.toString(neighbors[0].to) == "ATGC");
                
                // Check that the transition nt is ok
                assert(neighbors[0].nt == NUCL_C);
            }
            
        }
        
        std::cout << "Test OK" << std::endl;
    
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;

}
