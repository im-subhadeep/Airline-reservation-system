#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Problem Statement
A new airlines have only one plane of capacity 40. Your system will assign seats on each flight. 5%
seats are reserved for first class and rest for economic class. Passengers are allowed to book single
and group tickets. Passenger may be a Prime category passenger (first class) or normal category
(economic class). Generate a passenger list sorted on category if 60% tickets are sold. Senior citizens
will have preference over normal category. Passengers may enquire about seat through interactive
mode.*/

#define TOTAL_SEATS 40
#define FIRST_CLASS_SEATS 2
#define ECONOMIC_CLASS_SEATS 38

typedef struct
{
    char name1[20];
    char name2[10];
    int age;
    int seatNumber;
    int isSeniorCitizen;
    int category;
} Passenger;

Passenger passengerList[TOTAL_SEATS];
int totalPassengers = 0;
int primeSeats = 1;
int normalSeats = 3;

void initializeSeats()
{
    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        passengerList[i].seatNumber = i + 1;
    }
}

void bookTicket()
{
    if (totalPassengers == TOTAL_SEATS)
    {
        printf("Sorry, all seats have been booked.\n");
        return;
    }

    Passenger newPassenger;

    printf("Enter passenger name: ");
    scanf("%s", newPassenger.name1);
    scanf("%s", newPassenger.name2);

    printf("Enter passenger age: ");
    scanf("%d", &newPassenger.age);

    if (newPassenger.age >= 60)
    {
        newPassenger.isSeniorCitizen = 1;
    }
    else
    {
        newPassenger.isSeniorCitizen = 0;
    }

    printf("Is the passenger a Prime Category or Normal Category? (1 for Prime, 0 for Normal): ");
    scanf("%d", &newPassenger.category);

    if (newPassenger.category)
    {
        if (primeSeats <= FIRST_CLASS_SEATS)
        {
            newPassenger.seatNumber = primeSeats;
            primeSeats++;
        }
        else
        {
            printf("Sorry, there are no more first class seats available. Assigning an economic class seat.\n");
            newPassenger.seatNumber = normalSeats;
            newPassenger.category = 0;
            normalSeats++;
        }
    }
    else
    {
        if (normalSeats <= TOTAL_SEATS)
        {
            newPassenger.seatNumber = normalSeats;
            normalSeats++;
        }
        else
        {
            printf("Sorry, all seats have been booked.\n");
            return;
        }
    }

    passengerList[totalPassengers] = newPassenger;
    totalPassengers++;

    printf("Ticket booked successfully. Seat number: %d\n", newPassenger.seatNumber);
}

void generatePassengerList()
{
    int soldTickets = totalPassengers;
    int minTicketsToSort = TOTAL_SEATS * 0.6;

    if (soldTickets < minTicketsToSort)
    {
        printf("Not enough tickets sold to generate the passenger list.\n");
        return;
    }

    // Sort the passenger list based on category (first class or economic class) and then by seniority within each category
    for (int i = 0; i < totalPassengers - 1; i++)
    {
        for (int j = 0; j < totalPassengers - i - 1; j++)
        {
            if ((passengerList[j].category < passengerList[j + 1].category) ||
                (passengerList[j].category == passengerList[j + 1].category && passengerList[j].isSeniorCitizen < passengerList[j + 1].isSeniorCitizen))
            {
                Passenger temp = passengerList[j];
                passengerList[j] = passengerList[j + 1];
                passengerList[j + 1] = temp;
            }
        }
    }

    printf("Passenger List:\n");
    printf("Seat No.   Passenger Name   Age   Category\n");
    for (int i = 0; i < totalPassengers; i++)
    {
        printf("%-10d %-16s %-16s %-5d %s\n", passengerList[i].seatNumber, passengerList[i].name1, passengerList[i].name2, passengerList[i].age, (passengerList[i].category == 1) ? "First Class" : "Economic Class");
    }
}

void seatInquiry()
{
    int seatNumber;

    printf("Enter the seat number to inquire: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > TOTAL_SEATS)
    {
        printf("Invalid seat number.\n");
        return;
    }

    for (int i = 0; i < totalPassengers; i++)
    {
        if (passengerList[i].seatNumber == seatNumber)
        {
            printf("Seat number %d is booked by %s %s.\n", seatNumber, passengerList[i].name1, passengerList[i].name2);
            return;
        }
    }

    printf("Seat number %d is available.\n", seatNumber);
}

int main()
{
    FILE *ftr = fopen("Airline Reservation System.csv", "w+");
    fprintf(ftr, "Name,Age,Senior Citizen,Category,Seat Number");

    initializeSeats();

    int option;
    do
    {
        printf("\n--- Airline Reservation System ---\n");
        printf("1. Book a ticket\n");
        printf("2. Generate passenger list\n");
        printf("3. Seat inquiry\n");
        printf("4. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            bookTicket();
            break;
        case 2:
            generatePassengerList();
            break;
        case 3:
            seatInquiry();
            break;
        case 4:
            printf("Exiting the program. Goodbye!\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    } while (option != 4);

    for (int i = 0; i < totalPassengers; i++)
    {
        fprintf(ftr, "\n%s %s", passengerList[i].name1, passengerList[i].name2);
        fprintf(ftr, ",%d", passengerList[i].age);
        if (passengerList[i].isSeniorCitizen == 1)
        {
            fprintf(ftr, ",Yes");
        }
        else
        {
            fprintf(ftr, ",No");
        }
        if (passengerList[i].category == 1)
        {
            fprintf(ftr, ",Prime");
        }
        else
        {
            fprintf(ftr, ",Normal");
        }
        fprintf(ftr, ",%d", passengerList[i].seatNumber);
    }

    return 0;
}
 