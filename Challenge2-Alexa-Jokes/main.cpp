#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// This is a function to read jokes from the text file
vector<string> loadJokes() {
    vector<string> jokes;
    ifstream file("randomJokes.txt");
    string line;

    // This checks if the file opened correctly
    if (!file.is_open()) {
        cout << "Error: Could not open randomJokes.txt" << endl;
        return jokes;
    }

    // This reads each joke and store it in a vector
    while (getline(file, line)) {
        if (!line.empty() && line.find('?') != string::npos) {
            jokes.push_back(line);
        }
    }

    file.close();
    return jokes;
}

// This is a function to select and display a random joke
void tellJoke(const vector<string>& jokes) {
    int randomIndex = rand() % jokes.size();
    string joke = jokes[randomIndex];

    // This separates the question from the punchline
    size_t position = joke.find('?');
    string setup = joke.substr(0, position + 1);
    string punchline = joke.substr(position + 1);

    cout << "\nAlexa: " << setup << endl;
    cout << "\nPress Enter to hear the punchline...";

    // This waits for the user before showing the answer
    string input;
    getline(cin, input);

    cout << "\nAlexa: " << punchline << endl;
}

int main() {
    // This starts the random number generator
    srand(time(0));

    cout << "==================================" << endl;
    cout << "        Alexa Joke Generator      " << endl;
    cout << "==================================" << endl;

    cout << "\nWelcome to the Alexa Joke Generator!" << endl;
    cout << "Type 'Alexa, tell me a joke' to hear a joke." << endl;
    cout << "Type 'quit' to exit the program." << endl;

    // This load the jokes from the text file
    vector<string> jokes = loadJokes();

    if (jokes.empty()) {
        cout << "\nNo jokes were found. Program closing." << endl;
        return 1;
    }

    string command;

    // This keeps asking for commands until the user quits
    while (true) {
        cout << "\nEnter your command: ";
        if (!getline(cin, command)) {
            break;
        }

        // This accepts the command with or without a comma
        if (command == "Alexa, tell me a joke" ||
            command == "Alexa tell me a joke") {
            tellJoke(jokes);
        }
        else if (command == "quit") {
            cout << "\nThank you for using the Joke Generator!" << endl;
            break;
        }
        else {
            cout << "Unknown command. Please try again." << endl;
        }
    }

    return 0;
}
