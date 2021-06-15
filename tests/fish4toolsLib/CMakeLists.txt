set(SOURCES
  test_fish4toolsEmbedded.cc
  test_fish4toolsDataTreeNode.cc
  test_fish4toolsDataBalancedTree.cc
  gtest_main.cc
)

set(CMAKE_CXX_COMPILER g++)

add_executable(UTest_fish4toolsEmbedded ${SOURCES})
set_target_properties(UTest_fish4toolsEmbedded PROPERTIES COMPILE_FLAGS -pthread LINK_FLAGS -pthread)
target_link_libraries(UTest_fish4toolsEmbedded fish4tools pthread gtest)

set_target_properties(UTest_fish4toolsEmbedded
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin"
)

gtest_discover_tests(UTest_fish4toolsEmbedded)
