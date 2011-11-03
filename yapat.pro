TEMPLATE = app
DEPENDPATH += librend/inc \
              librend/src \
              libuni/inc \
              libuni/src \
              libvm/inc \
              shaders/inc \
              shaders/src \
              utils/inc \
              utils/src
INCLUDEPATH += . utils/inc librend/inc libuni/inc libvm/inc shaders/inc
DESTDIR = bin
OBJECTS_DIR = obj
MOC_DIR = moc

# Input
HEADERS += version.h \
           librend/inc/input.hh \
           librend/inc/nulloutput.hh \
           librend/inc/output.hh \
           librend/inc/ptrenderer.hh \
           librend/inc/qimageoutput.hh \
           librend/inc/qtptrenderer.hh \
           librend/inc/renderer.hh \
           librend/inc/testinput.hh \
           libuni/inc/box.hh \
           libuni/inc/camera.hh \
           libuni/inc/envmap.hh \
           libuni/inc/light.hh \
           libuni/inc/lightrect.hh \
           libuni/inc/lightsphere.hh \
           libuni/inc/object.hh \
           libuni/inc/plane.hh \
           libuni/inc/ray.hh \
           libuni/inc/shader.hh \
           libuni/inc/sphere.hh \
           libuni/inc/surfaceobject.hh \
           libuni/inc/unibase.hh \
           libuni/inc/unicontext.hh \
           libuni/inc/universe.hh \
           libvm/inc/vmmatrix.hh \
           libvm/inc/vmvector.hh \
           shaders/inc/chessshader.hh \
           shaders/inc/glassshader.hh \
           shaders/inc/mirrorshader.hh \
           shaders/inc/snookershader.hh \
           utils/inc/log.hh \
           utils/inc/metrix.hh \
           utils/inc/rand.hh
SOURCES += main.cpp \
           librend/src/input.cpp \
           librend/src/nulloutput.cpp \
           librend/src/output.cpp \
           librend/src/ptrenderer.cpp \
           librend/src/qimageoutput.cpp \
           librend/src/qtptrenderer.cpp \
           librend/src/renderer.cpp \
           librend/src/testinput.cpp \
           libuni/src/box.cpp \
           libuni/src/camera.cpp \
           libuni/src/envmap.cpp \
           libuni/src/light.cpp \
           libuni/src/lightrect.cpp \
           libuni/src/lightsphere.cpp \
           libuni/src/object.cpp \
           libuni/src/plane.cpp \
           libuni/src/shader.cpp \
           libuni/src/sphere.cpp \
           libuni/src/surfaceobject.cpp \
           libuni/src/unicontext.cpp \
           libuni/src/universe.cpp \
           shaders/src/chessshader.cpp \
           shaders/src/glassshader.cpp \
           shaders/src/mirrorshader.cpp \
           shaders/src/snookershader.cpp \
           utils/src/log.cpp \
           utils/src/metrix.cpp \
           utils/src/rand.cpp

         
