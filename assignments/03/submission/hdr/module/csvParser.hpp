#ifndef __CSVPARSER_HPP
#define __CSVPARSER_HPP

/*************************************************************************
 * NAME: CSVPARSER MODULE
 * AUTHOR: CHARLES NORDEN
 * DESCRIPTION: a csv data processor.
 * FUNCTIONALITY:
 * This processor does the following tasks:
 *  1. OPEN FILE STREAM:
 *      - Accept an filepath (passed as string)
 *      - Open a *.csv file-stream at that path
 *          (MUST check if opening was SUCCESSFULLY)
 *
 *  2.a EXTRACT A LINE OF RAW STRING:
 *      - Scan each line with the delimiter '\n'
 *
 *  2.b PROCESS RAW STRING INTO STRINGS OF DATA TYPES:
 *      - Process the line into smaller strings separated by ','
 *
 *  2.c STORE THE STRING PACKETS:
 *      - Push each string to its own <string>vector
 *      - Push the <strings>vector into a container of <strings>vectors
 *
 * ----------------------------------------------------------------------
 * FUTURE: BETTER RESETSTREAM BEHAVIOR. (In case input is refreshed)
 *         REWRITE THE DATABASE WITH HASHING AND MAPPING.
 *         BETTER IMPLEMENTATION OF OMP.
 * ----------------------------------------------------------------------
 * VER: 0.1.5     2021/01/11
 *      Changed to a better versioning convention.
 *      Changed a converter template function to be copy assignment
 *
 * VER: 0.1.4     2020/11/28
 *      Changed the the converter function to be better typed-safe.
 * 
 * VER: 0.1.3     2020/11/28 Decluttered this template.
 *      Tightened up the access privilege into the input stream.
 *      Made the input stream a pure ifstream.
 *      Added a namspace for error messages. Initial implementation of
 *      openMP to database destruction.
 *
 * VER: 0.1.2     2020/11/27
 *      Added a function overload for the string-to-data converter function.
 *
 * VER: 0.1.1     2020/11/23
 *      Fixed the raw validation function to be safer.
 *      Minor update to template string-to-data converter function.
 *      Initial implementation of Doxygen style to descriptions.
 *
 * VER: 0.1.0      2020/11/16
 *      First complete version.
 *
 * VER: 0.0.6     2020/11/11
 *      Fixed namespace std error. Prefixed all containers with <std::>.
 *
 * VER: 0.0.5     2020/11/05
 *      Implemented clearer naming convention for various functions
 *
 * VER: 0.0.4     2020/11/02
 *      Changed the format of the hidden functions.
 *
 * VER: 0.0.3     2020/11/01
 *      Added an overloaded constructor in case delimiter not supplied.
 *
 * VER: 0.0.2     2020/11/01
 *      FIXED THE RETURN CARRIAGE BUG.
 *
 * PROTOTYPE VERSION 0.0.1 COMPLETED 2020/10/31.
 *
 *************************************************************************/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <omp.h>
#include <sstream>
#include <list>
#include <vector>

namespace parser_err {
const std::string WRONG_FILEPATH = "ERROR: NO SOURCE FOUND AT GIVEN PATH.\n";
const std::string NO_DATA_FOUND = "ERROR: NEGATIVE VALUE GIVEN FOR COLUMNS.\n";
} // namespace parser_err

const char DEFAULT_COLUMNS_SEPARATOR = ',';

using namespace parser_err;

/*************************************************************************
 * @brief Class Container for streaming *.csv as input.
 *        Only the parser has internal access to this container.
 */
class csvStream {
private:
  // (internal) Open input stream.
  void _openStream() { inStream.open(filepath); }

protected:
  std::string filepath;
  std::ifstream inStream;

  // Check if stream is open.
  void e_isOpenStream() {
    if (!inStream.is_open()) {
      std::cerr << parser_err::WRONG_FILEPATH;
      exit(1);
    }
  }

  // (internal) Reset input stream.
  void resetStream() {
    inStream.close();
    _openStream();
    e_isOpenStream();
  }

  // Close input stream.
  void closeStream() { inStream.close(); }

  /**
   * @brief Construct a new csv Stream object
   * @param path
   */
  explicit csvStream(const std::string &path) : filepath{path} {
    _openStream();
    e_isOpenStream();
  }

public:
  ~csvStream() = default;
};

/*************************************************************************
 * @brief Class Container for extracting raw data from an open csvStream.
 *        Data are extracted into packets of strings.
 */
template <typename D> class csvParser : protected csvStream {
private:
  int columns = -1; // default -1 in case no data in file.
  char column_wall;
  std::string raw_line;

  // Interface for accessing extracted string data.
  std::vector<std::list<std::string>> database;

  // Unload database from memory.
  void _clearDatabase() {
    database.clear();
  }

  // Get the number of column splitters.
  void _getNumsColSplitters() {
    std::getline(inStream, raw_line);
    for (auto ch : raw_line) { columns += (ch == column_wall) ? 1 : 0; }
      //if (ch == column_wall)
        //++columns;
    
    e_validateRawData();
    columns += 2;
  }

  // Validate that input is not empty.
  void e_validateRawData() {
    if (columns < 0) {
      if (raw_line.size() > 1)
        return;

      std::cerr << parser_err::NO_DATA_FOUND;
      exit(1);
    }
  }

  // Extract a packet of strings and Return a reference to it.
  void _rawToStringPacket() {
    std::istringstream line_stream;
    static std::string token;

    // Create a packet at the local scope
    std::list<std::string> packet;

    // Handle the return carriage character
    size_t tail = raw_line.size() - 1;
    if (raw_line.at(tail) == '\r')
      raw_line.erase(tail);

    // Extract data packet from the line
    line_stream.str(raw_line);
    for (auto i = 0; i < columns; ++i) {
      std::getline(line_stream, token, column_wall);
      packet.push_back(token);
    }
    
    database.push_back(packet);
  }

public:
  /**
   * @brief Construct a new csv Parser object.
   * Take 3 parameters: filepath as string, the number of columns and an ASCII
   * character for the columns splitter.
   * @param filepath
   * @param num_cols
   * @param splitter
   */
  explicit csvParser(const std::string &filepath, const int num_cols, const char splitter = DEFAULT_COLUMNS_SEPARATOR)
      : csvStream(filepath), columns{num_cols}, column_wall{splitter} {
    e_validateRawData();
  }

  /**
   * @brief Construct a new csv Parser object.
   * Take 2 parameters: filepath as string and the number of columns.
   * @param filepath
   * @param splitter
   */
  explicit csvParser(const std::string &filepath, const char splitter = DEFAULT_COLUMNS_SEPARATOR)
      : csvStream(filepath), column_wall{splitter} {
    _getNumsColSplitters();
    resetStream();
  }

  // Destruct the csv Parser object
  ~csvParser() { _clearDatabase(); }

  // Extract all data while stream is open.
  void extractAllRaw() {
    this->e_isOpenStream();
    this->e_validateRawData();
    // Continue to extract data until the end of file:
    while (std::getline(inStream, raw_line)) {
      _rawToStringPacket();
    }
    closeStream();
  }

  bool DEBUG_isOpenStream() { return this->inStream.is_open(); }

  /**
   * @brief Access the database interface.
   * @return vector<vector<string>*>&
   */
  std::vector<std::list<std::string>> &accessDB() { return this->database; }

  /**
   * @brief TEMPLATE: Implement as needed. Convert a string packet at given
   * index to a real operating datum.
   * @param datum
   * @param index
   */
  void convertRaw(D &datum, size_t index);

  /**
   * @brief TEMPLATE: Implement as needed. Convert a string packet at given
   * index to a real operating datum.
   * @param index
   * @return D
   */
  D convertRaw(size_t index);
};

#endif
