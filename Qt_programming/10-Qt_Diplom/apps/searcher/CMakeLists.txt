add_executable(searcher
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(searcher PRIVATE
    Qt6::Core
    Qt6::Sql
    Qt6::Widgets
    searchdb
)

add_custom_command(TARGET searcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/config/searcher.ini.example"
        "$<TARGET_FILE_DIR:searcher>/searcher.ini"
)
