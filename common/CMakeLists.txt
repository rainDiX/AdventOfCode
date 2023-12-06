set(SOURCE_FILES commonIO.cpp commonFn.cpp)

add_library(common_lib STATIC ${SOURCE_FILES})

target_include_directories(common_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
