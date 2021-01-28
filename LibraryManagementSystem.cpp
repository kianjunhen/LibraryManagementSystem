#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <time.h>
#include <iomanip>

using namespace std;

// Structs and Classes Declaration
struct DoublyNodeTypeForPatron {
    string PatronID;
    string PatronName;
    string PatronGender;
    string PatronDOB;
    string PatronEmail;
    string PatronContactNumber;
    
    DoublyNodeTypeForPatron* next;
    DoublyNodeTypeForPatron* prev;
};

class PatronList {
public:
    int sizeforPatron = 0;
    void AddPatron(string, string, string, string, string, string);
    void SearchPatron_ID(string);
    void SearchPatron_NAME(string);
    void PrintfromBeginning();
    void PrintfromBehind();
    void UpdatePatronInformation(string);
    void getPatronwithActiveBookBorrow();
    void PrintLast10BooksByAPatron();
    
    void PrintPatronID();
};

struct DoublyNodeTypeForBorrow {
    int BorrowID;
    string BookTitle;
    string PatronID;
    string BorrowDate;
    string ReturnDate;
    string ActualReturnedDate;
    bool Extension;
    
    DoublyNodeTypeForBorrow* next;
    DoublyNodeTypeForBorrow* prev;
};

class BorrowList {
public:
    int BookSize = 0;
    
    void AddBorrow(string, string);
    void PrintfromBeginning();
    void PrintfromBehind();
    void UpdateActualReturnedDate(int);
    void Print10Last();
    void MakeExtension(int);
    void UpdateExtensionDate(int, string);
    void SetBookToUnavailable(string);
    void PrintBorrowList();
    void PrintBorrowID();
    
    //Get today date and return date (15 days after)
    string getToday();
    string getReturnedDate();
};

class DATE {
public:
    void extend_date(int, int, int, int);
    int day, mon, year;
};

struct colNode {
    int BookID;
    bool Status;
    colNode* next;
};

struct BookTitleList {
    string BookTitle;
    BookTitleList* next;
};

struct rowNode {
    string BookTitle;
    string BookAuthor;
    string BookGenre;
    string BookCategory;
    int BookISBN;
    colNode* nextCopy;
    rowNode* nextBook;
};

class BookList {
private:
    int getRandomISBN();
public:
    colNode* AddFirstCopy();
    colNode* AddSecondCopy();
    void AddNewBook(string, string, string, string);
    void Print();
    void PrintAvailableBookTitle();
    void Search_Category(string);
    void Search_Genre(string);
    void Search_Title(string);
    void UpdateBookInfo(string, string, string, string, int);
    void PrintISBN();
    void DeleteBook(int);
};

// Global Variable Declaration
DoublyNodeTypeForPatron* headforPatron;
DoublyNodeTypeForPatron* tailforPatron;

DoublyNodeTypeForBorrow* headforBorrow;
DoublyNodeTypeForBorrow* tailforBorrow;

rowNode* head;
colNode* colHead;
BookTitleList* bookAvailableList;

int sizeRow = 0;
int sizeCol = 0;
const int MAX_COPIES = 2;
int sizeforPatron = 0;
int BorrowBookSize = 1;
const int MAX_PRINT = 10;
const int MAX_BORROW = 3;


// Methods

string getGender(int GenderOption) {
    //This method will be return either MALE or FEMALE as string
    if(GenderOption == 1) {
        return "MALE";
    } else {
        return "FEMALE";
    }
};

bool checkBorrowID(int BorrowID) {
    //Copy value of headforBorrow into currentBorrow
    DoublyNodeTypeForBorrow* currentBorrow = headforBorrow;
    if (currentBorrow == NULL) {
        //Check if the borrow list is not pointing to any link list, then return false
        return false;
    }
    else {
        
        while (currentBorrow != NULL) {
            //If the borrow list is pointing to a link list, then check if the borrow ID is matched to the given borrow ID
            if (currentBorrow->BorrowID == BorrowID) {
                //If the borrow ID is found, then return true
                return true;
            }
            //If not, then move to the next link list record
            currentBorrow = currentBorrow->next;
        }
    }
    //Return false, if the given borrow ID does not match any in link list of borrow
    return false;
};

bool case_insensitive_match(string s1, string s2) {
    //This method is to convert string to all lower cases for the given string 1 and string 2
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    
    //After converting to the lower case, then start to compare if the two given strings are matched
    if (s1.compare(s2) == 0)
        return true; //The strings are same
    return false; //not matched
}


void PatronList::AddPatron(string PatronID, string PatronName, string PatronGender, string PatronDOB, string PatronEmail, string PatronContactNumber) {
    
    //Copy value of headforPatron into current
    DoublyNodeTypeForPatron* current = new DoublyNodeTypeForPatron;
    current = headforPatron;
    bool flag = false;
    
    //Iterate it if the current traversal is not NULL
    while (current != NULL) {
        //Matching the patron link list and the given patron ID
        if (case_insensitive_match(current->PatronID, PatronID)) {
            //Set true value to flag to indicate the patron ID is found, and break the iteration
            flag = true;
            break;
        }
        current = current->next;
    }
    
    //If no duplicate patron ID is detected
    if (!flag) {
        //Create a new node for patron
        DoublyNodeTypeForPatron* newNode = new DoublyNodeTypeForPatron;
        newNode->next = NULL;
        newNode->prev = tailforPatron;
        tailforPatron = newNode;
        newNode->PatronID = PatronID;
        newNode->PatronName = PatronName;
        newNode->PatronGender = PatronGender;
        newNode->PatronDOB = PatronDOB;
        newNode->PatronEmail = PatronEmail;
        newNode->PatronContactNumber = PatronContactNumber;
        
        //If the headforPatron is pointing to NULL
        if (headforPatron == NULL) {
            headforPatron = newNode;
            tailforPatron = newNode;
            
        }
        else {
            newNode->prev->next = newNode;
        }
        //Increase the size of Patron list
        sizeforPatron++;
        cout << "A new patron is added into the system." << endl;
        cout << "The new patron name is: " << PatronName << endl;
    }
    //If detected
    else {
        cout << "DUPLICATION OF ID";
        cout << endl;
    }
};

void PatronList::PrintLast10BooksByAPatron() {
    //Copy value of headforPatron into patronList
    DoublyNodeTypeForPatron* patronList = headforPatron;
    //Copy value of tailforBorrow into currentBorrow
    DoublyNodeTypeForBorrow* currentBorrow = tailforBorrow;
    
    //Instantiated counter to be 0
    int counter = 0;
    
    //Iterate it if the patronlist is not NULL
    while (patronList != NULL) {
        currentBorrow = tailforBorrow;
        cout << patronList->PatronName << endl;
        counter = 0;
        //Iterate it if the currentBorrow is not NULL
        while (currentBorrow != NULL) {
            //If the Patron ID of patronlist is matched to Patron IID of currentBorrow and the counter is below 10
            if (patronList->PatronID == currentBorrow->PatronID && counter < MAX_PRINT) {
                //Print the records
                cout << counter + 1 << " " << currentBorrow->BookTitle << " " << currentBorrow->BorrowDate << " " << currentBorrow->ActualReturnedDate << endl;
                //Add 1 to counter
                counter++;
            }
            //Move to the previous borrow
            currentBorrow = currentBorrow->prev;
        }
        cout << endl;
        //Move to the next patron
        patronList = patronList->next;
    }
}

void PatronList::getPatronwithActiveBookBorrow() {
    //Copy value of headforBorrow into currentBorrow
    DoublyNodeTypeForBorrow* currentBorrow = headforBorrow;
    //Copy value of headforPatron into currentPatron
    DoublyNodeTypeForPatron* currentPatron = headforPatron;
    
    //Instantiated counter to be 0
    int counter = 0;
    
    //Iterate if the currentPatron is not NULL
    while (currentPatron != NULL) {
        currentBorrow = headforBorrow;
        counter = 0;
        cout << currentPatron->PatronName << endl;
        //Iterate if the currentBorrow is not NULL
        while (currentBorrow != NULL) {
            //Check if the patron ID of currentPatron with Patron ID of currentBorrow and the counter is below 10
            if (currentPatron->PatronID == currentBorrow->PatronID && counter < MAX_BORROW) {
                //Check if the actual returned date is NULL
                if (currentBorrow->ActualReturnedDate == "NULL") {
                    cout << counter + 1 << " " << currentBorrow->BookTitle << endl;
                    //Increment 1 to counter
                    counter++;
                }
            }
            //Move to the next borrow
            currentBorrow = currentBorrow->next;
        }
        cout << endl;
        //Move to the next patron
        currentPatron = currentPatron->next;
    }
};

int totalBookBorrowedByPatron(string PatronID) {
    //Copy value of headforBorrow into currentBorrow
    DoublyNodeTypeForBorrow* currentBorrow = headforBorrow;
    
    //Instatianted counter to be 0
    int counter = 0;
    
    //Iterate if the currentBorrow is not NULL
    while(currentBorrow != NULL) {
        //Check if the Patron ID of currentBorrow is matched to the given PatronID and the actual returned date is NULL
        if(currentBorrow -> PatronID == PatronID && currentBorrow->ActualReturnedDate == "NULL") {
            //Increment 1 to counter
            counter++;
        }
        //Move to the next borrow
        currentBorrow = currentBorrow -> next;
    }
    //Return counter value to the method
    return counter;
};

void PatronList::SearchPatron_ID(string PatronID) {
    //Copy value of headforPatron into current
    DoublyNodeTypeForPatron* current = new DoublyNodeTypeForPatron;
    current = headforPatron;
    
    bool flag = false;
    
    //Iterate if the current is not NULL
    while (current != NULL) {
        //Check if the given Patron ID is matched the Patron ID in Patron link list
        if (case_insensitive_match(current->PatronID, PatronID)) {
            //Set true value to flag and break the iteration
            flag = true;
            break;
        }
        //Move to the next patron if not found
        current = current->next;
    }
    
    //If flag equals to true
    if (flag) {
        //Print the records
        cout << "\n\nPatron ID: " << current->PatronID << endl;
        cout << "Patron Name: " << current->PatronName << endl;
        cout << "Patron Gender: " << current->PatronGender << endl;
        cout << "Date of Birth: " << current->PatronDOB << endl;
        cout << "Patron Email: " << current->PatronEmail << endl;
        cout << "Contact Number: " << current->PatronContactNumber << endl;
        //Call method to return the value of book borrowed by passing patron ID
        cout << "Total current book(s) borrowed: " << totalBookBorrowedByPatron(current->PatronID) << endl;
        cout << endl;
    }
    //If flag equals to false, means the given patron ID is not found
    else {
        cout << "NO PATRON ID IS FOUND.";
        cout << endl;
    }
}

void PatronList::SearchPatron_NAME(string PatronName) {
    //Copy value of headforPatron into current
    DoublyNodeTypeForPatron* current = new DoublyNodeTypeForPatron;
    current = headforPatron;
    
    bool flag = false;
    
    //Iterate if the current is not NULL
    while (current != NULL) {
        //Check if the given patron name is matched to the patron name of patron link list
        if (case_insensitive_match(current->PatronName, PatronName)) {
            //Set a true value to flag and break the iteration
            flag = true;
            break;
        }
        //Move to the next patron if not found
        current = current->next;
    }
    
    //If flag equals to true
    if (flag) {
        cout << "\n\nPatron ID: " << current->PatronID << endl;
        cout << "Patron Name: " << current->PatronName << endl;
        cout << "Patron Gender: " << current->PatronGender << endl;
        cout << "Date of Birth: " << current->PatronDOB << endl;
        cout << "Patron Email: " << current->PatronEmail << endl;
        cout << "Contact Number: " << current->PatronContactNumber << endl;
        //Call method to return the value of book borrowed by passing patron ID
        cout << "Total current book(s) borrowed: " << totalBookBorrowedByPatron(current->PatronID) << endl;
        cout << endl;
    }
    //If flag equals to false, means the given patron name is not found
    else {
        cout << "NO PATRON NAME IS FOUND.";
        cout << endl;
    }
}

void PatronList::PrintfromBeginning() {
    //Copy value of headforPatron into current
    DoublyNodeTypeForPatron* current = headforPatron;
    cout << endl << endl;
    cout << setw(20) << left << "PATRON ID" << setw(30) << left << "PATRON NAME" << setw(15) << left << "GENDER" << setw(20) << left << "DATE OF BIRTH" << setw(30) << left << "PATRON EMAIL" << setw(20) << left << "TEL. NUMBER" << endl;
    //Iterate if the current is not NULL
    while (current != NULL) {
        //Print all the records of patron list
        cout << setw(20) << left << current->PatronID << setw(30) << left << current->PatronName << setw(15) << left << current->PatronGender << setw(20) << left << current->PatronDOB << setw(30) << left << current->PatronEmail << setw(20) << left << current->PatronContactNumber;
        //Move to the next patron
        current = current->next;
        cout << endl;
    }
    cout << endl;
};

void PatronList::PrintfromBehind() {
    //Copy value of headforPatron into current
    DoublyNodeTypeForPatron* current = tailforPatron;
    cout << endl << endl;
    cout << setw(20) << left << "PATRON ID" << setw(30) << left << "PATRON NAME" << setw(15) << left << "GENDER" << setw(20) << left << "DATE OF BIRTH" << setw(30) << left << "PATRON EMAIL" << setw(20) << left << "TEL. NUMBER" << endl;
    //Iterate if the current is not NULL
    while (current != NULL) {
        //Print all the records
        cout << setw(20) << left << current->PatronID << setw(30) << left << current->PatronName << setw(15) << left << current->PatronGender << setw(20) << left << current->PatronDOB << setw(30) << left << current->PatronEmail << setw(20) << left << current->PatronContactNumber;
        //Move to the previous patron
        current = current->prev;
        cout << endl;
    }
    cout << endl;
};

void PatronList::UpdatePatronInformation(string PatronID) {
    //Copy value of headforPatron into current
    DoublyNodeTypeForPatron* current = headforPatron;
    int GenderOption;
    bool flag = false;
    //Iterate if the current is not NULL
    while (current != NULL) {
        //Check if the given patron ID is matched with the patron ID in patron list
        if (case_insensitive_match(current->PatronID, PatronID)) {
            //Set a true value to flag and break the iteration, if found
            flag = true;
            break;
        }
        //Move to the next patron
        current = current->next;
    }
    
    string PatronName;
    string PatronEmail;
    string PatronContactNumber;
    string PatronDOB;
    
    //If patron ID is found
    if (flag) {
        //Get patron details
        cout << "Please enter the patron name: ";
        getline(cin, PatronName);
        
        //Iterate if the given input is not either 1 or 0
        while(true) {
            cout << "Is the patron Male? (1 - YES / 0 - NO): ";
            cin >> GenderOption;
            if(GenderOption == 0 || GenderOption == 1) {
                //Break the iteration if the given input is 1 or 0
                break;
            } else {
                cout << "Please enter 1 or 0 ONLY. \n";
            }
        }
        cin.get();
        //Get the patron details
        cout << "Please enter patron DOB: ";
        getline(cin, PatronDOB);
        cout << "Please enter patron Email: ";
        getline(cin, PatronEmail);
        cout << "Please enter patron Contact Number: ";
        getline(cin, PatronContactNumber);
        //Instatiate the updated patron details to the current node type
        current->PatronName = PatronName;
        current->PatronGender = getGender(GenderOption);
        current->PatronDOB = PatronDOB;
        current->PatronEmail = PatronEmail;
        current->PatronContactNumber = PatronContactNumber;
        cout << "Update successfully";
        cout << endl;
    }
    else {
        cout << "The Patron ID, " << PatronID << ", not found.";
        cout << "Please try again.";
    }
}

void PatronList::PrintPatronID() {
    //Copy value of headforPatron into currentPatron
    DoublyNodeTypeForPatron* currentPatron = headforPatron;
    cout << endl << endl;
    //If size of patron is greater than 0
    if(sizeforPatron > 0) {
        //Print the header of patron
        cout << setw(30) << left << "Patron Name" << setw(15) << left << "Patron ID" << endl;
        //Iterate if the currentPatron is not NULL
        while(currentPatron != NULL) {
            //Print all the records of patron
            cout << setw(30) << left << currentPatron -> PatronName << setw(15) << left << currentPatron -> PatronID << endl;
            //Move to the next patron
            currentPatron = currentPatron -> next;
        }
    }
    cout << endl;
};

void BorrowList::AddBorrow(string BookTitle, string PatronID) {
    //Create a current as a pointer
    DoublyNodeTypeForBorrow* current = new DoublyNodeTypeForBorrow;
    //Copy value of headforPatron into currentPatron
    DoublyNodeTypeForPatron* currentPatron = headforPatron;
    BorrowList borrowList;
    
    bool checkForPatron = false;
    bool checkForBook = false;
    
    string capitalPatronID;
    string capitalPatronName;
    
    bool NoAvailableBook = false;
    //Copy value of head into currentRow
    rowNode* currentRow = head;
    //Iterate if the currentRow is not NULL
    while(currentRow != NULL) {
        //Check if the given BookTitle is matched with the BookTitle of Book list
        if(case_insensitive_match(currentRow -> BookTitle, BookTitle)) {
            //Copy value of nextCopy into nextCopy pointer
            colNode* nextCopy = currentRow -> nextCopy;
            //Check if both books are 0
            if(nextCopy -> Status == 0 && nextCopy -> next -> Status == 0) {
                //Set a true value to NoAvailableBook and break the iteration
                NoAvailableBook = true;
                break;
            }
            //Move to the next copy
            nextCopy = nextCopy -> next;
        }
        //Move to the next book
        currentRow = currentRow -> nextBook;
    }
    
    //Copy value of headforBorrow into current
    current = headforBorrow;
    int counter = 0;
    //Iterate if the current is not NULL
    while (current != NULL) {
        //Check if the given patron ID is matched with the patron ID of borrow list and actual returned date is NULL
        if (case_insensitive_match(current->PatronID, PatronID) && current->ActualReturnedDate == "NULL") {
            //Increment 1 to the counter
            counter++;
        }
        current = current->next;
    }
    
    //Copy value of head into currentRow
    currentRow = head;
    //Iterate if the currentRow is not NULL
    while(currentRow != NULL) {
        //Check if the given BookTitle is matched with the BookTitle of book list
        if(case_insensitive_match(currentRow -> BookTitle, BookTitle)) {
            //Set a true value to checkForBook and break the iteration
            checkForBook = true;
            break;
        }
        //Move to the next book
        currentRow = currentRow -> nextBook;
    }
    
    //Iterate if the currentPatron is not NULL
    while(currentPatron != NULL) {
        //Check if the given patron ID is matched with the patron ID of patron list
        if(case_insensitive_match(currentPatron -> PatronID, PatronID)) {
            //Set the true value to the checkForPatron and break the iteration
            checkForPatron = true;
            capitalPatronID = currentPatron -> PatronID;
            capitalPatronName = currentPatron -> PatronName;
            break;
        }
        //Move to the next patron
        currentPatron = currentPatron -> next;
    }
    
    //If both checkForPatron and checkForBook are true value
    if(checkForPatron && checkForBook) {
        //Check if the counter is below 3 and the book is available
        if (counter < MAX_BORROW && !NoAvailableBook) {
            //Create a new node
            DoublyNodeTypeForBorrow* newNode = new DoublyNodeTypeForBorrow;
            newNode->BorrowID = BorrowBookSize;
            newNode->BookTitle = BookTitle;
            newNode->PatronID = capitalPatronID;
            newNode->BorrowDate = getToday();
            newNode->ReturnDate = getReturnedDate();
            newNode->ActualReturnedDate = "NULL";
            newNode->Extension = 0;
            newNode->next = NULL;
            newNode->prev = tailforBorrow;
            tailforBorrow = newNode;
            //Check if the headforBorrow is not pointing to any
            if (headforBorrow == NULL) {
                newNode->prev = NULL;
                headforBorrow = newNode;
                tailforBorrow = newNode;
            }
            else {
                newNode->prev->next = newNode;
            }
            //Set the copy of the selected title to be unavailable
            borrowList.SetBookToUnavailable(BookTitle);
            cout << "A new book borrow transaction is made for Patron " << capitalPatronName << " with the book title of " << BookTitle <<endl;
            //Incremental 1 to size of borrow book
            BorrowBookSize++;
        } else if (NoAvailableBook) { //NoAvailableBook is true only if both copies of book is 0
            cout << "The book availability currently is 0." << endl;
            cout << "Please try to borrow another book." << endl;
        }
        else { //If the book is available but the patron has reached its maximum
            cout << "The patron, " << PatronID << ", has exceed the numbers of borrows limited." << endl;
            cout << "Please advise him/her to make book return before borrow another book" << endl;
        }
    }
    if (!checkForPatron) { //If the given patron ID is not found
        cout << "Patron ID, " << PatronID << ", not found." << endl;
        cout << "Please enter Patron ID based on the given list ONLY." << endl;
    }
};

void BorrowList::PrintfromBeginning() {
    //Copy value of headforBorrow into current
    DoublyNodeTypeForBorrow* current = new DoublyNodeTypeForBorrow;
    current = headforBorrow;
    
    cout << endl << endl;
    if(current == NULL) { //Check if the current is not pointing to any
        cout << "The borrow list is empty." << endl;
    } else {
        //Print the header of borrow list
        cout << setw(10) << left << "BORROW ID" << setw(35) << left << "BOOK TITLE" << setw(15) << left << "PATRON ID" << setw(15) << left << "BORROW DATE" << setw(15) << left << "RETURN DATE" << setw(25) << left << "ACTUAL RETURNED DATE" << setw(10) << left << "EXTENSION" << endl;
        while (current != NULL) { //Iterate if the current is not NULL
            //Print all the records of borrow list
            cout << setw(10) << left << current->BorrowID << setw(35) << left << current->BookTitle << setw(15) << left << current->PatronID << setw(15) << left << current->BorrowDate << setw(15) << left << current->ReturnDate << setw(25) << left << current->ActualReturnedDate << setw(10) << left << current->Extension;
            //Move to the next borrow list
            current = current->next;
            cout << endl;
        }
    }
    cout << endl;
};

void BorrowList::SetBookToUnavailable(string BookTitle) {
    //Copy value of head into currentRow
    rowNode* currentRow = head;
    while(currentRow != NULL) { //Iterate if the currentRow is not NULL
        //Check if the given BookTitle is matched with the BookTitle of borrow list
        if(case_insensitive_match(currentRow -> BookTitle, BookTitle)) {
            //Copy value of nextCopy of currentRow into currentCol
            colNode* currentCol = currentRow -> nextCopy;
            if(currentCol -> Status != 0) { //If the status of first copy is not 0
                currentCol -> Status = 0; //Assign 0 to the status
            } else { //If the status of first copy is 0
                if(currentCol -> next -> Status != 0) { //Check the status of second copy is not 0
                    currentCol -> next -> Status = 0; //Assign 0 to the status
                }
            }
            //Move to the next copy
            currentCol = currentCol -> next;
        }
        //Move to the next book
        currentRow = currentRow -> nextBook;
    }
};

void BorrowList::PrintfromBehind() {
    //Copy value of tailforBorrow into current
    DoublyNodeTypeForBorrow* current = tailforBorrow;
    
    cout << endl << endl;
    if(current == NULL) { //If the current is not pointing to any
        cout << "The borrow list is empty." << endl;
    } else {
        //Print the header of borrow list
        cout << setw(10) << left << "BORROW ID" << setw(35) << left << "BOOK TITLE" << setw(15) << left << "PATRON ID" << setw(15) << left << "BORROW DATE" << setw(15) << left << "RETURN DATE" << setw(25) << left << "ACTUAL RETURNED DATE" << setw(10) << left << "EXTENSION" << endl;
        while (current != NULL) { //Iterate if the current is not NULL
            //Print all records of borrow list
            cout << setw(10) << left << current->BorrowID << setw(35) << left << current->BookTitle << setw(15) << left << current->PatronID << setw(15) << left << current->BorrowDate << setw(15) << left << current->ReturnDate << setw(25) << left << current->ActualReturnedDate << setw(10) << left << current->Extension;
            current = current->prev; //Move to the previous borrow record
            cout << endl;
        }
    }
    cout << endl;
    
};

string BorrowList::getToday() {
    //This method is to get today date as string by using its local time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string days = to_string(ltm->tm_mday);
    string months = to_string(1 + ltm->tm_mon);
    string years = to_string(1900 + ltm->tm_year);
    string date = days + "/" + months + "/" + years;
    return date;
}

void tokenize(string const& str, const string delim, vector<string>& out)
{
    
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
};

void BorrowList::PrintBorrowID() {
    //Copy value of headforBorrow into current
    DoublyNodeTypeForBorrow* current = headforBorrow;
    cout << endl << endl;
    cout << setw(10) << left << "BORROW ID" << setw(35) << left << "BOOK TITLE" << setw(10) << left << "PATRON ID" << endl;
    while(current != NULL) { //Iterate if the current is not NULL
        if(current -> ActualReturnedDate == "NULL") { //Check if the actual returned date is not NULL
            //Print all records of borrow list
            cout << setw(10) << left << current -> BorrowID << setw(35) << left << current -> BookTitle << setw(10) << left << current -> PatronID << endl;
        }
        current = current -> next; //Move to the next borrow
    }
    cout << endl;
}

void BorrowList::UpdateExtensionDate(int BorrowID, string returnDate) {
    //Copy value of headforBorrow into current
    DoublyNodeTypeForBorrow* current = headforBorrow;
    while (current->BorrowID != BorrowID) { //Iterate if the given borrow ID is not matched with the borrow ID of borrow list
        current = current->next; //Move to the next borrow record
    }
    current->ReturnDate = returnDate; //Set the new return date
    current->Extension = 1; //Update the extension status
    cout << "UPDATE SUCCESSFULLY !";
    cout << endl;
}

void BorrowList::MakeExtension(int BorrowID) {
    //Copy value of headforBorrow into current
    DoublyNodeTypeForBorrow* current = new DoublyNodeTypeForBorrow;
    current = headforBorrow;
    
    int dateArray[3];
    bool flag = false;
    while (current != NULL) { //Iterate if the current is not NULL
        //If the given borrow ID is matched with the borrow ID of borrow list and its extension is 1
        if (current->Extension == 1 && current -> BorrowID == BorrowID) {
            flag = true; //Set a true value to flag
            break; //Break the iteration
        }
        current = current->next; //Move to the next borrow
    }
    
    current = headforBorrow; //Copy value of headforBorrow into current
    while (current->BorrowID != BorrowID) { //Iterate if the given borrow ID is not matched with the borrow ID of borrow list
        current = current->next; //Move to the next borrow
    }
    
    if (!flag) { //If the borrow ID does not make any extension before
        string rDate = current->ReturnDate;
        const string delimiter = "/";
        vector<string> out;
        tokenize(rDate, delimiter, out);
        for (int i = 0; i < 3; i++) {
            dateArray[i] = stoi(out[i]);
        }
        DATE date;
        //Pass the day, month, and year as well as number of extension days to extend_date method
        date.extend_date(dateArray[0], dateArray[1], dateArray[2], 15);
        string rDays = to_string(date.day); //Convert int into string
        string rMonth = to_string(date.mon); //Convert int into string
        string rYear = to_string(date.year); //Convert int into string
        string newReturnDate = rDays + "/" + rMonth + "/" + rYear; //Concatenate three string with / symbols to a single string
        UpdateExtensionDate(current->BorrowID, newReturnDate); //Update the return date of the borrow ID to be new returned date
    }
    else {
        cout << "THE EXTENSION IS NOT ALLOWED, PLEASE THINK ABOUT OTHERS.";
        cout << endl;
    }
}

void BorrowList::Print10Last() {
    //Copy value of tailforBorrow into current
    DoublyNodeTypeForBorrow* current = tailforBorrow;
    int counter = 0;
    
    cout << endl <<endl; 
    if(current == NULL) { //Check if the current is NULL
        cout << "The borrow list is empty." << endl;
    } else {
        //Print the header of borrow list
        cout << setw(10) << left << "BORROW ID" << setw(35) << left << "BOOK TITLE" << setw(15) << left << "PATRON ID" << setw(15) << left << "BORROW DATE" << setw(15) << left << "RETURN DATE" << setw(25) << left << "ACTUAL RETURNED DATE" << setw(10) << left << "EXTENSION" << endl;
        while (current != NULL && counter < MAX_PRINT) { //Iterate if the current is not NULL and the counter is lesser than 10
            //Print all records of borrow list
            cout << setw(10) << left << current->BorrowID << setw(35) << left << current->BookTitle << setw(15) << left << current->PatronID << setw(15) << left << current->BorrowDate << setw(15) << left << current->ReturnDate << setw(25) << left << current->ActualReturnedDate << setw(10) << left << current->Extension;
            current = current->prev; //Move to the previous borrow
            counter++; //Increment 1 to counter
            cout << endl;
        }
    }
    cout << endl;
}


string BorrowList::getReturnedDate() {
    //This method will return a new returned date which after 15 days
    time_t now = time(0);
    tm* ltm = localtime(&now);
    DATE date;
    date.extend_date(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year, 15);
    string rDays = to_string(date.day);
    string rMonth = to_string(date.mon);
    string rYear = to_string(date.year);
    string rDate = rDays + "/" + rMonth + "/" + rYear;
    return rDate;
}

void BorrowList::UpdateActualReturnedDate(int BorrowID) {
    //Copy value of headforBorrow into current
    DoublyNodeTypeForBorrow* current = headforBorrow;
    bool flag = false;
    while (current != NULL) { //Iterate if the current is not NULL
        //Check if the given borrow ID is matched with the borrow ID of borrow list and its returned date is not NULL
        if (current->BorrowID == BorrowID && current->ActualReturnedDate != "NULL") {
            flag = true; //Set true value to flag
            break; //Break the iteration
        }
        current = current->next; //Move to the next borrow
    }
    if (flag) { //If the returned date of the given borrow ID is not NULL
        cout << "The book has already returned" << endl;
    }
    else {
        current = headforBorrow; //Copy value of headforBorrow into current
        while (current != NULL) { //Iterate if the current is not NULL
            if (current->BorrowID == BorrowID) { //Check if the borrow ID of borrow list is matched with the given borrow ID
                current->ActualReturnedDate = getToday(); //Update the actual returned date to be today
                cout << "The book, " << current->BookTitle << ", has successfully returned by Patron ID - " << current->PatronID;
                cout << endl;
            }
            current = current->next; //Move to the next borrow record
        }
        
    }
    
}

void DATE::extend_date(int d1, int m1, int y1, int days) {
    static int month[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31 ,30, 31 };
    for (int i = 1; i <= days; i++) {
        d1++;
        if ((d1 > month[m1 - 1]) || (y1 % 4 != 0 && m1 == 2 && d1 > 28)) {
            d1 = 1;
            m1++;
        }
        if (m1 > 12) {
            m1 = 1;
            y1++;
        }
        day = d1;
        mon = m1;
        year = y1;
    }
}


colNode* BookList::AddSecondCopy() {
    //This method will create the second copy for the book
    colNode* newCopy = new colNode;
    newCopy -> BookID = sizeCol + 2;
    newCopy -> Status = 1;
    newCopy -> next = NULL;
    return newCopy;
}

colNode* BookList::AddFirstCopy() {
    //This method will create the first copy for the book
    colNode* newCopy = new colNode;
    newCopy -> BookID = sizeCol + 1;
    newCopy -> Status = 1;
    newCopy -> next = AddSecondCopy(); //Call the method to create the second copy
    return newCopy;
};

void BookList::AddNewBook(string BookTitle, string BookAuthor, string BookGenre, string BookCategory) {
    rowNode* newBook = new rowNode; //Create a new node type
    rowNode* current = head; //Copy value of head into current
    bool flag = false;
    
    while(current != NULL) { //Iterate if the current is not NULL
        //Check if the added new book does not have the same name with the same author
        if(case_insensitive_match(current -> BookTitle, BookTitle) && case_insensitive_match(current -> BookAuthor, BookAuthor)) {
            flag = true; //Set flag to be true
            break; //Break the iteration
        }
        current = current -> nextBook; //Move to the next book
    }
    
    if(!flag) { //If the added new book is not added before
        newBook -> BookTitle = BookTitle;
        newBook -> BookAuthor = BookAuthor;
        newBook -> BookGenre = BookGenre;
        newBook -> BookCategory = BookCategory;
        newBook -> BookISBN = BookList::getRandomISBN();
        newBook -> nextBook = NULL;
        newBook -> nextCopy = AddFirstCopy();
        sizeCol = sizeCol + 2;
        
        if(head == NULL ){ //If the head is NULL
            head = newBook;
        } else {
            rowNode* lastBook = head; //Copy value of head into lastBook
            while(lastBook -> nextBook != NULL){ //Iterate if the next book of last book is not NULL
                lastBook = lastBook -> nextBook; //Move to the next book
            }
            lastBook -> nextBook = newBook; //Assign newBook node type to the previous nextBook
        }
        sizeRow++;
        cout << "A new book with two copies is added into the system." << endl;
        cout << "The new book name is: " << BookTitle << endl;
    } else {
        cout << "THE SAME BOOK WITH SAME AUTHOR IS DETECTED";
        cout << endl;
    }
    
};

void BorrowList::PrintBorrowList() {
    DoublyNodeTypeForBorrow* current = headforBorrow; //Copy value of headforBorrow into current
    int BorrowID;
    BorrowList borrowList;
    
    bool flag = false;
    bool exitFunction = false;
    
    cout << endl << endl;
    
    if (current != NULL) { //Check if the current is pointing to any
        cout << setw(10) << left << "BORROW ID" << setw(35) << left << "BOOK TITLE" << setw(10) << left << "PATRON ID" << endl;
        while (current != NULL) { //Iterate if the current is not NULL
            if (current->ActualReturnedDate == "NULL") { //Check if the actual returned date is NULL
                //Print all records of borrow list
                cout << setw(10) << left << current->BorrowID << setw(35) << left << current->BookTitle << setw(10) << left << current->PatronID << endl;
            }
            current = current->next; //Move to the next borrow
        }
        cout << endl;
    }
    else {
        cout << "The borrow book transaction currently is empty." << endl;
        exitFunction = true; //If the current is not pointing to any, set exitFunction to be true
    }
    
    if (!exitFunction) {
        //Check if all the books have returned.
        current = headforBorrow; //Copy value of headforBorrow into current
        while (current != NULL) { //Iterate if the current is not NULL
            if (current->ActualReturnedDate == "NULL") { //Check if the actual returned date is NULL
                flag = true; //Set true value to flag
                break; //Break the iteration
            }
            current = current->next; //Move to the next borrow
        }
        
        if (!flag) { //Check if all the books were returned
            cout << "All the books have returned, and no returned book is required." << endl;
        }
        else {
            cout << "Please enter the borrow ID: ";
            cin >> BorrowID;
            
            if(BorrowID < BorrowBookSize) {
                if (checkBorrowID(BorrowID)) //Check if the borrow ID is existed
                        borrowList.UpdateActualReturnedDate(BorrowID); //Update the actual returned date of borrow ID
            }
            else {
                cout << "Borrow ID " << BorrowID << " not found." << endl;
            }
                
        }
    }
    cout << endl;
}



void BookList::Print() {
    rowNode* currentRow = head; //Copy value of head into currentRow
    int counter = 0;
    cout << endl << endl;
    cout << setw(35) << left << "BOOK TITLE" << setw(35) << left << "BOOK AUTHOR" << setw(15) << left << "GENRE" << setw(15) << left << "CATEGORY" << setw(10) << left << "ISBN" << setw(10) << left << "AVAILABILITY" << endl;
    while(currentRow != NULL) { //Iterate if the currentRow is not NULL
        colNode* nextCopy = currentRow -> nextCopy;
        if(nextCopy -> Status == 1 || nextCopy -> next -> Status == 1) { //Check if either books is available
            counter = 0;
            cout << setw(35) << left << currentRow -> BookTitle << setw(35) << left << currentRow -> BookAuthor << setw(15) << left << currentRow -> BookGenre << setw(15) << left << currentRow -> BookCategory << setw(10) << left << currentRow -> BookISBN << setw(10) << left;
            for(int i =0; i < MAX_COPIES; i++) {
                if(nextCopy -> Status == 1) { //Check if the status is 0 then increment 1 to counter
                    counter ++;
                }
                nextCopy = nextCopy -> next; //Move to the next copy
            }
            cout << counter << endl; //Print the number of available copy
            
        }
        currentRow = currentRow -> nextBook; //Move to the next book
        
    }
    cout << endl;
};

void BookList::PrintAvailableBookTitle() {
    rowNode* currentRow = head; //Copy value of head into currentRow
    bookAvailableList =  NULL;
    while(currentRow != NULL) { //Iterate if the currentRow is not NULL
        colNode* nextCopy = currentRow -> nextCopy;
        while(nextCopy != NULL) { //Iterate if the nextCopy is not NULL
            if(nextCopy -> Status == 1 || nextCopy -> next -> Status == 1) { //Check if either book is available
                BookTitleList* newTitle = new BookTitleList;
                newTitle -> BookTitle = currentRow -> BookTitle;
                newTitle -> next = NULL;
                if(bookAvailableList == NULL){ //Check if the bookAvailableList is NULL
                    bookAvailableList = newTitle;
                } else {
                    BookTitleList* current = bookAvailableList;
                    while (current -> next != NULL) { //Iterate if the next of current is not NULL
                        current = current -> next; //Move to the next BookTitleList
                    }
                    current -> next = newTitle; //Assign the title to the next BookTitleList
                }
                break; //Break the iteration
            }
            nextCopy = nextCopy -> next; //Move to the next copy
        }
        currentRow = currentRow -> nextBook; //Move to the next book
    }
    
    if(bookAvailableList == NULL) { //Check if the bookAvailableList is empty
        cout << "Its empty!";
        cout << endl;
    } else {
        BookTitleList* current = bookAvailableList; //Copy value of bookAvailableList into current
        cout << "\n\nBOOK TITLE" << endl;
        while (current != NULL) { //Iterate if the current is not NULL
            cout << current -> BookTitle <<endl; //Print the record
            current = current -> next; //Move to the next book title
        }
        cout << endl;
    }
};

void BookList::Search_Category(string BookCategory) {
    //Copy value of head into currentRow
    rowNode* currentRow = head;
    cout << endl << endl;
    
    cout << setw(35) << left << "BOOK TITLE" << setw(35) << left << "BOOK AUTHOR" << setw(15) << left << "GENRE" << setw(15) << left << "CATEGORY" << setw(10) << left << "ISBN" << setw(15) << left << "FIRST COPY" << setw(15) << left << "SECOND COPY" <<endl;
    
    for(int i = 0; i < sizeRow; i++) { //Iterate all the books
        //Check if the given book category is matched with the book category of book list
        if(currentRow -> BookCategory == BookCategory) {
            cout << setw(35) << left << currentRow -> BookTitle << setw(35) << left << currentRow -> BookAuthor << setw(15) << left << currentRow -> BookGenre << setw(15) << left << currentRow -> BookCategory << setw(10) << left << currentRow -> BookISBN;
            colNode* nextCopy = currentRow -> nextCopy;
            for(int j = 0; j < MAX_COPIES; j++) { //Iterate all the copies
                if(nextCopy -> Status == 1) { //Check if the Status is 1
                    cout << setw(15) << left << "Yes";
                } else {
                    cout << setw(15) << left << "No";
                }
                nextCopy = nextCopy -> next; //Move to the next copy
            }
            cout << endl;
        }
        
        currentRow = currentRow -> nextBook; //Move to the next book
    }
    cout << endl;
};

void BookList::Search_Genre(string BookGenre) {
    rowNode* currentRow = head; //Copy value of head into currentRow
    cout << endl << endl;
    
    cout << setw(35) << left << "BOOK TITLE" << setw(35) << left << "BOOK AUTHOR" << setw(15) << left << "GENRE" << setw(15) << left << "CATEGORY" << setw(10) << left << "ISBN" << setw(15) << left << "FIRST COPY" << setw(15) << left << "SECOND COPY" <<endl;
    
    for(int i = 0; i < sizeRow; i++) { //Iterate all the books
        if(currentRow -> BookGenre == BookGenre) { //Check if the given book genre is matched with the book genre of book list
            cout << setw(35) << left << currentRow -> BookTitle << setw(35) << left << currentRow -> BookAuthor << setw(15) << left << currentRow -> BookGenre << setw(15) << left << currentRow -> BookCategory << setw(10) << left << currentRow -> BookISBN;
            colNode* nextCopy = currentRow -> nextCopy;
            for(int j = 0; j < MAX_COPIES; j++) { //Iterate all the copies
                if(nextCopy -> Status == 1) { //Check if the status is 1
                    cout << setw(15) << left << "Yes";
                } else {
                    cout << setw(15) << left << "No";
                }
                nextCopy = nextCopy -> next; //Move to  the next copy
            }
            cout << endl;
        }
        currentRow = currentRow -> nextBook; //Move to the next book
    }
    cout << endl;
};

void BookList::Search_Title(string BookTitle) {
    rowNode* currentRow = head; //Copy value  of head into currentRow
    bool flag = false;
    while(currentRow != NULL) { //Iterate if the currentRow is not NULL
        //Check if the given BookTitle is matched the BookTitle of book list
        if(case_insensitive_match(currentRow -> BookTitle, BookTitle)) {
            flag = true; //Set the flag to be true
            break; //Break the iteration
        }
        currentRow = currentRow -> nextBook; //Move to the next book
    }
    
    if(!flag) { //If no books found
        cout << "THERE IS NO " << BookTitle << " BOOK IN LIBRARY";
        cout << endl;
    } else {
        cout << "\n\nTitle: " << currentRow -> BookTitle <<endl;
        cout << "Author: " << currentRow -> BookAuthor << endl;
        cout << "Genre: " << currentRow -> BookGenre << endl;
        cout << "Category: " << currentRow -> BookCategory << endl;
        cout << "ISBN: " << currentRow -> BookISBN << endl;
        
        colNode* nextCopy = currentRow -> nextCopy;
        for(int j = 0; j < MAX_COPIES; j++) { //Iterate all the copies
            cout << "Book Status - Copy " << j+1 << ": ";
            if(nextCopy -> Status == 1) { //Check if the status is 1
                cout << "Available" << endl;
            } else {
                cout << "Unavailable" << endl;
            }
            nextCopy = nextCopy -> next; //Move to the next copy
        }
        cout <<endl;
    }
};

void BookList::UpdateBookInfo(string BookTitle, string BookAuthor, string BookCategory, string BookGenre, int ISBN) {
    rowNode* current = head; //Copy value of head into current
    bool flag = false;
    while(current != NULL) { //Iterate if the current is not NULL
        if(current -> BookISBN == ISBN) { //Check if the given ISBN is matched with the ISBN of book list
            flag = true; //Set flag to be true
            break; //Break the iteration
        }
        current = current -> nextBook; //Move to the next book
    }
    
    if(flag) { //If the book is found
        current -> BookTitle = BookTitle;
        current -> BookAuthor = BookAuthor;
        current -> BookCategory = BookCategory;
        current -> BookGenre = BookGenre;
        cout << "The book with " << ISBN << " is updated successfully.";
        cout << endl;
    } else {
        cout << "NO ISBN IS FOUND.";
        cout << endl;
    }
};

//void BookList::UpdateBook(string BookTitle, int BookID) {
//    rowNode* current = head; //Copy value of head into current
//    bool flag = false;
//
//    while(current -> BookTitle != BookTitle) {  //Iterate if the given booktitle is not matched with the booktitle of book list
//        current = current -> nextBook; //Move to the next book
//    }
//    
//    colNode* nextCopy = current -> nextCopy;
//
//    while(nextCopy != NULL) { //Iterate if the nextCopy is not NULL
//        if(nextCopy -> Status != 0) { //Check if the status is not NULL
//            flag = true; //Set the flag to be true
//            break; //Break the iteration
//        }
//        nextCopy = nextCopy -> next; //Move to the next copy
//    }
//
//    if(flag) {
//        for(int i = 0; i < MAX_COPIES; i ++ ) { //Iterate all the copies
//            while(nextCopy -> BookID != BookID) { //Iterate if the given BookID is not matched with the BookID of book liist
//                nextCopy = nextCopy -> next; //Move to the next copy
//            }
//            nextCopy -> Status = 0; //Set the status to be 0
//        }
//    } else {
//        cout << "The book " << current -> BookTitle << " is currently borrowed by someone." << endl;
//    }
//
//};

void BookList::DeleteBook(int ISBN) {
    rowNode* current = head; //Copy value of head into current
    bool flag = false;
    while(current != NULL) { //Iterate if the current is not NULL
        if(current -> BookISBN == ISBN) { //Check if the given ISBN is matched with the Book ISBN of book list
            flag = true; //Set the flag to be true
            break; //Break the iteration
        }
        current = current -> nextBook; //Move to the next book
    }

    if(flag) { //If the book ISBN is found
        if(current-> BookISBN == head -> BookISBN) {
            head = current->nextBook;
        } else if (current->nextBook == NULL) {
            rowNode* beforelast = head;
            while(beforelast -> nextBook -> nextBook != NULL) {
                beforelast = beforelast -> nextBook;
            }
            beforelast->nextBook = NULL;
        } else {
            rowNode* beforeCurrent = head;
            while(beforeCurrent->nextBook != current) {
                beforeCurrent = beforeCurrent -> nextBook;
            }
            beforeCurrent -> nextBook = current -> nextBook;
        }

        colNode* nextCopy = current -> nextCopy;
        colNode* headCol = nextCopy;
        if(nextCopy->Status == 1 && nextCopy -> next->Status == 1) { //Check if both copies are available
            //Delete all the copies
            while(headCol != NULL) {
                nextCopy = nextCopy -> next;
                delete headCol;
                headCol = nextCopy;
            }
            delete current;
            cout << endl;
        } else {
            cout << "Someone is borrowing one of the copies, cannot be deleted.";
            cout <<endl;
        }
        
    } else {
        cout << "No ISBN, " << ISBN << ", not found." << endl;
        cout << "Please try again." << endl;
    }

};

int BookList::getRandomISBN() {
    //This method will get a random ISBN as integer
    rowNode* current = head;
    int ISBN = (rand()%10000)+1;
    while(current != NULL) {
        if(current -> BookISBN == ISBN) {
            ISBN = (rand()%10000)+99;
            break;
        }
        current = current -> nextBook;
    }
    return ISBN;
};

void BookList::PrintISBN() {
    rowNode* currentRow = head; //Copy value of head into currentRow
    cout << endl << endl;
    cout << setw(35) << left << "BOOK TITLE" << setw(35) << left << "BOOK AUTHOR" << setw(35) << left << "ISBN" <<endl;
    while (currentRow != NULL) { //Iterate if the currentRow is not NULL
        //Print all the records of book list
        cout << setw(35) << left << currentRow -> BookTitle << setw(35) << left << currentRow -> BookAuthor << setw(35) << left << currentRow -> BookISBN << endl;
        currentRow = currentRow -> nextBook; //Move to the next book
    }
    cout << endl;
}

enum GENRE_FICTION {
    FANTASY = 1,
    SCIENCE = 2,
    HISTORICAL = 3,
    REALISTIC = 4,
    FAN = 5
};

enum GENRE_NONFICTION {
    NARRATIVE = 1,
    BIOGRAPHY = 2,
    PERIODICALS = 3,
    SELF_HELP = 4,
    REFERENCE = 5
};

void AddDataForPatron(PatronList* patronList) {
    patronList -> AddPatron("HKJ001", "HEN KIAN JUN", "MALE", "29/09/1997", "KJHEN0929@GMAIL.COM", "60139338783");
    patronList -> AddPatron("LWY002", "LEE WAI YEN", "FEMALE", "13/10/1998", "LWYEN1013@GMAIL.COM", "6014848592");
    patronList -> AddPatron("LBK003", "LOW BOON KIAT", "MALE", "11/22/1999", "BOONKIAT1122@GMAIL.COM", "6012395858");
    patronList -> AddPatron("NZJ004", "NG ZHENG JUE", "MALE", "20/06/1999", "ZHENGJUE1999@GMAIL.COM", "6019483838");
    patronList -> AddPatron("LYK005", "LIM YI KANG", "MALE", "23/03/1999", "YIKANG123@GMAIL.COM", "6012394859");
    patronList -> AddPatron("YMW006", "YONG MUN WEI", "MALE", "17/10/1997", "YONGMUNWEI@GMAIL.COM", "6019273828");
    patronList -> AddPatron("TKM007", "TEOH KHEN MENG", "MALE", "17/10/1997", "KHENMENG1997@GMAIL.COM", "6019212328");
    patronList -> AddPatron("TYJ008", "LIM AH BENG", "MALE", "24/10/1998", "JIFFRED1998@GMAIL.COM", "6019272322");
};

void AddDataForBook(BookList* bookList) {
    bookList -> AddNewBook("HARRY POTTER", "J. K. ROWLING", "FANTASY", "FICTION");
    bookList -> AddNewBook("MEIN KAMPF", "ADOLF HITLER", "HISTORICAL", "FICTION");
    bookList -> AddNewBook("13 REASONS WHY", "JAY ASHER", "REALISTIC", "FICTION");
    bookList -> AddNewBook("THE INVISIBLE MAN", "H. G. WELLS", "SCIENCE", "FICTION");
    bookList -> AddNewBook("THE HUNGER GAMES", "SUZANNE COLLINS", "NARRATIVE", "NON-FICTION");
    bookList -> AddNewBook("I HAVE A DREAM", "MARTIN LUTHER KING JR.", "BIOGRAPHY", "NON-FICTION");
    bookList -> AddNewBook("CRIME AND PERIODICALS", "NOVA EVERLY", "PERIODICALS", "NON-FICTION");
    bookList -> AddNewBook("A NEW EARTH", "ECKHART TOLLE", "SELF-HELP", "NON-FICTION");
    bookList -> AddNewBook("THE HERO WITH A THOUSAND FACES", "JOSEPH CAMPBELL", "REFERENCE", "NON-FICTION");
};


string getFiction(bool isFiction) {
    //This method is to return either FICTION or NON-FICTION based on the given boolean
    if(isFiction) {
        return "FICTION";
    } else {
        return "NON-FICTION";
    }
};

string getGenre(bool isFiction, int GenreNumber) {
    //This method is to return Book Genre based on the given integer
    string Genre;
    if(isFiction == 1) { //If it is fiction
        switch(GenreNumber) {
            case GENRE_FICTION::FANTASY:
                Genre = "FANTASY";
                break;
            case GENRE_FICTION::SCIENCE:
                Genre = "SCIENCE";
                break;
            case GENRE_FICTION::HISTORICAL:
                Genre = "HISTORICAL";
                break;
            case GENRE_FICTION::REALISTIC:
                Genre = "REALISTIC";
                break;
            case GENRE_FICTION::FAN:
                Genre = "FAN";
                break;
        }
    } else { //If it is non-fiction
        switch(GenreNumber) {
            case GENRE_NONFICTION::NARRATIVE:
                Genre = "NARRATIVE";
                break;
            case GENRE_NONFICTION::BIOGRAPHY:
                Genre = "BIOGRAPHY";
                break;
            case GENRE_NONFICTION::PERIODICALS:
                Genre = "PERIODICALS";
                break;
            case GENRE_NONFICTION::SELF_HELP:
                Genre = "SELF-HELP";
                break;
            case GENRE_NONFICTION::REFERENCE:
                Genre = "REFERENCE";
                break;
        }
    }
    return Genre;
};

void getNewbook(BookList* bookList) {
    cin.get();
    int isFiction;
    int GenreOption;
    string bookTitle;
    string bookAuthor;
    string bookCategory;
    string bookGenre;
    string OptionInput = "Your option is: ";
    string GenreForFiction = "1 - Fantasy\n2 - Science\n3 - Historical\n4 - Realistic\n5 - Fan\n";
    string GenreForNonFiction = "1 - Narrative\n2 - Biography\n3 - Periodicals\n4 - Self-Help\n5 - Reference\n";
    
    cout << "Enter the new book title: ";
    getline(cin, bookTitle);
    cout << "Enter the new book author: ";
    getline(cin, bookAuthor);
    
    while(true) { //Iterate if the isFiction is not either 1 or 0
        cout << "Is the new book Fiction? (1 - YES / 0 - NO): ";
        cin >> isFiction;
        if(isFiction == 1 || isFiction == 0) {
            break; //Break the iteration
        } else {
            cout << "Please enter 1 or 0 ONLY.\n";
        }
    }
    
    while(true) { //Iterate if the GenreOption is not between 1 and 5
        if(isFiction == 1) {
            cout << GenreForFiction;
        } else {
            cout << GenreForNonFiction;
        }
        
        cout << OptionInput;
        cin >> GenreOption;
        
        if(GenreOption >= 1 && GenreOption <= 5) {
            break; //Break the iteration
        } else {
            cout << "Please enter 1 - 5 ONLY.\n";
        }
    }
    
    bookCategory = getFiction(isFiction); //Get the book category by passing integer value
    bookGenre = getGenre(isFiction, GenreOption); //Get the book genre by passing integer value
    
    bookList -> AddNewBook(bookTitle, bookAuthor, bookGenre, bookCategory); //Call method to add new book
    
}

void getBook(BookList* bookList) {
    cin.get();
    string bookCategory;
    string bookGenre;
    string bookTitle;
    int isFiction;
    int SearchBookOption;
    int GenreOption;
    
    string GenreForFiction = "1 - Fantasy\n2 - Science\n3 - Historical\n4 - Realistic\n5 - Fan\n";
    string GenreForNonFiction = "1 - Narrative\n2 - Biography\n3 - Periodicals\n4 - Self-Help\n5 - Reference\n";
    string OptionInput = "Your option is: ";
    
    cout << "You want to search a book based on: ";
    cout << "\n1 - Search based on Category\n2 - Search based on Genre\n3 - Search based on Title\n";
    cout << OptionInput;
    cin >> SearchBookOption;
    
    if(SearchBookOption == 1) {
        while(true) { //Iterate if the isFiction is not either 1 or 0
            cout << "Fiction or Non-Fiction? (1 - Fiction / 0 - Non-Fiction): ";
            cin >> isFiction;
            if(isFiction == 1 || isFiction == 0) {
                break; //Break the iteration
            } else {
                cout << "Please enter 1 or 0 ONLY.\n";
            }
        }
        bookCategory = getFiction(isFiction); //Get the book category by passiing integer value
        bookList -> Search_Category(bookCategory);
    } else if (SearchBookOption == 2) {
        cout << "1 - Fantasy\n2 - Science\n3 - Historical\n4 - Realistic\n5 - Fan\n6 - Narrative\n7 - Biography\n8 - Periodicals\n9 - Self-Help\n10 - Reference\n";
        cout << "Please enter genre: ";
        cin >> GenreOption;
        
        if(GenreOption >= 1 && GenreOption <= 10) {
            switch (GenreOption) {
                case 1:
                    bookGenre = "FANTASY";
                    break;
                case 2:
                    bookGenre = "SCIENCE";
                    break;
                case 3:
                    bookGenre = "HISTORICAL";
                    break;
                case 4:
                    bookGenre = "REALISTIC";
                    break;
                case 5:
                    bookGenre = "FAN";
                    break;
                case 6:
                    bookGenre = "NARRATIVE";
                    break;
                case 7:
                    bookGenre = "BIOGRAPHY";
                    break;
                case 8:
                    bookGenre = "PERIODICALS";
                    break;
                case 9:
                    bookGenre = "SELF-HELP";
                    break;
                case 10:
                    bookGenre = "REFERENCE";
                    break;
            }
        } else{
            cout << "INVALID INPUT";
        }
        
        bookList -> Search_Genre(bookGenre);
    } else if(SearchBookOption == 3) {
        cin.get();
        cout << "Please enter the book title: ";
        getline(cin, bookTitle);
        bookList -> Search_Title(bookTitle);
    } else {
        cout << "INVALID INPUT";
    }
};

void getPrintBook(BookList* BookList) {
    int PrintOption;
    string OptionInput = "Your option is: ";
    cout << "1 - Print all book title\n2 - Print Available book title\n";
    cout << OptionInput;
    cin >> PrintOption;
    do { //Iterate if the PrintOption is not 0
        if (PrintOption == 2 || PrintOption == 1) {
            switch (PrintOption) {
                case 1: {
                    BookList->PrintAvailableBookTitle();
                    break;
                }
                case 2: {
                    BookList->Print();
                    break;
                }
                default: {
                    cout << "INVALID INPUT\n";
                    break;
                }
            }
        } else {
            cout << "Please enter 1-2 ONLY.\n";
        }
        cout << "1 - Print all book title\n2 - Print Available book title\n";
        cout << "If you wish to quit Print Section, you may enter 0 *\n";
        cout << OptionInput;
        cin >> PrintOption;
    } while (PrintOption != 0);
};

bool checkIfISBNAvailable(int ISBN) {
    rowNode* currentRow = head; //Copy value of head into currentRow
    bool flag = false;
    while(currentRow != NULL) { //Iterate if the currentRow is not NULL
        if(currentRow -> BookISBN == ISBN) { //Check if the given ISBN is matched with the book ISBN of book list
            flag = true; //Set flag to be true
            break; //Break the iteration
        }
        currentRow = currentRow -> nextBook; //Move to the next book
    }
    return flag; //Return true if the book ISBN is found, otherwise return false
};

void getUpdateABook(BookList* bookList) {
    cin.get();
    int ISBN;
    int isFiction;
    int GenreOption;
    string bookTitle;
    string bookAuthor;
    string bookCategory;
    string bookGenre;
    string OptionInput = "Your option is: ";
    string GenreForFiction = "1 - Fantasy\n2 - Science\n3 - Historical\n4 - Realistic\n5 - Fan\n";
    string GenreForNonFiction = "1 - Narrative\n2 - Biography\n3 - Periodicals\n4 - Self-Help\n5 - Reference\n";
    
    bookList -> PrintISBN();
    cout << "Please enter a book ISBN: ";
    cin >> ISBN;
    
    if(checkIfISBNAvailable(ISBN)) { //Check the method to check if the book ISBN is existed
        cin.get();
        cout << "Please enter the book title: ";
        getline(cin, bookTitle);
        cout << "Please enter the book author: ";
        getline(cin, bookAuthor);
        
        while(true) { //Iterate if the isFiction is not either 1 or 0
            cout << "Is the new book Fiction? (1 - YES / 0 - NO): ";
            cin >> isFiction;
            if(isFiction == 1 || isFiction == 0) {
                break; //Break the iteratioin
            } else {
                cout << "Please enter 1 or 0 ONLY.\n";
            }
        }
        
        while(true) { //Iterate if the genre option is not between 1 and 5
            if(isFiction == 1) {
                cout << GenreForFiction;
            } else {
                cout << GenreForNonFiction;
            }
            
            cout << OptionInput;
            cin >> GenreOption;
            
            if(GenreOption >= 1 && GenreOption <= 5) {
                break; //Break the iterationi
            } else {
                cout << "Please enter 1 - 5 ONLY.\n";
            }
        }
        
        bookCategory = getFiction(isFiction); //Get the book category by passing integer value
        bookGenre = getGenre(isFiction, GenreOption); //Get the book genre by passing integer value
        
        bookList -> UpdateBookInfo(bookTitle, bookAuthor, bookCategory, bookGenre, ISBN); //Call method to update the book detals
    } else {
        cout << "No ISBN is found." << endl;
    }
};

void DeleteABook(BookList* bookList) {
    int ISBN;
    bookList -> PrintISBN();
    cout << "Please enter a book ISBN that you wish to delete: ";
    cin >> ISBN;

    bookList -> DeleteBook(ISBN); //Call deletebook method to delete book by passing ISBN
}

void getNewPatron(PatronList* patronList) {
    cin.get();
    bool GenderOption = 1;
    string PatronID;
    string PatronName;
    string PatronDOB;
    string PatronEmail;
    string PatronContactNumber;
    string OptionInput = "Your option is: ";
    
    cout << "Please enter your Patron ID: ";
    getline(cin, PatronID);
    cout << "Please enter your Patron Name: ";
    getline(cin, PatronName);
    
    while(true) { //Iterate if the gender option is not ether 1 or 0
        cout << "Is the patron Male? (1 - YES / 0 - NO): ";
        cin >> GenderOption;
        if(GenderOption == 0 || GenderOption == 1) {
            break; //Break the iteration
        } else {
            cout << "Please enter 1 or 0 ONLY. \n";
        }
    }
    cin.get();
    cout << "Please enter your DOB: ";
    getline(cin, PatronDOB);
    cout << "Please enter your Email: ";
    getline(cin, PatronEmail);
    cout << "Please enter your Contact Number: ";
    getline(cin, PatronContactNumber);
    
    //Call method to add new patron by passing arguments
    patronList -> AddPatron(PatronID, PatronName, getGender(GenderOption), PatronDOB, PatronEmail, PatronContactNumber);
    
};

void getPatron(PatronList* patronList) {
    cin.get();
    string PatronID;
    string PatronName;
    string OptionInput = "Your option is: ";
    int SearchPatronOption;
    
    cout << "You want to search a patron based on: ";
    cout << "\n1 - Search based on Patron ID\n2 - Search based on Patron Name\n";
    cout << OptionInput;
    cin >> SearchPatronOption;
    
    if(SearchPatronOption == 1) {
        cin.get();
        cout << "Please enter patron ID: ";
        getline(cin, PatronID);
        patronList -> SearchPatron_ID(PatronID);
    } else if (SearchPatronOption == 2) {
        cin.get();
        cout << "Please enter patron Name: ";
        getline(cin, PatronName);
        patronList -> SearchPatron_NAME(PatronName);
    } else {
        cout << "INVALID INPUT";
    }
};

void getPrintPatron(PatronList* patronList) {
    int PrintOption;
    string OptionInput = "Your option is: ";
    cout << "1 - Print from beginning\n2 - Print from behind\n";
    cout << OptionInput;
    cin >> PrintOption;
    
    do { //Iterate if the print option is not 0
        if(PrintOption == 2 || PrintOption == 1) {
            switch(PrintOption) {
                case 1: {
                    patronList -> PrintfromBeginning();
                    break;
                }
                case 2: {
                    patronList -> PrintfromBehind();
                    break;
                }
                default: {
                    cout << "INVALID INPUT\n";
                    break;
                }
            }
        } else {
            cout << "Please enter 1-2 ONLY.\n";
        }
        
        cout << "1 - Print from beginning\n2 - Print from behind\n";
        cout << "If you wish to quit Print Section, you may enter 0 *\n";
        cout << OptionInput;
        cin >> PrintOption;
    } while (PrintOption != 0);
};

void makeReturnBook(BorrowList* borrowList) {
    borrowList->PrintBorrowList(); //Call method to print borrow list
}

bool CheckPatronID(string PatronID) {
    //Copy value of headforPatron into currentPatron
    DoublyNodeTypeForPatron* currentPatron = headforPatron;
    bool flag = false;
    while(currentPatron != NULL) { //Iterate if the currentPatron is not NULL
        if(case_insensitive_match(currentPatron -> PatronID, PatronID)) {
            flag = true; //Set the flag to be true
            break; //Break the iteration
        }
        currentPatron = currentPatron -> next; //Move to the next patron
    }
    return flag;
}

void getUpdatePatron(PatronList* patronList) {
    cin.get();
    patronList -> PrintPatronID();
    string PatronID;
    cout << "Please enter your Patron ID: ";
    getline(cin, PatronID);
    patronList -> UpdatePatronInformation(PatronID);
};


string getISBNtoBookTitle(int ISBN) {
    rowNode* currentRow = head; //Copy value of head into currentRow
    string bookTitle;
    while (currentRow != NULL) { //Iterate if the currentRow is not NULL
        if (currentRow->BookISBN == ISBN) { //Check if the given Book ISBN is matched with the book ISBN of book list
            bookTitle = currentRow->BookTitle; //Assign book title to the BookTitle
            break; //Break the iteration
        }
        currentRow = currentRow->nextBook; //Move to the next book
    }
    return bookTitle; //Return the book title string
};

void getNewBorrow(BorrowList* borrowList, PatronList* patronList, BookList* bookList) {
    cin.get();
    int BookISBN;
    string PatronID;
    string OptionInput = "Your option is: ";
    
    patronList->PrintPatronID();
    cout << "Please enter patron ID: ";
    getline(cin, PatronID);
    
    bookList->PrintISBN();
    cout << "Please enter Book ISBN ONLY: ";
    cin >> BookISBN;
    
    if (checkIfISBNAvailable(BookISBN)) { //Check if the ISBN is existed
        borrowList->AddBorrow(getISBNtoBookTitle(BookISBN), PatronID); //Add a new book borrow transaction
    }
    else {
        cout << "Book ISBN, " << BookISBN << ", not found." << endl;
        cout << "Please try again" << endl;
    }
    
};

void getPrintBorrow(BorrowList* borrowList) {
    int PrintOption;
    string OptionInput = "Your option is: ";
    cout << "1 - Print from beginning\n2 - Print from behind\n3 - Print last 10 book borrowed by patrons\n";
    cout << OptionInput;
    cin >> PrintOption;
    
    do { //Iterate if the print option is not 0
        if(PrintOption > 0) {
            switch (PrintOption) {
                case 1:
                    borrowList -> PrintfromBeginning();
                    break;
                case 2:
                    borrowList -> PrintfromBehind();
                    break;
                case 3:
                    borrowList -> Print10Last();
                    break;
                default:
                    cout << "INVALID INPUT\n";
                    break;
            }
        } else {
            cout << "Please enter 1, 2, or 3 ONLY.\n";
        }
        
        cout << "1 - Print from beginning\n2 - Print from behind\n3 - Print last 10 book borrowed by patrons\n";
        cout << "If you wish to quit Print Section, you may enter 0 *\n";
        cout << OptionInput;
        cin >> PrintOption;
    } while (PrintOption != 0);
};


void getMakeUpdateExtension(BorrowList* borrowList) {
    int BorrowID;
    
    borrowList -> PrintBorrowID();
    cout << "Please enter the borrow ID: ";
    cin >> BorrowID;
    
    if(BorrowID < BorrowBookSize) {
        if(checkBorrowID(BorrowID)) //Check if the given borrow ID is existed
            borrowList -> MakeExtension(BorrowID); //Call make extension method by passing borrow ID
    } else {
        cout << "Borrow ID " << BorrowID << " not found." << endl;
    }
    
};

bool Login(string Username, string Password) {
    const int ROW = 5;
    const int COL = 2;
    bool loginSuccess = false;
                                    //username  //password
    //Create credentials database
    string Credentials[ROW][COL] = {{"admin", "admin"},
                                    {"john", "123"},
                                    {"nicole", "123"},
                                    {"test", "123"},
                                    {"jd", "123"}};
    
    for(int i = 0; i < ROW; i++){ //Iterate all the credentiials
        //Check if the given username and password are matched with the credentials database
        if(case_insensitive_match(Username, Credentials[i][0]) && case_insensitive_match(Password, Credentials[i][1])) {
            loginSuccess = true; //Set loginSuccess to be true
            break; //Break the iteration
        }
        else
            loginSuccess = false;
        
    }
    
    return loginSuccess;
    
};

int main() {
    
    // Object instatiation
    PatronList patronList;
    BorrowList borrowList;
    BookList bookList;
    
    //Add dummy data
    AddDataForPatron(&patronList);
    AddDataForBook(&bookList);
    
    int MenuOption;
    int option;
    int inputMenu = 0;
    bool optionError = 0;
    int LoginChance = 0;
    bool LoginSuccess = false;
    string Username;
    string Password;
    
    string WelcomeMessage = "\n================ WELCOME TO LIBRARY MANAGEMENT SYSTEM ================ \n";
    string Menu = "\nMAIN MENU:\n1 - Book\n2 - Patron\n3 - Borrow Transaction\n";
    string BookMenu = "\nBOOK MENU:\n1 - Add a new book\n2 - Search\n3 - Print\n4 - Update book information\n5 - Delete a book\n";
    string PatronMenu = "\nPATRON MENU:\n1 - Add a new patron\n2 - Search\n3 - Print\n4 - Update a patron information\n5 - Get patron with active book borrow\n6 - Print the last 10 books borrowed by patron\n";
    string BorrowMenu = "\nBORROW MENU:\n1 - Add a new book borrow transaction\n2 - Print\n3 - Make Extension\n4 - Return a book\n";
    string OptionInput = "Your option is: ";
    
    
    do { //Iterate if the LoginChance is not equal to 3
        cout << "Please enter your username: ";
        cin >> Username;
        cout << "Please enter your password: ";
        cin >> Password;
        
        if(Login(Username, Password)) {
            LoginSuccess = true;
            break;
        } else {
            cout << "Incorrect username or password\n";
            cout << "Please try again.\n";
        }
        LoginChance++;
    } while(LoginChance != 3);
    
    if(LoginSuccess) { //If LoginSuccess is true
        while(!optionError) {
            cout << WelcomeMessage;
            cout << Menu;
            cout << OptionInput;
            cin >> option;
            
            if(option == 1) {
                cout << BookMenu;
                inputMenu = 1;
                optionError = 1;
            } else if(option == 2) {
                cout << PatronMenu;
                inputMenu = 2;
                optionError = 1;
            } else if(option == 3) {
                cout << BorrowMenu;
                inputMenu = 3;
                optionError = 1;
            } else {
                cout << "INVALID INPUT";
            }
        }
        
        cout << OptionInput;
        cin >> option;
        
        do { //Iterate if the MenuOption is not 0
            
            if(inputMenu == 1 && (option >= 1 && option <= 5)) {
                do { //Iterate if the option is not 0
                    switch(option) {
                        case 1: {
                            getNewbook(&bookList);
                            break;
                        }
                        case 2: {
                            getBook(&bookList);
                            break;
                        }
                        case 3: {
                            getPrintBook(&bookList);
                            break;
                        }
                        case 4: {
                            getUpdateABook(&bookList);
                            break;
                        }
                        case 5: {
                            DeleteABook(&bookList);
                            break;
                        }
                        default: {
                            cout << "INVALID INPUT";
                            break;
                        }
                    }
                    
                    cout << BookMenu;
                    cout << "If you wish to quit Book Section, you may enter 0 *\n";
                    cout << OptionInput;
                    cin >> option;
                } while (option != 0);
                
            }
            
            if (inputMenu == 2 && (option >= 1 && option <= 6)) {
                do { //Iterate if the option is not 0
                    switch(option) {
                        case 1: {
                            getNewPatron(&patronList);
                            break;
                        }
                        case 2: {
                            getPatron(&patronList);
                            break;
                        }
                        case 3: {
                            getPrintPatron(&patronList);
                            break;
                        }
                        case 4: {
                            getUpdatePatron(&patronList);
                            break;
                        }
                        case 5: {
                            patronList.getPatronwithActiveBookBorrow();
                            break;
                        }
                        case 6: {
                            patronList.PrintLast10BooksByAPatron();
                            break;
                        }
                        default: {
                            cout << "INVALID INPUT";
                            break;
                        }
                    }
                    
                    cout << PatronMenu;
                    cout << "If you wish to quit Patron Section, you may enter 0 *\n";
                    cout << OptionInput;
                    cin >> option;
                } while (option != 0);
            }
            
            if (inputMenu == 3 && (option >= 1 && option <= 4)) {
                do { //Iterate if the option is not 0
                    switch(option) {
                        case 1: {
                            getNewBorrow(&borrowList, &patronList, &bookList);
                            break;
                        }
                        case 2: {
                            getPrintBorrow(&borrowList);
                            break;
                        }
                        case 3: {
                            getMakeUpdateExtension(&borrowList);
                            break;
                        }
                        case 4: {
                            makeReturnBook(&borrowList);
                            break;
                        }
                        default: {
                            cout << "INVALID INPUT";
                            break;
                        }
                    }
                    
                    cout << BorrowMenu;
                    cout << "If you wish to quit Borrow Section, you may enter 0 *\n";
                    cout << OptionInput;
                    cin >> option;
                    
                } while (option != 0);
                
            }
            
            //Enter back to the Main Menu
            optionError = 0;
            
            while(!optionError) {
                cout << WelcomeMessage;
                cout << Menu;
                cout << "If you wish to quit Main Menu, you may enter 0 *\n";
                cout << OptionInput;
                cin >> option;
                
                if(option == 1) {
                    cout << BookMenu;
                    inputMenu = 1;
                    optionError = 1;
                } else if(option == 2) {
                    cout << PatronMenu;
                    inputMenu = 2;
                    optionError = 1;
                } else if(option == 3) {
                    cout << BorrowMenu;
                    inputMenu = 3;
                    optionError = 1;
                } else if(option == 0) {
                    exit(0);
                } else {
                    cout << "INVALID INPUT";
                }
            }
            
            cout << OptionInput;
            cin >> option;
            MenuOption = option;
            
        } while (MenuOption != 0);
    } else {
        //If the loginChance is more than 3 times
        cout << "You have exceeded the maximum numbers of login tries.";
    }
    return 0;
}
