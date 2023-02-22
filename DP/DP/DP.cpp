#include <iostream>
#include <memory>

class IDatabase {
public:
    virtual ~IDatabase() {}
    virtual void save(const std::string& data) = 0;
};

class SqliteDatabase : public IDatabase {
public:
    virtual void save(const std::string& data) {
        std::cout << "Saved data to SQLite database: " << data << std::endl;
    }
};

class MySQLDatabase : public IDatabase {
public:
    virtual void save(const std::string& data) {
        std::cout << "Saved data to MySQL database: " << data << std::endl;
    }
};

class User {
public:
    User(const std::string& name, const std::string& email)
        : name(name), email(email) {}
    std::string name;
    std::string email;
};

class IUserRepository {
public:
    virtual ~IUserRepository() {}
    virtual void add(const User& user) = 0;
};

class UserRepository : public IUserRepository {
public:
    UserRepository(std::shared_ptr<IDatabase> database) : database(database) {}
    virtual void add(const User& user) {
        std::string data = "User: " + user.name + ", Email: " + user.email;
        database->save(data);
    }
private:
    std::shared_ptr<IDatabase> database;
};
int main() {
    std::shared_ptr<IDatabase> database = std::make_shared<SqliteDatabase>();
    std::shared_ptr<IUserRepository> userRepository = std::make_shared<UserRepository>(database);
    userRepository->add(User("Oguzhan", "oguzhansezer14@gmail.com"));

    database = std::make_shared<MySQLDatabase>();
    userRepository = std::make_shared<UserRepository>(database);
    userRepository->add(User("Hasan", "hasan@gmail.com"));

    return 0;
}
