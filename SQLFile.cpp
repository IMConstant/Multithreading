//
// Created by koko on 19.07.19.
//

#include "SQLFile.h"

SQLFile::SQLFile(std::string _file_name) : file_name(_file_name), session(nullptr) {
    Poco::Data::SQLite::Connector::registerConnector();
    session = new Session("SQLite", "simple.db");

    *session << "DROP TABLE IF EXISTS Arrays", now;
    *session << "CREATE TABLE Arrays (Address VARCHAR(255))", now;
}

void SQLFile::add(std::string str) {
    Statement insert(*session);

    insert << "INSERT INTO Arrays VALUES(?)", use(str);
    insert.execute();
}