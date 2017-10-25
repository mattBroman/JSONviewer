TARGET = JSONviewer
CC = g++
VERSION = -std=c++14
DEBUG = -g
HEADER_FLAGS = -I./Headers/
LIBRARY_FLAGS = -L.
DOLLAR_SIGN = $
OBJECTS = PrintTableBtn.o InputSelector.o TableBuilder.o  GUI.o SQLTable.o AppMain.o
OBJECT_COMPLIE = $(CC) $(VERSION) $(DEBUG) $(HEADER_FLAGS) -c $<
FLTK_OBJECT_COMPILE = $(CC) $(VERSION) $(DEBUG) $(HEADER_FLAGS) -c -lfltk $<

$(TARGET) : $(OBJECTS)
	$(CC) $(VERSION) $(DEBUG) $(HEADER_FLAGS) $(LIBRARY_FLAGS) $(OBJECTS) libDatabase.so -lfltk -o $@
	
AppMain.o : AppMain.cpp
	$(FLTK_OBJECT_COMPILE)
	
TableBuilder.o : TableBuilder.cpp
	$(OBJECT_COMPLIE)
	
InputSelector.o : InputSelector.cpp
	$(OBJECT_COMPLIE)

PrintTableBtn.o : PrintTableBtn.cpp
	$(FLTK_OBJECT_COMPILE)

GUI.o : GUI.cpp
	$(FLTK_OBJECT_COMPILE)

SQLTable.o : SQLTable.cpp
	$(FLTK_OBJECT_COMPILE)
	
clean :
	rm *.o $(TARGET)
	
