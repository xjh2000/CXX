include_directories(.)
aux_source_directory(. DIR_LIB_SRCS)
add_library(Calculate ${DIR_LIB_SRCS} BinNode.h BinTree.h)
