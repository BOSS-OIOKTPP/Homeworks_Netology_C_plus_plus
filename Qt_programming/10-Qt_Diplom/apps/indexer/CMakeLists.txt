add_executable(indexer
    main.cpp
)

target_link_libraries(indexer PRIVATE
    Qt6::Core
    searchdb
)

set_target_properties(indexer PROPERTIES AUTOMOC OFF)

add_custom_command(TARGET indexer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/config/indexer.ini.example"
        "$<TARGET_FILE_DIR:indexer>/indexer.ini"
)
