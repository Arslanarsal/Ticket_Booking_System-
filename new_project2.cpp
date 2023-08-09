#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <conio.h>
class MovieTicketBookingSystem;

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
    string title;
    string description;
    string timings;
    double price;
    Seats seats;

public:
    Movie() {}

    Movie(const string &movieTitle, const string &movieDescription, const string &movieTimings, double moviePrice, int seatsAvailable)
    {
        title = movieTitle;
        description = movieDescription;
        timings = movieTimings;
        price = moviePrice;
        seats.SetSeats(seatsAvailable);
    }

    string getTitle() const
    {
        return title;
    }

    string getDescription() const
    {
        return description;
    }

    string getTimings() const
    {
        return timings;
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
        file << title << endl;
        file << description << endl;
        file << timings << endl;
        file << price << endl;
        file << seats.getAvailableSeats() << endl;
    }

    void loadFromFile(ifstream &file)
    {
        getline(file, title);
        getline(file, description);
        getline(file, timings);
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

// Definition of the Seats class

class CustomerData
{
private:
    string ID;
    string movieTitle;
    double price;
    int bookedSeats;
    string movieTime;
    string bookingTime;

public:
    CustomerData(const string &id, const string &title, double ticketPrice, int seats, const string &time, const string &booking)
    {
        ID = id;
        movieTitle = title;
        price = ticketPrice;
        bookedSeats = seats;
        movieTime = time;
        bookingTime = booking;
    }

    string getID() const
    {
        return ID;
    }

    string getMovieTitle() const
    {
        return movieTitle;
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

class MovieTicketBookingSystem
{
private:
    Movie movies[MAX_MOVIES];
    int movieCount = 0;

public:
    MovieTicketBookingSystem()
    {
        loadMoviesFromFile();
    }

    void addMovie(const string &title, const string &description, const string &timings, double price, int availableSeats)
    {
        if (movieCount < MAX_MOVIES)
        {
            Movie movie(title, description, timings, price, availableSeats);
            movies[movieCount++] = movie;
            cout << "Movie added successfully!" << endl;
            saveMoviesToFile();
        }
        else
        {
            cout << "Maximum movie limit reached. Cannot add more movies." << endl;
        }
    }

    void deleteMovie(const string &title)
    {
        for (int i = 0; i < movieCount; ++i)
        {
            if (movies[i].getTitle() == title)
            {
                for (int j = i; j < movieCount - 1; ++j)
                {
                    movies[j] = movies[j + 1];
                }
                movieCount--;
                cout << "Movie deleted successfully!" << endl;
                saveMoviesToFile();
                return;
            }
        }
        cout << "Movie not found!" << endl;
    }

    void showMovieList() const
    {
        if (movieCount == 0)
        {
            cout << "No movie available\n";
            return;
        }

        cout << "Movie List:\n\n";
        for (int i = 0; i < movieCount; ++i)
        {
            if (movies[i].getAvailableSeats() == 0)
            {
                continue;
            }

            cout << "      Title                 : " << movies[i].getTitle() << endl;
            cout << "      Description           : " << movies[i].getDescription() << endl;
            cout << "      Timings               : " << movies[i].getTimings() << endl;
            cout << "      Price                 : $" << movies[i].getPrice() << endl;
            cout << "      Available Seats       : " << movies[i].getAvailableSeats() << endl;
            cout << "             -----------------------\n\n";
        }
    }

    bool bookTicket(const string &title, int numSeats, const string &customerID)
    {
        for (int i = 0; i < movieCount; ++i)
        {
            if (movies[i].getTitle() == title)
            {
                if (movies[i].getAvailableSeats() < numSeats)
                {
                    cout << "Sorry, only " << movies[i].getAvailableSeats() << " seats are available for this movie." << endl;
                    return false;
                }

                string bookingTime = getTimeString();

                movies[i].bookTicket(numSeats);
                CustomerData customerData(customerID, title, movies[i].getPrice(), numSeats, movies[i].getTimings(), bookingTime);
                saveCustomerData(customerData);

                saveMoviesToFile();
                cout << numSeats << " ticket(s) booked successfully!" << endl;
                return true;
            }
        }
        cout << "Movie not found!" << endl;
        return false;
    }

    void viewBookings(const string &customerID)
    {
        ifstream inputFile("Data.txt");
        if (inputFile.is_open())
        {
            string id, title, price, seats, movieTime, bookingTime;
            bool found = false;

            while (inputFile >> id >> title >> price >> seats >> movieTime >> bookingTime)
            {
                if (id == customerID)
                {
                    found = true;
                    cout << "\n          MOVIE TICKET" << endl;
                    cout << "    Movie Name      : " << title << endl;
                    cout << "    No of Seats     : " << seats << endl;
                    cout << "    Price           : $" << price << endl;
                    cout << "    Movie Timing    : " << movieTime << endl;
                    cout << "    Issue Date      : " << bookingTime << endl;
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

    void showMovieTimings() const
    {
        cout << "\n\t\tMovies Timing\n"
             << endl;
        for (int i = 0; i < movieCount; ++i)
        {
            cout << "\tMovie         : " << movies[i].getTitle() << endl;
            cout << "\tMovie Time    : " << movies[i].getTimings() << endl;
            cout << "\t-----------------------" << endl;
        }
    }

    void showTicketPrice() const
    {
        cout << "\n\t\tMovies Price\n"
             << endl;
        for (int i = 0; i < movieCount; ++i)
        {
            cout << "\tMovie         : " << movies[i].getTitle() << endl;
            cout << "\tMovie Price   : $" << movies[i].getPrice() << endl;
            cout << "\t-----------------------" << endl;
        }
    }

    void checkAvailableSeats() const
    {
        cout << "Check Available Seats" << endl;

        cout << "\n\t\tAvailable Seats\n"
             << endl;
        for (int i = 0; i < movieCount; ++i)
        {
            cout << "\tMovie             : " << movies[i].getTitle() << endl;
            cout << "\tAvailable Seats   : " << movies[i].getAvailableSeats() << endl;
            cout << "\t-----------------------" << endl;
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
            file << customerData.getMovieTitle() << endl;
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

int main()
{
    system("cls");
    MovieTicketBookingSystem bookingSystem;
    int choice, num;
    string customerID;

    cout << "\n\n                -------------------------------------------------------------" << endl;
    cout << "                |                                                           |" << endl;
    cout << "                |          Welcome To Movie Ticket Booking System           |" << endl;
    cout << "                |                                                           |" << endl;
    cout << "                -------------------------------------------------------------"
         << "\n\n\n";

    cout << "\n\n             1. Login as an admin" << endl;
    cout << "             0. Login as a customer" << endl;
    cout << "\n             Enter your choice: ";
    cin >> num;
    system("cls");

    if (num)
    {
        // Admin Section
        do
        {
            cout << "\n\n             1. Add a New Movie" << endl;
            cout << "             2. Delete a Movie" << endl;
            cout << "             3. View Your Movies List" << endl;
            cout << "             4. Exit\n\n";
            cout << "Enter your choice: ";
            cin >> choice;
            system("cls");

            switch (choice)
            {
            case 1:
            {
                string title, description, timings;
                double price;
                int availableSeats;

                cout << "\n\t\tEnter the movie title         : ";
                cin.ignore();
                getline(cin, title);

                cout << "\t\tEnter the movie description   : ";
                getline(cin, description);

                cout << "\t\tEnter the movie timings       : ";
                getline(cin, timings);

                cout << "\t\tEnter the ticket price        : ";
                cin >> price;

                cout << "\t\tEnter the available seats     : ";
                cin >> availableSeats;

                bookingSystem.addMovie(title, description, timings, price, availableSeats);
                break;
            }
            case 2:
            {
                string title;
                cout << "\n\t\tEnter the movie title to delete: ";
                cin.ignore();
                getline(cin, title);
                bookingSystem.deleteMovie(title);
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
            cout << "             3. Movie Timings" << endl;
            cout << "             4. Price for Tickets" << endl;
            cout << "             5. Check Available Seats" << endl;
            cout << "             6. Show Movies List" << endl;
            cout << "             7. Exit\n\n";
            cout << "Enter your choice: ";
            cin >> choice;
            system("cls");

            switch (choice)
            {
            case 1:
            {
                string movieTitle;
                int numSeats;
                cout << "\n          Select a movie to book a ticket:" << endl;
                bookingSystem.showMovieList();

                cout << "Enter the movie title                          : ";
                cin.ignore();
                getline(cin, movieTitle);

                cout << "Enter the number of seats you want to book     : ";
                cin >> numSeats;

                if (bookingSystem.bookTicket(movieTitle, numSeats, customerID))
                {
                    cout << numSeats << " ticket(s) booked successfully!" << endl;
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
                bookingSystem.showMovieTimings();
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

// class Utility
// {
// public:
//     static string getCnic()
//     {
//         char ch[14];
//         char temp;
//         int i = 0;
//         while (i < 13)
//         {
//             temp = getch();
//             if (temp >= '0' && temp <= '9')
//             {
//                 cout << temp;
//                 ch[i] = temp;
//                 i++;
//             }
//             else if (temp == '\b')
//             {
//                 cout << "\b \b";
//                 i--;
//             }
//         }
//         ch[i] = '\0';
//         string str = ch;
//         return str;
//     }
// };
