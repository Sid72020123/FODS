#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

/* TEXT FILE BASED VERSION */

struct Movie {
    int movieID;
    char name[30];
    char time[10];
    int totalSeats;
    int availableSeats;
    float price;
};

struct Booking {
    int bookingID;
    int movieID;
    char customerName[30];
    int tickets;
    float totalAmount;
};

void addMovie();
void viewMovies();
void bookTicket();
void cancelBooking();
void adminMenu();
void userMenu();

void main() {
    int choice;
    clrscr();
    do {
        clrscr();
        printf("\n==================================");
        printf("\n   MOVIE TICKET BOOKING SYSTEM");
        printf("\n==================================");
        printf("\n1. Admin Menu");
        printf("\n2. User Menu");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: adminMenu(); break;
            case 2: userMenu(); break;
            case 3: printf("\nThank You!"); break;
            default: printf("\nInvalid Choice!"); getch();
        }
    } while(choice != 3);
    getch();
}

void adminMenu() {
    int ch;
    do {
        clrscr();
        printf("\n----- ADMIN MENU -----");
        printf("\n1. Add Movie");
        printf("\n2. View Movies");
        printf("\n3. Back");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: addMovie(); break;
            case 2: viewMovies(); break;
        }
    } while(ch != 3);
}

void userMenu() {
    int ch;
    do {
        clrscr();
        printf("\n----- USER MENU -----");
        printf("\n1. View Movies");
        printf("\n2. Book Ticket");
        printf("\n3. Cancel Booking");
        printf("\n4. Back");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: viewMovies(); break;
            case 2: bookTicket(); break;
            case 3: cancelBooking(); break;
        }
    } while(ch != 4);
}

void addMovie() {
    FILE *fp;
    struct Movie m;
    clrscr();

    fp = fopen("movies.txt", "a");

    printf("\nEnter Movie ID: ");
    scanf("%d", &m.movieID);
    printf("Enter Movie Name (no spaces): ");
    scanf("%s", m.name);
    printf("Enter Show Time: ");
    scanf("%s", m.time);
    printf("Enter Total Seats: ");
    scanf("%d", &m.totalSeats);
    m.availableSeats = m.totalSeats;
    printf("Enter Ticket Price: ");
    scanf("%f", &m.price);

    fprintf(fp, "%d %s %s %d %d %.2f\n",
            m.movieID, m.name, m.time,
            m.totalSeats, m.availableSeats, m.price);

    fclose(fp);
    printf("\nMovie Added Successfully!");
    getch();
}

void viewMovies() {
    FILE *fp;
    struct Movie m;
    clrscr();

    fp = fopen("movies.txt", "r");
    if(fp == NULL) {
        printf("\nNo Movies Available!");
        getch();
        return;
    }

    printf("\nID  Name        Time   Seats  Price");
    printf("\n------------------------------------");

    while(fscanf(fp, "%d %s %s %d %d %f",
          &m.movieID, m.name, m.time,
          &m.totalSeats, &m.availableSeats, &m.price) != EOF) {
        printf("\n%d  %s  %s  %d  %.2f",
               m.movieID, m.name, m.time,
               m.availableSeats, m.price);
    }
    fclose(fp);
    getch();
}

void bookTicket() {
    FILE *fp, *ft, *fb;
    struct Movie m;
    struct Booking b;
    int found = 0;

    clrscr();
    fp = fopen("movies.txt", "r");
    ft = fopen("temp.txt", "w");
    fb = fopen("bookings.txt", "a");

    printf("Enter Movie ID: ");
    scanf("%d", &b.movieID);

    while(fscanf(fp, "%d %s %s %d %d %f",
          &m.movieID, m.name, m.time,
          &m.totalSeats, &m.availableSeats, &m.price) != EOF) {

        if(m.movieID == b.movieID) {
            found = 1;
            printf("Movie: %s (%s)", m.name, m.time);
            printf("\nAvailable Seats: %d", m.availableSeats);
            printf("\nEnter Customer Name (no spaces): ");
            scanf("%s", b.customerName);
            printf("Enter Tickets: ");
            scanf("%d", &b.tickets);

            if(b.tickets <= m.availableSeats) {
                b.bookingID = rand() % 1000 + 1;
                b.totalAmount = b.tickets * m.price;
                m.availableSeats -= b.tickets;

                fprintf(fb, "%d %d %s %d %.2f\n",
                        b.bookingID, b.movieID,
                        b.customerName, b.tickets, b.totalAmount);

                printf("\nBooking Successful!");
                printf("\nBooking ID: %d", b.bookingID);
                printf("\nTotal Amount: %.2f", b.totalAmount);
            } else {
                printf("\nNot Enough Seats!");
            }
        }

        fprintf(ft, "%d %s %s %d %d %.2f\n",
                m.movieID, m.name, m.time,
                m.totalSeats, m.availableSeats, m.price);
    }

    fclose(fp);
    fclose(ft);
    fclose(fb);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    if(!found)
        printf("\nMovie Not Found!");

    getch();
}

void cancelBooking() {
    FILE *fb;
    struct Booking b;
    int id, found = 0;

    clrscr();
    fb = fopen("bookings.txt", "r");
    printf("Enter Booking ID: ");
    scanf("%d", &id);

    while(fscanf(fb, "%d %d %s %d %f",
          &b.bookingID, &b.movieID,
          b.customerName, &b.tickets, &b.totalAmount) != EOF) {
        if(b.bookingID == id) {
            found = 1;
            printf("\nBooking Found for %s", b.customerName);
            printf("\nBooking Cancelled (Seats not restored - demo)");
            break;
        }
    }

    fclose(fb);

    if(!found)
        printf("\nBooking Not Found!");

    getch();
}
