TARGET=OpenCL1
SOURCES+=main.cpp \
         OpenCL.cpp
HEADERS+=OpenCL.h
OTHER_FILES+=square.cl
CONFIG-=app_bundle
macx:LIBS+= -framework OpenCL
