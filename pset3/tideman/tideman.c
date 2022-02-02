#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //needed for qsort function


// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }


    add_pairs();

    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check entereted name exists, and if so, update vote tally
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // check voter ranks and increase number of voters who prefer candidate [i] to [j]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++) //for each ith candidate and those beside it,
        {
            if (preferences[i][j] > preferences[j][i]) //update struct pair with winner/loser info
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

//Custom comparison function to be used for qsort library function
int compare_victory(const void *first, const void *second)
{
    pair *order1 = (pair *)first;
    pair *order2 = (pair *)second;

    //compares win quantity between pairs and returns strength of each victory between pairs as per qsort documentation
    return (preferences[order2->winner][order2->loser] - preferences[order1->winner][order1->loser]);
}


// Sort pairs in decreasing order by strength of victory using qsort function from stdlib library
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), compare_victory);
    return;
}

// Custom recursive function to verify if new pair creates a cycle
bool is_cycle(int end, int start)
{
    // Set base case as to return true if a cycle is created
    if (end == start)
    {
        return true;
    }
    // Recursively iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (is_cycle(i, start))
            {
                return true;
            }
        }
    }
    return false;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    // iterate through each pair in pairs
    for (int i = 0; i < pair_count; i++)
    {
        // Lock pairs that do not create cycles, otherwise leave them as false
        if (!is_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Winner is defined as candidate with no incoming edges
    // So tally number of false values in lock_pairs and return candidate with most (candidate_count)
    for (int i = 0; i < candidate_count; i++)
    {
        int falses = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                falses++;
                if (falses == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }

    return;
}

