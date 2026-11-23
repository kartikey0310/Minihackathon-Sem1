<div align="center">

# 🚌 Campus Share

**A campus ride-booking and fare system built in C**

*Student verification · 3D-array fares · Monthly bus pass · Printed tickets*

!\[Language](https://img.shields.io/badge/language-C-2B4A9A?style=for-the-badge\&logo=c\&logoColor=white)
!\[Type](https://img.shields.io/badge/app-console%20menu-E2874F?style=for-the-badge)
!\[Storage](https://img.shields.io/badge/storage-binary%20files-22303F?style=for-the-badge)
!\[Event](https://img.shields.io/badge/C%20Mini%20Hackathon-UPES-2B4A9A?style=for-the-badge)

**Team Coding Rangers**
Kartikey Agarwal · Rudra Gupta · Shubh Agarwal

</div>

\---

## 📌 The problem

Travel from campus to the hospital, railway station, airport and ISBT has **no fixed, visible pricing**, students get **no discount or pass**, and there is **no record** of past rides.

## ✅ Our solution

One menu-driven C program that books, prices and records every ride.

|||
|-|-|
|**6** locations|Bidholi Main Gate, Kandoli Main Gate, Hospital, Railway Station, Airport, ISBT|
|**4** vehicles|Bike, Car, Bus, Auto, each with its own base fare|
|**25%** student discount|Applied after the SAP ID is verified from `Students.dat`|
|**10%** return-trip discount|Applied on top of the student discount|
|**Rs. 1500** monthly pass|Free unlimited **Bus** rides for the pass holder|
|**Tickets + history**|Unique booking ID, saved to `Bookings.dat` and viewable later|

\---

## 🧭 How it works

```mermaid
flowchart TD
    A(\[START]) --> B{UPES student?}
    B -- No --> M\[MAIN MENU]
    B -- Yes --> C\[Enter SAP ID]
    C --> D{Found in Students.dat?}
    D -- Yes --> E\[Verified student, check pass]
    D -- No --> M
    E --> M
    M --> M1\[1 Book Ride]
    M --> M2\[2 Buy Monthly Pass]
    M --> M3\[3 Check Monthly Pass]
    M --> M4\[4 View Booking History]
    M --> M5\[5 Exit]
    M1 --> F{Active pass AND Bus?}
    F -- Yes --> G\[Fare = 0]
    F -- No --> H{Verified student?}
    H -- Yes --> I\[Fare x 0.75]
    H -- No --> J{Return trip?}
    I --> J
    J -- Yes --> K\[Fare x 0.90]
    J -- No --> L\[Generate ID, save booking, print ticket]
    K --> L
    G --> L
```

### Fare formula

```
fare = arr\[from]\[to]\[vehicle]          // 3D array: int arr\[6]\[6]\[4]
if (active pass AND Bus)  fare = 0
else {
    if (verified student)  fare = fare \* 0.75
    if (return trip)       fare = fare \* 0.90
}
```

**Example:** Bidholi Main Gate → Airport, Car, student, return trip
`430 × 0.75 × 0.90 =` **Rs. 290.25**

\---

## 🎫 Sample ticket

```
==================================
        CAMPUS SHARE TICKET
==================================
Booking ID   : 1001
SAP ID       : 500012345
Student      : Yes
From         : Bidholi Main Gate
To           : Airport
Vehicle      : Car
Return Trip  : Yes
Monthly Pass : No
----------------------------------
TOTAL FARE   : Rs. 290.25
==================================
        THANK YOU FOR RIDING!
==================================
```

*(Layout shown is illustrative; the exact wording is printed by `PrintTicket()`.)*

\---

## 💰 Base fare table (Rs.)

The table is symmetric (A→B costs the same as B→A) and same-place trips are blocked.

|Route|Bike|Car|Bus|Auto|
|-|-:|-:|-:|-:|
|Bidholi – Kandoli|20|80|10|30|
|Bidholi – Hospital|80|190|50|130|
|Bidholi – Railway Station|85|205|50|135|
|Bidholi – Airport|180|430|110|290|
|Bidholi – ISBT|90|215|55|145|
|Kandholi – Hospital|70|170|40|110|
|Kandholi – Railway Station|75|180|45|120|
|Kandholi – Airport|170|410|100|270|
|Kandholi – ISBT|80|190|50|130|
|Hospital – Railway Station|20|80|10|30|
|Hospital – Airport|130|310|80|210|
|Hospital – ISBT|25|80|15|40|
|Railway Station – Airport|135|325|80|215|
|Railway Station – ISBT|20|80|10|30|
|Airport – ISBT|140|335|85|225|

\---

## 🗂️ Repository files

|File|Purpose|
|-|-|
|`Campus\_share\_Shuttler.c`|The complete C source code|
|`S.exe`|Pre-built Windows executable|
|`Students.dat`|Verified UPES student SAP IDs (binary, `long` values)|
|`Pass.dat`|SAP IDs holding an active monthly pass (created on first purchase)|
|`Bookings.dat`|Master ledger, one record per ride|
|`BookingID.dat`|Last booking ID used (first ticket is `1001`)|

### Main functions

|Function|Responsibility|
|-|-|
|`main()`|Login and menu loop|
|`BookRide()`|Trip selection and fare logic|
|`Isstudent()`|Verifies the SAP ID in `Students.dat`|
|`CheckPass()` · `BuyPass()` · `ViewPass()`|Manage `Pass.dat`|
|`ReturnTrip()`|Asks for and applies the return discount|
|`GenerateBookingID()`|Reads, increments and stores the booking ID|
|`SaveBooking()` · `ViewBookings()`|File I/O for ride history|
|`PrintTicket()`|Prints the ticket to the console|

**C concepts used:** 3D arrays · structures · binary file handling (`fopen`, `fread`, `fwrite`) · functions with parameters · `switch` / loops · `const char \*` name tables

\---

## 🚀 Getting started

**1. Compile**

```bash
gcc Campus\_share\_Shuttler.c -o campus\_share
```

**2. Run** (from the folder that contains the `.dat` files)

```bash
./campus\_share          # Windows: campus\_share.exe   (or run the included S.exe)
```

**3. Add your own students (optional).** `Students.dat` is a binary file of `long` SAP IDs. To create one, compile and run this small program once:

```c
#include <stdio.h>
int main(void) {
    long ids\[] = {500012345L, 500067890L};          /\* put real SAP IDs here \*/
    FILE \*f = fopen("Students.dat", "wb");
    fwrite(ids, sizeof(long), 2, f);
    fclose(f);
    return 0;
}
```

If `Students.dat` is missing, the program reports it and continues with everyone treated as a normal user.

\---

## ⚠️ Edge cases handled

* Invalid location or vehicle choices are rejected
* Same boarding and destination are blocked
* Unknown SAP IDs continue as a normal user
* A missing `Students.dat` is reported instead of crashing
* Only verified students can buy a pass, and only one pass per SAP ID

## 🔭 What's next

* \[ ] Pass expiry dates (30-day lifecycle)
* \[ ] Safer input handling that rejects non-numeric characters
* \[ ] Admin menu for dynamic student and fare management
* \[ ] GUI and real payment integration

\---

<div align="center">

Made for the **C Programming Mini Hackathon · UPES** by **Team Coding Rangers**

</div>


