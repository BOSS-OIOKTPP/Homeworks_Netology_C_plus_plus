add_executable(db_demo
    main.cpp
)

target_link_libraries(db_demo PRIVATE
    Qt6::Core
    searchdb
)

set_target_properties(db_demo PROPERTIES AUTOMOC OFF)

add_custom_command(TARGET db_demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/db_demo.ini.example"
        "$<TARGET_FILE_DIR:db_demo>/db_demo.ini"
)
