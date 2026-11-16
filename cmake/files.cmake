# Add sources to executable/library
target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/syscall.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sysmem.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/startup_stm32f446xx.S"
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/stm32f446xe_flash.ld" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/stm32f446xe_flash.ld")
