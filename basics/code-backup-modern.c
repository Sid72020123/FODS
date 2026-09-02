#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MODERN GCC COMPATIBLE VERSION (TEXT FILE BASED) */

struct Movie
{
    int movieID;
    char name[50];
    char time[20];
    int totalSeats;
    int availableSeats;
    float price;
};

struct Booking
{
    int bookingID;
    int movieID;
    char customerName[50];
    int tickets;
    float totalAmount;
};

void addMovie();
void viewMovies();
void bookTicket();
void cancelBooking();
void adminMenu();
void userMenu();

int main()
{
    int choice;
    do
    {
        printf("\n==================================");
        printf("\n   MOVIE TICKET BOOKING SYSTEM");
        printf("\n==================================");
        printf("\n1. Admin Menu");
        printf("\n2. User Menu");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            adminMenu();
            break;
        case 2:
            userMenu();
            break;
        case 3:
            printf("\nThank You!\n");
            break;
        default:
            printf("\nInvalid Choice!\n");
        }
    } while (choice != 3);

    return 0;
}

void adminMenu()
{
    int ch;
    do
    {
        printf("\n----- ADMIN MENU -----");
        printf("\n1. Add Movie");
        printf("\n2. View Movies");
        printf("\n3. Back");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            addMovie();
            break;
        case 2:
            viewMovies();
            break;
        }
    } while (ch != 3);
}

void userMenu()
{
    int ch;
    do
    {
        printf("\n----- USER MENU -----");
        printf("\n1. View Movies");
        printf("\n2. Book Ticket");
        printf("\n3. Cancel Booking");
        printf("\n4. Back");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            viewMovies();
            break;
        case 2:
            bookTicket();
            break;
        case 3:
            cancelBooking();
            break;
        }
    } while (ch != 4);
}

void addMovie()
{
    FILE *fp;
    struct Movie m;

    fp = fopen("movies.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

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
    printf("Movie Added Successfully!\n");
}

void viewMovies()
{
    FILE *fp;
    struct Movie m;

    fp = fopen("movies.txt", "r");
    if (fp == NULL)
    {
        printf("\nNo Movies Available!\n");
        return;
    }

    printf("\nID  Name        Time        Seats  Price");
    printf("\n-----------------------------------------");

    while (fscanf(fp, "%d %s %s %d %d %f",
                  &m.movieID, m.name, m.time,
                  &m.totalSeats, &m.availableSeats, &m.price) != EOF)
    {
        printf("\n%d  %s  %s  %d  %.2f",
               m.movieID, m.name, m.time,
               m.availableSeats, m.price);
    }
    fclose(fp);
}

void bookTicket()
{
    FILE *fp, *ft, *fb;
    struct Movie m;
    struct Booking b;
    int found = 0;

    fp = fopen("movies.txt", "r");
    ft = fopen("temp.txt", "w");
    fb = fopen("bookings.txt", "a");

    if (fp == NULL || ft == NULL || fb == NULL)
    {
        printf("File error!\n");
        return;
    }

    printf("Enter Movie ID: ");
    scanf("%d", &b.movieID);

    while (fscanf(fp, "%d %s %s %d %d %f",
                  &m.movieID, m.name, m.time,
                  &m.totalSeats, &m.availableSeats, &m.price) != EOF)
    {

        if (m.movieID == b.movieID)
        {
            found = 1;
            printf("Movie: %s (%s)\n", m.name, m.time);
            printf("Available Seats: %d\n", m.availableSeats);
            printf("Enter Customer Name (no spaces): ");
            scanf("%s", b.customerName);
            printf("Enter Tickets: ");
            scanf("%d", &b.tickets);

            if (b.tickets <= m.availableSeats)
            {
                b.bookingID = rand() % 10000 + 1;
                b.totalAmount = b.tickets * m.price;
                m.availableSeats -= b.tickets;

                fprintf(fb, "%d %d %s %d %.2f\n",
                        b.bookingID, b.movieID,
                        b.customerName, b.tickets, b.totalAmount);

                printf("Booking Successful!\n");
                printf("Booking ID: %d\n", b.bookingID);
                printf("Total Amount: %.2f\n", b.totalAmount);
            }
            else
            {
                printf("Not enough seats!\n");
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

    if (!found)
        printf("Movie Not Found!\n");
}

void cancelBooking()
{
    FILE *fb;
    struct Booking b;
    int id, found = 0;

    fb = fopen("bookings.txt", "r");
    if (fb == NULL)
    {
        printf("No bookings found!\n");
        return;
    }

    printf("Enter Booking ID: ");
    scanf("%d", &id);

    while (fscanf(fb, "%d %d %s %d %f",
                  &b.bookingID, &b.movieID,
                  b.customerName, &b.tickets, &b.totalAmount) != EOF)
    {
        if (b.bookingID == id)
        {
            found = 1;
            printf("Booking Found for %s\n", b.customerName);
            printf("Booking Cancelled (demo only)\n");
            break;
        }
    }

    fclose(fb);

    if (!found)
        printf("Booking Not Found!\n");
}
