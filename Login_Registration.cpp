#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct User {
    std::string username;
    std::string password;
};

void registerUser(const std::string& username, const std::string& password) {
    std::ofstream userFile("users.txt", std::ios::app); // Open file in append mode

    if (!userFile.is_open()) {
        std::cout << "Error: Could not open/create user file.\n";
        return;
    }

    userFile << username << ":" << password << "\n";
    userFile.close();
    std::cout << "User registered successfully!\n";
}

bool loginUser(const std::string& username, const std::string& password) {
    std::ifstream userFile("users.txt");
    std::string line;

    while (std::getline(userFile, line)) {
        std::istringstream iss(line);
        std::string storedUsername, storedPassword;
        std::getline(iss, storedUsername, ':');
        std::getline(iss, storedPassword);

        if (storedUsername == username && storedPassword == password) {
            userFile.close();
            return true; // Login successful
        }
    }

    userFile.close();
    return false; // User not found or incorrect password
}

int main() {
    char choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case '1': {
            std::string newUsername, newPassword;
            std::cout << "Enter username: ";
            std::cin >> newUsername;
            std::cout << "Enter password: ";
            std::cin >> newPassword;
            registerUser(newUsername, newPassword);
            break;
        }
        case '2': {
            std::string inputUsername, inputPassword;
            std::cout << "Enter username: ";
            std::cin >> inputUsername;
            std::cout << "Enter password: ";
            std::cin >> inputPassword;

            if (loginUser(inputUsername, inputPassword)) {
                std::cout << "Login successful!\n";
            }
            else {
                std::cout << "Login failed. Invalid username or password.\n";
            }
            break;
        }
        case '3':
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '3');

    return 0;
}
