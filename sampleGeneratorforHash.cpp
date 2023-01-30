#include <iostream> 
#include <fstream>
#include <limits>
#include <random> 
#include <unordered_set> 
using namespace std;


/** 
 * It is bad data generator, as many un-inserted keys will be searched for or deleted from the hash table. 
*/
int main(int argc, char **argv)
{
    ofstream inputFile("input5.txt"); // output into the input.txt 
    ofstream outputFile("output.txt"); // output into the output.txt
    const string OPTIONS[3] = {"search", "insert", "delete"};
    unsigned int seed = 13354;
    unsigned int numOperations = 1000000; 
    unsigned int keyUpperBound = numeric_limits<int>::max(); 

    mt19937 rng(seed);
    uniform_int_distribution< unsigned int> valGen(0, keyUpperBound);
    discrete_distribution<unsigned int> optGen({40, 40, 20}); // generator for no. of {search, insert, delete}, 40% search, 40% insert, 20% delete. 

    unordered_set<unsigned int> hashTable; // hash table to store the keys, just for output a correct answer.
    for (unsigned int i = 0; i < numOperations; i++)
    {
        unsigned int opt = optGen(rng); 
        unsigned int val = valGen(rng); 
        inputFile << OPTIONS[opt] << " " << val << endl;

        if (opt == 0) // search
        {
            if (hashTable.find(val) != hashTable.end())
                outputFile << val << " was found" << endl;
            else
                outputFile << val << " does not exist" << endl;
        }
        else if (opt == 1) // insert
        {
            hashTable.insert(val); 
        }
        else // delete
        {
            if (hashTable.find(val) != hashTable.end())
            {
                outputFile << val << " was deleted successfully" << endl;
                hashTable.erase(val);
            }
            else
                outputFile << val << " does not exist" << endl;
        }
    }
}