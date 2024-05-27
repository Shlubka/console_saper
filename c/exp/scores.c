#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file;
    int scores[10];
    char names[10][50];
    int new_score, i, j, pos;
    char new_name[50];

    file = fopen("scores.txt", "r+");
    if (file == NULL) {
        //printf("Error: Unable to open file.\n");
        return 1;
    }

    // Read scores and names from file
    for (i = 0; i < 10; i++) {
        if (fscanf(file, "%d%*c%[^\n]\n", &scores[i], names[i]) != 1) {
            // If there are not enough scores in the file, set the remaining scores to 0 and names to empty strings
            scores[i] = 0;
            strcpy(names[i], "");
        }
    }

    printf("Enter your name: ");
    fgets(new_name, 50, stdin);
    new_name[strcspn(new_name, "\n")] = '\0'; // Remove newline character from name

    printf("Enter your score: ");
    scanf("%d", &new_score);

    // Find the position to insert the new score
    for (i = 0; i < 10; i++) {
        if (new_score > scores[i]) {
            pos = i;
            break;
        }
    }

    // Shift the scores and names to make room for the new score and name
    for (j = 10 - 1; j > pos; j--) {
        scores[j] = scores[j - 1];
        strcpy(names[j], names[j - 1]);
    }

    // Insert the new score and name
    scores[pos] = new_score;
    strcpy(names[pos], new_name);

    // Write the scores and names to the file
    fseek(file, 0, SEEK_SET);
    for (i = 0; i < 10; i++) {
        fprintf(file, "%d %s\n", scores[i], names[i]);
    }

    //printf("Your score has been successfully added to the leaderboard.\n");

    fclose(file);
    return 0;
}

