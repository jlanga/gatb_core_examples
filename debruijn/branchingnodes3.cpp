#include <gatb/gatb_core.cpp>

/* Branching nodes 3: Working with edges */

int main(int argc, char* argv[])
{
    size_t kmerSize = 7;
    
    const char* sequences[] = {
        "AGGCGCTAGGGAGAGGATGATGAAA",
        "AGGCGCTCGGGAGAGGATGATGAAA",
        "AGGCGCTTGGGAGAGGATGATGAAA"
    };
    
    try
    {
        // Create the graph
        Graph graph = Graph::create (
            new BankStrings (sequences, ARRAY_SIZE(sequences)),
            "-kmer-size %d -abundance-min 1 -verbose 0", kmerSize
        );
        
        // Take the first node, which should be a branching node
        Node node = graph.buildNode (sequences[0]);
        
        // Retrieve the branching neighbors for the node (as BRANCHING EDGES!)
        Graph::Vector<BranchingEdge> branchingNeighbors =
            graph.successors<BranchingEdge> (node);
        
        std::cout 
            << "We found "
            << branchingNeighbors.size()
            << " branching neighbors from node "
            << graph.toString(node)
            << std::endl;
        
        // Iterate over the branching neighbors to print them
        for (size_t i = 0; i < branchingNeighbors.size(); i++)
        {
            // Note; we don't display all the transition nucleotides, only the
            // first transition nucleotide. We also display the number of 
            // transitions needed to link the two branching nodes.
            std::cout << graph.toString (branchingNeighbors[i]) << std::endl;
        }
        
    }
    
    catch(Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
