set(test_srcs
	test_RegionEstatica.cpp
	test_PilaEstatica.cpp
)

include_directories(
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/ext/googletest/include
)

if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

add_executable(IS220-tests
	${test_srcs}
)

target_link_libraries(IS220-tests
	gtest
	gtest_main
)