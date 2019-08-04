cmake_minimum_required(VERSION 3.10)
project(SQLRPS)

set(CMAKE_CXX_STANDARD 11)

set(Poco_DIR "/usr/local/lib/cmake/")
set(Poco_INCLUDE_DIRS "/usr/include/Poco/")

find_package(Poco REQUIRED COMPONENTS Data Foundation Net XML Util DataSQLite)

#INCLUDE_DIRECTORIES("/usr/include/openssl")
INCLUDE_DIRECTORIES("/usr/local/include/Poco")

add_executable(ReversePairSequence Test1/source.cpp)
target_link_libraries(ReversePairSequence ${Poco_LIBRARIES})

add_executable(${PROJECT_NAME} main.cpp DataBase.cpp DataBase.h)
target_link_libraries(${PROJECT_NAME} ${Poco_LIBRARIES})
