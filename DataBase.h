//
// Created by koko on 19.07.19.
//

#ifndef SQLRPS_SQLFILE_H
#define SQLRPS_SQLFILE_H

#include <string>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/SessionFactory.h>

using Poco::Data::Session;
using Poco::Data::Statement;

using namespace Poco::Data::Keywords;

class DataBase {
    std::string file_name;
    Session *session;

public:
    explicit DataBase(std::string _file_name);
    ~DataBase() {
        delete session;
    }

    void add(std::string str);
};


#endif //SQLRPS_SQLFILE_H
