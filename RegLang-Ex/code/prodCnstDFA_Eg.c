#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 2
#define NUM_STATES 10


static int map_alphabet(char c) {
    if (c == '0') return 0;
    if (c == '1') return 1;
    return -1;
}

// State = (modulo_5 * 2) + parity (where Even = 0, Odd = 1)
typedef enum {
    S0_E = 0,   S0_O = 1,
    S1_E = 2,   S1_O = 3,
    S2_E = 4,   S2_O = 5,
    S3_E = 6,   S3_O = 7,
    S4_E = 8,   S4_O = 9
} State;

static const State transition_table[NUM_STATES][ALPHABET_SIZE] = {
//  Current State      | Input '0'      | Input '1'
    [S0_E]           = { S1_E,      S0_O },
    [S0_O]           = { S1_O,      S0_E },
    [S1_E]           = { S2_E,      S1_O },
    [S1_O]           = { S2_O,      S1_E },
    [S2_E]           = { S3_E,      S2_O },
    [S2_O]           = { S3_O,      S2_E },
    [S3_E]           = { S4_E,      S3_O },
    [S3_O]           = { S4_O,      S3_E },
    [S4_E]           = { S0_E,      S4_O },
    [S4_O]           = { S0_O,      S4_E }
};

static const bool accepting_states[NUM_STATES] = {
    [S0_E] = true,  
    [S0_O] = false,
    [S1_E] = false, [S1_O] = false,
    [S2_E] = false, [S2_O] = false,
    [S3_E] = false, [S3_O] = false,
    [S4_E] = false, [S4_O] = false
};



bool simulate_dfa(const char *input) {
    
    State current_state = S0_E; 
    for (size_t i = 0; input[i] != '\0'; i++) {
        int symbol_idx = map_alphabet(input[i]);
        
        if (symbol_idx == -1) return false;

        current_state = transition_table[current_state][symbol_idx];
    }
    
    return accepting_states[current_state];
}

int main(void) {

    const char *test_strings[] = {
        "0000011",  
        "11",        
        "00000",     
        "000001",    
        "0000",      
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    printf("DFA Simulation Verification:\n");
    printf("-----------------------------\n");
    
    for (size_t i = 0; i < num_tests; i++) {
        bool result = simulate_dfa(test_strings[i]);
        printf("Input: %-12s -> %s\n", test_strings[i], result ? "ACCEPTED" : "REJECTED");
    }

    return 0;
}
