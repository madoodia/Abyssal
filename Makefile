# =================================== #
# (C) 2019 madoodia@gmail.com.
# All rights reserved.
# =================================== #


# ------------------------------------------------
PROJECT_NAME       = $(FOLDER_NAME)

OBJECTS_SRC        = src/main.obj \
                     src/oglWindow.obj

OBJECTS_OUT        = main.obj \
                     oglWindow.obj

USELESS_EXT        = *.obj \
                     *.lib \
                     *.exp \
                     *.idb

# ------------------------------------------------
GLEW_LOCATION    	= $(SDKS_LOCATION)/OpenGL/GLEW
QT_LOCATION    	    = $(SDKS_LOCATION)/Qt5
EXTRA_WIN_LIBS	    = opengl32.lib glew32.lib Qt5Widgets.lib Qt5Core.lib Qt5Gui.lib
DEFAULT_WIN_LIBS	= kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

# ------------------------------------------------
TARGET             = $(PROJECT_NAME).exe
INCLUDES           = -I. -I$(GLEW_LOCATION)/include -I$(QT_LOCATION)/include
LIBS               = -LIBPATH:$(GLEW_LOCATION)/lib -LIBPATH:$(QT_LOCATION)/lib $(EXTRA_WIN_LIBS) $(DEFAULT_WIN_LIBS)
LINKER_FLAGS       = -nologo  -MACHINE:X64
DEL_FILE           = del
LINKER             = link

# ------------------------------------------------
CC           = cl
DEFINES      = -DUNICODE -DWIN32 -D_WIN64 -D_WINDOWS -DNT_PLUGIN
CC_FLAGS     = -Zc:wchar_t -O2 -FC -MD -W3 -GR -EHs $(DEFINES) # Warning Level 3
# CC_FLAGS     = -Zc:wchar_t -O2 -FC -MD -Wall -GR -EHs $(DEFINES) # Full warningg


.SUFFIXES: .cpp .c .obj .exe

.cpp.obj:
    $(CC) -c $(INCLUDES) $(CC_FLAGS) @<<
    $<
<<

all: Makefile $(TARGET) clean

$(TARGET):  $(OBJECTS_SRC)
    $(LINKER) $(LINKER_FLAGS) -OUT:$(TARGET) $(OBJECTS_OUT) $(LIBS)

clean:
    -$(DEL_FILE) $(USELESS_EXT)