#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate through the list of candidates to find a match for the provided name
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the provided name matches the name of a valid candidate
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If the voter hasn't already ranked this candidate at a higher preference
            if (preferences[voter][rank] == -1)
            {
                // Update the voter's preference for this rank to the candidate's index
                preferences[voter][rank] = i;
                return true; // Successfully recorded the preference
            }
        }
    }

    // If no candidate with the provided name was found or the voter has already ranked this candidate higher
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate through each voter's preferences
    for (int i = 0; i < voter_count; i++)
    {
        // Initialize rank to 0 (first preference)
        int rank = 0;

        // Find the highest-ranked non-eliminated candidate
        while (candidates[preferences[i][rank]].eliminated)
        {
            rank++;
        }

        // Increment the vote count for the highest-ranked non-eliminated candidate
        candidates[preferences[i][rank]].votes++;
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Calculate the minimum number of votes needed to win
    int majority = voter_count / 2 + 1;

    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If a candidate has more than half of the votes, they win
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // No candidate has more than half of the votes
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_votes = voter_count; // Initialize min_votes to a high value

    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is still in the election (not eliminated)
        if (!candidates[i].eliminated)
        {
            // Update min_votes if the current candidate has fewer votes
            if (candidates[i].votes < min_votes)
            {
                min_votes = candidates[i].votes;
            }
        }
    }

    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is still in the election (not eliminated)
        if (!candidates[i].eliminated)
        {
            // If any candidate has a different number of votes than 'min', it's not a tie
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }

    // All remaining candidates have the same number of votes, it's a tie
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate has the minimum number of votes and is not already eliminated
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            // Eliminate the candidate by setting the 'eliminated' flag to true
            candidates[i].eliminated = true;
        }
    }
}
