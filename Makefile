# =================================== #
# (C) 2019 madoodia@gmail.com.
# All rights reserved.
# =================================== #


# ------------------------------------------------
PROJECT_NAME       = $(FOLDER_NAME)

OBJECTS_SRC        = src/main.obj \
                     src/dummy.obj \
                     src/shader.obj \
                     src/stb_image.obj \
                     src/oglWindow.obj

OBJECTS_OUT        = main.obj \
                     dummy.obj \
                     shader.obj \
                     stb_image.obj \
                     oglWindow.obj

EXTRA_OBJS         = moc_oglWindow.obj

EXTRA_CPP          = moc_oglWindow.cpp

EXTRA_H            = moc_predefs.h

USELESS_EXT        = *.obj \
                     *.lib \
                     *.exp \
                     *.idb \
                     *.cpp \
                     *.h

##################
 


##################

# ------------------------------------------------
GLEW_LOCATION    	= $(SDKS_LOCATION)/OpenGL/GLEW
QT_LOCATION    	    = $(SDKS_LOCATION)/Qt5
STB_LOCATION        = $(SDKS_LOCATION)/OpenGL/STB
QT_MOC_DUMMY        = $(HOME_DIR)src/dummy.cpp
EXTRA_WIN_LIBS	    = opengl32.lib Qt5Widgets.lib Qt5Core.lib Qt5Gui.lib glew32.lib
DEFAULT_WIN_LIBS	= kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

# ------------------------------------------------
TARGET             = $(PROJECT_NAME).exe
INCLUDES           = -I. -I$(GLEW_LOCATION)/include -I$(QT_LOCATION)/include -I$(STB_LOCATION) -I$(QT_LOCATION)/mkspecs/win32-msvc
LIBS               = -LIBPATH:$(QT_LOCATION)/lib -LIBPATH:$(GLEW_LOCATION)/lib $(EXTRA_WIN_LIBS) $(DEFAULT_WIN_LIBS)
LINKER_FLAGS       = -nologo  -MACHINE:X64
DEL                 = del
LINKER              = link
MOC                 = moc

# ------------------------------------------------
CC           = cl
DEFINES      = -DUNICODE -DWIN32 -D_WIN64 -D_WINDOWS -DNT_PLUGIN
CC_FLAGS     = -Zc:wchar_t -O2 -FC -MT -W3 -GR -EHs $(DEFINES) # Warning Level 3
# CC_FLAGS     = -Zc:wchar_t -O2 -FC -MD -Wall -GR -EHs $(DEFINES) # Full warningg


.SUFFIXES: .cpp .c .obj .exe

.cpp.obj:
    $(CC) -c $(INCLUDES) $(CC_FLAGS) @<<
    $<
<<

all: Makefile $(EXTRA_H) $(EXTRA_CPP) $(EXTRA_OBJS) $(TARGET) cleanup

# --- HELP ---
# TIP: When you are using Q_OBJECTS in any header file
# you have to create its moc_FILE.cpp from FILE.h
# and moc_FILE.obj from moc_FILE.cpp
# to avoid errors of Unresolved External ...
# 
# Q_OBJECT Dummy header file
moc_predefs.h: $(QT_MOC_DUMMY)
    $(CC) -O2 -P -Fi:moc_predefs.h $(QT_MOC_DUMMY)

# oglWindow
moc_oglWindow.cpp: src/oglWindow.h moc_predefs.h
    $(MOC) $(DEFINES) -Imoc_predefs.h $(INCLUDES) src/oglWindow.h -o moc_oglWindow.cpp
moc_oglWindow.obj: moc_oglWindow.cpp 
    $(CC) $(CL_FLAGS) moc_oglWindow.cpp -c $(INCLUDES)

# --- HELP ---

$(TARGET):  $(OBJECTS_SRC)
    $(LINKER) $(LINKER_FLAGS) -OUT:$(TARGET) $(EXTRA_OBJS) $(OBJECTS_OUT) $(LIBS)

cleanup:
    -$(DEL) $(USELESS_EXT)