project(mylib)

add_library(${PROJECT_NAME} src/mycp.c src/myls.c)

add_library(sub::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
PUBLIC ${PROJECT_SOURCE_DIR}/include
)
