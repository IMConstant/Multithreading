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

class SQLFile {
    std::string file_name;
    Session *session;

public:
    explicit SQLFile(std::string _file_name);
    ~SQLFile() {
        delete session;
    }

    void add(std::string str);
};


#endif //SQLRPS_SQLFILE_H
