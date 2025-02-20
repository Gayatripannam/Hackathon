#include <stdio.h>
#include <string.h>

#define MAX_USERS 100  
#define MAX_MOVIES 100  
#define MAX_REVIEWS 100  

struct User {
    char firstname[50];
    char lastname[50];
    int date,month,year;
    int contact;
    char email[100];
    char password[50];
};

struct Movie {
    char title[100];
    char genre[50];
    int year;
    float rating;
};

struct Review {
    char firstname[50];
    char movieName[100];
    char review[255];
    float rating;
};

struct User users[MAX_USERS];  
struct Movie movies[MAX_MOVIES] = {
    {"Inception", "Sci-Fi", 2010, 8.8},
    {"The Dark Knight", "Action", 2008, 9.0},
    {"Interstellar", "Sci-Fi", 2014, 8.6},
    {"Titanic", "Romance", 1997, 7.8},
    {"Avatar", "Sci-Fi", 2009, 7.9},
    {"The God Father", "Sci-fi", 1972,8.0},
    {"Hunger Games", "Sci-fi", 2012, 7.8},
    {"Joker", "Fiction", 2019, 8.9},
    {"Tenet", "Fiction",2020, 7.6},
    {"Prisoner","Action",2013,8.6}
};  
struct Review reviews[MAX_REVIEWS];

int userCount = 0;
int movieCount = 5;
int reviewCount = 0;
int loggedInUserIndex = -1;  // Stores index of logged-in user (-1 if not signed in)

void clearInputBuffer() {
    while (getchar() != '\n'); // Clears input buffer
}

void signUp() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }
    printf("Enter firstname: ");
    scanf("%49s", users[userCount].firstname);

    printf("Enter lastname: ");
    scanf("%49s", users[userCount].lastname);

    printf("Enter DOB (DD MM YYYY): ");
    scanf("%d %d %d", &users[userCount].date, &users[userCount].month, &users[userCount].year);

    printf("Enter contact number: \n");
    scanf("%d",&users[userCount].contact);
    printf("Enter password: ");
    scanf("%49s", users[userCount].password);
    printf("Enter email: ");
    scanf("%99s", users[userCount].email);
    userCount++;
    printf("User registered successfully!\n");
}

int signIn() {
    char firstname[50], lastname[50],  password[50];
    
    printf("Enter firstname: ");
    scanf("%49s", firstname);

    printf("Enter password: ");
    scanf("%49s", password);


    for (int i = 0; i < userCount; i++) {
        if (strcmp(firstname, users[i].firstname) == 0 && 

            strcmp(password, users[i].password) == 0) {
            loggedInUserIndex = i;
            printf("Login successful! Welcome, %s \n", users[i].firstname);
            return 1;
        }
    }
    printf("Invalid credentials!\n");
    return 0;
}

void editProfile() {
    if (loggedInUserIndex == -1) {
        printf("You need to sign in first!\n");
        return;
    }
    printf("Enter new email: ");
    scanf("%99s", users[loggedInUserIndex].email);
    printf("Profile updated successfully!\n");
}

void changePassword() {
    if (loggedInUserIndex == -1) {
        printf("You need to sign in first!\n");
        return;
    }
    char newPassword[50];
    printf("Enter new password: ");
    scanf("%49s", newPassword);
    strcpy(users[loggedInUserIndex].password, newPassword);
    printf("Password changed successfully!\n");
}

void displayAllMovies() {
    if (movieCount == 0) {
        printf("No movies available!\n");
        return;
    }
    printf("\nList of Movies:\n");
    for (int i = 0; i < movieCount; i++) {
        printf("Title: %s, Genre: %s, Year: %d, Rating: %.1f\n", 
               movies[i].title, movies[i].genre, movies[i].year, movies[i].rating);
    }
}

void createReview() {
    if (loggedInUserIndex == -1) {
        printf("You need to sign in first!\n");
        return;
    }
    if (reviewCount >= MAX_REVIEWS) {
        printf("Review limit reached!\n");
        return;
    }

    clearInputBuffer();

    strcpy(reviews[reviewCount].firstname, users[loggedInUserIndex].firstname);
    printf("Enter movie name: ");
    fgets(reviews[reviewCount].movieName, 100, stdin);
    strtok(reviews[reviewCount].movieName, "\n");

    printf("Enter your review: ");
    fgets(reviews[reviewCount].review, 255, stdin);
    strtok(reviews[reviewCount].review, "\n");

    printf("Enter rating (0.0 - 10.0): ");
    scanf("%f", &reviews[reviewCount].rating);

    reviewCount++;
    printf("Review added successfully!\n");
}

void displayMyReviews() {
    if (loggedInUserIndex == -1) {
        printf("You need to sign in first!\n");
        return;
    }
    int found = 0;
    printf("\nMy Reviews:\n");
    for (int i = 0; i < reviewCount; i++) {
        if (strcmp(reviews[i].firstname, users[loggedInUserIndex].firstname) == 0) {
            printf("Movie: %s, Review: %s, Rating: %.1f\n", 
                   reviews[i].movieName, reviews[i].review, reviews[i].rating);
            found = 1;
        }
    }
    if (!found) {
        printf("You have not submitted any reviews yet.\n");
    }
}

void displayAllReviews() {
    if (reviewCount == 0) {
        printf("No reviews available!\n");
        return;
    }
    printf("\nAll Reviews:\n");
    for (int i = 0; i < reviewCount; i++) {
        printf("User: %s, Movie: %s, Review: %s, Rating: %.1f\n", 
               reviews[i].firstname, reviews[i].movieName, reviews[i].review, reviews[i].rating);
    }
}

void deleteMyReview() {
    if (loggedInUserIndex == -1) {
        printf("You need to sign in first!\n");
        return;
    }
    
    char movieName[100];
    clearInputBuffer();
    printf("Enter the movie name of the review you want to delete: ");
    fgets(movieName, 100, stdin);
    movieName[strcspn(movieName, "\n")] = 0;  // Safe newline removal

    char currentUser[100];
    snprintf(currentUser, 100, "%s", users[loggedInUserIndex].firstname);

    // Debugging - Print entered values
    printf("Debug: Looking for review by [%s] for movie [%s]\n", currentUser, movieName);

    int found = 0;
    for (int i = 0; i < reviewCount; i++) {
        printf("Debug: Checking [%s] vs [%s]\n", reviews[i].firstname, currentUser);
        printf("Debug: Checking [%s] vs [%s]\n", reviews[i].movieName, movieName);

        if (strcmp(reviews[i].firstname, currentUser) == 0 && strcmp(reviews[i].movieName, movieName) == 0) {
            for (int j = i; j < reviewCount - 1; j++) {
                reviews[j] = reviews[j + 1];
            }
            reviewCount--;
            printf("Your review has been deleted successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Review not found!\n");
    }
}


void signOut() {
    if (loggedInUserIndex == -1) {
        printf("No user is signed in!\n");
        return;
    }
    loggedInUserIndex = -1;
    printf("You have been signed out.\n");
}

int main() {
    int choice;

    do {
        printf("\nMovie Database System\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Edit Profile\n");
        printf("4. Change Password\n");
        printf("5. Display All Movies\n");
        printf("6. Create Review\n");
        printf("7. Display My Reviews\n");
        printf("8. Display All Reviews\n");
        printf("9. Delete my Reviews\n");
        printf("10. Sign Out\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: signUp(); break;
            case 2: signIn(); break;
            case 3: editProfile(); break;
            case 4: changePassword(); break;
            case 5: displayAllMovies(); break;
            case 6: createReview(); break;
            case 7: displayMyReviews(); break;
            case 8: displayAllReviews(); break;
            case 9: deleteMyReview(); break;
            case 10: signOut(); break;
            case 11: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 11);

    return 0;
}
