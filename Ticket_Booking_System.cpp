#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_MOVIES = 10;
const string FILENAME = "movies.txt";

class Movie
{
private:
    string title;
    string description;
    string timings;
    double price;
    int availableSeats;

public:
    Movie() {}

    Movie(const string &movieTitle, const string &movieDescription, const string &movieTimings, double moviePrice, int seatsAvailable)
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

    void bookTicket()
    {
        if (availableSeats > 0)
        {
            availableSeats--;
            cout << "Ticket booked successfully!" << endl;
        }
        else
        {
            cout << "Sorry, no seats available for this movie." << endl;
        }
    }

    // Function to save movie data to a file
    void saveToFile(ofstream &file) const
    // void saveToFile()
    {
        // ofstream file("movies.txt");
        file << title << endl;
        file << description << endl;
        file << timings << endl;
        file << price << endl;
        file << availableSeats << endl;
    }

    // Function to load movie data from a file
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
    int movieCount;

public:
    MovieTicketBookingSystem()
    {
        loadMoviesFromFile();
    }

    void addMovie(string &title, const string &description, const string &timings, double &price, int &availableSeats)
    {
        if (movieCount < MAX_MOVIES)
        {
            Movie movie(title, description, timings, price, availableSeats);
            movies[movieCount++] = movie;
            cout << "Movie added successfully!" << endl;
            saveMoviesToFile(); // Save movie data to file after adding a new movie
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
                saveMoviesToFile(); // Save movie data to file after deleting a movie
                return;
            }
        }
        cout << "Movie not found!" << endl;
    }

    void showMovieList() const
    {
        cout << "Movie List:" << endl;
        for (int i = 0; i < movieCount; ++i)
        {
            cout << "Title: " << movies[i].getTitle() << endl;
            cout << "Description: " << movies[i].getDescription() << endl;
            cout << "Timings: " << movies[i].getTimings() << endl;
            cout << "Price: $" << movies[i].getPrice() << endl;
            cout << "Available Seats: " << movies[i].getAvailableSeats() << endl;
            cout << "-----------------------" << endl;
        }
    }

    void bookTicket(const string &title)
    {
        for (int i = 0; i < movieCount; ++i)
        {
            if (movies[i].getTitle() == title)
            {
                movies[i].bookTicket();
                saveMoviesToFile(); // Save movie data to file after booking a ticket
                return;
            }
        }
        cout << "Movie not found!" << endl;
    }

    // Function to load movie data from the file
    void loadMoviesFromFile()
    {
        // const string FILENAME = ;
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

    // Function to save movie data to the file
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

    void viewBookings() const
    {
        // Implementation for viewing bookings
        cout << "View your Bookings" << endl;
    }

    void showMovieTimings() const
    {
        // Implementation for showing movie timings
        cout << "Movie Timings" << endl;
    }

    void showTicketPrice() const
    {
        // Implementation for showing ticket prices
        cout << "Price for Tickets" << endl;
    }

    void checkAvailableSeats() const
    {
        cout << "Check Available Seats" << endl;
        // Implementation for checking available seats

        cout << "Available Seats:" << endl;
        for (int i = 0; i < movieCount; ++i)
        {
            cout << "Movie: " << movies[i].getTitle() << endl;
            cout << "Available Seats: " << movies[i].getAvailableSeats() << endl;
            cout << "-----------------------" << endl;
        }
    }

    void getMembership()
    {
        // Implementation for getting a membership
        cout << "Get a Membership" << endl;
    }
};

int main()
{
    MovieTicketBookingSystem bookingSystem;
    int choice;

    do
    {
        cout << "---------- Movie Ticket Booking System ----------" << endl;
        cout << "1. Book a Ticket" << endl;
        cout << "2. View your Bookings" << endl;
        cout << "3. Movie Timings" << endl;
        cout << "4. Price for Tickets" << endl;
        cout << "5. Check Available Seats" << endl;
        cout << "6. Add a New Movie" << endl;
        cout << "7. Delete a Movie" << endl;
        cout << "8. Show Movies List" << endl;
        cout << "9. Get a Membership" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Select a movie to book a ticket:" << endl;
            bookingSystem.showMovieList();

            string movieTitle;
            cout << "Enter the movie title: ";
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
            string title, description, timings;
            double price;
            int availableSeats;

            cout << "Enter the movie title: ";
            cin.ignore();
            getline(cin, title);

            cout << "Enter the movie description: ";
            getline(cin, description);

            cout << "Enter the movie timings: ";
            getline(cin, timings);

            cout << "Enter the ticket price: ";
            cin >> price;

            cout << "Enter the available seats: ";
            cin >> availableSeats;

            bookingSystem.addMovie(title, description, timings, price, availableSeats);
            break;
        }
        case 7:
        {
            string title;
            cout << "Enter the movie title to delete: ";
            cin.ignore();
            getline(cin, title);
            bookingSystem.deleteMovie(title);
            break;
        }
        case 8:
        {
            bookingSystem.showMovieList();
            break;
        }
        case 9:
        {
            bookingSystem.getMembership();
            break;
        }
        case 10:
        {
            cout << "Exiting the program. Thank you for using the Movie Ticket Booking System!" << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }

    } while (choice != 10);

    return 0;
}
