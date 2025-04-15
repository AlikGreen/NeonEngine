function(copy_to_build_dir SRC_FILE DEST_NAME)
    if(NOT EXISTS ${SRC_FILE})
        message(FATAL_ERROR "Source file '${SRC_FILE}' does not exist!")
    endif()

    # Define the destination path in the build directory
    set(DEST_FILE "${CMAKE_BINARY_DIR}/${DEST_NAME}")

    # Copy the file at CMake configure time
    configure_file(${SRC_FILE} ${DEST_FILE} COPYONLY)

    message(STATUS "Copied ${SRC_FILE} to ${DEST_FILE}")
endfunction()
