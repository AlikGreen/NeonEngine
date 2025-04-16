function(copy_to_build SOURCE_PATH DEST_PATH)
    if(EXISTS "${SOURCE_PATH}")
        if(IS_DIRECTORY "${SOURCE_PATH}")
            # Copy an entire directory.
            file(COPY "${SOURCE_PATH}" DESTINATION "${DEST_PATH}")
        else()
            # Copy a single file.
            configure_file("${SOURCE_PATH}" "${DEST_PATH}" COPYONLY)
        endif()
    else()
        message(FATAL_ERROR "The source path '${SOURCE_PATH}' does not exist!")
    endif()
endfunction()