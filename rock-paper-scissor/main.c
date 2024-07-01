#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to simulate the game
int game(int userChoice, int compChoice) {
    if (userChoice == compChoice)
        return -1; // Tie
    else if ((userChoice == 1 && compChoice == 3) || 
             (userChoice == 2 && compChoice == 1) || 
             (userChoice == 3 && compChoice == 2))
        return 1; // User wins
    else
        return 0; // Computer wins
}

int main() {
    int userChoice, compChoice;
    // Initialize random number generator
    srand(time(NULL));
    // Generate random number for computer's choice
    compChoice = rand() % 3 + 1; // 1 for Stone, 2 for Paper, 3 for Scissors
    // Ask user for input
    printf("Enter your choice:\n");
    printf("1. Stone\n");
    printf("2. Paper\n");
    printf("3. Scissors\n");
    scanf("%d", &userChoice);
    // Validate user input
    if (userChoice < 1 || userChoice > 3) {
        printf("Invalid choice. Please enter a number between 1 and 3.\n");
        return 1; // Exit with error
    }
    // Determine winner
    int result = game(userChoice, compChoice);
    // Display results
    printf("Computer chose: ");
    switch (compChoice) {
        case 1:
            printf("Stone\n");
            break;
        case 2:
            printf("Paper\n");
            break;
        case 3:
            printf("Scissors\n");
            break;
    }
    printf("You chose: ");
    switch (userChoice) {
        case 1:
            printf("Stone\n");
            break;
        case 2:
            printf("Paper\n");
            break;
        case 3:
            printf("Scissors\n");
            break;
    }
    // Determine and display winner
    if (result == 1)
        printf("Congratulations! You win!\n");
    else if (result == 0)
        printf("Computer wins. Better luck next time!\n");
    else
        printf("It's a tie!\n");
    return 0;
}
