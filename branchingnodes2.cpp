#include <gatb/gatb_core.hpp>

/* Branching nodes 2: working with branching neighbors of a node */

int main(int argc, char* argv[])
{
    size_t kmerSize = 7;
    
    // We define some sequences used for building the test graph. Note that the
    // sequences have a difference at index == kmerSize, so the initial node 
    // AGGCGCT has 3 counting outcoming neighbors (and therefore is a branching
    // node).
    
    const char* sequences[] =
        {
        //      x <- difference here
        "AGGCGCTAGGGAGAGGATGATGAAA",
        "AGGCGCTCGGGAGAGGATGATGAAA",
        "AGGCGCTTGGGAGAGGATGATGAAA"
        };
    
    try
    {
        // Create graph
        Graph graph = Graph::create(
            new BankStrings (sequences, ARRAY_SIZE(sequences)),
            "-abundance-min 1 -verbose 0",
            kmerSize
        );
        // Get the first node
        Node node = graph.buildNode(sequences[0]);
        
        // Retrieve the branching neighbors
        Graph::Vector<BranchingNode> branchingNeighbors =
            graph.successors<BranchingNode> (node);
        
        std::cout
            << "We found "
            << branchingNeighbors.size()
            << " branching neighbors from node "
            << graph.toString(node)
            << std::endl;
        
        // Loop over the branching neighbors
        for (size_t i = 0; i < branchingNeighbors.size(); i++)
        {
            std::cout << graph.toString(branchingNeighbors[i]) << std::endl;
        } 
        
        // Loop over the branching neighbors
        
    }
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
