set(TEST_SOURCES test_graphe_interface.cpp ${PROJECT_SOURCE_DIR}/Graphe.cpp)

add_executable(
        test_graphe_interface
        ${TEST_SOURCES})

add_executable(
        test_graphe_algorithmes
        test_graphe_algorithmes.cpp
        ${PROJECT_SOURCE_DIR}/Graphe.cpp
        ${PROJECT_SOURCE_DIR}/Graphe_algorithmes.cpp
)

target_include_directories(test_graphe_interface PRIVATE ${PROJECT_SOURCE_DIR} )

target_include_directories(test_graphe_algorithmes PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(
        test_graphe_interface
        gtest_main
        gtest
        pthread
)

target_link_libraries(
        test_graphe_algorithmes
        gtest_main
        gtest
        pthread
)


include(GoogleTest)
gtest_discover_tests(test_graphe_interface)
gtest_discover_tests(test_graphe_algorithmes)
