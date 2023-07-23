#include <bits/stdc++.h>
using namespace std;

const int MAX_MOVIES = 10;
const string FILENAME = "movies.txt";

class Movie
{
private:
    int Seats;
    string ID;
    time_t now = time(0);
    string dt = ctime(&now);

    string title;
    string description;
    string timings;
    double price;
    int availableSeats;

public:
    Movie() {}

    Movie(string &movieTitle, string &movieDescription, string &movieTimings, double moviePrice, int seatsAvailable)
    {
        title = movieTitle;
        description = movieDescription;
        timings = movieTimings;
        price = moviePrice;
        availableSeats = seatsAvailable;
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
        return availableSeats;
    }

    void setData()
    {
        cin.ignore();
        cout << "Enter CNIC Number without Dashes               : ";
        cin >> ID;

        ifstream input("Data.txt");
        string find;
        if (input.is_open())
        {
            while (getline(input, find))
            {
                if (find.length() > 0)
                {
                    if (find == ID)
                    {
                        cout << "Already Booked a ticket in this CNIC Please use another CNIC" << endl;
                        setData();
                    }
                }
            }

            input.close();
        }

        ofstream file("Data.txt", ios::app);
        if (file.is_open())
        {
            file << ID << endl;
            file << title << endl;
            file << price << endl;
            file << Seats << endl;
            file << timings << endl;
            file << dt << endl;
            file.close();
        }
        else
        {
            cout << "Error opening file. Movie data not saved." << endl;
        }
    }

    void bookTicket()
    {
        if (availableSeats == 0)
        {
            cout << "Sorry, no seats available for this movie." << endl;
            return;
        }

        cout << "Enter Numbers of Seats you want to booked      : ";
        cin >> Seats;
        if (availableSeats >= Seats)
        {
            setData();
            availableSeats -= Seats;
            cout << "   Ticket booked successfully!" << endl;
        }
        else
        {
            cout << "\t\t\t\t\t\t\tOnly " << availableSeats << " Seats are left" << endl;
            bookTicket();
        }
    }

    void saveToFile(ofstream &file) const

    {

        file << title << endl;
        file << description << endl;
        file << timings << endl;
        file << price << endl;
        file << availableSeats << endl;
    }

    void loadFromFile(ifstream &file)
    {
        getline(file, title);
        getline(file, description);
        getline(file, timings);
        file >> price;
        file >> availableSeats;
        file.ignore();
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

    void addMovie(string &title, string &description, string &timings, double &price, int &availableSeats)
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

    void bookTicket(const string &title)
    {
        for (int i = 0; i < movieCount; ++i)
        {
            if (movies[i].getTitle() == title)
            {
                movies[i].bookTicket();
                saveMoviesToFile();
                return;
            }
        }
        cout << "Movie not found!" << endl;
    }

    void loadMoviesFromFile()
    {

        ifstream file("movies.txt");
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
        ofstream file("movies.txt");
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

    void viewBookings()
    {
        string ID, tital, price, movie_time, booking_time, seats;
        bool flag = false;
        ifstream input("Data.txt");
        string find;

        cout << "\n\t    Enter your CNIC Number: ";
        cin >> ID;

        if (input.is_open())
        {

            while (getline(input, find))
            {

                if (find.length() > 0)
                {
                    if (find == ID)
                    {
                        getline(input, tital);
                        getline(input, price);
                        getline(input, seats);
                        getline(input, movie_time);
                        getline(input, booking_time);
                        flag = true;
                        break;
                    }
                }
            }

            input.close();
        }
        if (flag)
        {
            cout << "\n          MOVIE TICKET" << endl;
            cout << "    Movie Name      : " << tital << endl;
            cout << "    No of Seats     : " << seats << endl;
            cout << "    Price           : " << price << " USD" << endl;
            cout << "    Movie Timing    : " << movie_time << endl;
            cout << "    Issue Date      : " << booking_time << endl;
        }
        else
        {
            cout << "No Booking in this CNIC ";
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
            cout << "\tMovie Price   : " << movies[i].getPrice() << endl;
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
};

int main()
{
    system("cls");
    MovieTicketBookingSystem bookingSystem;
    int choice, num;

    cout << "\n\n				-------------------------------------------------------------" << endl;
    cout << "				|                                                           |" << endl;
    cout << "				|          Welcome To Movie Ticket Booking System           |" << endl;
    cout << "				|                                                           |" << endl;
    cout << "				-------------------------------------------------------------"
         << "\n\n\n";

    cout << "\n\n             1. Login as a admin" << endl;
    cout << "             0. Login as a Customer" << endl;
    cout << "\n             Enter your choice: ";
    cin >> num;
    system("cls");
    if (num)
    {
        do
        {

            cout << " \n\n             1. Add a New Movie" << endl;
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
                break;
            }
            default:
            {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
            }
        } while (true);
    }
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
            cout << "\n          Select a movie to book a ticket:" << endl;
            bookingSystem.showMovieList();

            string movieTitle;
            cout << "Enter the movie title                          : ";
            cin.ignore();
            getline(cin, movieTitle);

            bookingSystem.bookTicket(movieTitle);
            break;
        }
        case 2:
        {
            bookingSystem.viewBookings();
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
            break;
        }
        default:
        {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }
    } while (true);
    return 0;
}
