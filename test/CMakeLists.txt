set(test_srcs
	test_RegionEstatica.cpp
	
	test_PilaEstatica.cpp
	test_ColaEstatica.cpp
	test_ColaCircularEstatica.cpp
	test_ListaEstatica.cpp
	test_ListaCircularEstatica.cpp
	test_ListaDobleEstatica.cpp
	test_ListaDobleCircularEstatica.cpp
	
	test_AlgoritmosCola.cpp
)

include_directories(
	${PROJECT_SOURCE_DIR}/ext/googletest/include
)

if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
	
	if(MSVC_VERSION EQUAL 1700)
		add_definitions(-D_VARIADIC_MAX=10)
	endif()
endif()

add_executable(IS220-test
	${test_srcs}
)

target_link_libraries(IS220-test
	gtest
	gtest_main
)
