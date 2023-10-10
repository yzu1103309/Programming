#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <vector>
using std::vector;

#include <cstring>

struct Date
{
    int year = 0;
    int month = 0;
    int day = 0;
};

struct AvailTable
{
    Date date;
    int numAvailTables[ 4 ][ 6 ] = {}; // the number of available tables,
};  // numAvailTables[ 1 ][ i ] is the number of available type i tables on 11:30
// numAvailTables[ 2 ][ i ] is the number of available type i tables on 14:30
// numAvailTables[ 3 ][ i ] is the number of available type i tables on 17:30

struct Reservation
{
    int numCustomers = 0;              // number of customers
    Date date;                         // reservation date
    int time = 0;                      // reservation time code
    char name[ 8 ] = "";               // name
    char mobileNumber[ 12 ] = "";      // mobile phone number
    char email[ 40 ] = "";             // email address
    char password[ 12 ] = "";          // reservation password
    char reservationNumber[ 12 ] = ""; // reservation number
};

// tableTypes[ i ] is the table type for i customers
const int tableTypes[ 13 ] = { 0, 1, 1, 2, 2, 3, 4, 4, 0, 0, 5, 5, 5 };

const int TOTAL_NUM_TABLES = 2; // suppose there are totally 2 tables for all types

// return current date
Date computeCurrentDate();

// return true if and only if year is a leap year
inline bool leapYear( int year );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// return true if and only if date1 == date2
bool equal( Date date1, Date date2 );

// return true if and only if date1 < date2
bool less( Date date1, Date date2 );

// return true if and only if date1 <= date2
bool lessEqual( Date date1, Date date2 );

// return date + numDays
Date add( Date date, int numDays );

// delete out of date data in availTables, and append new data from rear of availTables
void initAvailTables( vector< AvailTable > &availTables, Date currentDate );

// read available table informations after currentDate, from the file AvailTables.dat
void loadAvailTables( vector< AvailTable > &availTables, Date currentDate );

// read reservation informations after or equal to currentDate, from the file Reservations.dat
void loadReservations( vector< Reservation > &reservations, Date currentDate );

// make reservation
void makeReservation( vector< Reservation > &reservations, vector< AvailTable > &availTables, Date currentDate );

// choose a date and a time
void chooseDateTime( vector< AvailTable > &availTables, Reservation &reservation, Date currentDate, int tableType );

// display dates on which there are tables available
void displayAvailDates( vector< AvailTable > &availTables, bool available[], int tableType );

// return true if there are available tables on availTables[ i ].date for corresponding table type
bool availableTables( vector< AvailTable > &availTables, size_t i, int tableType );

// --availTables[ i ].numAvailTables[ timeCode ][ tableType ], where availTables[ i ].date == date
void decreaseAvailTables( vector< AvailTable > &availTables, Date date, int timeCode, int tableType );

// use reservationNumber to make a reservation inquiry, and let user choose whether to cancel it
void reservationInquiry( vector< Reservation > &reservations, vector< AvailTable > &availTables );

// display all fields of reservation which includes
// mobileNumber, name, date, time, email, numCustomers, password and reservationNumber
void displayReservationInfo( const Reservation &reservation );

// display reservations[ i ], where
// reservations[ i ].reservationNumber is equal to the specified reservationNumber
void displayReservationInfo( const vector< Reservation > &reservations, char reservationNumber[] );

// erase reservations[ position ]
void erase( vector< Reservation > &reservations, int position );

// write availTables into the file AvailTables.dat
void saveAvailTables( const vector< AvailTable > &availTables );

// write reservations into the file Reservations.dat
void saveReservations( const vector< Reservation > &reservations );

int main()
{
    cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

    srand( static_cast< unsigned int >( time( 0 ) ) );
    Date currentDate = computeCurrentDate();

    //for testing bugs
    /*
    currentDate.year = 2698;
    currentDate.month = 7;
    currentDate.day = 29;
    */

    vector< AvailTable > availTables; // vector of all available table informations
    initAvailTables( availTables, currentDate );

    vector< Reservation > reservations; // vector of all available table informations
    loadReservations( reservations, currentDate );

    bool userExited = false; // user has not chosen to exit

    // loop while user has not chosen option to exit system
    while( !userExited )
    {
        // show main menu and get user selection
        cout << "\n1 - Book a Table\n";
        cout << "2 - My Bookings\n";
        cout << "3 - End\n\n";

        int mainMenuSelection;
        do cout << "Enter your choice: (1~3): ";
        while( ( mainMenuSelection = inputAnInteger( 1, 3 ) ) == -1 );

        // decide how to proceed based on user's menu selection
        switch( mainMenuSelection )
        {
        case 1:
            makeReservation( reservations, availTables, currentDate ); // make reservation
            break;
        case 2:
            reservationInquiry( reservations, availTables ); // reservation inquiry
            break;
        case 3: // user chose to terminate session
            saveAvailTables( availTables );
            saveReservations( reservations );
            userExited = true; // this session should end
            cout << endl;
            break;
        default: // user did not enter an integer from 1-3
            cout << "\nIncorrect choice!" << endl;
        }
    }

    system( "pause" );
}

Date computeCurrentDate()
{
    Date Current;
    int seconds = static_cast< int >( time(0) ) + 8 * 60 * 60;
    int year = 1970;
    int secondsPerYear = 365 * 24 * 60 * 60;
    if (leapYear(year))
    {
        secondsPerYear += 24 * 60 * 60;
    }

    while (seconds >= secondsPerYear)
    {
        seconds -= secondsPerYear;
        year++;

        secondsPerYear = 365 * 24 * 60 * 60;
        if (leapYear(year))
        {
            secondsPerYear += 24 * 60 * 60;
        }
    }
    Current.year = year;
    int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (leapYear(year))
    {
        days[2] = 29;
    }
    int month = 1;
    while (seconds >= days[month] * 24 * 60 * 60)
    {
        seconds -= days[month] * 24 * 60 * 60;
        month++;
    }
    Current.month = month;
    int day = seconds / (24 * 60 * 60) + 1;
    Current.day = day;
    return Current;
}

inline bool leapYear( int year )
{
    return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

int inputAnInteger( int begin, int end )
{
    char string[ 80 ];
    cin.getline( string, 80, '\n' );

    if( strlen( string ) == 0 )
        exit( 0 );

    for( unsigned int i = 0; i < strlen( string ); i++ )
        if( string[ i ] < '0' || string[ i ] > '9' )
            return -1;

    int number = atoi( string );

    if( number >= begin && number <= end )
        return number;
    else
        return -1;
}

bool equal( Date date1, Date date2 )
{
    return ( date1.year == date2.year &&
             date1.month == date2.month &&
             date1.day == date2.day );
}

bool less( Date date1, Date date2 )
{
    if( date1.year < date2.year )
        return true;
    if( date1.year > date2.year )
        return false;

    if( date1.month < date2.month )
        return true;
    if( date1.month > date2.month )
        return false;

    if( date1.day < date2.day )
        return true;

    return false;
}

bool lessEqual( Date date1, Date date2 )
{
    return less( date1, date2 ) || equal( date1, date2 );
}

Date add( Date date, int numDays )
{
    int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    if(leapYear(date.year))
    {
        days[2]=29;
    }

    date.day += numDays;
    while (date.day > days[date.month])
    {
        date.day -= days[date.month];
        date.month++;
    }
    while (date.month > 12)
    {
        date.month -= 12;
        date.year++;
    }
    return date;
}

void initAvailTables( vector< AvailTable > &availTables, Date currentDate )
{
    loadAvailTables( availTables, currentDate );

    AvailTable addBuffer;
    for(int i=1;i<=3;i++){
        for(int j=1;j<=5;j++){
            addBuffer.numAvailTables[i][j]=TOTAL_NUM_TABLES;
        }
    }

    for(int t=availTables.size()+1;t<=30;t++){
        //add to 30 days
        addBuffer.date=add(currentDate,t);
        availTables.push_back(addBuffer);
    }

}

void loadAvailTables( vector< AvailTable > &availTables, Date currentDate )
{
    ifstream File("AvailTables4.dat", ios::in | ios::binary);

    if (!File)
    {
        cout << "There's something wrong with the files...exiting...";
        exit(1);
    }
    AvailTable readBuffer;

    while (File.read(reinterpret_cast<char*>(&readBuffer), sizeof(readBuffer)))
    {
        if (less(currentDate, readBuffer.date))
        {
            availTables.push_back(readBuffer);
        }
    }
}

void loadReservations( vector< Reservation > &reservations, Date currentDate )
{
    ifstream RFile("Reservations.dat", ios::in | ios::binary);
    if (!RFile)
    {
        cout << "Reservation list could not be accessed";
        exit(1);
    }
    Reservation buffer;
    while (RFile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer)))
    {
        if (lessEqual(currentDate, buffer.date))
        {
            reservations.push_back(buffer);
        }
    }
    RFile.close();
}

void makeReservation( vector< Reservation > &reservations, vector< AvailTable > &availTables, Date currentDate )
{
    Reservation newReservation;

    do
    {
        cout << "\nEnter the number of customers (1 - 7, 10 - 12): ";
        newReservation.numCustomers = inputAnInteger( 1, 12 );
    }
    while( newReservation.numCustomers == 8 ||
            newReservation.numCustomers == 9 ||
            newReservation.numCustomers == -1 );

    int tableType = tableTypes[ newReservation.numCustomers ];

    chooseDateTime( availTables, newReservation, currentDate, tableType );

    cout << "\nEnter name: ";
    cin >> newReservation.name;

    cout << "\nEnter mobile number: ";
    cin >> newReservation.mobileNumber;

    cout << "\nEnter email address: ";
    cin >> newReservation.email;

    cout << "\nEnter reservation password: ";
    cin >> newReservation.password;
    cin.ignore();

    newReservation.reservationNumber[ 0 ] = 1 + rand() % 9 + '0';
    for( int i = 1; i < 8; i++ )
        newReservation.reservationNumber[ i ] = rand() % 10 + '0';

    cout << setfill( ' ' ) << endl << setw( 11 ) << "Mobile No." << setw( 10 ) << "Name"
         << setw( 14 ) << "Date" << setw( 9 ) << "Time" << setw( 30 ) << "Email"
         << setw( 19 ) << "No of Customers" << setw( 12 ) << "Password"
         << setw( 19 ) << "Reservation No." << endl;

    displayReservationInfo( newReservation );

    cout << "\nReservation Completed!\n";

    reservations.push_back( newReservation );

    decreaseAvailTables( availTables, newReservation.date, newReservation.time, tableType );
}

// choose a date and a time
void chooseDateTime( vector< AvailTable > &availTables, Reservation &reservation, Date currentDate, int tableType )
{
    cout << "Choose a date" << endl;
    bool available[30]= {};

    displayAvailDates(availTables,available,tableType);
    int chDate;
    do
    {
        cout << endl;
        cout << setfill(' ') << setw(3) << "? ";
    }

    while((chDate=inputAnInteger(1,30))==-1||available[chDate-1]==false);

    cout << endl << "choose a time: " << endl;

    for (int k = 1; k < 4; k++)
    {
        if (availTables[chDate-1].numAvailTables[k][tableType] != 0)
        {
            switch (k)
            {
            case 1:
                cout << "1. 11:30" << endl;
                break;
            case 2:
                cout << "2. 14:30" << endl;
                break;
            case 3:
                cout << "3. 17:30" << endl;
                break;
            }
        }
    }

    int chTime;
    do
    {
        cout << "? ";
    }
    while ((chTime = inputAnInteger(1, 3)) == -1 || availTables[chDate - 1].numAvailTables[chTime][tableType] == 0);

    reservation.date = availTables[chDate - 1].date;
    reservation.time = chTime;

}

void displayAvailDates( vector< AvailTable > &availTables, bool availableDate[], int tableType )
{
    for(size_t i = 0; i < availTables.size() && i < 30; i++)
    {
        availableDate[i] = availableTables(availTables, i, tableType);
        if(availableDate[i])
        {
            cout << setfill(' ') << setw(3) << i + 1 << ". " << availTables[i].date.year << "/"<< setfill('0')
                 <<setw(2) << availTables[i].date.month << "/" << setw(2) << availTables[i].date.day;
        }
        if(i%4==3)
        {
            cout<<endl;
        }
    }
}

// returns true if there are available tables on availTables[ i ].date for corresponding table type
bool availableTables( vector< AvailTable > &availTables, size_t i, int tableType )
{
    for(int k = 1; k < 4; k++) //time code
    {
        if(availTables[i].numAvailTables[k][tableType]!=0)
        {
            return true;
        }
    }
    return false;
}

// --availTables[ i ].numAvailTables[ timeCode ][ tableType ], where availTables[ i ].date == date
void decreaseAvailTables( vector< AvailTable > &availTables, Date date, int timeCode, int tableType )
{
    for (size_t i = 0; i < 30 && i < availTables.size(); i++)
    {
        if (equal(availTables[i].date,date))
        {
            availTables[i].numAvailTables[timeCode][tableType]--;
        }
    }
}

void reservationInquiry( vector< Reservation > &reservations, vector< AvailTable > &availTables )
{
    if( reservations.size() == 0 )
    {
        cout << "\nNo reservations!\n";
        return;
    }

    cout << "\nEnter reservation number: ";
    char reservationNumber[ 12 ];
    cin >> reservationNumber;
    cin.ignore();

    int position;
    char password[12];
    for (size_t i = 0; i < reservations.size(); i++)
    {
        if (strcmp(reservations[i].reservationNumber, reservationNumber) == 0)
        {
            position = i;
            do
            {
                cout << "Enter reservation password: ";
                cin >> password;
                cin.ignore();
                if (strcmp(reservations[i].password, password) == 0)
                {
                    cout << endl;
                    displayReservationInfo(reservations, reservationNumber);
                    char YN;
                    cout << endl;
                    cout << "Cancel this reservation ( y/n )? ";
                    cin >> YN;
                    cin.ignore();
                    if (YN == 'y')
                    {
                        for (size_t t = 0; t < 30 && t < availTables.size(); t++)
                        {
                            if (equal(reservations[i].date,availTables[t].date))
                            {
                                availTables[t].numAvailTables[reservations[i].time][tableTypes[reservations[i].numCustomers]]++;
                            }
                        }
                        erase(reservations, position);
                        cout << endl << "This reservation has been cancelled." << endl;
                        break;
                    }
                }
                else
                {
                    cout << "Wrong Password. Please retry..." << endl;
                }
            }
            while (strcmp(reservations[i].password,password)!=0);
            break; //if found, then stop searching.
        }
        else if (i == reservations.size() - 1)
        {
            cout << "No reservations with this reservation number!";
        }
    }
}

// displays all fields of reservation which includes
// mobileNumber, name, date, time, email, numCustomers, password and reservationNumber
void displayReservationInfo( const Reservation &reservation )
{
    char times[ 4 ][ 8 ] = { "", "11:30", "14:30", "17:30" };
    cout << setfill( ' ' ) << setw( 11 ) << reservation.mobileNumber
         << setw( 10 ) << reservation.name
         << "    " << reservation.date.year << "/" << setfill( '0' )
         << setw( 2 ) << reservation.date.month << '/'
         << setw( 2 ) << reservation.date.day
         << setfill( ' ' ) << setw( 9 ) << times[ reservation.time ]
         << setw( 30 ) << reservation.email
         << setw( 19 ) << reservation.numCustomers
         << setw( 12 ) << reservation.password
         << setw( 19 ) << reservation.reservationNumber << endl;
}

// displays reservations[ i ], where
// reservations[ i ].reservationNumber is equal to the specified reservationNumber
void displayReservationInfo( const vector< Reservation > &reservations, char reservationNumber[] )
{
    cout << setfill( ' ' ) << setw( 11 ) << "Mobile No." << setw( 10 ) << "Name"
         << setw( 14 ) << "Date" << setw( 9 ) << "Time" << setw( 30 ) << "Email"
         << setw( 19 ) << "No of Customers" << setw( 12 ) << "Password"
         << setw( 19 ) << "Reservation No." << endl;

    for( size_t i = 0; i < reservations.size(); ++i )
        if( strcmp( reservations[ i ].reservationNumber, reservationNumber ) == 0 )
            break;

    char times[ 4 ][ 8 ] = { "", "11:30", "14:30", "17:30" };
    int count = 0;
    for( size_t i = 0; i < reservations.size(); ++i )
        if( strcmp( reservations[ i ].reservationNumber, reservationNumber ) == 0 )
            displayReservationInfo( reservations[ i ] );
}

// erase reservations[ position ]
void erase( vector< Reservation > &reservations, int position )
{
    /*Reservation buffer;
    reservations.push_back(buffer);
    for (size_t t = position; t < reservations.size(); t++) {
        reservations[t] = reservations[t + 1];
        reservations.resize(reservations.size() - 1);
    }*/
    reservations.erase(reservations.begin() + position);
}

void saveAvailTables( const vector< AvailTable > &availTables )
{
    ofstream Fsave("AvailTables4.dat", ios::out | ios::binary);
    for(size_t t=0;t<availTables.size();t++){
        Fsave.write(reinterpret_cast<const char*>(&availTables[t]), sizeof(availTables[t]));
    }
}

void saveReservations(const vector< Reservation >& reservations)
{
    ofstream Fsave("Reservations.dat", ios::out | ios::binary);
    if (!Fsave)
    {
        cout << "Reservation file could not be accessed" << endl;
        exit(0);
    }
    for (size_t i = 0; i < reservations.size(); i++)
    {
        Fsave.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(reservations[i]));
    }
    Fsave.close();
}
