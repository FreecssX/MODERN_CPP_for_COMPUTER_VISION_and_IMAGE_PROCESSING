#################### Import the 'io_tools' library here ########################
find_library(iolib libio_tools.so ${PROJECT_SOURCE_DIR}/lib)
#################### Create a library 'image' below this line ##################
add_library(image SHARED image.cpp)
target_link_libraries(image ${iolib})
