project(ciostream-test)

add_executable(cio_assert "Assert/main.c")
target_link_libraries(cio_assert PUBLIC cio-static)

add_executable(cio_rb "RingBuffer/baseio.c")
target_link_libraries(cio_rb PUBLIC cio-static)

add_executable(cio_rb_restore "RingBuffer/restore.c")
target_link_libraries(cio_rb_restore PUBLIC cio-static)

add_executable(cio_wrap "CioWrap/main.c")
target_link_libraries(cio_wrap PUBLIC cio-static)

add_executable(cio_buf_in "BufferedInputStream/base.c")
target_link_libraries(cio_buf_in PUBLIC cio-static)

add_executable(cio_buf_in_readline "BufferedInputStream/readline.c")
target_link_libraries(cio_buf_in_readline PUBLIC cio-static)
