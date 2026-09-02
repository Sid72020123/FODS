#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

struct Movie
{
    int movieID;
    char name[30];
    char time[15];
    int totalSeats;
    int availableSeats;
    float price;
};

struct Booking
{
    int bookingID;
    int movieID;
    char customerName[30];
    int tickets;
    float totalAmount;
};

void viewMovies();
void bookTicket();
void cancelBooking();

void main()
{
    int choice;
    clrscr();

    do
    {
        clrscr();
        printf("\n==================================");
        printf("\n   MOVIE TICKET BOOKING SYSTEM");
        printf("\n==================================");
        printf("\n1. View Movies");
        printf("\n2. Book Ticket");
        printf("\n3. Cancel Booking");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
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
        case 4:
            printf("\nThank You!");
            break;
        default:
            printf("\nInvalid Choice!");
        }
        getch();
    } while (choice != 4);
}

void viewMovies()
{
    FILE *fp;
    struct Movie m;

    clrscr();
    fp = fopen("movies.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo movies available!");
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

    clrscr();
    fp = fopen("movies.txt", "r");
    ft = fopen("temp.txt", "w");
    fb = fopen("bookings.txt", "a");

    if (fp == NULL || ft == NULL || fb == NULL)
    {
        printf("\nFile error!");
        return;
    }

    printf("\nEnter Movie ID: ");
    scanf("%d", &b.movieID);

    while (fscanf(fp, "%d %s %s %d %d %f",
                  &m.movieID, m.name, m.time,
                  &m.totalSeats, &m.availableSeats, &m.price) != EOF)
    {

        if (m.movieID == b.movieID)
        {
            found = 1;
            printf("\nMovie: %s (%s)", m.name, m.time);
            printf("\nAvailable Seats: %d", m.availableSeats);

            printf("\nEnter Customer Name (no spaces): ");
            scanf("%s", b.customerName);

            printf("Enter Tickets: ");
            scanf("%d", &b.tickets);

            if (b.tickets <= m.availableSeats)
            {
                b.bookingID = rand() % 1000 + 1;
                b.totalAmount = b.tickets * m.price;
                m.availableSeats -= b.tickets;

                fprintf(fb, "%d %d %s %d %.2f\n",
                        b.bookingID, b.movieID,
                        b.customerName, b.tickets, b.totalAmount);

                printf("\nBooking Successful!");
                printf("\nBooking ID: %d", b.bookingID);
                printf("\nTotal Amount: %.2f", b.totalAmount);
            }
            else
            {
                printf("\nNot enough seats!");
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
        printf("\nMovie Not Found!");
}

void cancelBooking()
{
    FILE *fb;
    struct Booking b;
    int id, found = 0;

    clrscr();
    fb = fopen("bookings.txt", "r");

    if (fb == NULL)
    {
        printf("\nNo bookings found!");
        return;
    }

    printf("\nEnter Booking ID: ");
    scanf("%d", &id);

    while (fscanf(fb, "%d %d %s %d %f",
                  &b.bookingID, &b.movieID,
                  b.customerName, &b.tickets, &b.totalAmount) != EOF)
    {

        if (b.bookingID == id)
        {
            found = 1;
            printf("\nBooking Found for %s", b.customerName);
            printf("\nBooking Cancelled (demo only)");
            break;
        }
    }

    fclose(fb);

    if (!found)
        printf("\nBooking Not Found!");
}
