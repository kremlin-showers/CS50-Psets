#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool visited[MAX];


// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int l, int m);


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
// compating candidates name to names in the list of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }




    }
// if no match is found returning false


    return false;


}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
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
//checking weather more people like i or more people like j
    int x = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int y = preferences[i][j] - preferences[j][i];
// if more people like i then adding i as a winner over j in a pair
            if (y > 0)
            {
                pairs[x].winner = i;
                pairs[x].loser = j;
                x++;
            }
// if more people like j then adding j as a winner over i
            else if (y < 0)
            {
                pairs[x].winner = j;
                pairs[x].loser = i;
                x++;
            }

        }

    }
// updating pair count
    pair_count = x;


    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
// creating an array called margins that stores all the margins of victory
    int margins[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        margins[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }
// sorting the margins array and making the pairs array mirror the margins array
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (margins[j] < margins[j + 1])
            {
                int var = margins[j + 1];

                margins[j + 1] = margins[j];
                margins[j] = var;

                pair var2 = pairs[j];

                pairs[j] = pairs[j + 1];
                pairs[j + 1] = var2;



            }





        }
    }









    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int ex = pairs[0].winner;
    locked[pairs[0].winner][pairs[0].loser] = true;
    for (int i = 0; i < pair_count; i++)
    {
        if (pairs[i].loser != ex)
        {
            
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            if (!check_cycle(ex, pairs[i].winner))
            {
                ex = pairs[i].winner;
                
                
            }
            for (int j = 0; j < candidate_count; j++)
            {
                visited[j] = false;
            }
            
            
            
            
            
            
            
            
            
            
        }
        
        
        
        
        
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        winner[i] = 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                winner[i] = 0;
            }    

        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }
        
        
        
        
    }
    
    

    return;
    
}
// function for checking the existance of cycles
bool check_cycle(int l, int m)
{
    if (visited[l])
    {
        return false;
    }
    
    visited[l] = true;
    
    if (locked[l][m])
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[l][i])
        {
            if (check_cycle(i, l))
            {
                return true;
            }
            
        }
    }
    return false;
}

