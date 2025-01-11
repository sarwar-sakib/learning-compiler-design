#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

// Simple class to handle NFA to DFA conversion
class Automaton {
    vector<vector<set<int>>> nfa;  // The NFA transitions
    map<set<int>, int> dfaStates;  // Maps NFA state combinations to DFA states
    vector<vector<int>> dfaTransitions;  // The DFA transitions

public:
    // Initialize NFA with number of states
    Automaton(int numStates) {
        nfa = vector<vector<set<int>>>(numStates, vector<set<int>>(3));
    }

    // Add a transition to NFA: from -> to on input symbol
    void addNFA(int from, char symbol, int to) {
        // Convert symbol to index: 'e'->0, '0'->1, '1'->2
        int index = (symbol == 'e') ? 0 : (symbol == '0') ? 1 : 2;
        nfa[from][index].insert(to);
    }

    // Find all states reachable through epsilon transitions
    set<int> findEpsilonClosure(int state) {
        set<int> closure = {state};
        queue<int> toProcess;
        toProcess.push(state);

        while (!toProcess.empty()) {
            int current = toProcess.front();
            toProcess.pop();

            // Look at epsilon transitions
            for (int next : nfa[current][0]) {
                if (closure.find(next) == closure.end()) {
                    closure.insert(next);
                    toProcess.push(next);
                }
            }
        }
        return closure;
    }

    // Convert NFA to DFA
    void convertToDFA() {
        queue<set<int>> unprocessedStates;
        
        // Start with initial state
        set<int> startState = findEpsilonClosure(1);
        dfaStates[startState] = 0;
        unprocessedStates.push(startState);

        // Process each state
        while (!unprocessedStates.empty()) {
            set<int> currentStates = unprocessedStates.front();
            unprocessedStates.pop();
            
            // Add new state to DFA transitions
            vector<int> transitions(2, -1);
            dfaTransitions.push_back(transitions);
            
            // Process input symbols 0 and 1
            for (int input = 1; input <= 2; input++) {
                set<int> nextStates;
                
                // Find all possible next states
                for (int state : currentStates) {
                    for (int next : nfa[state][input]) {
                        set<int> closure = findEpsilonClosure(next);
                        nextStates.insert(closure.begin(), closure.end());
                    }
                }
                
                // If we found next states
                if (!nextStates.empty()) {
                    // Create new DFA state if needed
                    if (dfaStates.find(nextStates) == dfaStates.end()) {
                        dfaStates[nextStates] = dfaStates.size();
                        unprocessedStates.push(nextStates);
                    }
                    
                    // Add transition
                    dfaTransitions[dfaStates[currentStates]][input-1] = dfaStates[nextStates];
                }
            }
        }
    }

    // Print the DFA transition table
    void printDFA() {
        cout << "\nDFA Transition Table:\n";
        cout << "State\t0\t1\n";
        cout << "---------------------\n";
        for (int i = 0; i < dfaTransitions.size(); i++) {
            cout << "q" << i << "\t";
            for (int j = 0; j < 2; j++) {
                if (dfaTransitions[i][j] == -1)
                    cout << "-\t";
                else
                    cout << "q" << dfaTransitions[i][j] << "\t";
            }
            cout << "\n";
        }
    }
};

int main() {
    // Create automaton with 5 states (0 to 4)
    Automaton automaton(5);

    // Add NFA transitions
    automaton.addNFA(1, 'e', 2);  
    automaton.addNFA(1, '1', 1);  
    automaton.addNFA(2, 'e', 3);  
    automaton.addNFA(2, '0', 2);  
    automaton.addNFA(3, '0', 2);  
    automaton.addNFA(3, '1', 1);  

    // Convert NFA to DFA and print result
    automaton.convertToDFA();
    automaton.printDFA();

    return 0;
}