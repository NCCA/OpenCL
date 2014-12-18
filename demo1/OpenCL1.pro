TARGET=OpenCL1
SOURCES+=main.cpp
OTHER_FILES+=square.cl
CONFIG-=app_bundle
macx:LIBS+= -framework OpenCL
