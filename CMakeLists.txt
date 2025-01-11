cmake_minimum_required(VERSION 3.19)

project(PaperTraderBackend)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)

# Specify paths for libcurl
set(CURL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/third_party/libcurl/include")
set(CURL_LIBRARY "${CMAKE_SOURCE_DIR}/include/third_party/libcurl/lib/libcurl_a.lib")

# Define CURL_STATICLIB to link with the static library
add_definitions(-DCURL_STATICLIB)

# Include directories for libcurl and nlohmann/json (header-only library)
include_directories(${CURL_INCLUDE_DIR} include include/third_party/json src)

# Add source files
set(SOURCES
    src/main.cpp
    src/network/StockDataFetcher.cpp
    src/core/Portfolio.cpp
    src/core/Stock.cpp
    src/utils/envparser.cpp
)

# Add header files for clarity (optional, not required for compilation)
set(HEADERS
    src/network/StockDataFetcher.h
    src/core/Portfolio.h
    src/core/Stock.h
)

# Create the backend executable
add_executable(PaperTraderBackend ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(PaperTraderBackend
    ${CURL_LIBRARY}
    ws2_32
    crypt32
    wldap32
    advapi32
    normaliz
)

# Path to your .env file
set(ENV_FILE "${CMAKE_SOURCE_DIR}/.env")

# Ensure .env is copied to the output directory
add_custom_command(
    TARGET PaperTraderBackend POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${ENV_FILE} $<TARGET_FILE_DIR:PaperTraderBackend>
)
