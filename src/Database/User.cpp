#include "Database/User.hpp"
#include <iostream>

namespace Auth {
std::optional<User> promptLogin(
    sqlite3* t_db
) {
    // User details
    std::string username, password;

    // Promp the User to input s/he credentials
    std::cout << "=== Login ===\n";
    std::cout << "Leave Blank for guest login\n";
    std::cout << "Username: ";
    std::getline(std::cin, username);

    // Handle specific login for guests:
    if (username.empty()){
        std::cout << "Logging in as Guest\n";
        return User{"guest", false};
    }

    std::cout << "Password: ";
    std::getline(std::cin, password);

    // Prepare the string to execute
    const std::string sql =
        "SELECT is_admin FROM users WHERE username = ? AND password = ?;";

    sqlite3_stmt* connection = nullptr;
    
    if (sqlite3_prepare_v2(t_db, sql.c_str(), -1, &connection, nullptr) != SQLITE_OK) {
        std::cout << "Login query failed.\n";
        return std::nullopt; // Q failed
    }

    sqlite3_bind_text(
        connection,
        1,
        username.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        connection,
        2,
        password.c_str(),
        -1, 
        SQLITE_TRANSIENT
    );

    if (sqlite3_step(connection) == SQLITE_ROW) {
        int is_admin = sqlite3_column_int(connection, 0);
        sqlite3_finalize(connection);
        return User{username, is_admin == 1};
    }

    sqlite3_finalize(connection);
    std::cout << "Invalid username or password.\n";
    return std::nullopt;
}

}
