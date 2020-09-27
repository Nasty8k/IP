project(prog)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

# to be added to this project
target_link_libraries(${PROJECT_NAME}
    sub::lib_Lab1
)
