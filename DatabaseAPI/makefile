TARGET = DatabaseAPI

DatabaseAPI.so: Database.o Table.o Record.o Exceptions.o Helper.o
	ar rcs $@ $^
Database.o: Database.cpp
	g++ -std=c++11 -g -c $<
Table.o: Table.cpp
	g++ -std=c++11 -g -c $<
Record.o: Record.cpp
	g++ -std=c++11 -g -c $<
Helper.o: Helper.cpp
	g++ -std=c++11 -g -c $<
Exceptions.o: Exceptions.cpp
	g++ -std=c++11 -g -c $<
clean:
	rm -f *.o *.a $(TARGET).so
