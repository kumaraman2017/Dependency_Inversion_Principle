#include <iostream>
using namespace std;

// Abstraction (Interface)
/*
This demonstrates the Dependency Inversion Principle. UserService, the high-level module,
 depends on the Database abstraction rather than directly depending on MySQL or MongoDB.
 The concrete database implementation is injected through the constructor,
  which is Dependency Injection.
*/
class Database {
public:
    virtual void save(string data) = 0; // Pure virtual function
};

// MySQL implementation (Low-level module)
class MySQLDatabase : public Database {
public:
    void save(string data) override {
        cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');" << endl;
    }
};

// MongoDB implementation (Low-level module)
class MongoDBDatabase : public Database {
public:
    void save(string data) override {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

// High-level module (Now loosely coupled)
class UserService {
private:
    Database* db;  // Dependency Injection

public:
    UserService(Database* database) {  
        db = database;
    }
    
    void storeUser(string user) {
        db->save(user);
    }
};

int main() {
    MySQLDatabase mysql;
    MongoDBDatabase mongodb;

    UserService service1(&mysql);
    service1.storeUser("Aditya");

    UserService service2(&mongodb);
    service2.storeUser("Rohit");
}