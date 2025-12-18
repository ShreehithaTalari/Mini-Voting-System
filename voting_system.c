#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 25
#define MAX_NAME_LENGTH 100

struct candidate {
    char name[MAX_NAME_LENGTH];
    char symbol;
    int votes;
    struct candidate *next;
};

struct voter {
    char name[MAX_NAME_LENGTH];
    int age;
    struct voter *next;
};

void add_candidates(struct candidate **candidates_head, int *candidate_count);
void show_candidates(struct candidate *candidates_head);
void add_voter(struct voter **voters_head);
void delete_voter(struct voter **voters_head, char *voter_name);
void voting(struct candidate *candidates_head, struct voter *voters_head);
void show_result(struct candidate *candidates_head);

int main() {
    struct candidate *candidates_head = NULL;
    struct voter *voters_head = NULL;
    int choice;
    int candidate_count = 0;

    do {
        printf("1. Add candidates.\n");
        printf("2. Show candidates.\n");
        printf("3. Add voter.\n");
        printf("4. Delete voter.\n");
        printf("5. Vote.\n");
        printf("6. Show results.\n");
        printf("7. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_candidates(&candidates_head, &candidate_count);
                break;
            case 2:
                show_candidates(candidates_head);
                break;
            case 3:
                add_voter(&voters_head);
                break;
            case 4: {
                char voter_name[MAX_NAME_LENGTH];
                printf("Enter the name of the voter to delete: ");
                scanf("%s", voter_name);
                delete_voter(&voters_head, voter_name);
                break;
            }
            case 5:
                voting(candidates_head, voters_head);
                break;
            case 6:
                show_result(candidates_head);
                break;
            case 7:
                printf("Exiting the program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

void add_candidates(struct candidate **candidates_head, int *candidate_count) {
    struct candidate *new_candidate = (struct candidate *)malloc(sizeof(struct candidate));
    if (new_candidate == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter name of candidate %d: ", *candidate_count + 1);
    scanf("%s", new_candidate->name);
    printf("Enter symbol for candidate %d: ", *candidate_count + 1);
    scanf(" %c", &new_candidate->symbol);
    
    new_candidate->votes = 0;
    new_candidate->next = *candidates_head;
    *candidates_head = new_candidate;

    (*candidate_count)++;
}

void show_candidates(struct candidate *candidates_head) {
    if (candidates_head == NULL) {
        printf("No candidates available.\n");
        return;
    }

    struct candidate *temp = candidates_head;
    while (temp != NULL) {
        printf("Name: %s, Symbol: %c, Votes: %d\n", temp->name, temp->symbol, temp->votes);
        temp = temp->next;
    }
}

void add_voter(struct voter **voters_head) {
    struct voter *new_voter = (struct voter *)malloc(sizeof(struct voter));
    if (new_voter == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter name of voter: ");
    scanf("%s", new_voter->name);
    printf("Enter age of voter: ");
    scanf("%d", &new_voter->age);

    if (new_voter->age < 18) {
        printf("Voter is not eligible.\n");
        free(new_voter);
        return;
    }

    new_voter->next = *voters_head;
    *voters_head = new_voter;
}

void delete_voter(struct voter **voters_head, char *voter_name) {
    struct voter *temp = *voters_head;
    struct voter *prev = NULL;

    if (temp != NULL && strcmp(temp->name, voter_name) == 0) {
        *voters_head = temp->next;
        free(temp);
        printf("Voter deleted.\n");
        return;
    }

    while (temp != NULL && strcmp(temp->name, voter_name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Voter not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Voter deleted.\n");
}

void voting(struct candidate *candidates_head, struct voter *voters_head) {
    struct voter *temp_voter = voters_head;
    int choice;

    while (temp_voter != NULL) {
        if (temp_voter->age >= 18) {
            show_candidates(candidates_head);
            printf("Voter %s, please enter your vote (1 to N): ", temp_voter->name);
            scanf("%d", &choice);

            struct candidate *temp_candidate = candidates_head;
            int count = 1;
            while (temp_candidate != NULL && count < choice) {
                temp_candidate = temp_candidate->next;
                count++;
            }

            if (temp_candidate != NULL) {
                temp_candidate->votes++;
            } else {
                printf("Invalid choice.\n");
            }
        }
        temp_voter = temp_voter->next;
    }
}

void show_result(struct candidate *candidates_head) {
    struct candidate *temp = candidates_head;
    int max_votes = -1;
    struct candidate *winner = NULL;

    while (temp != NULL) {
        if (temp->votes > max_votes) {
            max_votes = temp->votes;
            winner = temp;
        }
        temp = temp->next;
    }

    if (winner != NULL) {
        printf("Winner: %s with symbol %c and %d votes.\n", winner->name, winner->symbol, winner->votes);
    } else {
        printf("No winner.\n");
    }
}
