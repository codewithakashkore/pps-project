#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 100
#define MAX_PASSENGERS 100

// ---------------- FLIGHT STRUCTURE ----------------

struct Flight
{
    int flightNumber;
    char source[30];
    char destination[30];
    char date[20];
    char departureTime[20];
    char arrivalTime[20];
    int seatCapacity;
    int availableSeats;
    float ticketPrice;
    char flightStatus[20];
};

// ---------------- PASSENGER STRUCTURE ----------------

struct Passenger
{
    int bookingID;
    char name[30];
    char passportNumber[20];
    char mobileNumber[15];
    int flightNumber;
    char bookingStatus[20];
};

// ---------------- GLOBAL VARIABLES ----------------

struct Flight flights[MAX_FLIGHTS];
struct Passenger passengers[MAX_PASSENGERS];

int flightCount = 0;
int passengerCount = 0;
int bookingCounter = 1000;

// ---------------- ADMIN LOGIN ----------------

int adminLogin()
{
    char username[20];
    char password[20];

    printf("\n===== ADMIN LOGIN =====\n");

    printf("Username: ");
    scanf("%19s", username);

    printf("Password: ");
    scanf("%19s", password);

    if(strcmp(username, "admin") == 0 &&
       strcmp(password, "admin123") == 0)
    {
        printf("\nLogin Successful!\n");
        return 1;
    }

    printf("\nInvalid Credentials!\n");
    return 0;
}

// ---------------- USER LOGIN ----------------

int userLogin()
{
    char username[20];
    char password[20];

    printf("\n===== USER LOGIN =====\n");

    printf("Username: ");
    scanf("%19s", username);

    printf("Password: ");
    scanf("%19s", password);

    if(strcmp(username, "user") == 0 &&
       strcmp(password, "user123") == 0)
    {
        printf("\nLogin Successful!\n");
        return 1;
    }

    printf("\nInvalid Credentials!\n");
    return 0;
}

// ---------------- ADD FLIGHT ----------------

void addFlight()
{
    struct Flight f;

    printf("\n===== ADD FLIGHT =====\n");

    printf("Flight Number: ");
    scanf("%d", &f.flightNumber);

    printf("Source: ");
    scanf("%29s", f.source);

    printf("Destination: ");
    scanf("%29s", f.destination);

    printf("Date (DD/MM/YYYY): ");
    scanf("%19s", f.date);

    printf("Departure Time: ");
    scanf("%19s", f.departureTime);

    printf("Arrival Time: ");
    scanf("%19s", f.arrivalTime);

    printf("Seat Capacity: ");
    scanf("%d", &f.seatCapacity);

    f.availableSeats = f.seatCapacity;

    printf("Ticket Price: ");
    scanf("%f", &f.ticketPrice);

    printf("Flight Status (OnTime/Delayed): ");
    scanf("%19s", f.flightStatus);

    flights[flightCount] = f;
    flightCount++;

    printf("\nFlight Added Successfully!\n");
}

// ---------------- DISPLAY FLIGHTS ----------------

void displayFlights()
{
    int i;

    if(flightCount == 0)
    {
        printf("\nNo Flights Available!\n");
        return;
    }

    printf("\n========== FLIGHTS ==========\n");

    for(i = 0; i < flightCount; i++)
    {
        printf("\nFlight Number : %d", flights[i].flightNumber);
        printf("\nSource        : %s", flights[i].source);
        printf("\nDestination   : %s", flights[i].destination);
        printf("\nDate          : %s", flights[i].date);
        printf("\nDeparture     : %s", flights[i].departureTime);
        printf("\nArrival       : %s", flights[i].arrivalTime);
        printf("\nSeats Left    : %d", flights[i].availableSeats);
        printf("\nPrice         : %.2f", flights[i].ticketPrice);
        printf("\nStatus        : %s", flights[i].flightStatus);
        printf("\n-----------------------------\n");
    }
}

// ---------------- SEARCH FLIGHTS ----------------

void searchFlights()
{
    char source[30];
    char destination[30];
    int found = 0;

    printf("\n===== SEARCH FLIGHTS =====\n");

    printf("Enter Source: ");
    scanf("%29s", source);

    printf("Enter Destination: ");
    scanf("%29s", destination);

    for(int i = 0; i < flightCount; i++)
    {
        if(strcmp(flights[i].source, source) == 0 &&
           strcmp(flights[i].destination, destination) == 0)
        {
            found = 1;

            printf("\nFlight Number : %d", flights[i].flightNumber);
            printf("\nDate          : %s", flights[i].date);
            printf("\nDeparture     : %s", flights[i].departureTime);
            printf("\nArrival       : %s", flights[i].arrivalTime);
            printf("\nPrice         : %.2f", flights[i].ticketPrice);
            printf("\nSeats Left    : %d", flights[i].availableSeats);
            printf("\nStatus        : %s", flights[i].flightStatus);
            printf("\n-----------------------------\n");
        }
    }

    if(found == 0)
    {
        printf("\nNo Flights Found!\n");
    }
}

// ---------------- BOOK TICKET ----------------

void bookTicket()
{
    int flightNo;
    int found = 0;

    printf("\n===== BOOK TICKET =====\n");

    printf("Enter Flight Number: ");
    scanf("%d", &flightNo);

    for(int i = 0; i < flightCount; i++)
    {
        if(flights[i].flightNumber == flightNo)
        {
            found = 1;

            if(flights[i].availableSeats <= 0)
            {
                printf("\nNo Seats Available!\n");
                return;
            }

            struct Passenger p;

            p.bookingID = bookingCounter++;

            printf("Passenger Name: ");
            scanf("%29s", p.name);

            printf("Passport Number: ");
            scanf("%19s", p.passportNumber);

            printf("Mobile Number: ");
            scanf("%14s", p.mobileNumber);

            p.flightNumber = flightNo;

            strcpy(p.bookingStatus, "CONFIRMED");

            passengers[passengerCount] = p;
            passengerCount++;

            flights[i].availableSeats--;

            printf("\nTicket Booked Successfully!\n");
            printf("Booking ID: %d\n", p.bookingID);

            return;
        }
    }

    if(found == 0)
    {
        printf("\nFlight Not Found!\n");
    }
}

// ---------------- CANCEL TICKET ----------------

void cancelTicket()
{
    int bookingID;
    int found = 0;

    printf("\n===== CANCEL TICKET =====\n");

    printf("Enter Booking ID: ");
    scanf("%d", &bookingID);

    for(int i = 0; i < passengerCount; i++)
    {
        if(passengers[i].bookingID == bookingID)
        {
            found = 1;

            int flightNo = passengers[i].flightNumber;

            for(int j = 0; j < flightCount; j++)
            {
                if(flights[j].flightNumber == flightNo)
                {
                    flights[j].availableSeats++;
                    break;
                }
            }

            for(int j = i; j < passengerCount - 1; j++)
            {
                passengers[j] = passengers[j + 1];
            }

            passengerCount--;

            printf("\nTicket Cancelled Successfully!\n");
            return;
        }
    }

    if(found == 0)
    {
        printf("\nBooking ID Not Found!\n");
    }
}

// ---------------- VIEW PASSENGERS ----------------

void viewPassengers()
{
    if(passengerCount == 0)
    {
        printf("\nNo Passengers Found!\n");
        return;
    }

    printf("\n===== PASSENGER DETAILS =====\n");

    for(int i = 0; i < passengerCount; i++)
    {
        printf("\nBooking ID      : %d", passengers[i].bookingID);
        printf("\nPassenger Name  : %s", passengers[i].name);
        printf("\nPassport Number : %s", passengers[i].passportNumber);
        printf("\nMobile Number   : %s", passengers[i].mobileNumber);
        printf("\nFlight Number   : %d", passengers[i].flightNumber);
        printf("\nBooking Status  : %s", passengers[i].bookingStatus);
        printf("\n-------------------------------\n");
    }
}

// ---------------- UPDATE FLIGHT STATUS ----------------

void updateFlightStatus()
{
    int flightNo;
    char status[20];

    printf("\nEnter Flight Number: ");
    scanf("%d", &flightNo);

    for(int i = 0; i < flightCount; i++)
    {
        if(flights[i].flightNumber == flightNo)
        {
            printf("Enter New Status: ");
            scanf("%19s", status);

            strcpy(flights[i].flightStatus, status);

            printf("\nFlight Status Updated!\n");
            return;
        }
    }

    printf("\nFlight Not Found!\n");
}

// ---------------- DELETE FLIGHT ----------------

void deleteFlight()
{
    int flightNo;

    printf("\nEnter Flight Number to Delete: ");
    scanf("%d", &flightNo);

    for(int i = 0; i < flightCount; i++)
    {
        if(flights[i].flightNumber == flightNo)
        {
            for(int j = i; j < flightCount - 1; j++)
            {
                flights[j] = flights[j + 1];
            }

            flightCount--;

            printf("\nFlight Deleted Successfully!\n");
            return;
        }
    }

    printf("\nFlight Not Found!\n");
}

// ---------------- MAIN FUNCTION ----------------

int main()
{
    int choice;
    int mainChoice;

    while(1)
    {
        printf("\n=================================");
        printf("\n AIRLINE MANAGEMENT SYSTEM");
        printf("\n=================================");

        printf("\n1. Admin Login");
        printf("\n2. User Login");
        printf("\n3. Exit");

        printf("\nEnter Choice: ");
        scanf("%d", &mainChoice);

        switch(mainChoice)
        {
            case 1:

                if(adminLogin())
                {
                    do
                    {
                        printf("\n\n===== ADMIN MENU =====");
                        printf("\n1. Add Flight");
                        printf("\n2. Delete Flight");
                        printf("\n3. Display Flights");
                        printf("\n4. View Passengers");
                        printf("\n5. Update Flight Status");
                        printf("\n6. Logout");

                        printf("\nEnter Choice: ");
                        scanf("%d", &choice);

                        switch(choice)
                        {
                            case 1:
                                addFlight();
                                break;

                            case 2:
                                deleteFlight();
                                break;

                            case 3:
                                displayFlights();
                                break;

                            case 4:
                                viewPassengers();
                                break;

                            case 5:
                                updateFlightStatus();
                                break;

                            case 6:
                                printf("\nLogged Out...\n");
                                break;

                            default:
                                printf("\nInvalid Choice!\n");
                        }

                    } while(choice != 6);
                }

                break;

            case 2:

                if(userLogin())
                {
                    do
                    {
                        printf("\n\n===== USER MENU =====");
                        printf("\n1. Search Flights");
                        printf("\n2. Display Flights");
                        printf("\n3. Book Ticket");
                        printf("\n4. Cancel Ticket");
                        printf("\n5. Logout");

                        printf("\nEnter Choice: ");
                        scanf("%d", &choice);

                        switch(choice)
                        {
                            case 1:
                                searchFlights();
                                break;

                            case 2:
                                displayFlights();
                                break;

                            case 3:
                                bookTicket();
                                break;

                            case 4:
                                cancelTicket();
                                break;

                            case 5:
                                printf("\nLogging Out...\n");
                                break;

                            default:
                                printf("\nInvalid Choice!\n");
                        }

                    } while(choice != 5);
                }

                break;

            case 3:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}