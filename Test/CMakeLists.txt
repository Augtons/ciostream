project(ciostream-test)

add_executable(cio_rb "RingBuffer/main.c")
target_link_libraries(cio_rb PUBLIC cio-static)

add_executable(cio_base "CioWrap/main.c")
target_link_libraries(cio_base PUBLIC cio-static)
