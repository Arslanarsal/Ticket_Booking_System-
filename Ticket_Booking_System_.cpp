#include <bits/stdc++.h>
#include <conio.h>

using namespace std;
class Utility
{
public:
    static string getCnic()
    {
        char ch[14];
        char temp;
        int i = 0;
        while (i < 13)
        {
            temp = getch();
            if (temp >= '0' && temp <= '9')
            {
                cout << temp;
                ch[i] = temp;
                i++;
            }
            else if (temp == '\b' && i > 0)
            {
                cout << "\b \b";
                i--;
            }
        }
        ch[i] = '\0';
        string str = ch;
        return str;
    }

    static string checkChar()
    {
        char ch[100];
        char temp;
        int i = 0;
        while (i < 100)
        {
            temp = getch();
            if (temp >= 'a' && temp <= 'z' || temp >= 'A' && temp <= 'Z' || temp == ' ')
            {
                cout << temp;
                ch[i] = temp;
                i++;
            }
            else if (temp == '\r')
            {
                break;
            }

            else if (temp == '\b' && i > 0)
            {
                cout << "\b \b";
                i--;
            }
        }
        ch[i] = '\0';
        string str = ch;
        return str;
    }

    static double getprice()
    {
        char ch[5];
        char temp;
        int i = 0;
        while (i < 5)
        {
            temp = getch();
            if (temp >= '0' && temp <= '9')
            {
                cout << temp;
                ch[i] = temp;
                i++;
            }
            else if (temp == '\r')
            {
                break;
            }
            else if (temp == '\b' && i > 0)
            {
                cout << "\b \b";
                i--;
            }
        }
        ch[i] = '\0';
        string str = ch;
        double ans = 0;
        for (int i = 0; str[i] != '\0'; i++)
        {
            ans = (ans * 10) + (str[i] - '0');
        }

        return ans;
    }

    static string getdata()
    {
        char ch[10];
        char temp;
        int i = 0;
        while (i < 6)
        {
            if (i == 2 || i == 5)
            {
                temp = '/';
                cout << temp;
                ch[i] = temp;
                i++;
                continue;
            }

            temp = getch();

            if (i == 0)
            {
                if (temp >= '0' && temp <= '3')
                {
                    cout << temp;
                    ch[i] = temp;
                    i++;
                }
            }

            else if (i == 1)
            {
                if (ch[0] == '3')
                {
                    if (temp >= '0' && temp <= '1')
                    {
                        cout << temp;
                        ch[i] = temp;
                        i++;
                    }
                }
                else if (temp >= '0' && temp <= '9')
                {
                    cout << temp;
                    ch[i] = temp;
                    i++;
                }
            }

            if (i == 3)
            {
                if (temp >= '0' && temp <= '1')
                {
                    cout << temp;
                    ch[i] = temp;
                    i++;
                }
            }

            else if (i == 4)
            {
                if (ch[3] == '1')
                {
                    if (temp >= '0' && temp <= '2')
                    {
                        cout << temp;
                        ch[i] = temp;
                        i++;
                    }
                }
                else if (temp >= '0' && temp <= '9')
                {
                    cout << temp;
                    ch[i] = temp;
                    i++;
                }
            }

            else if (temp == '\r')
            {
                break;
            }
            else if (temp == '\b' && i > 0)
            {
                cout << "\b \b";
                i--;
            }
        }
        ch[6] = '2';
        ch[7] = '0';
        ch[8] = '2';
        ch[9] = '3';

        cout << ch[6];
        cout << ch[7];
        cout << ch[8];
        cout << ch[9];

        ch[10] = '\0';
        string str = ch;

        return str;
    }

    static int checknum(int n)
    {
        char ch[0];
        char temp;
        char c = n + '0';
        while (true)
        {
            temp = getch();
            if (temp >= '0' && temp <= c)
            {
                cout << temp;
                ch[0] = temp;
                return (ch[0] - '0');
            }
        }
    }

    static char checkYN()
    {
        char ch[0];
        char temp;
        while (true)
        {
            temp = getch();
            if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N')
            {
                cout << temp;
                ch[0] = temp;
                return ch[0];
            }
        }
    }
};

const int MAX_MOVIES = 10;
const string FILENAME = "movies.txt";

class Seats
{
private:
    int availableSeats;

public:
    Seats()
    {
        availableSeats = 0;
    }

    Seats(int seats)
    {
        availableSeats = seats;
    }

    void SetSeats(int seats)
    {
        availableSeats = seats;
    }

    int getAvailableSeats() const
    {
        return availableSeats;
    }

    bool bookSeats(int numSeats)
    {
        if (availableSeats >= numSeats)
        {
            availableSeats -= numSeats;
            return true;
        }
        return false;
    }

    void addSeats(int numSeats)
    {
        availableSeats += numSeats;
    }
};

class Movie
{
private:
    string Name;
    string description;
    string Time;
    double price;
    Seats seats;

public:
    Movie() {}

    Movie(const string &movieName, const string &movieDescription, const string &movieTime, double moviePrice, int seatsAvailable)
    {
        Name = movieName;
        description = movieDescription;
        Time = movieTime;
        price = moviePrice;
        seats.SetSeats(seatsAvailable);
    }

    string getName() const
    {
        return Name;
    }

    string getDescription() const
    {
        return description;
    }

    string gettime() const
    {
        return Time;
    }

    double getPrice() const
    {
        return price;
    }

    int getAvailableSeats() const
    {
        return seats.getAvailableSeats();
    }

    void saveToFile(ofstream &file) const
    {
        file << Name << endl;
        file << description << endl;
        file << Time << endl;
        file << price << endl;
        file << seats.getAvailableSeats() << endl;
    }

    void loadFromFile(ifstream &file)
    {
        getline(file, Name);
        getline(file, description);
        getline(file, Time);
        file >> price;
        int seatsAvailable;
        file >> seatsAvailable;
        file.ignore();
        seats = Seats(seatsAvailable);
    }

    bool bookTicket(int numSeats)
    {
        return seats.bookSeats(numSeats);
    }
};

class CustomerData
{
private:
    string ID;
    string movieName;
    double price;
    int bookedSeats;
    string movieTime;
    string bookingTime;

public:
    CustomerData(const string &id, const string &Name, double ticketPrice, int seats, const string &time, const string &booking)
    {
        ID = id;
        movieName = Name;
        price = ticketPrice;
        bookedSeats = seats;
        movieTime = time;
        bookingTime = booking;
    }

    string getID() const
    {
        return ID;
    }

    string getMovieName() const
    {
        return movieName;
    }

    double getPrice() const
    {
        return price;
    }

    int getBookedSeats() const
    {
        return bookedSeats;
    }

    string getMovieTime() const
    {
        return movieTime;
    }

    string getBookingTime() const
    {
        return bookingTime;
    }
};

class BookingSystem
{
private:
    Movie movies[MAX_MOVIES];
    int movieCount = 0;

public:
    BookingSystem()
    {
        loadMoviesFromFile();
    }

    void addMovie(const string &Name, const string &description, const string &Time, double price, int availableSeats)
    {
        if (movieCount < MAX_MOVIES)
        {
            Movie movie(Name, description, Time, price, availableSeats);
            movies[movieCount++] = movie;
            cout << "Movie added successfully!" << endl;
            saveMoviesToFile();
        }
        else
        {
            cout << "Maximum movie limit reached. Cannot add more movies." << endl;
        }
    }

    void deleteMovie(const string &Name)
    {
        for (int i = 0; i < movieCount; ++i)
        {
            if (movies[i].getName() == Name)
            {
                for (int j = i; j < movieCount - 1; ++j)
                {
                    movies[j] = movies[j + 1];
                }
                movieCount--;
                cout << "\n\nMovie deleted successfully!" << endl;
                saveMoviesToFile();
                return;
            }
        }
        cout << "\n\nMovie not found!" << endl;
    }

    void showMovieList() const
    {
        if (movieCount == 0)
        {
            cout << "No movie available\n";
            return;
        }

        cout << "\n\n\t\tMovie List:\n\n";
        for (int i = 0; i < movieCount; ++i)
        {
            if (movies[i].getAvailableSeats() == 0)
            {
                continue;
            }

            cout << "      Name                  : " << movies[i].getName() << endl;
            cout << "      Description           : " << movies[i].getDescription() << endl;
            cout << "      Time                  : " << movies[i].gettime() << endl;
            cout << "      Price                 : $" << movies[i].getPrice() << endl;
            cout << "      Available Seats       : " << movies[i].getAvailableSeats() << endl;
            cout << "             -----------------------\n\n";
        }
    }

    bool bookTicket(const string &Name, int numSeats, const string &customerID)
    {
        for (int i = 0; i < movieCount; ++i)
        {
            if (movies[i].getName() == Name)
            {
                if (movies[i].getAvailableSeats() < numSeats)
                {
                    cout << "\nSorry, only " << movies[i].getAvailableSeats() << " seats are available for this movie." << endl;
                    return false;
                }

                string bookingTime = getTimeString();

                movies[i].bookTicket(numSeats);
                CustomerData customerData(customerID, Name, movies[i].getPrice(), numSeats, movies[i].gettime(), bookingTime);
                saveCustomerData(customerData);

                saveMoviesToFile();
                // cout << numSeats << " ticket(s) booked successfully!" << endl;
                return true;
            }
        }
        cout << "\nMovie not found!" << endl;
        return false;
    }

    void viewBookings(const string &customerID)
    {
        ifstream inputFile("Data.txt");

        if (inputFile.is_open())
        {
            string id, Name, price, seats, movieTime, bookingTime;
            bool found = false;

            while (!inputFile.eof())
            {
                getline(inputFile, id);
                if (id == customerID)
                {
                    found = true;

                    getline(inputFile, Name);
                    getline(inputFile, price);
                    getline(inputFile, seats);
                    getline(inputFile, movieTime);
                    getline(inputFile, bookingTime);

                    cout << "\n\n          MOVIE TICKET\n" << endl;
                    cout << "    Movie Name           : " << Name << endl;
                    cout << "    No of Seats          : " << seats << endl;
                    cout << "    Price per Ticket     : $" << price << endl;
                    cout << "    Movie Timing         : " << movieTime << endl;
                    cout << "    Issue Date           : " << bookingTime << endl;
                }
            }

            inputFile.close();
            if (!found)
            {
                cout << "No booking found for this CNIC." << endl;
            }
        }
        else
        {
            cout << "Error opening file. No booking data found." << endl;
        }
    }

    void showMovieTime() const
    {
        cout << "\n\t\tMovies Time\n"
             << endl;
        for (int i = 0; i < movieCount; ++i)
        {
            cout << "\tMovie         : " << movies[i].getName() << endl;
            cout << "\tMovie Time    : " << movies[i].gettime() << endl;
            cout << "\t-----------------------\n" << endl;
        }
    }

    void showTicketPrice() const
    {
        cout << "\n\t\tMovies Price\n"
             << endl;
        for (int i = 0; i < movieCount; ++i)
        {
            cout << "\tMovie         : " << movies[i].getName() << endl;
            cout << "\tMovie Price   : $" << movies[i].getPrice() << endl;
            cout << "\t-----------------------\n" << endl;
        }
    }

    void checkAvailableSeats() const
    {
        cout << "Check Available Seats" << endl;

        cout << "\n\t\tAvailable Seats\n"
             << endl;
        for (int i = 0; i < movieCount; ++i)
        {
            cout << "\tMovie             : " << movies[i].getName() << endl;
            cout << "\tAvailable Seats   : " << movies[i].getAvailableSeats() << endl;
            cout << "\t-----------------------\n" << endl;
        }
    }

    void loadMoviesFromFile()
    {
        ifstream file(FILENAME);
        if (file.is_open())
        {
            file >> movieCount;
            file.ignore();

            for (int i = 0; i < movieCount; ++i)
            {
                Movie movie;
                movie.loadFromFile(file);
                movies[i] = movie;
            }
            file.close();
        }
        else
        {
            cout << "Error opening file. No movie data loaded." << endl;
        }
    }

    void saveMoviesToFile() const
    {
        ofstream file(FILENAME);
        if (file.is_open())
        {
            file << movieCount << endl;
            for (int i = 0; i < movieCount; ++i)
            {
                movies[i].saveToFile(file);
            }
            file.close();
        }
        else
        {
            cout << "Error opening file. Movie data not saved." << endl;
        }
    }

    void saveCustomerData(const CustomerData &customerData)
    {
        ofstream file("Data.txt", ios::app);
        if (file.is_open())
        {
            file << customerData.getID() << endl;
            file << customerData.getMovieName() << endl;
            file << fixed << setprecision(2) << customerData.getPrice() << endl;
            file << customerData.getBookedSeats() << endl;
            file << customerData.getMovieTime() << endl;
            file << customerData.getBookingTime() << endl;
            file.close();
        }
        else
        {
            cout << "Error opening file. Customer data not saved." << endl;
        }
    }

    string getTimeString()
    {
        time_t now = time(0);
        string dt = ctime(&now);
        return dt;
    }
};

bool adminLogin()
{
    cout << "\n\n\n\n\t\t\tEnter Your CNIC Number:  ";
    string str, str2;
    str = Utility::getCnic();
    ifstream file("AdminData.txt");
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, str2);
            if (str == str2)
            {
                cout << "\nLogin successfully";
                file.close();
                return true;
            }
        }
    }
    else
    {
        cout << "Error opening file. Customer data not saved." << endl;
    }
    file.close();
    return false;
}

void adminRegister()
{
    cout << "\nEnter Your CNIC Number:  ";
    string str;

    str = Utility::getCnic();
    ofstream file("AdminData.txt", ios::app);
    if (file.is_open())
    {
        file << str << endl;
        cout << "\nRegister successfully";
        file.close();
        return;
    }
    else
    {
        cout << "Error opening file. Customer data not saved." << endl;
    }
    file.close();
    return;
}

int main()
{
    //  system("Color 0A");
    system("cls");
    BookingSystem bookingSystem;
    int choice, num;
    string customerID;

    cout << "\n\n                -------------------------------------------------------------" << endl;
    cout << "                |                                                           |" << endl;
    cout << "                |          Welcome To Movie Ticket Booking System           |" << endl;
    cout << "                |                                                           |" << endl;
    cout << "                -------------------------------------------------------------"
         << "\n\n\n";

    cout << "\n\n             1. Login as a admin" << endl;
    cout << "             0. Login as a customer" << endl;
    cout << "\n             Enter your choice: ";
    num = Utility::checknum(1);
    system("cls");

    if (num)
    {
        if (!adminLogin())
        {
            char ch;
            cout << "\nLogin Faild\n\n";
            cout << "You want to Register: (y/n):  ";
            ch = Utility::checkYN();

            if (ch == 'y' || ch == 'Y')
            {
                adminRegister();
            }
            else
            {
                main();
            }
            cout << endl;
        }
        do
        {

            cout << "\n\n             1. Add a New Movie" << endl;
            cout << "             2. Delete a Movie" << endl;
            cout << "             3. View Your Movies List" << endl;
            cout << "             4. Exit\n\n";
            cout << "Enter your choice: ";
            choice = Utility::checknum(4);
            system("cls");

            switch (choice)
            {
            case 1:
            {
                string Name, description, Time;
                double price;
                int availableSeats;

                cout << "\n\t\tEnter the movie Name                      : ";
                // cin.ignore();
                Name = Utility::checkChar();

                cout << "\n\t\tEnter the movie description               : ";
                description = Utility::checkChar();

                cout << "\n\t\tEnter the Date, in this format (DD/MM)    : ";
                Time = Utility::getdata();

                cout << "\n\t\tEnter the ticket price                    : ";
                price = Utility::getprice();

                cout << "\n\t\tEnter the available seats                 : ";
                availableSeats = Utility::getprice();
                cout << endl;
                bookingSystem.addMovie(Name, description, Time, price, availableSeats);
                break;
            }
            case 2:
            {
                string Name;
                cout << "\n\t\tEnter the movie Name to delete: ";

                Name = Utility::checkChar();
                bookingSystem.deleteMovie(Name);
                break;
            }
            case 3:
            {
                bookingSystem.showMovieList();
                break;
            }
            case 4:
            {
                cout << "Exiting the program. Thank you for using the Movie Ticket Booking System!" << endl;
                main();
            }
            default:
            {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
            }
        } while (true);
    }
    else
    {
        // Customer Section
        cout << "\n\n             Enter your CNIC Number: ";
        customerID = Utility::getCnic();
        system("cls");

        do
        {
            cout << "\n\n             1. Book a Ticket" << endl;
            cout << "             2. View your Bookings" << endl;
            cout << "             3. View Movie Date" << endl;
            cout << "             4. Price for Tickets" << endl;
            cout << "             5. Check Available Seats" << endl;
            cout << "             6. Show Movies List" << endl;
            cout << "             7. Exit\n\n";
            cout << "Enter your choice: ";
            choice = Utility::checknum(7);
            system("cls");

            switch (choice)
            {
            case 1:
            {
                string movieName;
                int numSeats;
                cout << "\n          Select a movie to book a ticket:" << endl;
                bookingSystem.showMovieList();

                cout << "Enter the movie Name                          : ";
                movieName = Utility::checkChar();

                cout << "\nEnter the number of seats you want to book     : ";
                numSeats = Utility::getprice();
                cout << endl;

                if (bookingSystem.bookTicket(movieName, numSeats, customerID))
                {
                    cout <<"\n"<< numSeats << " ticket(s) booked successfully!" << endl;
                }
                // else
                // {
                //     cout << "Ticket booking failed. Please try again." << endl;
                // }
                break;
            }
            case 2:
            {
                bookingSystem.viewBookings(customerID);
                break;
            }
            case 3:
            {
                bookingSystem.showMovieTime();
                break;
            }
            case 4:
            {
                bookingSystem.showTicketPrice();
                break;
            }
            case 5:
            {
                bookingSystem.checkAvailableSeats();
                break;
            }
            case 6:
            {
                bookingSystem.showMovieList();
                break;
            }
            case 7:
            {
                cout << "Exiting the program. Thank you for using the Movie Ticket Booking System!" << endl;
                main();
            }
            default:
            {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
            }
        } while (true);
    }

    return 0;
}
