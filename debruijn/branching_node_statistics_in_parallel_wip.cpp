#include <gatb/gatb_core.hpp>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

/* Statistics about branching nodes in/out degerees */

int main(int argc, char* argv[])
{

    OptionsParser parser ("GraphStats");
    parser.push_back (new OptionOneParam (STR_URI_GRAPH, "graph input", true));
    parser.push_back (new OptionOneParam (STR_NB_CORES,  "nbcores", false, "0"));
    
    try
    {
        IProperties* options = parser.parse(argc, argv);
        
        // Load the graph
        Graph graph = Graph::load( options->getStr(STR_URI_GRAPH));
        
        // Set the specified number of cores
        size_t nbCores = options->getStr(STR_NB_CORES);
        
        // Get an iterator of branching nodes. Make it with a progress bar.
        ProgressGraphIterator<BranchingNode,ProgressTimer> itBranching(
            graph.iterator<BranchingNode>(), "statistics"
        );
        
        // Define unique identifiers for a couple (indegree, outdegree)
        typedef pair<size_t,size_t> InOut_t;
        
        // We want to gather some statistics during the iteration.
        // Note the use of ThreadObject: this object will be cloned N times (one
        // per thread) and each clone will be reachable within the iteration 
        // block through the ThreadObject::operator()
        ThreadObject <map <InOut, size_t> > topology;
        
        // Dispatch the iteration over the cores. Note the lambda expression
        IDipatcher::Status status = Dispatcher(nbCores).iterate (
            itBranching, [&] (const BranchingNode& node)
            {
                // Retrieve the current instance of map <InOut_t, size_t> for
                // the current running thread
                map <InOut_t, size_t>& localTopology = topology;
                
                // Get the branching node neighbors for the current branching 
                // node.
                Graph::Vector<BranchingEdge> successors   =
                    graph.successors  <BranchingEdge> (node);
                Graph::Vector<BranchingEdge> predecessors =
                    graph.predecessors<BranchingEdge> (node);
                
                // Increase de occurrences number for the current couple
                // (in/out) neighbors
                localTopology [
                    make_pair(predecessors.size(), successors.size())
                    ]++;
                
            }
        );
        
        // The parallel processing is done. We now retrieve the calculations
        // done in each thread in a single map.
        // To do so, we get each map<InOut_t, size_t> object filled in each 
        // thread, and we add its data into the global map
        // That global map is reachable through the ThreadObject::operator*.
        // The topology.foreach will loop over all cloned objects used in the 
        // threads.
        topology.foreach ([&] (const map <InOut_t, size_t>& t))
        {
            // Update the occurrences of the current couple in&out
            for each (t.begin; t.end(), [&] (const pair<InOut_t, size_t>& p)) {
                (*topology) [p.first] += p.secondM
            }
        }
        
    
    }
    catch (OptionFailure &e)
    {
        return e.displayErrors (std::cout);
    }
    catch (Exception& e)
    {
        cerr << "EXCEPTION: " << e.getMessage() << endl;
    }

    return EXIT_SUCCESS;

}
