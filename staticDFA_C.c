#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 2
#define NUM_STATES 10


static inline int map_alphabet(char c) {
    if (c == '0') return 0;
    if (c == '1') return 1;
    return -1; 
}

// State names represented as integers 0 through 9
// For clarity, we map (modulo_5_zeros, parity_ones) to a single dimension:
// State = (modulo_5 * 2) + parity (where Even = 0, Odd = 1)
typedef enum {
    S0_E = 0, S0_O = 1,
    S1_E = 2, S1_O = 3,
    S2_E = 4, S2_O = 5,
    S3_E = 6, S3_O = 7,
    S4_E = 8, S4_O = 9
} State;

// The static transition table representing \delta(State, Symbol)
static const State transition_table[NUM_STATES][ALPHABET_SIZE] = {
    // Current State | Input '0' | Input '1'
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

// The set of accepting states F
static const bool accepting_states[NUM_STATES] = {
    [S0_E] = true,  // 0 zeros (mod 5), even ones (mod 2)
    [S0_O] = false,
    [S1_E] = false, [S1_O] = false,
    [S2_E] = false, [S2_O] = false,
    [S3_E] = false, [S3_O] = false,
    [S4_E] = false, [S4_O] = false
};

/**
 * Simulates the DFA execution over an input string.
 */
bool simulate_dfa(const char *input) {
    State current_state = S0_E; // Initial state q_0

    for (size_t i = 0; input[i] != '\0'; i++) {
        int symbol_idx = map_alphabet(input[i]);
        
        // Reject immediately if a character outside \Sigma is encountered
        if (symbol_idx == -1) {
            return false; 
        }

        // Transition to the next state: q = \delta(q, \sigma)
        current_state = transition_table[current_state][symbol_idx];
    }

    // Return true if the final state is in F
    return accepting_states[current_state];
}

int main(void) {
    // Test cases
    const char *test_strings[] = {
        "0000011",   // Valid: five 0s, two 1s
        "11",        // Valid: zero 0s (0 mod 5), two 1s
        "00000",     // Valid: five 0s, zero 1s
        "000001",    // Invalid: odd number of 1s
        "0000",      // Invalid: four 0s
        "010101010"  // Valid: five 0s, four 1s
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