get_filename_component(CURRENT_DIR "." ABSOLUTE)

list(APPEND SRCS "${CURRENT_DIR}/main.cpp")
set(SRCS "${SRCS}" PARENT_SCOPE)

# Detect platform and include relevant files.
string(TOLOWER "${CMAKE_SYSTEM_NAME}" SYS_NAME_LWR)
if(EXISTS "${PROJECT_SOURCE_DIR}/src/os/${SYS_NAME_LWR}")
    add_subdirectory("os/${SYS_NAME_LWR}")
    include_directories("os/${SYS_NAME_LWR}")
else()
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not a supported platform!")
endif()
