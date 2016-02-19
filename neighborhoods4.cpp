#include <gatb/gatb_core.hpp>

/* Branching Nodes: Working with neighbors 2 */

int main(int argc, char* argv[])
{
    size_t kmerSize = 7;
    
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
        Graph graph = Graph::create (
            new BankStrings(sequences, ARRAY_SIZE(sequences)),
            "-kmer-size %d -abundance-min 1 -verbose 0", kmerSize
        );
        
        // Get the first node
        Node node = graph.buildNode(sequences[0]);
        
        // Get the branching neighbors of node
        Graph::Vector<BranchingNode> branchingNeighbors =
            graph.successors<BranchingNode> (node);
        
        std::cout 
            << "We found "
            << branchingNeighbors.size()
            << " branching neighbors from node"
            << graph.toString(node)
            << std::endl;
        
        // Loop over those neighbors and print them
        for (size_t i = 0; i < branchingNeighbors.size(); i++)
        {
            std::cout << graph.toString(branchingNeighbors[i]) << std::endl;
        }
    }
    
    
    catch(Exception& e)
    {
        std::cerr << "Exception: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
