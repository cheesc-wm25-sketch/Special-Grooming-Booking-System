#include <iostream> 
#include <iomanip> 
#include <fstream>
#include <string>
#include <algorithm> 
#include <ctime> 
#include <cstdlib>
using namespace std;  

// **************************************** Customer Registration & Login **************************************** 
//Customer variables' structure 
struct Customer{
    string userID;
    string username; 
    string phNO; 
};

//Pet variables' structure 
struct Pet{
    string userID; 
    string petID; 
    string petName; 
    string petType;
    string petGender;
    string petBreed; 
    int petAge; 
}; 

struct serviceBooking{
    string bookingID;
    string userID;
    string username;
    string petID;
    string petName;
    string serviceSelected;
    int serviceDuration = 0;
    int day = 0;
    int month = 0;
    int year = 0;
    int startTime = 0;
    int endTime = 0;    
};

// ===== FUNCTION PROTOTYPES =====

void aboutUs(); 

// Registration & Login Module 
string generateUserID(); // Customer Registration & Login 
bool isAValidUsername(Customer &c);
bool isAValidPhoneNumber(Customer &c);
bool isExistingCustomer(Customer &c);
void customerRegistration(Customer &c);
void customerLogin(Customer &c);
string generatePetID(); // Pet Registration
bool isAValidPetName(Pet &p);
bool isExistingPet(Pet &p);
void petRegistration(Customer &c);

void customerMenu(); 

// Service Grooming Booking Module 
Pet selectPet(Customer &c, serviceBooking &b); 
string generateBookingID();
void saveBooking(Customer &c, Pet selectedPet, serviceBooking &b); 
void bookGroomingService(Customer &c, Pet selectedPet, serviceBooking &b); 
bool validBookingDate(serviceBooking b); 
string displayTime(int minutes);
bool isTimeAvailable(serviceBooking &b, int newStartTime, int newEndTime); 
void modifyGroomingService(serviceBooking &b); 
void updateBookingService(serviceBooking &b); 
bool modifyBookingTime(serviceBooking &b); 
void modifyBooking(Customer &c); 
int safeStoi(const string &str); 
void viewBookingHistory(Customer &c);
void cancelGroomingService(Customer &c); 
void customerServiceMenu(Customer &c, serviceBooking &b); 

// Staff Menu Module 
void viewAllBookings(); 
void searchCustomerDetails(); 
void modifyCustomerBooking(); 
void viewGroomingHistory(); 
void cancelCustomerBooking(); 
void viewCustomerBookings(); 

// Report Menu 
void customerRecords(); 
void petRecords(); 
void bookingRecords(); 
void groomingServiceReports(); 
void bookingStatusReports(); 
void reportMenu(); 
void staffMenu(); 

void aboutUs(){
    char returnOption; 
    cout << endl << endl << setfill('*') << setw(55) << "" << endl; 
    cout << "About Us\n"; 
    cout << setfill('*') << setw(55) << "" << endl << endl;  
    cout << "Welcome to Special Pet Grooming System!\n"; 
    cout << "We provide professional grooming services for your beloved pets.\n"; 
    cout << "Our team of experienced groomers ensures that your pets receive the best care and attention.\n"; 
    cout << "We offer a range of grooming services including bathing, haircut, nail trimming, and ear cleaning.\n"; 
    cout << "Book an appointment today and give your pets the pampering they deserve!\n";     
    
    do{ 
        cout << "\nWould you like to return to the main menu? (Y/N): "; 
        cin.ignore();
        cin.get(returnOption);

        if (returnOption == 'Y' || returnOption == 'y'){
            return; 
        }
        else if (returnOption == 'N' || returnOption == 'n'){
            cout << "Thanks for using us. Have a good day!"; 
            exit (0); 
        }
    }while(returnOption != 'Y' && returnOption != 'y' && returnOption != 'N' && returnOption != 'n');
}

//User ID generation function 
string generateUserID(){
    ifstream file("userdata.txt");

    string fileUserID;
    string fileUsername;
    string filePhone; 

    int highestID = 999;

    while (getline(file, fileUserID, '|') && getline(file, fileUsername, '|') && getline(file, filePhone)){
        if (fileUserID.substr(0, 4) == "CUST"){
            int idNumber = stoi(fileUserID.substr(4));

            if (idNumber > highestID)
            {
                highestID = idNumber;
            }
        }
    }

    file.close();

    return "CUST" + to_string(highestID + 1);
}

//Username validation function, alphanumeric and spaces only 
bool isAValidUsername(Customer &c){
    for (char character : c.username){
        if (!isalpha(character ) && !isspace(character)){
            return false;
        }
    }
    return true;
}

//Phone number validation function, must be 10 or 11 digits and only contain numbers  
bool isAValidPhoneNumber(Customer &c){
    if (c.phNO.length() != 10 && c.phNO.length() != 11){
        return false;
    }
    for (char character : c.phNO){
        if (!isdigit(character)){
            return false; 
        } 
    }
    return true; 
} 

// Check if the customer already exists in the userdata.txt file 
bool isExistingCustomer(Customer &c){
    ifstream infile("userdata.txt");
    string line; 
    while (getline(infile, line)){ 
        if (line.find(c.username) != string::npos && line.find(c.phNO) != string::npos){
            infile.close(); 
            return true; 
        }
    }
    infile.close();
    return false;
}

//Customer registration function 
void customerRegistration(Customer &c){
    cin.ignore();
    cout << "\nEnter your username: ";
    getline(cin, c.username);
    cout << "Enter your phone number: ";
    cin >> c.phNO;
    cin.ignore();

    // Check whether customer already exists
    if (isExistingCustomer(c))
    {
        cout << "\nThis username and phone number have already registered!\n";
        cout << "Please login instead.\n";
        return;
    }

    // Validate username
    while (!isAValidUsername(c))
    {
        cout << "\nUsername is invalid!";
        cout << "\nPlease enter a valid username (alphanumeric and space only): ";
        getline(cin, c.username);
    }

    // Validate phone number
    while (!isAValidPhoneNumber(c))
    {
        cout << "\n-------- Invalid phone number! --------\n";
        cout << "Enter your phone number again (without '-'): ";
        cin >> c.phNO;
        cin.ignore();
    }

    // Generate User ID
    c.userID = generateUserID();

    // Save customer
    ofstream infile("userdata.txt", ios::app);
    infile << c.userID << "|" << c.username << "|" << c.phNO << "|" << endl;
    infile.close();

    cout << "\n*******************************************\n";
    cout << "       Registration successful!\n";
    cout << "*******************************************\n";
    cout << "Your User ID is: " << c.userID << endl;
    cout << "Please remember your User ID for future use.\n";
}

//Customer login function
void customerLogin(Customer &c){  
    bool found = false; 

    cin.ignore(); 
    cout << "\nEnter your username: "; 
    getline(cin, c.username); 
    cout << "Enter your phone number: "; 
    cin >> c.phNO; 

    ifstream infile("userdata.txt");
    string fileUserID, fileUsername, filePhone;

    while (getline(infile, fileUserID, '|') && getline(infile, fileUsername, '|') && getline(infile, filePhone))
    {
        // Remove possible spaces if needed
        if (fileUsername.find(c.username) != string::npos && filePhone.find(c.phNO) != string::npos){
            found = true;

            c.userID = fileUserID; // IMPORTANT: Store the logged-in user's ID 
            cout << "\n*******************************************\n";
            cout << "       Login successful!\n";
            cout << "*******************************************\n"; 
            cout << "\nWelcome, " << c.username << "!\n";
            cout << "Your User ID is: " << c.userID << endl; 
            break;
        }
    }
    infile.close();

    if (found)
    {
        ifstream infile("petdata.txt");

        string fileUserID, filePetID, filePetType;
        string filePetName, filePetGender, filePetBreed, filePetAge;

        Pet pets[100];
        int petCount = 0;

        cout << "\n******** Your Pets ********\n";
        while (getline(infile, fileUserID, '|') && getline(infile, filePetID, '|') &&
            getline(infile, filePetType, '|') && getline(infile, filePetName, '|') &&
            getline(infile, filePetGender, '|') && getline(infile, filePetBreed, '|') &&
            getline(infile, filePetAge))
        {
            if (fileUserID == c.userID)
            {
                if (petCount < 100)
                {
                    pets[petCount].userID = fileUserID;
                    pets[petCount].petID = filePetID;
                    pets[petCount].petType = filePetType;
                    pets[petCount].petName = filePetName;
                    pets[petCount].petGender = filePetGender;
                    pets[petCount].petBreed = filePetBreed;
                    pets[petCount].petAge = stoi(filePetAge);

                    petCount++;
                }
            }
        } 
        infile.close();

        if (petCount == 0)
        {
            cout << "\nYou have no registered pets.\n";
            return;
        }
        else{
            for (int i = 0; i < petCount; i++) 
            {
                cout << "\n" << i + 1 << ". "
                    << pets[i].petName
                    << " (" << pets[i].petType << ")";

                cout << "\n   Pet ID: " << pets[i].petID;
                cout << "\n   Gender: " << pets[i].petGender;
                cout << "\n   Breed: " << pets[i].petBreed;
                cout << "\n   Age: " << pets[i].petAge << endl;
            }
        }
    }
} 


//Pet ID Generation 
string generatePetID()
{
    ifstream file("petdata.txt");

    string fileUserID, filePetID, filePetType;
    string filePetName, filePetGender, filePetBreed, filePetAge;
    int highestID = 999;

    while (getline(file, fileUserID, '|') && getline(file, filePetID, '|') &&
           getline(file, filePetType, '|') && getline(file, filePetName, '|') &&
           getline(file, filePetGender, '|') && getline(file, filePetBreed, '|') &&
           getline(file, filePetAge))
    {
        if (filePetID.substr(0, 3) == "PET")
        {
            int idNumber = stoi(filePetID.substr(3));

            if (idNumber > highestID)
            {
                highestID = idNumber;
            }
        }
    }

    file.close();

    return "PET" + to_string(highestID + 1);
}

bool isAValidPetName(Pet &p){
    if (p.petName.empty()){
        return false;
    }

    for (char c : p.petName){
        if (!isalpha(c) && c != ' '){
            return false;
        }
    }
    return true;
}

bool isExistingPet(Pet &p){
    ifstream infile("petdata.txt");
    string line, header;
    getline(infile, header); // Skip the header line 
    while (getline(infile, line)){ 
        if (line.find(p.petID) != string::npos 
            && line.find(p.userID) != string::npos 
            && line.find(p.petName) != string::npos 
            && line.find(p.petType) != string::npos)
        {
            infile.close();
            return true; 
        }
    }
    infile.close();
    return false;
}

//Pet Registration Function 
void petRegistration(Customer &c)
{
    char choice;

    do
    {
        Pet p;
        p.userID = c.userID;

        // 1. Get pet information
        cout << "\nUser ID: " << p.userID << endl;

        cout << "Enter your pet's name: ";
        getline(cin, p.petName);

        while (!isAValidPetName(p))
        {
            cout << "Pet name is invalid!";
            cout << "\nPlease enter a valid pet name: ";
            getline(cin, p.petName);
        }

        cout << "Enter your pet's type (Dog/Cat): ";
        getline(cin, p.petType);

        cout << "Enter your pet's gender (Male/Female): ";
        getline(cin, p.petGender);

        cout << "Enter your pet's breed: ";
        getline(cin, p.petBreed);

        cout << "Enter your pet's age: ";
        cin >> p.petAge;
        cin.ignore();

        // 2. Check whether pet already exists
        ifstream infile("petdata.txt");
        string userID, petID, petType;
        string petName, petGender, petBreed;
        int petAge;

        bool exists = false;

        while (getline(infile, userID, '|') && getline(infile, petID, '|') &&
               getline(infile, petType, '|') && getline(infile, petName, '|') &&
               getline(infile, petGender, '|') && getline(infile, petBreed, '|') &&
               infile >> petAge)
        {
            infile.ignore();
            if (userID == p.userID && petName == p.petName &&
                petType == p.petType && petBreed == p.petBreed)
            {
                exists = true;
                break;
            }
        }
        infile.close();

        // 3. Decide what to do with the pet
        if (exists){
            cout << "\n*******************************************\n";
            cout << "       Pet already registered!\n";
            cout << "*******************************************\n";
        }else{
            p.petID = generatePetID();
            ofstream outfile("petdata.txt", ios::app);

            outfile << p.userID << "|" << p.petID << "|"
                    << p.petType << "|" << p.petName << "|"
                    << p.petGender << "|" << p.petBreed << "|"
                    << p.petAge << endl;
            outfile.close();

            cout << "\n*******************************************\n";
            cout << "       Pet Registered Successfully!\n";
            cout << "*******************************************\n";

            cout << "Pet ID: " << p.petID << endl;
            cout << "Pet Name: " << p.petName << endl;
        }

        // 4. Ask only ONCE
        cout << "\nWould you like to register another pet?\n";
        cout << "1. Yes, register another pet\n";
        cout << "2. Back to Customer Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == '2'){
            return;
        }

    } while (choice == '1');
}

// ----------------------------------------------- Customer Registration & Login Main Menu ----------------------- 
//this registration login = customer menu 
void customerMenu()
{
    int customerOption;

    Customer c;
    serviceBooking b;

    do
    {
        cout << "\n\n";
        cout << endl << endl << setfill('*') << setw(55) << "" << endl; 
        cout << "                  Customer Menu\n"; 
        cout << setfill('*') << setw(55) << "" << endl << endl;  
        cout << "1. Customer Register\n";
        cout << "2. Customer Login\n";
        cout << "3. Pet Register\n";
        cout << "4. Service Booking Menu\n";
        cout << "5. Back to Main Menu\n";
        cout << "6. Exit\n";

        cout << "\nEnter your option (1-6): ";
        cin >> customerOption;
        cin.ignore();

        switch (customerOption)
        {
            case 1:
                customerRegistration(c);
                break;
            case 2:
            {
                customerLogin(c);
                cin.ignore();
                cout << "\nPress <Enter> to return to Customer Menu.";
                cin.get();
                cin.ignore();
                break;
            }

            case 3:
            {
                if (c.userID.empty())
                {
                    cout << "\nPlease login or register a customer first.\n";
                }
                else
                {
                    petRegistration(c);
                }

                cout << "\nPress <Enter> to return to Customer Menu.";
                cin.get();
                cin.ignore(); 
                break;
            }

            case 4:
            {
                if (c.userID.empty())
                {
                    cout << "\nPlease login or register a customer first.\n";
                }
                else
                {
                    customerServiceMenu(c, b);
                }

                cout << "\nPress <Enter> to return to Customer Menu.";
                cin.get();

                break;
            }

            case 5:
            {
                cout << "\nReturning to Main Menu...\n"; 
                break;
            }

            case 6:
            {
                cout << "\nThanks for using us. Have a good day!\n";
                exit(0);
            }

            default:
            {
                cout << "\nInvalid option! Please enter 1-6.\n";

                cout << "\nPress <Enter> to continue.";
                cin.get();

                break;
            }
        }

    } while (customerOption != 5);
}

// ***************************************** Service Grooming Booking Module *****************************
//Submenu, Case 1: Pet Selection 
// Select a pet from the list of pets registered by the customer
Pet selectPet(Customer &c, serviceBooking &b)
{
    ifstream infile("petdata.txt");

    string fileUserID, filePetID, filePetType;
    string filePetName, filePetGender;
    string filePetBreed, filePetAge;

    // Arrays to store the customer's pets
    Pet pets[50]; 
    int petCount = 0; 
    // Read the file 
    while (getline(infile, fileUserID, '|') && getline(infile, filePetID, '|') &&
           getline(infile, filePetType, '|') && getline(infile, filePetName, '|') &&
           getline(infile, filePetGender, '|') && getline(infile, filePetBreed, '|') &&
           getline(infile, filePetAge))
    {
        if (fileUserID == c.userID) //make sure the userID is same as the logged-in user, then only display the pet(s) belong to the user
        {
            if (petCount < 50){
                pets[petCount].userID = fileUserID;
                pets[petCount].petID = filePetID;
                pets[petCount].petType = filePetType;
                pets[petCount].petName = filePetName;
                pets[petCount].petGender = filePetGender;
                pets[petCount].petBreed = filePetBreed;
                pets[petCount].petAge = stoi(filePetAge);

                petCount++;
            }
        }
    } 
    infile.close(); 

    // Display all the pets 
    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl; 
    cout << "Please select a pet to proceed with the grooming service.\n"; 
    cout << "                 YOUR PET(S)\n";
    cout << setfill('*') << setw(55) << "" << endl;

    if (petCount == 0){
        cout << "You have no registered pets.\n"; 
        return Pet(); 
    } 

    for (int i = 0; i < petCount; i++){
        cout << i + 1 << ". " << pets[i].petName << " (" << pets[i].petType << ")" << endl;
    }

    // Select a specified pet to proceed grooming service 
    int petOption; 
    do{
        cout << "\nSelect your pet: ";
        cin >> petOption;

        if (petOption < 1 || petOption > petCount){
        cout << "Invalid option!";
        }
    }while (petOption < 1 || petOption > petCount); 

    // Array starts from 0, so need -1 to obtain the exact pet 
    Pet selectedPet = pets[petOption - 1];

    cout << "\nYou selected: " << selectedPet.petName << endl;
    cout << "\nPet ID: " << selectedPet.petID << endl;

    return selectedPet; 
}

string generateBookingID()
{
    ifstream file("bookingdata.txt");

    string fileBookingID, fileUserID, fileUsername;
    string filePetID, filePetName, fileService;
    string fileDate, fileStartTime, fileEndTime;

    int highestID = 999;

    while (getline(file, fileBookingID, '|') && getline(file, fileUserID, '|') &&
           getline(file, fileUsername, '|') && getline(file, filePetID, '|') &&
           getline(file, filePetName, '|') && getline(file, fileService, '|') && getline(file, fileDate, '|') &&
           getline(file, fileStartTime, '|') && getline(file, fileEndTime))
    {
        if (fileBookingID.substr(0, 4) == "BOOK"){
            int idNumber = stoi(fileBookingID.substr(4));
            if (idNumber > highestID)
            {
                highestID = idNumber;
            }
        }
    }
    file.close();

    return "BOOK" + to_string(highestID + 1);
}

void saveBooking(Customer &c, Pet selectedPet, serviceBooking &b){ 
    ofstream infile("bookingdata.txt", ios::app);

    // Store customer information
    b.userID = c.userID; 
    b.username = c.username; 

    // Store selected pet information
    b.petID = selectedPet.petID;
    b.petName = selectedPet.petName;

    // Create date in the same format used for checking
    string bookingDate = to_string(b.day) + "/" + to_string(b.month) + "/" + to_string(b.year);
    infile << b.bookingID << "|"
        << b.userID << "|"
        << b.username << "|"
        << b.petID << "|"
        << b.petName << "|"
        << b.serviceSelected << "|"
        << bookingDate << "|"
        << b.startTime << "|"
        << b.endTime
        << endl;
    infile.close();
}

//Case 2: Book Grooming Service + Time Availability 
void bookGroomingService(Customer &c, Pet selectedPet, serviceBooking &b){
    // Current date and time 
    time_t now = time(0);
    tm *currentTime = localtime(&now); 
    int currentDay = currentTime->tm_mday;
    int currentMonth = currentTime->tm_mon + 1;
    int currentYear = currentTime->tm_year + 1900;
    int currentHour = currentTime->tm_hour;
    int currentMinute = currentTime->tm_min;
    int currentMinutes = currentHour * 60 + currentMinute;

    // Booking details (user & pet) 
    cout << "\n" << setfill('*') << setw(55) << "" << endl;
    cout << "              BOOKING DETAILS\n";
    cout << setfill('*') << setw(55) << "" << endl; 
    cout << "\nCustomer: " << c.username << endl;
    cout << "User ID: " << c.userID << endl;
    cout << "\nPet Name: " << selectedPet.petName << endl;
    cout << "Pet ID: " << selectedPet.petID << endl;
    cout << "Pet Type: " << selectedPet.petType << endl;
    cout << "\nGrooming Service: " << b.serviceSelected << endl; 
    cout << "Duration: " << b.serviceDuration << " minutes\n";

    // Owner select a date  
    do{
        cout << "\nEnter booking date (DD/MM/YYYY)\n";

        cout << "Day (two digits): ";
        cin >> b.day;

        cout << "Month (two digits): ";
        cin >> b.month;

        cout << "Year (four digits): ";
        cin >> b.year; 

    } while (!validBookingDate (b));

    // Time slots 
    int timeSlots[] =
    {
        540,   // 9:00 AM
        570,   // 9:30 AM
        600,   // 10:00 AM
        630,   // 10:30 AM
        660,   // 11:00 AM
        690,   // 11:30 AM

        780,   // 1:00 PM
        810,   // 1:30 PM
        840,   // 2:00 PM
        870,   // 2:30 PM
        900,   // 3:00 PM
        930,   // 3:30 PM
        960,   // 4:00 PM
        990    // 4:30 PM
    };

    int slotCount = 14;
    int availableSlots[14];
    int availableCount = 0;

    // Show availability time slot(s)
    cout << "\nAvailable Time Slots:\n";

    for (int i = 0; i < slotCount; i++){
        int StartTime = timeSlots[i];
        int EndTime = StartTime + b.serviceDuration;
        bool available = true;

        // Check whether the service fits within operating hours
        bool morningAvailable = (StartTime >= 540 && EndTime <= 720); 
        bool afternoonAvailable = (StartTime >= 780 && EndTime <= 1020);

        if (!morningAvailable && !afternoonAvailable){
            available = false; //if the morning operating hours and afternoon operating hours are out of service, then return false 
        }

        // Check current time if booking today
        if (b.day == currentDay && b.month == currentMonth && b.year == currentYear){
            if (StartTime <= currentMinutes){
                available = false;
            }
        }

        // Check existing bookings from bookingdata.txt
        if (!isTimeAvailable(b, StartTime, EndTime)){
            available = false;
        }

        // DISPLAY AVAILABLE SLOT 
        if (available){
            availableSlots[availableCount] = StartTime;

            cout << availableCount + 1 << ". " << displayTime(StartTime)<< endl;
            availableCount++;
        }
    }

    // NO AVAILABLE SLOT 
    if (availableCount == 0){
        cout << "\nNo available time slots for this date.\n";
        return;
    }

    // SELECT TIME 
    int timeOption;
    do{
        cout << "\nSelect your time slot: ";
        cin >> timeOption;
        if (timeOption < 1 || timeOption > availableCount){
            cout << "Invalid option! Please select again.\n";
            cin >> timeOption;
        }
    } while (timeOption < 1 || timeOption > availableCount);

    int selectedStartTime = availableSlots[timeOption - 1];
    int selectedEndTime = selectedStartTime + b.serviceDuration; 

    b.startTime = selectedStartTime;
    b.endTime = selectedEndTime;

    // DISPLAY BOOKING 
    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "             BOOKING DETAILS\n";
    cout << setfill('*') << setw(55) << "" << endl;

    cout << "\nCustomer : " << c.username << endl;
    cout << "Pet      : " << selectedPet.petName << endl;
    cout << "Service  : " << b.serviceSelected << endl;
    cout << "Date     : " << b.day << "/" << b.month << "/" << b.year << endl;
    cout << "Time     : " << displayTime(selectedStartTime) << " - " << displayTime(selectedEndTime) << endl; 

    char confirm; 

    do
    {
        cout << "Confirm booking? (Y/N): ";
        cin >> confirm;

        if (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n')
        {
            cout << "Invalid input! Please enter Y or N.\n";
        }

    } while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');

    if (confirm == 'Y' || confirm == 'y')
    {
        b.bookingID = generateBookingID(); 
        saveBooking(c, selectedPet, b);

        cout << "\nBooking successfully recorded!\n";
        cout << "Booking ID: " << b.bookingID << endl;
    }
    else
    {
        cout << "\nBooking cancelled.\n";
    }

    customerServiceMenu(c, b); // Return to service menu after booking 
} 

//check is it a date in the past 
bool validBookingDate(serviceBooking b)
{
    // Month value can only be in between 1 to 12 
    if (b.month < 1 || b.month > 12){
        cout << "\nInvalid month!\n";
        return false; 
    }
    //Day value can only be in between 1 to 31 
    if (b.day < 1 || b.day > 31){
        cout << "\nInvalid day!\n";
        return false;
    }

    // Get today's date but the now is unreadable by human yet 
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    //Make the current date to be readable and accessible by humans 
    int currentDay = currentTime->tm_mday;
    int currentMonth = currentTime->tm_mon + 1;
    int currentYear = currentTime->tm_year + 1900;

    // Check if date value is in the past
    if (b.year < currentYear || (b.year == currentYear && b.month < currentMonth) || 
        (b.year == currentYear && b.month == currentMonth && b.day < currentDay))
    {
        cout << "\nInvalid date!";
        cout << "\nYou cannot book a past date.\n";
        return false; //once returned false, the do-while loop will run 
    }

    // Create the booking date 
    tm bookingDate = {}; //tm is a structure to store date and time info, ={} initialise all its value to 0 
    bookingDate.tm_mday = b.day; 
    bookingDate.tm_mon = b.month - 1; //make it readable by pc as the month is actually started with 0 to 11 
    bookingDate.tm_year = b.year - 1900; //make it readable by pc as the year started since 1900 

    // Calculate the day of the week
    mktime(&bookingDate);

    //in tm_wday Sunday = 0 (off day), then Saturday = 6 
    if (bookingDate.tm_wday == 0){ 
        cout << "\nSorry, we are closed on Sunday.\n";
        return false;
    }
    return true; //if the date is not in the past, and when the day is not Sundy 
} 

//convert minutes into a readable time 
string displayTime(int minutes){

    serviceBooking b; 
    int hour = minutes / 60;
    int minute = minutes % 60;

    string period; 

    if (hour >= 12){
        period = "PM";
    }else{
        period = "AM";
    }

    if (hour > 12){
        hour = hour - 12;
    }

    if (hour == 0){
        hour = 12;
    }

    string time = to_string(hour) + ":";

    if (minute < 10){
        time += "0";
    }

    time += to_string(minute) + " " + period;
    return time;
}

// Check if the new booking time overlaps with existing bookings
bool isTimeAvailable(serviceBooking &b, int newStartTime, int newEndTime)
{
    ifstream bookingFile("bookingdata.txt");

    string fileBookingID, fileUserID, fileUsername;
    string filePetID, filePetName, fileService;
    string fileDate, fileStartTime, fileEndTime;

    // Create the date the customer is trying to book
    string bookingDate = to_string(b.day) + "/" + to_string(b.month) + "/" + to_string(b.year);

    while (getline(bookingFile, fileBookingID, '|') && getline(bookingFile, fileUserID, '|') &&
           getline(bookingFile, fileUsername, '|') && getline(bookingFile, filePetID, '|') &&
           getline(bookingFile, filePetName, '|') && getline(bookingFile, fileService, '|') &&
           getline(bookingFile, fileDate, '|') && getline(bookingFile, fileStartTime, '|') &&
           getline(bookingFile, fileEndTime))
    {
        int existingStartTime = stoi(fileStartTime);
        int existingEndTime = stoi(fileEndTime);

        // Only check bookings on the same date
        if (fileDate == bookingDate)
        {
            // Check overlapping time
            if (newStartTime < existingEndTime &&
                newEndTime > existingStartTime)
            {
                bookingFile.close();

                return false;
            }
        }
    }

    bookingFile.close();

    return true;
} 

//Submenu, Case 1: Grooming Services 
void selectGroomingServices(Customer &c, Pet selectedPet, serviceBooking &b){ 
    int serviceOption; 
    do{
        cout << "\n \n";
        cout << setfill('*') << setw(55) << "" << endl;
        cout << "             GROOMING SERVICES\n";
        cout << setfill('*') << setw(55) << "" << endl << endl;

        cout << "1. Bathing         - 30 minutes\n";
        cout << "2. Haircut         - 60 minutes\n";
        cout << "3. Nail trimming   - 30 minutes\n";
        cout << "4. Ear cleaning    - 30 minutes\n";
        cout << "5. Back to Customer Menu\n";
        cout << "6. Back to Main Menu\n";
        cout << "7. Exit ";

        cout << "\nEnter your option (1-5): ";
        cin >> serviceOption;
        if (serviceOption < 1 || serviceOption > 5){
            cout << "Invalid option. Please choose a number between 1 to 5!\n"; 
        } 
    } while (serviceOption < 1 || serviceOption > 5); 

    switch (serviceOption){
        case 1:
            b.serviceSelected = "Bathing";
            b.serviceDuration = 30; 
            break;
        case 2:
            b.serviceSelected = "Haircut";
            b.serviceDuration = 60;
            break;
        case 3:
            b.serviceSelected = "Nail trimming";
            b.serviceDuration = 30;
            break;
        case 4:
            b.serviceSelected = "Ear cleaning";
            b.serviceDuration = 30;
            break;
        case 5:
            return;
        case 6:
            cout << "\nReturning to Main Menu...\n";
            return;
        default: 
            cout << "Thanks for using us. Have a good day!"; 
    }

    bookGroomingService(c, selectedPet, b); 
}

//Select a new grooming service for the selected booking 
void modifyGroomingService(serviceBooking &b)
{
    int serviceOption;

    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "          MODIFY GROOMING SERVICE\n";
    cout << setfill('*') << setw(55) << "" << endl;

    cout << "1. Bathing         - 30 minutes\n";
    cout << "2. Haircut         - 60 minutes\n";
    cout << "3. Nail trimming   - 30 minutes\n";
    cout << "4. Ear cleaning    - 30 minutes\n";

    do
    {
        cout << "\nSelect your new service (1-4): ";
        cin >> serviceOption;

        if (serviceOption < 1 || serviceOption > 4)
        {
            cout << "Invalid option! Please select again.\n";
        }

    } while (serviceOption < 1 || serviceOption > 4);

    switch (serviceOption)
    {
        case 1:
            b.serviceSelected = "Bathing";
            b.serviceDuration = 30;
            break;

        case 2:
            b.serviceSelected = "Haircut";
            b.serviceDuration = 60;
            break;

        case 3:
            b.serviceSelected = "Nail trimming";
            b.serviceDuration = 30;
            break;

        case 4:
            b.serviceSelected = "Ear cleaning";
            b.serviceDuration = 30;
            break;
    }
}

void updateBookingService(serviceBooking &b)
{
    ifstream bookingFile("bookingdata.txt");
    ofstream tempFile("temp.txt");

    string fileBookingID, fileUserID, fileUsername;
    string filePetID, filePetName, fileService;
    string fileDate, fileStartTime, fileEndTime;

    while (getline(bookingFile, fileBookingID, '|') && getline(bookingFile, fileUserID, '|') &&
           getline(bookingFile, fileUsername, '|') && getline(bookingFile, filePetID, '|') &&
           getline(bookingFile, filePetName, '|') && getline(bookingFile, fileService, '|') &&
           getline(bookingFile, fileDate, '|') && getline(bookingFile, fileStartTime, '|') &&
           getline(bookingFile, fileEndTime))
    {
        if (fileBookingID == b.bookingID){
            tempFile << b.bookingID << "|" << b.userID << "|" << b.username << "|"
                     << b.petID << "|" << b.petName << "|" << b.serviceSelected << "|"
                     << b.day << "/" << b.month << "/" << b.year << "|"
                     << b.startTime << "|" << b.endTime << endl;
        }else{
            tempFile << fileBookingID << "|" << fileUserID << "|" << fileUsername << "|" << filePetID << "|"
                     << filePetName << "|" << fileService << "|" << fileDate << "|" << fileStartTime << "|"
                     << fileEndTime << endl;
        }
    }
    bookingFile.close();
    tempFile.close();

    remove("bookingdata.txt");
    rename("temp.txt", "bookingdata.txt");

    cout << "\nBooking successfully updated!\n";
}

bool modifyBookingTime(serviceBooking &b){
    int timeSlots[] =
    {
        540, 570, 600, 630, 660, 690,
        780, 810, 840, 870, 900, 930, 960, 990
    };

    int slotCount = 14; 
    int availableSlots[14];
    int availableCount = 0;

    time_t now = time(0);
    tm *currentTime = localtime(&now);

    int currentDay = currentTime->tm_mday;
    int currentMonth = currentTime->tm_mon + 1;
    int currentYear = currentTime->tm_year + 1900;
    int currentMinutes = currentTime->tm_hour * 60 + currentTime->tm_min;

    cout << "\nAvailable Time Slots:\n";

    for (int i = 0; i < slotCount; i++)
    {
        int startTime = timeSlots[i];
        int endTime = startTime + b.serviceDuration;

        bool available = true;
        bool morningAvailable =(startTime >= 540 && endTime <= 720); // Morning: 9:00am - 12:00pm
        bool afternoonAvailable =(startTime >= 780 && endTime <= 1020); // Afternoon: 1:00pm - 5:00pm

        if (!morningAvailable && !afternoonAvailable){
            available = false;
        }

        // If booking is today, don't allow a time that has already passed
        if (b.day == currentDay && b.month == currentMonth && b.year == currentYear){
            if (startTime <= currentMinutes)
            {
                available = false;
            }
        }

        // Check whether another booking occupies the time
        if (!isTimeAvailable(b, startTime, endTime)){
            available = false;
        }

        if (available){
            availableSlots[availableCount] = startTime;
            cout << availableCount + 1 << ". " << displayTime(startTime) << endl;
            availableCount++;
        }
    }

    // No available slots
    if (availableCount == 0)
    {
        cout << "\nNo available time slots for this date.\n";
        return false;
    }

    // Let customer choose
    int timeOption;

    do
    {
        cout << "\nSelect your time slot: ";
        cin >> timeOption;

        if (timeOption < 1 || timeOption > availableCount)
        {
            cout << "Invalid option! Please select again.\n";
        }

    } while (timeOption < 1 || timeOption > availableCount);

    // Set new time
    b.startTime = availableSlots[timeOption - 1];
    b.endTime = b.startTime + b.serviceDuration;

    return true;
}

void modifyBooking(Customer &c){
    ifstream bookingFile("bookingdata.txt");

    serviceBooking futureBookings[50];
    int count = 0;

    string fileBookingID, fileUserID, fileUsername;
    string filePetID, filePetName, fileService;
    string fileDate, fileStartTime, fileEndTime;

    // Read booking file
    while (getline(bookingFile, fileBookingID, '|') && getline(bookingFile, fileUserID, '|') &&
           getline(bookingFile, fileUsername, '|') && getline(bookingFile, filePetID, '|') &&
           getline(bookingFile, filePetName, '|') && getline(bookingFile, fileService, '|') &&
           getline(bookingFile, fileDate, '|') && getline(bookingFile, fileStartTime, '|') &&
           getline(bookingFile, fileEndTime))
    {
        // Only show this customer's bookings
        if (fileUserID == c.userID)
        {
            serviceBooking b;

            b.bookingID = fileBookingID;
            b.userID = fileUserID;
            b.username = fileUsername;
            b.petID = filePetID;
            b.petName = filePetName;
            b.serviceSelected = fileService;

            // Get date
            sscanf(fileDate.c_str(), "%d/%d/%d", &b.day, &b.month, &b.year);

            b.startTime = stoi(fileStartTime);
            b.endTime = stoi(fileEndTime);

            // Get service duration
            if (fileService == "Bathing")
                b.serviceDuration = 30;
            else if (fileService == "Haircut")
                b.serviceDuration = 60;
            else if (fileService == "Nail trimming")
                b.serviceDuration = 30;
            else if (fileService == "Ear cleaning")
                b.serviceDuration = 30;

            // Check whether booking is in the future
            // Compare year, month and day
            bool futureBooking = false;

            time_t now = time(0);
            tm *currentTime = localtime(&now);

            int currentYear = currentTime->tm_year + 1900;
            int currentMonth = currentTime->tm_mon + 1;
            int currentDay = currentTime->tm_mday;

            if (b.year > currentYear)
                futureBooking = true;

            else if (b.year == currentYear && b.month > currentMonth)
                futureBooking = true;

            else if (b.year == currentYear && b.month == currentMonth && b.day >= currentDay)
                futureBooking = true;

            if (futureBooking){
                futureBookings[count] = b;
                count++;
            }
        }
    }

    bookingFile.close();

    // No future bookings
    if (count == 0)
    {
        cout << "\nNo future bookings found.\n";
        return;
    }

    // Display future bookings
    cout << "\n";
    cout << setfill('*') << setw(65) << "" << endl;
    cout << "                 FUTURE BOOKINGS\n";
    cout << setfill('*') << setw(65) << "" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << "\n" << i + 1 << ". " << futureBookings[i].bookingID << endl;
        cout << "   Pet      : " << futureBookings[i].petName << endl;
        cout << "   Service  : " << futureBookings[i].serviceSelected << endl;

        cout << "   Date     : " << futureBookings[i].day << "/" << futureBookings[i].month << "/" << futureBookings[i].year << endl;

        cout << "   Time     : " << displayTime(futureBookings[i].startTime) << " - "
             << displayTime(futureBookings[i].endTime) << endl;
    }

    // Choose booking
    int bookingOption;
    do
    {
        cout << "\nSelect a booking to modify (1-" << count << "): ";
        cin >> bookingOption;

        if (bookingOption < 1 || bookingOption > count)
            cout << "Invalid option! Please try again.\n";
    } while (bookingOption < 1 || bookingOption > count);

    // Get selected booking
    serviceBooking selectedBooking = futureBookings[bookingOption - 1];

    // Modification menu
    int modifyOption;
    do
    {
        cout << "\n";
        cout << setfill('*') << setw(55) << "" << endl;
        cout << "              MODIFY BOOKING\n";
        cout << setfill('*') << setw(55) << "" << endl;

        cout << "Booking ID : " << selectedBooking.bookingID << endl;
        cout << "Pet        : " << selectedBooking.petName << endl;
        cout << "Service    : " << selectedBooking.serviceSelected << endl;
        cout << "Date       : " << selectedBooking.day << "/" << selectedBooking.month << "/" << selectedBooking.year << endl;
        cout << "Time       : " << displayTime(selectedBooking.startTime)
             << " - " << displayTime(selectedBooking.endTime) << endl;

        cout << "\n1. Modify Grooming Service\n";
        cout << "2. Modify Date and Time\n";
        cout << "3. Back\n";

        cout << "\nEnter your option (1-3): ";
        cin >> modifyOption;

        if (modifyOption < 1 || modifyOption > 3)
            cout << "Invalid option! Please try again.\n";

    } while (modifyOption < 1 || modifyOption > 3);


    switch (modifyOption)
    {
        case 1:
        {
            // Change service
            modifyGroomingService(selectedBooking);

            // Because service duration changed, choose a new suitable time
            if (modifyBookingTime(selectedBooking))
            {
                updateBookingService(selectedBooking);
            }
            break; 
        }

        case 2:
        {
            // Change date
            cout << "\nEnter new booking date\n";

            do{
                cout << "Day   : ";
                cin >> selectedBooking.day;

                cout << "Month : ";
                cin >> selectedBooking.month;

                cout << "Year  : ";
                cin >> selectedBooking.year;

                if (!validBookingDate(selectedBooking))
                    cout << "Invalid date! Please enter again.\n";
            } while (!validBookingDate(selectedBooking));

            // Choose new time for the new date
            if (modifyBookingTime(selectedBooking))
            {
                updateBookingService(selectedBooking);
            }
            break;
        }

        case 3:
            return;
    }
}

int safeStoi(const string& str) {
    string cleanStr = "";
    for (char ch : str) {
        if (isdigit(ch) || ch == '-') {
            cleanStr += ch;
        }
    }
    
    if (cleanStr.empty()) return 0;

    try {
        return stoi(cleanStr);
    } catch (...) {
        return 0; // Fallback value if reading fails
    }
}

void viewBookingHistory(Customer &c) {
    ifstream bookingFile("bookingdata.txt");

    if (!bookingFile) {
        cout << "\nError opening booking records file!\n";
        return;
    }

    // Fixed-size array to hold up to 100 bookings
    serviceBooking bookings[100];
    int bookingCount = 0;

    string fileBookingID, fileUserID, fileUsername;
    string filePetID, filePetName, fileService;
    string fileDate, fileStartTime, fileEndTime;

    // Read file line-by-line using delimiter '|'
    while (getline(bookingFile, fileBookingID, '|') && getline(bookingFile, fileUserID, '|') &&
        getline(bookingFile, fileUsername, '|') && getline(bookingFile, filePetID, '|') &&
        getline(bookingFile, filePetName, '|') && getline(bookingFile, fileService, '|') &&
        getline(bookingFile, fileDate, '|') && getline(bookingFile, fileStartTime, '|') &&
        getline(bookingFile, fileEndTime))
    {
        // Filter bookings for the logged-in customer only
        if (fileUserID == c.userID) {
            if (bookingCount < 100) {
                bookings[bookingCount].bookingID = fileBookingID;
                bookings[bookingCount].userID = fileUserID;
                bookings[bookingCount].username = fileUsername;
                bookings[bookingCount].petID = filePetID;
                bookings[bookingCount].petName = filePetName;
                bookings[bookingCount].serviceSelected = fileService;

                // Extract day, month, year from string formatted as "DD/MM/YYYY"
                sscanf(fileDate.c_str(), "%d/%d/%d", &bookings[bookingCount].day, &bookings[bookingCount].month, &bookings[bookingCount].year);

                // Use safeStoi instead of raw stoi
                bookings[bookingCount].startTime = safeStoi(fileStartTime);
                bookings[bookingCount].endTime = safeStoi(fileEndTime);
                bookingCount++;
            }
        }
    }
    bookingFile.close();

    // Display Header
    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "             BOOKING HISTORY FOR " << c.username << "\n";
    cout << setfill('*') << setw(55) << "" << endl;

    if (bookingCount == 0) {
        cout << "\nNo booking records found for your account.\n\n";
        return;
    }

    // Display formatted table/list of bookings
    for (int i = 0; i < bookingCount; i++) {
        cout << "\n" << i + 1 << ". Booking ID   : " << bookings[i].bookingID;
        cout << "\n   Pet Name     : " << bookings[i].petName << " (ID: " << bookings[i].petID << ")";
        cout << "\n   Service      : " << bookings[i].serviceSelected;
        cout << "\n   Date         : " << setfill('0') << setw(2) << bookings[i].day << "/"
                                        << setw(2) << bookings[i].month << "/"
                                        << bookings[i].year;
        cout << "\n   Time Slot    : " << displayTime(bookings[i].startTime) << " - " 
                                       << displayTime(bookings[i].endTime);
        cout << "\n   --------------------------------------------------";
    }

    cout << "\nTotal Bookings: " << bookingCount << "\n\n";
}

void cancelGroomingService(Customer &c)
{
    ifstream bookingFile("bookingdata.txt");
    ofstream tempFile("temp.txt");

    serviceBooking bookings[100];
    int bookingCount = 0;

    string fileBookingID, fileUserID, fileUsername;
    string filePetID, filePetName, fileService;
    string fileDate, fileStartTime, fileEndTime;

    // Read customer's bookings
    while (getline(bookingFile, fileBookingID, '|') && getline(bookingFile, fileUserID, '|') &&
           getline(bookingFile, fileUsername, '|') && getline(bookingFile, filePetID, '|') &&
           getline(bookingFile, filePetName, '|') && getline(bookingFile, fileService, '|') &&
           getline(bookingFile, fileDate, '|') && getline(bookingFile, fileStartTime, '|') &&
           getline(bookingFile, fileEndTime))
    {
        if (fileUserID == c.userID)
        {
            if (bookingCount < 100)
            {
                bookings[bookingCount].bookingID = fileBookingID;
                bookings[bookingCount].userID = fileUserID;
                bookings[bookingCount].username = fileUsername;
                bookings[bookingCount].petID = filePetID;
                bookings[bookingCount].petName = filePetName;
                bookings[bookingCount].serviceSelected = fileService;

                sscanf(fileDate.c_str(), "%d/%d/%d",
                       &bookings[bookingCount].day,
                       &bookings[bookingCount].month,
                       &bookings[bookingCount].year);

                bookings[bookingCount].startTime = stoi(fileStartTime);
                bookings[bookingCount].endTime = stoi(fileEndTime);

                bookingCount++;
            }
        }
    }

    bookingFile.close();

    // No booking found
    if (bookingCount == 0)
    {
        cout << "\nYou have no bookings to cancel.\n";
        tempFile.close();
        remove("temp.txt");
        return;
    }

    // Display customer's bookings
    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "             YOUR BOOKINGS\n";
    cout << setfill('*') << setw(55) << "" << endl;

    for (int i = 0; i < bookingCount; i++)
    {
        cout << "\n" << i + 1 << ". Booking ID: " << bookings[i].bookingID;
        cout << "\n   Pet: " << bookings[i].petName;
        cout << "\n   Service: " << bookings[i].serviceSelected;
        cout << "\n   Date: " << bookings[i].day << "/" << bookings[i].month << "/" << bookings[i].year;
        cout << "\n   Time: " << displayTime(bookings[i].startTime)
             << " - " << displayTime(bookings[i].endTime) << endl;
    }

    // Select booking
    int bookingOption;

    do
    {
        cout << "\nSelect the booking you want to cancel (1-" << bookingCount << "): ";
        cin >> bookingOption;

        if (bookingOption < 1 || bookingOption > bookingCount){
            cout << "Invalid option! Please select again.\n";
        }

    } while (bookingOption < 1 || bookingOption > bookingCount);

    // Get selected booking
    serviceBooking selectedBooking = bookings[bookingOption - 1];

    // Display selected booking
    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "             CANCEL BOOKING\n";
    cout << setfill('*') << setw(55) << "" << endl;

    cout << "\nBooking ID : " << selectedBooking.bookingID << endl;
    cout << "Pet        : " << selectedBooking.petName << endl;
    cout << "Service    : " << selectedBooking.serviceSelected << endl;
    cout << "Date       : " << selectedBooking.day << "/"
         << selectedBooking.month << "/" << selectedBooking.year << endl;
    cout << "Time       : " << displayTime(selectedBooking.startTime)
         << " - " << displayTime(selectedBooking.endTime) << endl;

    // Confirmation
    char confirmation;

    do{
        cout << "\nAre you sure you want to cancel this booking? (Y/N): ";
        cin >> confirmation;

        if (confirmation != 'Y' && confirmation != 'y' && confirmation != 'N' && confirmation != 'n')
        {
            cout << "Invalid input! Please enter Y or N.\n";
        }

    } while (confirmation != 'Y' && confirmation != 'y' && confirmation != 'N' && confirmation != 'n');

    // Customer chooses NO
    if (confirmation == 'N' || confirmation == 'n')
    {
        cout << "\nBooking cancellation cancelled.\n";
        tempFile.close();
        remove("temp.txt");
        return;
    }

    // Read booking file again and copy everything, except the selected booking
    ifstream originalFile("bookingdata.txt");

    while (getline(originalFile, fileBookingID, '|') && getline(originalFile, fileUserID, '|') &&
           getline(originalFile, fileUsername, '|') && getline(originalFile, filePetID, '|') &&
           getline(originalFile, filePetName, '|') && getline(originalFile, fileService, '|') &&
           getline(originalFile, fileDate, '|') && getline(originalFile, fileStartTime, '|') &&
           getline(originalFile, fileEndTime))
    {
        // Skip the booking that the customer wants to cancel
        if (fileBookingID == selectedBooking.bookingID)
        {
            continue;
        }

        // Keep all other bookings
        tempFile << fileBookingID << "|" << fileUserID << "|" << fileUsername << "|"
                 << filePetID << "|" << filePetName << "|" << fileService << "|"
                 << fileDate << "|" << fileStartTime << "|" << fileEndTime << endl;
    }

    originalFile.close();
    tempFile.close();

    // Replace old booking file with updated file
    remove("bookingdata.txt");
    rename("temp.txt", "bookingdata.txt");
    cout << "\nBooking successfully cancelled!\n";
}

//Submenu - Customer Service Menu 
void customerServiceMenu(Customer &c, serviceBooking &b)
{
    int serviceOption;

    do{
        cout << "\n\n";
        cout << setfill('*') << setw(55) << "" << endl;
        cout << "          Customer Service Menu\n";
        cout << setfill('*') << setw(55) << "" << endl << endl;

        cout << "1. Select a pet and a grooming service\n";
        cout << "2. Modify a grooming service\n";
        cout << "3. Cancel a grooming service\n";
        cout << "4. View booking history\n";
        cout << "5. Back to Customer Menu\n";

        cout << "\nEnter your option (1-5): ";
        cin >> serviceOption;

        switch (serviceOption){
            case 1:
            {
                Pet selectedPet = selectPet(c, b);

                if (!selectedPet.petID.empty())
                {
                    selectGroomingServices(c, selectedPet, b);
                }

                break;
            }

            case 2:
                modifyBooking(c);
                break;

            case 3:
                cancelGroomingService(c);
                break;

            case 4:
                viewBookingHistory(c);
                break;

            case 5:
                customerMenu();
                break;
            default:
                cout << "\nInvalid option! Please enter 1-5.\n";
        }

    } while (serviceOption != 5);
}

// ***************************************** Staff Menu Module ***************************** 
bool staffLogin()
{
    string username;
    string password;

    const string STAFF_USERNAME = "admin";
    const string STAFF_PASSWORD = "1234";

    cout << "\n===== STAFF LOGIN =====\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    if (username == STAFF_USERNAME && password == STAFF_PASSWORD)
    {
        cout << "\nLogin successful!\n";
        return true;
    }
    else
    {
        cout << "\nInvalid username or password!\n";
        return false;
    }
}

void viewAllBookings() {
    ifstream bookingFile("bookingdata.txt");

    if (!bookingFile) {
        cout << "\nError opening booking records file!\n";
        return;
    }

    string fileBookingID, fileUserID, fileUsername;
    string filePetID, filePetName, fileService;
    string fileDate, fileStartTime, fileEndTime;

    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "             ALL BOOKINGS\n";
    cout << setfill('*') << setw(55) << "" << endl;

    while (getline(bookingFile, fileBookingID, '|') && getline(bookingFile, fileUserID, '|') &&
           getline(bookingFile, fileUsername, '|') && getline(bookingFile, filePetID, '|') &&
           getline(bookingFile, filePetName, '|') && getline(bookingFile, fileService, '|') &&
           getline(bookingFile, fileDate, '|') && getline(bookingFile, fileStartTime, '|') &&
           getline(bookingFile, fileEndTime))
    {
        cout << "\nBooking ID   : " << fileBookingID;
        cout << "\nCustomer     : " << fileUsername << " (User ID: " << fileUserID << ")";
        cout << "\nPet Name     : " << filePetName << " (Pet ID: " << filePetID << ")";
        cout << "\nService      : " << fileService;
        cout << "\nDate         : " << fileDate;
        cout << "\nTime Slot    : " << displayTime(stoi(fileStartTime)) 
             << " - " << displayTime(stoi(fileEndTime));
        cout << "\n--------------------------------------------------";
    }

    bookingFile.close();
}

void searchCustomerDetails()
{
    ifstream userFile("userdata.txt");

    if (!userFile)
    {
        cout << "\nError opening customer records file!\n";
        return;
    }

    string searchUserID; 
    cout << "\nEnter the User ID of the customer to search: ";
    cin >> searchUserID;

    string fileUserID, fileUsername, filePhone;

    bool found = false;

    while (getline(userFile, fileUserID, '|') &&
           getline(userFile, fileUsername, '|') &&
           getline(userFile, filePhone, '|'))
    {
        if (fileUserID == searchUserID)
        {
            cout << "\n";
            cout << setfill('*') << setw(55) << "" << endl;
            cout << "             CUSTOMER DETAILS\n";
            cout << setfill('*') << setw(55) << "" << endl;

            cout << "\nUser ID   : " << fileUserID;
            cout << "\nUsername  : " << fileUsername;
            cout << "\nPhone     : " << filePhone << endl;

            found = true;
            break;
        }
    }

    userFile.close();

    if (!found){
        cout << "\nNo customer found for User ID: " << searchUserID << endl;
    }
}

void modifyCustomerBooking() {
    string searchPhone;
    cout << "\nEnter Customer Phone Number: ";
    cin >> searchPhone;
    cin.ignore();

    // Step 1: Find matching userID from userdata.txt
    ifstream userFile("userdata.txt");
    string fileUserID, fileUsername, filePhone;
    string targetUserID = "";

    while (getline(userFile, fileUserID, '|') && getline(userFile, fileUsername, '|') && getline(userFile, filePhone)){
        if (filePhone == searchPhone) {
            targetUserID = fileUserID;
            break;
        }
    }
    userFile.close();

    if (targetUserID.empty()) {
        cout << "\nNo customer account found with Phone Number: " << searchPhone << "\n";
        return;
    }

    // Step 2: Read customer's bookings into a fixed array
    ifstream bookingFile("bookingdata.txt");
    serviceBooking customerBookings[50];
    int count = 0;

    string fBookingID, fUserID, fUsername;
    string fPetID, fPetName, fService;
    string fDate, fStartTime, fEndTime;

    while (getline(bookingFile, fBookingID, '|') && getline(bookingFile, fUserID, '|') &&
           getline(bookingFile, fUsername, '|') && getline(bookingFile, fPetID, '|') &&
           getline(bookingFile, fPetName, '|') && getline(bookingFile, fService, '|') &&
           getline(bookingFile, fDate, '|') && getline(bookingFile, fStartTime, '|') &&
           getline(bookingFile, fEndTime))
    {
        if (fUserID == targetUserID && count < 50) {
            customerBookings[count].bookingID = fBookingID;
            customerBookings[count].userID = fUserID;
            customerBookings[count].username = fUsername;
            customerBookings[count].petID = fPetID;
            customerBookings[count].petName = fPetName;
            customerBookings[count].serviceSelected = fService;

            sscanf(fDate.c_str(), "%d/%d/%d", 
                   &customerBookings[count].day, 
                   &customerBookings[count].month, 
                   &customerBookings[count].year);

            customerBookings[count].startTime = stoi(fStartTime);
            customerBookings[count].endTime = stoi(fEndTime);
            count++;
        }
    }
    bookingFile.close();

    if (count == 0) {
        cout << "\nNo active bookings found for phone number: " << searchPhone << "\n";
        return;
    }

    // Step 3: Display bookings and select which one to modify
    cout << "\n--- Active Bookings for " << customerBookings[0].username << " ---";
    for (int i = 0; i < count; i++) {
        cout << "\n" << i + 1 << ". Booking ID: " << customerBookings[i].bookingID
             << " | Pet: " << customerBookings[i].petName
             << " | Service: " << customerBookings[i].serviceSelected
             << " | Date: " << customerBookings[i].day << "/" 
             << customerBookings[i].month << "/" << customerBookings[i].year;
    }

    int choice;
    cout << "\nSelect booking number to modify (1-" << count << "): ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > count) {
        cout << "Invalid selection! Operation cancelled.\n";
        return;
    }

    // Step 4: Modify the selected booking structure
    serviceBooking targetBooking = customerBookings[choice - 1];
    modifyGroomingService(targetBooking);

    // Step 5: Update bookingdata.txt via temp file
    ifstream originalFile("bookingdata.txt");
    ofstream tempFile("temp.txt");

    while (getline(originalFile, fBookingID, '|') &&
           getline(originalFile, fUserID, '|') &&
           getline(originalFile, fUsername, '|') &&
           getline(originalFile, fPetID, '|') &&
           getline(originalFile, fPetName, '|') &&
           getline(originalFile, fService, '|') &&
           getline(originalFile, fDate, '|') &&
           getline(originalFile, fStartTime, '|') &&
           getline(originalFile, fEndTime))
    {
        if (fBookingID == targetBooking.bookingID) {
            // Write updated record
            string dateStr = to_string(targetBooking.day) + "/" +  to_string(targetBooking.month) + "/" + to_string(targetBooking.year);

            tempFile << targetBooking.bookingID << "|" << targetBooking.userID << "|"
                     << targetBooking.username << "|" << targetBooking.petID << "|"
                     << targetBooking.petName << "|" << targetBooking.serviceSelected << "|"
                     << dateStr << "|" << targetBooking.startTime << "|"
                     << targetBooking.endTime << endl;
        } else {
            // Retain original record
            tempFile << fBookingID << "|" << fUserID << "|" << fUsername << "|"
                     << fPetID << "|" << fPetName << "|" << fService << "|"
                     << fDate << "|" << fStartTime << "|" << fEndTime << endl;
        }
    }

    originalFile.close();
    tempFile.close();

    remove("bookingdata.txt");
    rename("temp.txt", "bookingdata.txt");

    cout << "\nBooking " << targetBooking.bookingID << " modified successfully!\n";
}

void viewGroomingHistory() {
    string searchPhone;
    cout << "\nEnter Customer Phone Number: ";
    cin >> searchPhone;
    cin.ignore();

    // Step 1: Find matching userID from userdata.txt
    ifstream userFile("userdata.txt");
    string fileUserID, fileUsername, filePhone;
    string targetUserID = "";

    while (getline(userFile, fileUserID, '|') && getline(userFile, fileUsername, '|') && getline(userFile, filePhone, '|')){
        if (filePhone == searchPhone) {
            targetUserID = fileUserID;
            break;
        }
    }
    userFile.close();

    if (targetUserID.empty()) {
        cout << "\nNo customer account found with Phone Number: " << searchPhone << "\n";
        return;
    }

    // Step 2: Display booking history for the found user
    Customer c;
    c.userID = targetUserID;
    c.username = fileUsername; // Assuming username is needed for display
    viewBookingHistory(c);
}

void cancelCustomerBooking() {
    string searchPhone;
    cout << "\nEnter Customer Phone Number: ";
    cin >> searchPhone;
    cin.ignore();

    // Step 1: Find matching userID from userdata.txt
    ifstream userFile("userdata.txt");
    string fileUserID, fileUsername, filePhone;
    string targetUserID = "";

    while (getline(userFile, fileUserID, '|') && getline(userFile, fileUsername, '|') && getline(userFile, filePhone, '|')){
        if (filePhone == searchPhone) {
            targetUserID = fileUserID;
            break;
        }
    }
    userFile.close();

    if (targetUserID.empty()) {
        cout << "\nNo customer account found with Phone Number: " << searchPhone << "\n";
        return;
    }

    // Step 2: Cancel grooming service for the found user
    Customer c;
    c.userID = targetUserID;
    cancelGroomingService(c);
} 

void viewCustomerBookings() {
    string searchPhone;
    cout << "\nEnter Customer Phone Number: ";
    cin >> searchPhone;
    cin.ignore();

    // Step 1: Find matching userID from userdata.txt
    ifstream userFile("userdata.txt");
    string fileUserID, fileUsername, filePhone;
    string targetUserID = "";

    while (getline(userFile, fileUserID, '|') && getline(userFile, fileUsername, '|') && getline(userFile, filePhone, '|')){
        if (filePhone == searchPhone) {
            targetUserID = fileUserID;
            break;
        }
    }
    userFile.close();

    if (targetUserID.empty()) {
        cout << "\nNo customer account found with Phone Number: " << searchPhone << "\n";
        return;
    }

    // Step 2: View booking history for the found user
    Customer c;
    c.userID = targetUserID;
    viewBookingHistory(c);
}

//******* Report Menu *******/
void customerRecords() {
    ifstream userFile("userdata.txt");

    if (!userFile) {
        cout << "\nError opening customer records file!\n";
        return;
    }

    string fileUserID, fileUsername, filePhone;

    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "             CUSTOMER RECORDS\n";
    cout << setfill('*') << setw(55) << "" << endl;

    while (getline(userFile, fileUserID, '|') &&
           getline(userFile, fileUsername, '|') &&
           getline(userFile, filePhone, '|'))
    {
        cout << "\nUser ID   : " << fileUserID;
        cout << "\nUsername  : " << fileUsername;
        cout << "\nPhone     : " << filePhone;
        cout << "\n--------------------------------------------------";
    }

    userFile.close();
}

void petRecords()
{
    ifstream petFile("petdata.txt");

    if (!petFile)
    {
        cout << "\nError opening pet records file!\n";
        return;
    }

    string fileUserID;
    string filePetID;
    string filePetType;
    string filePetName;
    string filePetGender;
    string filePetBreed;
    string filePetAge;

    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "             PET RECORDS\n";
    cout << setfill('*') << setw(55) << "" << endl;

    while (getline(petFile, fileUserID, '|') &&
           getline(petFile, filePetID, '|') &&
           getline(petFile, filePetType, '|') &&
           getline(petFile, filePetName, '|') &&
           getline(petFile, filePetGender, '|') &&
           getline(petFile, filePetBreed, '|') &&
           getline(petFile, filePetAge, '|'))
    {
        cout << "\nPet ID     : " << filePetID;
        cout << "\nOwner ID   : " << fileUserID;
        cout << "\nPet Name   : " << filePetName;
        cout << "\nPet Type   : " << filePetType;
        cout << "\nPet Gender : " << filePetGender;
        cout << "\nPet Breed  : " << filePetBreed;
        cout << "\nPet Age    : " << filePetAge;

        cout << "\n--------------------------------------------------";
    }

    petFile.close();
}

void bookingRecords()
{
    ifstream file("bookingdata.txt");

    if (!file)
    {
        cout << "\nUnable to open booking data file.\n";
        return;
    }

    string fileBookingID, fileUserID, fileUsername;
    string filePetID, filePetName, fileService;
    string fileDate, fileStartTime, fileEndTime;

    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "             BOOKING RECORDS" << endl;
    cout << setfill('*') << setw(55) << "" << endl;

    bool found = false;

    while (
        getline(file, fileBookingID, '|') && getline(file, fileUserID, '|') &&
        getline(file, fileUsername, '|') && getline(file, filePetID, '|') &&
        getline(file, filePetName, '|') && getline(file, fileService, '|') &&
        getline(file, fileDate, '|') && getline(file, fileStartTime, '|') &&
        getline(file, fileEndTime)
    )
    {
        found = true;

        int startTime = stoi(fileStartTime);
        int endTime = stoi(fileEndTime);

        cout << "\n";
        cout << "Booking ID   : " << fileBookingID << endl;
        cout << "Customer     : " << fileUsername
             << " (User ID: " << fileUserID << ")" << endl;
        cout << "Pet Name     : " << filePetName
             << " (Pet ID: " << filePetID << ")" << endl;
        cout << "Service      : " << fileService << endl;
        cout << "Date         : " << fileDate << endl;
        cout << "Time Slot    : "
             << displayTime(startTime)
             << " - "
             << displayTime(endTime) << endl;
        cout << setfill('-') << setw(50) << "" << endl;
    }

    if (!found)
    {
        cout << "\nNo booking records found.\n";
    }

    file.close();
}

void groomingServiceReports()
{
    ifstream file("bookingdata.txt");

    if (!file)
    {
        cout << "Unable to open booking file!\n";
        return;
    }

    int bathingCount = 0;
    int haircutCount = 0;
    int nailTrimmingCount = 0;
    int earCleaningCount = 0;

    string line;

    while (getline(file, line, '|'))
    {
        if (line.find("Bathing") != string::npos)
        {
            bathingCount++;
        }
        else if (line.find("Haircut") != string::npos)
        {
            haircutCount++;
        }
        else if (line.find("Nail trimming") != string::npos)
        {
            nailTrimmingCount++;
        }
        else if (line.find("Ear cleaning") != string::npos)
        {
            earCleaningCount++;
        }
    }

    file.close();

    cout << "\n";
    cout << setfill('*') << setw(55) << "" << endl;
    cout << "           GROOMING SERVICE REPORT\n";
    cout << setfill('*') << setw(55) << "" << endl << endl;

    cout << left << setw(25) << "Service"
         << "Total Bookings" << endl;

    cout << "---------------------------------------\n";
    cout << left << setw(25) << "Bathing" << bathingCount << endl;
    cout << left << setw(25) << "Haircut" << haircutCount << endl;
    cout << left << setw(25) << "Nail trimming" << nailTrimmingCount << endl;
    cout << left << setw(25) << "Ear cleaning" << earCleaningCount << endl;
}

void reportMenu()
{
    int option; 

    do{
        cout << "\n \n";
        cout << setfill('*') << setw(55) << "" << endl;
        cout << "             REPORT MENU\n";
        cout << setfill('*') << setw(55) << "" << endl;

        cout << "\n1. Customer Records";
        cout << "\n2. Pet Records";
        cout << "\n3. Booking Records";
        cout << "\n4. Grooming Service Reports";
        cout << "\n5. Back to Staff Menu";
        cout << "\n6. Exit";

        cout << "\nEnter your option (1-7): ";
        cin >> option;

        while (option < 1 || option > 7){
            cout << "Invalid option! Please try again.";
            cout << "\nEnter your option (1-6): ";
            cin >> option;
        }

        switch (option){
            case 1:
                customerRecords();
                break;
            case 2:
                petRecords();
                break;
            case 3:
                bookingRecords();
                break;
            case 4:
                groomingServiceReports();
                break;
            case 5:
                return;   // Back to Staff Menu
            case 6:
                exit(0);  // Exit whole program
        }

    } while (option != 5);
}

// Submenu - Staff Menu
void staffMenu(){
    int staffOption;

    do{
        cout << "\n \n";
        cout << setfill('*') << setw(55) << "" << endl;
        cout << "             STAFF MENU\n";
        cout << setfill('*') << setw(55) << "" << endl << endl; 

        cout << "1. View all bookings for Today and Tomorrow\n";
        cout << "2. Search Customer Details\n";
        cout << "3. Modify a Customer's Booking\n";
        cout << "4. Cancel a Customer's Booking\n";
        cout << "5. View a Customer's Grooming History\n";
        cout << "6. Report Menu\n";
        cout << "7. Back to Main Menu\n";

        cout << "Enter your option (1-7): ";
        cin >> staffOption;

        while(staffOption < 1 || staffOption > 7){
            cout << "Invalid option! Please enter a number from 1 to 7.\n";
            cout << "Enter your option (1-7): ";
            cin >> staffOption;
        }

        switch(staffOption){

            case 1:
                viewAllBookings();
                break; 

            case 2: 
                searchCustomerDetails();
                break;

            case 3:
                modifyCustomerBooking();
                break;

            case 4:
                cancelCustomerBooking();
                break;

            case 5:
                viewGroomingHistory();
                break;

            case 6:
                reportMenu();
                break;

            case 7:
                return;   // Go back to Main Menu
        }

    } while(staffOption != 7);
}

// ************************************************** int Main Menu *********************************************** 
int main() {
    int option;

    do {
        cout << endl << endl << setfill('*') << setw(55) << "";
        cout << "\nWelcome to Special Pet Grooming System!\n";
        cout << setfill('*') << setw(55) << "" << endl << endl;

        cout << "Main Menu: \n";
        cout << "1. About us \n";
        cout << "2. Customer \n";
        cout << "3. Staff \n";
        cout << "4. Exit \n";

        cout << "Enter your option (1-4): ";
        cin >> option;

        // Validate input
        while (option < 1 || option > 4) {
            cout << "Invalid option! Please enter a number from 1 to 4.\n";
            cout << "Enter your option (1-4): ";
            cin >> option;
        }

        // Perform selected option
        if (option == 1) {
            aboutUs();
        }
        else if (option == 2) {
            customerMenu();
        }
        else if (option == 3) {
            if (staffLogin()){
                staffMenu();
            }else{
                cout << "Invalid login!"; 
            }
        }
        else if (option == 4) {
            cout << "\nThank you for using our system!\n"; 
        }
    } while (option != 4);

    return 0;
}