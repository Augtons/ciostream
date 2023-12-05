project(libciostream)

file(GLOB_RECURSE CIO_SRCS_OR_DIRS LIST_DIRECTORIES true "*.c" "*.cpp")
list(APPEND CIO_SRCS_OR_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
list(APPEND CIO_SRCS_OR_DIRS "${CIO_ROOT}/Port/CMake/port.c")

foreach(item IN LISTS CIO_SRCS_OR_DIRS)
    if(IS_DIRECTORY "${item}")
        list(APPEND CIO_INCLUDE_DIRS ${item})
    else()
        get_filename_component(ext ${item} LAST_EXT)
        if(${ext} STREQUAL ".c")
            list(APPEND CIO_C_SRCS ${item})
        elseif(${ext} STREQUAL ".cpp")
            list(APPEND CIO_CPP_SRCS ${item})
        endif()
    endif ()
endforeach()

add_library(cio        SHARED ${CIO_C_SRCS})
add_library(cio-static STATIC ${CIO_C_SRCS})

target_include_directories(cio          PUBLIC ${CIO_INCLUDE_DIRS})
target_include_directories(cio-static   PUBLIC ${CIO_INCLUDE_DIRS})

if (CIO_CPP_SRCS)
    add_library(ciopp        SHARED ${CIO_C_SRCS} ${CIO_CPP_SRCS})
    add_library(ciopp-static STATIC ${CIO_C_SRCS} ${CIO_CPP_SRCS})

    target_include_directories(ciopp        PUBLIC ${CIO_INCLUDE_DIRS})
    target_include_directories(ciopp-static PUBLIC ${CIO_INCLUDE_DIRS})
endif ()
