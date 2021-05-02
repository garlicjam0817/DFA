#include "FSA.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// parameterize constructor reading data from input stream
FSA::FSA(ifstream &ifs)
{
    string alphabet;
    ifs >> alphabet;

    for (char ch: alphabet)
        sigma.push_back(ch);

    ifs >> num_states;
    ifs >> start_state;

    int num_acceptstates;
    int value;
    ifs >> num_acceptstates;

    for(int i = 0; i < num_acceptstates; i++)
    {
        ifs >> value;
        accept_states.push_back(value);
    }

    state_table.resize(num_states);
    for(int i = 0; i < num_states; i++)
    {
        state_table[i].resize(sigma.size());
        for(int j = 0; j < sigma.size(); j++)
        {
            ifs >> value;
            state_table[i][j] = value;
        }
    }
}
 

// populate state table
void FSA::get_state_table(ifstream &ifs)
{
    //cout << "called stub version of get_state_table()\n";
    vector<int> table_row(sigma.size());

	//we first add a row of zeros, because C++ used 0-based
	state_table.push_back(table_row);

	//read the contents of state table from the file
	for(int row = 0; row < num_states; row++) {
		for (unsigned int col = 0; col < sigma.size(); col++)
			ifs >> table_row[col];
		state_table.push_back(table_row);
	}
}

// document me
void FSA::describe()
{
    std::string s(sigma.begin(), sigma.end());
    cout << "alphabet = " << s << endl;
    cout << "# states = " << num_states << endl;
    cout << "start state = " << start_state << endl;
    cout << "accept states = ";
    
    for(auto i : accept_states)
        cout << i << " ";
    
    cout << endl;
    
    int count = 1;
    for (vector<int> i : state_table)
    {
        cout << count << ":" << i[0] << " " << i[1] << endl;
        count++;
    }
}

 //trace the operation of the FSA
void FSA::trace(const string& in_string)
{
    int current_state = start_state;
    cout <<  "State trace: " << current_state;
    
    // loop through the ending string of the length
    for(int i = 0; i < in_string.length(); i++)
    {
        char currentChar = in_string[i];
        int index = find(sigma, currentChar);
        if(index != -1)
            current_state = state_table[current_state - 1][index];
        cout << "  " << current_state;
    }

    // see if the result is accepted or not
    if(find(accept_states, current_state) != -1)
        cout << "...accepted\n" << endl;
    else
        cout << "... not accepted\n" << endl;
}
 
template <typename T>
int FSA::find(const vector<T> v, const T x)
{
    // this function searches if the number in this vector
    // if it is then returns the position/index
    auto loc = std::find(v.begin(), v.end(), x);
    if (loc == v.end())
        return -1;
    return (loc - v.begin());
}

