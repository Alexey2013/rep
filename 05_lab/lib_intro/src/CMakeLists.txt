set(target ${MP2_INTRO_LIBRARY})

file(GLOB hdrs "*.h*" "${MP2_INTRO_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_TABLES_INCLUDE}"  "${MP2_LISTS_INCLUDE}" "${MP2_POLYNOMS_INCLUDE}" "${MP2_INTRO_INCLUDE}" )


add_library(${target} STATIC ${srcs} ${hdrs})