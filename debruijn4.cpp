#include <gatb/gatb_core.hpp>

// Graph creation from a fake bank and command line options

int main(int argc, char* argv[])
{
    // Fake bank with 3 seauences
    IBank* bank = new BankStrings(
        "ATCATCGATCGATCGTAGCGAT",
        "ACATCGATCGTACGTAGC",
        "CTAGCTGATCGTAGCTAGCTAGTATATAATCGATCG",
        NULL
    );

    try
    {
        Graph graph = Graph::create(bank, "-kmer-size 5 -abundance-min 1 -out mygraph");
        
        std::cout << graph.getInfo() << std::endl;
        
        // No need to delete graph
    }
    catch (Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }

}
