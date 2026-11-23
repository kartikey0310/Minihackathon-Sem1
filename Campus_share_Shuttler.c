#include <stdio.h>


/* =========================================================
   BOOKING STRUCTURE
   Used for storing booking records in binary file
   ========================================================= */

struct Booking
{
    int bookingID;
    long SAP_ID;
    int student;
    int from;
    int to;
    int vehicle;
    int returnTrip;
    int monthlyPass;
    float fare;
};


/* =========================================================
   FARE DATABASE

   Vehicle:
   0 = Bike
   1 = Car
   2 = Bus
   3 = Auto
   ========================================================= */

int arr[6][6][4] =
{
    {
        {0, 0, 0, 0},
        {20, 80, 10, 30},
        {80, 190, 50, 130},
        {85, 205, 50, 135},
        {180, 430, 110, 290},
        {90, 215, 55, 145}
    },

    {
        {20, 80, 10, 30},
        {0, 0, 0, 0},
        {70, 170, 40, 110},
        {75, 180, 45, 120},
        {170, 410, 100, 270},
        {80, 190, 50, 130}
    },

    {
        {80, 190, 50, 130},
        {70, 170, 40, 110},
        {0, 0, 0, 0},
        {20, 80, 10, 30},
        {130, 310, 80, 210},
        {25, 80, 15, 40}
    },

    {
        {85, 205, 50, 135},
        {75, 180, 45, 120},
        {20, 80, 10, 30},
        {0, 0, 0, 0},
        {135, 325, 80, 215},
        {20, 80, 10, 30}
    },

    {
        {180, 430, 110, 290},
        {170, 410, 100, 270},
        {130, 310, 80, 210},
        {135, 325, 80, 215},
        {0, 0, 0, 0},
        {140, 335, 85, 225}
    },

    {
        {90, 215, 55, 145},
        {80, 190, 50, 130},
        {25, 80, 15, 40},
        {20, 80, 10, 30},
        {140, 335, 85, 225},
        {0, 0, 0, 0}
    }
};


/* =========================================================
   LOCATION AND VEHICLE NAMES
   ========================================================= */

const char *locationNames[6] =
{
    "Bidholi Main Gate",
    "Kandholi Main Gate",
    "Hospital",
    "Railway Station",
    "Airport",
    "ISBT"
};


const char *vehicleNames[4] =
{
    "Bike",
    "Car",
    "Bus",
    "Auto"
};


/* =========================================================
   DISPLAY LOCATIONS
   ========================================================= */

void locations(void)
{
    int i;

    for(i = 0; i < 6; i++)
    {
        printf("%d. %s\n", i + 1, locationNames[i]);
    }
}


/* =========================================================
   CHECK STUDENT FROM BINARY FILE
   ========================================================= */

int Isstudent(long SAP_ID)
{
    long ID;

    FILE *fp = fopen("Students.dat", "rb");

    if(fp == NULL)
    {
        printf("\nERROR: Students.dat could not be opened.\n");
        return 0;
    }


    while(fread(&ID, sizeof(long), 1, fp) == 1)
    {
        if(SAP_ID == ID)
        {
            fclose(fp);

            return 1;
        }
    }


    fclose(fp);

    return 0;
}


/* =========================================================
   CHECK MONTHLY PASS
   ========================================================= */

int CheckPass(long SAP_ID)
{
    long ID;

    FILE *fp = fopen("Pass.dat", "rb");


    if(fp == NULL)
    {
        return 0;
    }


    while(fread(&ID, sizeof(long), 1, fp) == 1)
    {
        if(SAP_ID == ID)
        {
            fclose(fp);

            return 1;
        }
    }


    fclose(fp);

    return 0;
}


/* =========================================================
   GENERATE BOOKING ID

   BookingID.dat stores one integer.
   Example:

   1001
   1002
   1003

   But it is stored in binary form.
   ========================================================= */

int GenerateBookingID(void)
{
    int bookingID = 1000;

    FILE *fp = fopen("BookingID.dat", "rb");


    if(fp != NULL)
    {
        fread(&bookingID, sizeof(int), 1, fp);

        fclose(fp);
    }


    bookingID++;


    fp = fopen("BookingID.dat", "wb");


    if(fp != NULL)
    {
        fwrite(&bookingID, sizeof(int), 1, fp);

        fclose(fp);
    }


    return bookingID;
}


/* =========================================================
   BUY MONTHLY PASS
   ========================================================= */

void BuyPass(long SAP_ID, int student)
{
    FILE *fp;

    char choice;


    /* Only verified students can buy pass */

    if(!student)
    {
        printf("\nOnly verified UPES students can buy a monthly pass.\n");

        return;
    }


    /* Check whether student already has pass */

    if(CheckPass(SAP_ID))
    {
        printf("\nYou already have an active monthly pass.\n");

        return;
    }


    printf("\n========================================\n");
    printf("           MONTHLY PASS\n");
    printf("========================================\n");

    printf("Monthly Pass Price : Rs. 1500\n");

    printf("SAP ID             : %ld\n", SAP_ID);


    printf("\nDo you want to buy the pass? (Y/N): ");

    scanf(" %c", &choice);


    if(choice != 'Y' && choice != 'y')
    {
        printf("\nPurchase cancelled.\n");

        return;
    }


    /*
       Open binary file in append mode.
       New SAP ID is added at the end.
    */

    fp = fopen("Pass.dat", "ab");


    if(fp == NULL)
    {
        printf("\nUnable to open Pass.dat\n");

        return;
    }


    fwrite(&SAP_ID, sizeof(long), 1, fp);


    fclose(fp);


    printf("\n========================================\n");

    printf("     MONTHLY PASS PURCHASE SUCCESSFUL\n");

    printf("========================================\n");

    printf("SAP ID : %ld\n", SAP_ID);

    printf("Amount : Rs. 1500\n");

    printf("Status : ACTIVE\n");

    printf("========================================\n");
}


/* =========================================================
   VIEW MONTHLY PASS
   ========================================================= */

void ViewPass(long SAP_ID, int student)
{
    if(!student)
    {
        printf("\nMonthly passes are available only to verified students.\n");

        return;
    }


    printf("\n========================================\n");

    printf("          MONTHLY PASS STATUS\n");

    printf("========================================\n");


    printf("SAP ID : %ld\n", SAP_ID);


    if(CheckPass(SAP_ID))
    {
        printf("Status : ACTIVE\n");
    }

    else
    {
        printf("Status : NOT ACTIVE\n");
    }


    printf("========================================\n");
}


/* =========================================================
   RETURN TRIP
   ========================================================= */

int ReturnTrip(void)
{
    char choice;


    printf("\nDo you want a Return Trip? (Y/N): ");

    scanf(" %c", &choice);


    if(choice == 'Y' || choice == 'y')
    {
        return 1;
    }


    return 0;
}


/* =========================================================
   SAVE BOOKING IN BINARY FILE
   ========================================================= */

void SaveBooking(int bookingID,
                 long SAP_ID,
                 int student,
                 int from,
                 int to,
                 int vehicle,
                 int returnTrip,
                 int monthlyPass,
                 float fare)
{
    struct Booking b;


    /* Put all information inside structure */

    b.bookingID = bookingID;

    b.SAP_ID = SAP_ID;

    b.student = student;

    b.from = from;

    b.to = to;

    b.vehicle = vehicle;

    b.returnTrip = returnTrip;

    b.monthlyPass = monthlyPass;

    b.fare = fare;


    /* Open binary booking file */

    FILE *fp = fopen("Bookings.dat", "ab");


    if(fp == NULL)
    {
        printf("\nWarning: Booking could not be saved.\n");

        return;
    }


    /* Write complete structure */

    fwrite(&b, sizeof(struct Booking), 1, fp);


    fclose(fp);
}


/* =========================================================
   PRINT TICKET
   ========================================================= */

void PrintTicket(int bookingID,
                 long SAP_ID,
                 int student,
                 int from,
                 int to,
                 int vehicle,
                 int returnTrip,
                 int monthlyPass,
                 float fare)
{
    printf("\n");

    printf("============================================\n");

    printf("            CAMPUS SHARE TICKET\n");

    printf("============================================\n");


    printf("Booking ID    : %d\n", bookingID);


    /* Student details */

    if(student)
    {
        printf("SAP ID        : %ld\n", SAP_ID);

        printf("Student       : Yes\n");
    }

    else
    {
        printf("SAP ID        : N/A\n");

        printf("Student       : No\n");
    }


    /* Journey details */

    printf("From          : %s\n", locationNames[from]);

    printf("To            : %s\n", locationNames[to]);

    printf("Vehicle       : %s\n", vehicleNames[vehicle]);


    /* Return trip */

    if(returnTrip)
    {
        printf("Return Trip   : Yes\n");
    }

    else
    {
        printf("Return Trip   : No\n");
    }


    /* Monthly pass information */

    if(monthlyPass && vehicle == 2)
    {
        printf("Monthly Pass  : Applied\n");
    }

    else if(monthlyPass)
    {
        printf("Monthly Pass  : Active (Bus Only)\n");
    }

    else
    {
        printf("Monthly Pass  : No\n");
    }


    printf("--------------------------------------------\n");


    printf("TOTAL FARE    : Rs. %.2f\n", fare);


    printf("============================================\n");

    printf("          THANK YOU FOR RIDING!\n");

    printf("============================================\n");
}


/* =========================================================
   BOOK A RIDE
   ========================================================= */

void BookRide(long SAP_ID, int student)
{
    int choice1;

    int choice2;

    int choice3;


    int returnTrip = 0;

    int monthlyPass = 0;


    int bookingID;


    float fare;


    /* =====================================================
       BOARDING LOCATION
       ===================================================== */

    printf("\n========================================\n");

    printf("        SELECT BOARDING LOCATION\n");

    printf("========================================\n");


    locations();


    printf("Enter choice: ");

    scanf("%d", &choice1);


    /* =====================================================
       DESTINATION
       ===================================================== */

    printf("\n========================================\n");

    printf("          SELECT DESTINATION\n");

    printf("========================================\n");


    locations();


    printf("Enter choice: ");

    scanf("%d", &choice2);


    /* Validate locations */

    if(choice1 < 1 || choice1 > 6 ||
       choice2 < 1 || choice2 > 6)
    {
        printf("\nInvalid location choice.\n");

        return;
    }


    /* Same location is not allowed */

    if(choice1 == choice2)
    {
        printf("\nBoarding and destination cannot be the same.\n");

        return;
    }


    /*
       Convert menu number into array index.

       Menu:
       1 2 3 4 5 6

       Array:
       0 1 2 3 4 5
    */

    choice1--;

    choice2--;


    /* =====================================================
       VEHICLE SELECTION
       ===================================================== */

    printf("\n========================================\n");

    printf("            SELECT VEHICLE\n");

    printf("========================================\n");


    printf("1. Bike\n");

    printf("2. Car\n");

    printf("3. Bus\n");

    printf("4. Auto\n");


    printf("Enter choice: ");

    scanf("%d", &choice3);


    /* Validate vehicle */

    if(choice3 < 1 || choice3 > 4)
    {
        printf("\nInvalid vehicle choice.\n");

        return;
    }


    /*
       Convert menu vehicle number into array index.

       1 Bike -> 0
       2 Car  -> 1
       3 Bus  -> 2
       4 Auto -> 3
    */

    choice3--;


    /* =====================================================
       GET BASE FARE
       ===================================================== */

    fare = arr[choice1][choice2][choice3];


    /* =====================================================
       CHECK MONTHLY PASS
       ===================================================== */

    if(student)
    {
        monthlyPass = CheckPass(SAP_ID);
    }


    /*
       Monthly pass applies only to Bus.

       Bus index = 2
    */

    if(monthlyPass && choice3 == 2)
    {
        fare = 0;


        printf("\nMonthly pass applied to your bus ride.\n");
    }

    else
    {
        /* =================================================
           STUDENT DISCOUNT
           25% concession
           ================================================= */

        if(student)
        {
            fare = fare * 0.75f;
        }


        /* =================================================
           RETURN TRIP
           ================================================= */

        returnTrip = ReturnTrip();


        /*
           Return-trip discount = 10%
        */

        if(returnTrip)
        {
            fare = fare * 0.90f;
        }
    }


    /* =====================================================
       GENERATE BOOKING ID
       ===================================================== */

    bookingID = GenerateBookingID();


    /* =====================================================
       SAVE BOOKING
       ===================================================== */

    SaveBooking(
        bookingID,
        SAP_ID,
        student,
        choice1,
        choice2,
        choice3,
        returnTrip,
        monthlyPass,
        fare
    );


    /* =====================================================
       PRINT TICKET
       ===================================================== */

    PrintTicket(
        bookingID,
        SAP_ID,
        student,
        choice1,
        choice2,
        choice3,
        returnTrip,
        monthlyPass,
        fare
    );
}


/* =========================================================
   VIEW BOOKING HISTORY USING fread()
   ========================================================= */

void ViewBookings(long SAP_ID, int student)
{
    struct Booking b;

    int found = 0;


    /* Only verified students can see history */

    if(!student)
    {
        printf("\nBooking history requires a verified SAP ID.\n");

        return;
    }


    FILE *fp = fopen("Bookings.dat", "rb");


    if(fp == NULL)
    {
        printf("\nNo booking history found.\n");

        return;
    }


    printf("\n========================================\n");

    printf("            BOOKING HISTORY\n");

    printf("========================================\n");


    /*
       Read one Booking structure at a time
       from binary file.
    */

    while(fread(&b, sizeof(struct Booking), 1, fp) == 1)
    {
        /*
           Only show bookings belonging
           to currently logged-in student.
        */

        if(b.SAP_ID == SAP_ID)
        {
            found = 1;


            printf("\nBooking ID : %d\n", b.bookingID);


            printf("From       : %s\n",
                   locationNames[b.from]);


            printf("To         : %s\n",
                   locationNames[b.to]);


            printf("Vehicle    : %s\n",
                   vehicleNames[b.vehicle]);


            if(b.returnTrip)
            {
                printf("Return     : Yes\n");
            }

            else
            {
                printf("Return     : No\n");
            }


            if(b.monthlyPass)
            {
                printf("Pass       : Yes\n");
            }

            else
            {
                printf("Pass       : No\n");
            }


            printf("Fare       : Rs. %.2f\n", b.fare);


            printf("----------------------------------------\n");
        }
    }


    fclose(fp);


    if(!found)
    {
        printf("\nNo previous bookings found for SAP ID %ld.\n",
               SAP_ID);
    }
}


/* =========================================================
   MAIN FUNCTION
   ========================================================= */

int main(void)
{
    char studentChoice;


    long SAP_ID = 0;


    int student = 0;


    int menuChoice;


    printf("============================================\n");

    printf("             CAMPUS SHARE\n");

    printf("============================================\n");


    /* =====================================================
       STUDENT VERIFICATION
       ===================================================== */

    printf("\nAre you a UPES Student? (Y/N): ");

    scanf(" %c", &studentChoice);


    if(studentChoice == 'Y' ||
       studentChoice == 'y')
    {
        printf("Enter your SAP ID: ");

        scanf("%ld", &SAP_ID);


        /* Search SAP ID in Students.dat */

        student = Isstudent(SAP_ID);


        if(student)
        {
            printf("\nStudent verified successfully!\n");


            /* Check monthly pass */

            if(CheckPass(SAP_ID))
            {
                printf("Monthly Pass: ACTIVE\n");
            }

            else
            {
                printf("Monthly Pass: NOT ACTIVE\n");
            }
        }

        else
        {
            printf("\nStudent ID not found.\n");

            printf("Continuing as a normal user.\n");


            SAP_ID = 0;
        }
    }


    /* =====================================================
       MAIN MENU
       ===================================================== */

    do
    {
        printf("\n");

        printf("============================================\n");

        printf("                MAIN MENU\n");

        printf("============================================\n");


        printf("1. Book a Ride\n");

        printf("2. Buy Monthly Pass\n");

        printf("3. Check Monthly Pass\n");

        printf("4. View Booking History\n");

        printf("5. Exit\n");


        printf("--------------------------------------------\n");


        printf("Enter your choice: ");

        scanf("%d", &menuChoice);


        switch(menuChoice)
        {
            case 1:

                BookRide(SAP_ID, student);

                break;


            case 2:

                BuyPass(SAP_ID, student);

                break;


            case 3:

                ViewPass(SAP_ID, student);

                break;


            case 4:

                ViewBookings(SAP_ID, student);

                break;


            case 5:

                printf("\n============================================\n");

                printf(" Thank you for using Campus Share!\n");

                printf("============================================\n");

                break;


            default:

                printf("\nInvalid menu choice. Please try again.\n");
        }


    } while(menuChoice != 5);


    return 0;
}