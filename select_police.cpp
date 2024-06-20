/**
 * 
 * PHP-код, который открывает файл .mdb и выводит данные из таблицы policy с помощью SELECT-запроса:
 * 
 * g++ -o mdb_example select_police.cpp -lodbc
 * 
*/

#include <iostream>
#include <string>
#include <sql.h>
#include <sqlext.h>

int main() {
    std::string dbPath = "path_to_your_database.mdb"; // Установите путь к вашей базе данных
    std::string dsn = "DRIVER={Microsoft Access Driver (*.mdb)}; DBQ=" + dbPath;

    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;

    // Инициализация ODBC
    SQLRETURN ret = SQLAllocEnv(&env);
    if (ret != SQL_SUCCESS) {
        std::cerr << "Error allocating environment handle: " << ret << std::endl;
        return 1;
    }

    ret = SQLAllocConnect(env, &dbc);
    if (ret != SQL_SUCCESS) {
        std::cerr << "Error allocating connection handle: " << ret << std::endl;
        SQLFreeEnv(env);
        return 1;
    }

    // Установка соединения
    ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*)dsn.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "Error connecting to database: " << ret << std::endl;
        SQLFreeConnect(dbc);
        SQLFreeEnv(env);
        return 1;
    }

    // Формирование SELECT-запроса
    std::string query = "SELECT * FROM police";

    // Выполнение запроса
    ret = SQLAllocStmt(dbc, &stmt);
    if (ret != SQL_SUCCESS) {
        std::cerr << "Error allocating statement handle: " << ret << std::endl;
        SQLDisconnect(dbc);
        SQLFreeConnect(dbc);
        SQLFreeEnv(env);
        return 1;
    }

    ret = SQLExecDirect(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS) {
        std::cerr << "Error executing query: " << ret << std::endl;
        SQLFreeStmt(stmt, SQL_DROP);
        SQLDisconnect(dbc);
        SQLFreeConnect(dbc);
        SQLFreeEnv(env);
        return 1;
    }

    // Вывод результатов
    SQLSMALLINT columns;
    ret = SQLNumResultCols(stmt, &columns);
    if (ret != SQL_SUCCESS) {
        std::cerr << "Error getting column count: " << ret << std::endl;
        SQLFreeStmt(stmt, SQL_DROP);
        SQLDisconnect(dbc);
        SQLFreeConnect(dbc);
        SQLFreeEnv(env);
        return 1;
    }

    std::cout << "Results:" << std::endl;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        for (SQLSMALLINT i = 1; i <= columns; i++) {
            SQLCHAR buf[1024];
            SQLLEN indicator;
            ret = SQLGetData(stmt, i, SQL_CHAR, buf, 1024, &indicator);
            if (ret != SQL_SUCCESS) {
                std::cerr << "Error getting data: " << ret << std::endl;
                break;
            }
            std::cout << buf << " ";
        }
        std::cout << std::endl;
    }

    // Закрытие соединения
    SQLFreeStmt(stmt, SQL_DROP);
    SQLDisconnect(dbc);
    SQLFreeConnect(dbc);
    SQLFreeEnv(env);

    return 0;
}