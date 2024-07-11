#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <iomanip>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    cout<<std::setprecision(20);
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;

        // Подключение к MySQL серверу
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://localhost:3306", "root", "");  

        // Создание базы данных и выбор её
        sql::Statement* stmt = con->createStatement();
        stmt->execute("DROP DATABASE IF EXISTS ConstructionCompany");  // Удаление базы данных, если она существует
        stmt->execute("CREATE DATABASE ConstructionCompany");  // Создание новой базы данных
        stmt->execute("USE ConstructionCompany");  // Выбор базы данных для использования

        // Создание таблицы проектов
        stmt->execute("CREATE TABLE IF NOT EXISTS Projects ("
            "project_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
            "name VARCHAR(255) NOT NULL, "
            "budget DECIMAL(10, 2) NOT NULL)");

        // Создание таблицы сотрудников
        stmt->execute("CREATE TABLE IF NOT EXISTS Employees ("
            "employee_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
            "name VARCHAR(255) NOT NULL, "
            "position VARCHAR(255) NOT NULL, "
            "salary DECIMAL(10, 2) NOT NULL)");

        // Создание таблицы материалов
        stmt->execute("CREATE TABLE IF NOT EXISTS Materials ("
            "material_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
            "name VARCHAR(255) NOT NULL, "
            "cost DECIMAL(10, 2) NOT NULL)");

        // Создание таблицы для связывания проектов и материалов
        stmt->execute("CREATE TABLE IF NOT EXISTS ProjectMaterials ("
            "project_id INT, "
            "material_id INT, "
            "quantity INT NOT NULL, "
            "total_cost DECIMAL(10, 2), "
            "PRIMARY KEY (project_id, material_id), "
            "FOREIGN KEY (project_id) REFERENCES Projects(project_id), "
            "FOREIGN KEY (material_id) REFERENCES Materials(material_id))");

        // Создание триггера для расчета общей стоимости материалов
        stmt->execute("CREATE TRIGGER calc_total_cost "
            "BEFORE INSERT ON ProjectMaterials "
            "FOR EACH ROW "
            "SET NEW.total_cost = (SELECT cost FROM Materials WHERE material_id = NEW.material_id) * NEW.quantity");

        // Вставка данных в таблицу проектов
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Projects (name, budget) VALUES (?, ?)");
        pstmt->setString(1, "Residential Building");
        pstmt->setDouble(2, 500000.00);
        pstmt->execute();
        pstmt->setString(1, "Office Complex");
        pstmt->setDouble(2, 1200000.00);
        pstmt->execute();
        pstmt->setString(1, "Shopping Center");
        pstmt->setDouble(2, 3000000.00);
        pstmt->execute();
        pstmt->setString(1, "Warehouse    ");
        pstmt->setDouble(2, 750000.00);
        pstmt->execute();
        pstmt->setString(1, "Sports Complex");
        pstmt->setDouble(2, 1500000.00);
        pstmt->execute();
        pstmt->setString(1, "School        ");
        pstmt->setDouble(2, 2000000.00);
        pstmt->execute();
        pstmt->setString(1, "Hospital       ");
        pstmt->setDouble(2, 2500000.00);
        pstmt->execute();
        pstmt->setString(1, "Kindergarten   ");
        pstmt->setDouble(2, 1000000.00);
        pstmt->execute();
        pstmt->setString(1, "Parking         ");
        pstmt->setDouble(2, 600000.00);
        pstmt->execute();
        pstmt->setString(1, "Administrative");
        pstmt->setDouble(2, 1800000.00);
        pstmt->execute();
        delete pstmt;

        // Вставка данных в таблицу сотрудников
        pstmt = con->prepareStatement("INSERT INTO Employees (name, position, salary) VALUES (?, ?, ?)");
        pstmt->setString(1, "Ivan Ivanov");
        pstmt->setString(2, "Engineer");
        pstmt->setDouble(3, 80000.00);
        pstmt->execute();
        pstmt->setString(1, "Maria Smirnova");
        pstmt->setString(2, "Architect");
        pstmt->setDouble(3, 90000.00);
        pstmt->execute();
        pstmt->setString(1, "Petr Petrov");
        pstmt->setString(2, "Foreman");
        pstmt->setDouble(3, 70000.00);
        pstmt->execute();
        pstmt->setString(1, "Olga Sokolova");
        pstmt->setString(2, "Designer");
        pstmt->setDouble(3, 65000.00);
        pstmt->execute();
        pstmt->setString(1, "Sergey Kuznetsov");
        pstmt->setString(2, "Manager");
        pstmt->setDouble(3, 85000.00);
        pstmt->execute();
        pstmt->setString(1, "Elena Popova");
        pstmt->setString(2, "Accountant");
        pstmt->setDouble(3, 60000.00);
        pstmt->execute();
        pstmt->setString(1, "Dmitry Lebedev");
        pstmt->setString(2, "Electrician");
        pstmt->setDouble(3, 55000.00);
        pstmt->execute();
        pstmt->setString(1, "Natalya Kozlova");
        pstmt->setString(2, "Estimator");
        pstmt->setDouble(3, 70000.00);
        pstmt->execute();
        pstmt->setString(1, "Anton Novikov");
        pstmt->setString(2, "Storekeeper");
        pstmt->setDouble(3, 50000.00);
        pstmt->execute();
        pstmt->setString(1, "Galina Morozova");
        pstmt->setString(2, "Lawyer");
        pstmt->setDouble(3, 75000.00);
        pstmt->execute();
        delete pstmt;

        // Вставка данных в таблицу материалов
        pstmt = con->prepareStatement("INSERT INTO Materials (name, cost) VALUES (?, ?)");
        pstmt->setString(1, "Concrete");
        pstmt->setDouble(2, 100.00);
        pstmt->execute();
        pstmt->setString(1, "Steel");
        pstmt->setDouble(2, 150.00);
        pstmt->execute();
        pstmt->setString(1, "Brick");
        pstmt->setDouble(2, 50.00);
        pstmt->execute();
        pstmt->setString(1, "Wood  ");
        pstmt->setDouble(2, 120.00);
        pstmt->execute();
        pstmt->setString(1, "Insulation");
        pstmt->setDouble(2, 80.00);
        pstmt->execute();
        pstmt->setString(1, "Plumbing");
        pstmt->setDouble(2, 200.00);
        pstmt->execute();
        pstmt->setString(1, "Wiring");
        pstmt->setDouble(2, 75.00);
        pstmt->execute();
        pstmt->setString(1, "Windows");
        pstmt->setDouble(2, 180.00);
        pstmt->execute();
        pstmt->setString(1, "Doors");
        pstmt->setDouble(2, 160.00);
        pstmt->execute();
        pstmt->setString(1, "Ceramic");
        pstmt->setDouble(2, 90.00);
        pstmt->execute();
        delete pstmt;

        // Вставка данных в таблицу связывания проектов и материалов
        pstmt = con->prepareStatement("INSERT INTO ProjectMaterials (project_id, material_id, quantity) VALUES (?, ?, ?)");
        for (int i = 1; i <= 10; ++i) {
            for (int j = 1; j <= 10; ++j) {
                pstmt->setInt(1, i);
                pstmt->setInt(2, j);
                pstmt->setInt(3, 100 * i);
                pstmt->execute();
            }
        }
        delete pstmt;

        cout << "Проекты:" << endl;
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Projects");
        while (res->next()) {
            cout << "ID: " << res->getInt("project_id") << " \tНазвание: " << res->getString("name") << " \tБюджет: " << res->getDouble("budget") << endl;
        }
        delete res;

        cout << "\nСотрудники:" << endl;
        res = stmt->executeQuery("SELECT * FROM Employees");
        while (res->next()) {
            cout << "ID: " << res->getInt("employee_id") << " \tИмя: " << res->getString("name") << " \tДолжность: " << res->getString("position") << " \t\tЗарплата: " << res->getDouble("salary") << endl;
        }
        delete res;

        cout << "\nМатериалы:" << endl;
        res = stmt->executeQuery("SELECT * FROM Materials");
        while (res->next()) {
            cout << "ID: " << res->getInt("material_id") << " \tНазвание: " << res->getString("name") << " \t\tСтоимость: " << res->getDouble("cost") << endl;
        }
        delete res;

        cout << "\nМатериалы по проектам:" << endl;
        res = stmt->executeQuery("SELECT * FROM ProjectMaterials");
        while (res->next()) {
            cout << "ID проекта: " << res->getInt("project_id") << " \tID материала: " << res->getInt("material_id") << " \tКоличество: " << res->getInt("quantity") << " \tОбщая стоимость: " << res->getDouble("total_cost") << endl;
        }
        delete res;

        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cerr << "Ошибка SQL: " << e.what() << endl;
    }

    return 0;
}
