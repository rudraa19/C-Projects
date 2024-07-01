#include <ctype.h>   // Include ctype.h for character manipulation functions
#include <stdio.h>   // Include stdio.h for input and output functions
#include <string.h>  // Include string.h for string manipulation functions

// Array of points corresponding to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Function prototype for computing score
int compute_score(char word[]);

int main(void)
{
    char word1[50], word2[50];  // Declare two character arrays to store the words
    printf("Player 1: ");
    scanf("%s", word1);  // Get input for player 1's word
    printf("Player 2: ");
    scanf("%s", word2);  // Get input for player 2's word

    // Compute scores for both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Determine and print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(char word[])
{
    // Convert all characters in the word to uppercase
    for (int i = 0; i < strlen(word); i++)
    {
        word[i] = toupper(word[i]);
    }

    int score = 0;  // Initialize score to 0
    // Compute the score by summing the points for each letter in the word
    for (int j = 0; j < strlen(word); j++)
    {
        if (isalpha(word[j]))  // Check if the character is an alphabet letter
        {
            score += POINTS[word[j] - 'A'];  // Add the corresponding points
        }
    }
    return score;  // Return the computed score
}
