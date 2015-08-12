add_executable(query_test Query_test.cc)
#target_link_libraries(query_test mask boost_unit_test_framework)
target_link_libraries(query_test mask)

add_executable(stringutil_test StringUtil_test.cc)
target_link_libraries(stringutil_test mask)

add_executable(process_test Process_test.cc)
target_link_libraries(process_test mask)

add_executable(rapidstream_test RapidStream_test.cc)
target_link_libraries(rapidstream_test mask)
