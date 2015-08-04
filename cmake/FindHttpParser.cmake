# FindHttpParser
# --------
#
# Find http-parser
#
# Find the http-parser includes and library.  Once done this will define
#
#   HTTP_PARSER_INCLUDE_DIRS      - where to find http-parser include, etc.
#   HTTP_PARSER_LIBRARIES         - List of libraries when using http-parser.
#   HTTP_PARSER_FOUND             - True if http-parser found.
#

find_path(HTTP_PARSER_INCLUDE_DIR NAMES http_parser.h)
find_library(HTTP_PARSER_LIBRARY NAMES http_parser)

mark_as_advanced(HTTP_PARSER_LIBRARY HTTPPARSER_INCLUDE_DIR)

# handle the QUIETLY and REQUIRED arguments and set HTTP_PARSER_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(HttpParser REQUIRED_VARS HTTP_PARSER_LIBRARY HTTP_PARSER_INCLUDE_DIR)

if(HTTPPARSER_FOUND)
    set(HTTP_PARSER_INCLUDE_DIRS ${HTTP_PARSER_INCLUDE_DIR})
    set(HTTP_PARSER_LIBRARIES ${HTTP_PARSER_LIBRARY})
endif()
