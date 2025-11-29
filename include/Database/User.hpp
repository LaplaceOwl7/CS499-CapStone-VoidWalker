#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <optional>
#include <sqlite3.h>

namespace Auth {

/// @brief  Data structure to contain user infor
struct User {
    std::string username;
    bool is_admin;
};

/**
 * @brief Prompts the user to log in and verifies credentials against the database.
 * @param t_db SQLite connection.
 * @return A User object if authentication succeeds; std::nullopt if failed.
 */
std::optional<User> promptLogin(sqlite3* t_db);

}

#endif // USER_HPP
