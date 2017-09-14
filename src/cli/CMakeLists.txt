# Add files to parent scope
get_filename_component(CURRENT_DIR "." ABSOLUTE)
list(APPEND SRCS
    "${CURRENT_DIR}/main.cpp"
)
set(SRCS "${SRCS}" PARENT_SCOPE)