set(target ${MP2_SORT_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_SORT_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_TABLES_INCLUDE}" "${MP2_SORT_INCLUDE}")

add_library(${target} STATIC ${srcs} ${hdrs})