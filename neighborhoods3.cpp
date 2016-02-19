#include <gatb/gatb_core.hpp>

#undef NDEBUG
#include <cassert>

/* Node neighbor management: being more specific and querying for assembly */

int main(int argc, char* argv[])
{
    
    try
    {
        // Create graph from fake data bank
        Graph graph = Graph::create (
            new BankStrings("AATGC", NULL),
            "-kmer-size 4 -abundance-min 1 -verbose 0"
        );
        
        // Create an iterator
        Graph::Iterator<Node> it = graph.iterator<Node>();
        
        // Check that there are only 2 elements
        assert(it.len() == 2);
        
        // Loop over it
        for(it.start(); !it.isDone(); it.next())
        {
            // Save current node
            Node& current = it.item();
            
            // Get the string
            std::string s = graph.toString(current);
            
            if (s == "AATG")
            {
                // Suppose that we know the only possible successor transition
                // from this neghbor (NUCL_C). It could have been retrieved by 
                // any previous call to Graph::neighbors<Edge> method.
                
                // We want to get the successor of the current node, only by
                // giving the transition nucleotide.
                Node neighbor = graph.successor<Node> (current, NUCL_C);
                
                // !! This Graph::successor method does not check whether the 
                // neighbor actually belongs to the graph.
                // It is supposed here that the client knows perfectly that this
                // transition nucleotide is valid.
                // This possibility is available for performance matters since
                // checking graph membership may take some time.
                
                // Check the result
                assert( graph.toString( neighbor) == "ATGC");
                
                // There is an overloaded form for the Graph::successor method,
                // where the user can provide an extra boolean.
                // With this implementation, a check is done to be sure whether
                // the neighbor surely belongs to the graph.
                // If not so, the extra boolean is set to false, true otherwise.
                bool exists;
                Node potentialNeighbor;
                
                potentialNeighbor = graph.successor(current, NUCL_A, exists);
                assert (exists == false);
                
                potentialNeighbor = graph.successor(current, NUCL_C, exists);
                assert (exists == true);
                assert (graph.toString (potentialNeighbor) == "ATGC");
                
                potentialNeighbor = graph.successor(current, NUCL_G, exists);
                assert (exists == false);
                
                potentialNeighbor = graph.successor(current, NUCL_T, exists);
                assert (exists == false);
            }
        }
        
        std::cout << "Test OK" << std::endl;
    }
    catch(Exception& e)
    {
        std::cerr << "Exception: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;

}
