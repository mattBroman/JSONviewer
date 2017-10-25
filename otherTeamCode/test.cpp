#include <iostream>
#include <assert.h>
#include "API.h"

using namespace std;

int main(){
	Database* Library = new Database();		//create Library
	vector<string>* attributes = new vector<string>();
	attributes->push_back("Name");
	attributes->push_back("UIN");
	attributes->push_back("Sex");
	attributes->push_back("major");
	Table* classTable1 = new Table(attributes);	//create Table for class 1
		assert(("Table(vector<string>*) failed", classTable1->get_attributes().at(0) == "Name"));	
		assert(("Table(vector<string>*) failed", classTable1->get_attributes().at(1) == "UIN"));	
		assert(("Table(vector<string>*) failed", classTable1->get_attributes().at(2) == "Sex"));
		assert(("Table(vector<string>*) failed", classTable1->get_attributes().at(3) == "major"));
	Table* classTable2 = new Table();			//create Table for class 2
	classTable2->add_attribute("Name");
	classTable2->add_attribute("UIN");
	classTable2->add_attribute("Major");
	classTable2->add_attribute("RemoveMe");
		assert(("Table.get_size() failed", classTable1 -> get_size() == 0));		//test initial size
		assert(("Table.add_attribute(string) failed", classTable2->get_attributes().at(0) == "Name"));	
		assert(("Table.add_attribute(string) failed", classTable2->get_attributes().at(1) == "UIN"));	
		assert(("Table.add_attribute(string) failed", classTable2->get_attributes().at(2) == "Major"));
		assert(("Table.add_attribute(string) failed", classTable2->get_attributes().at(3) == "RemoveMe"));
		
		assert(("Table.add_attribute(string) failed", classTable2->get_attributes().size() == 4));
	
	//test to make sure size updates after remove attribute
	classTable2->remove_attribute("RemoveMe");
		assert(("Table.remove_attribute(string)", classTable2->get_attributes().size() == 3));
	
	//create and populate first record
	Record* firstStudent = new Record(4);
		assert(("Record(int) failed", firstStudent->get_entry(0) == ""));
		assert(("Record(int) failed", firstStudent->get_entry(1) == ""));
		assert(("Record(int) failed", firstStudent->get_entry(2) == ""));
		assert(("Record(int) failed", firstStudent->get_entry(3) == ""));
		assert(("Record(int) failed", firstStudent -> get_size() == 4));
	
	firstStudent -> set_entry(0, "James Aubin");	//add name
	firstStudent -> set_entry(1, "999999999");		//add fake UIN
	firstStudent -> set_entry(2, "male");			//add sex
	firstStudent -> set_entry(3, "Liberal Arts");			//add major
	
	//create and populate first record
	Record* secondStudent = new Record(4);
	secondStudent -> set_entry(0, "Mathew Broman");	//add name
	secondStudent -> set_entry(1, "000000000");		//add fake UIN
	secondStudent -> set_entry(2, "female");			//add sex
	secondStudent -> set_entry(3, "Dancing");			//add major
	
		assert(("Record.set_entry(int, string)", firstStudent -> get_entry(0) == "James Aubin"));
		assert(("Record.set_entry(int, string)", firstStudent -> get_entry(1) == "999999999"));
		assert(("Record.set_entry(int, string)", firstStudent -> get_entry(2) == "male"));
		assert(("Record.set_entry(int, string)", firstStudent -> get_entry(3) == "Liberal Arts"));
		assert(("Record.set_entry(int, string)", secondStudent -> get_entry(0) == "Matthew Broman"));
		assert(("Record.set_entry(int, string)", secondStudent -> get_entry(1) == "000000000"));
		assert(("Record.set_entry(int, string)", secondStudent -> get_entry(2) == "female"));
		assert(("Record.set_entry(int, string)", secondStudent -> get_entry(3) == "Dancing"));		//check to make sure entry added properly

	classTable1-> insert_record(firstStudent);		//push first student into the class table
	classTable2->insert_record(secondStudent);
		assert(("Table.insert_record(Record*) failed", classTable2->get_size() == 2));
		
	Library -> add_Table(classTable1, "students1");
	Library->add_Table(classTable2, "students2");
		assert(("Database.list_Tables() failed", Library->list_Tables().size() == 2));
		assert(("Database.list_Tables() failed", Library->list_Tables().at(0) == "students1"));
		assert(("Database.list_Tables() failed", Library->list_Tables().at(1) == "students2"));
		assert(("Database.get_Tables() failed", Library->get_Tables().size() == 2));
		assert(("Database.get_tables() failed", Library->get_Tables().at(0) == classTable1));
		assert(("Database.get_Tables() failed", Library->get_Tables().at(1) == classTable2));
	Library->drop_Table("students2");
		assert(("Database.drop_Table(string) failed", Library->get_Tables().size() == 1));
	classTable1->set_key("Name");
		assert(("Table.set_key(string) failed", Library->list_Tables().at(0) == "Name"));
	classTable1->set_key("students");
	
	
	
	classTable1->add_attribute("null");
		assert(("Table.add_attribute(string) failed", classTable1->get_record(0)->get_entry(4) == ""));
		assert(("Table.add_attribute(string) failed", classTable1->get_record(1)->get_entry(4) == ""));
		assert(("Table.add_attribute(string) failed", classTable1->get_attributes().size() == 5));
	secondStudent->set_entry(4, "Filled");
		assert(("Table.Count(string) failed", classTable1->Count("null") == 1));
		assert(("Table.Count(string) failed", classTable1->Count("Name") == 2));
		assert(("Table.Min(string) failed", classTable1->Min("UIN") == "000000000"));
		assert(("Table.Min(string) failed", classTable1->Min("Name") == "James Aubin"));
		assert(("Table.Max(string) failed", classTable1->Max("UIN") == "999999999"));
		assert(("Table.Mac(string) failed", classTable1->Max("Name") == "Matthew Broman"));
		assert(("Table.get_record(int) failed", classTable1->get_record(0) == firstStudent));
		assert(("Table.get_record(int) failed", classTable1->get_record(1) == secondStudent));
	classTable1->remove_attribute("null");
		assert(("Table.remove_attribute(string) failed", classTable1->get_attributes().size() == 4));
		
	Record* memeRecord1 = new Record(2);
	Record* memeRecord2 = new Record(2);
	Record* studentRecord3 = new Record(4);
	Record* studentRecord4 = new Record(4);
	
	studentRecord3->set_entry(0, "MemeKing");
	studentRecord3->set_entry(1, "123121234");
	studentRecord3->set_entry(2, "otherKin");
	studentRecord3->set_entry(3, "under water basket weaving");
	studentRecord4->set_entry(0, "Bettati");
	studentRecord4->set_entry(1, "998090987");
	studentRecord4->set_entry(2, "15 min milestones");
	studentRecord4->set_entry(3, "Italian Studies");
	memeRecord1->set_entry(0, "dank");
	memeRecord1->set_entry(1, "000000000");
	memeRecord2->set_entry(0, "not dank");
	memeRecord2->set_entry(1, "999999999");
	
	vector<string>* attributes1 = new vector<string>();
	attributes1->push_back("Dank?");
	attributes1->push_back("UIN");
	Table* memeTable = new Table(attributes1);
	classTable1->insert_record(studentRecord3);
	classTable1->insert_record(studentRecord4);
	memeTable->insert_record(memeRecord1);
	memeTable->insert_record(memeRecord2);
	
	//join test
	//cross join
	Table* crossTable = memeTable->cross_join(memeTable, classTable1);
		//check if input tables are unaffected
		assert(("Table.cross_join(Table* Table*) failed", memeTable->get_attributes().at(0) == "Dank?"));
		assert(("Table.cross_join(Table* Table*) failed", memeTable->get_attributes().at(1) == "UIN"));

		assert(("Table.cross_join(Table* Table*) failed", classTable1->get_attributes().at(0) == "Name"));
		assert(("Table.cross_join(Table* Table*) failed", classTable1->get_attributes().at(1) == "UIN"));
		assert(("Table.cross_join(Table* Table*) failed", classTable1->get_attributes().at(2) == "Sex"));
		assert(("Table.cross_join(Table* Table*) failed", classTable1->get_attributes().at(3) == "major"));

		//check that cross table is cross joined
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_attributes().at(0) == "Dank?"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_attributes().at(1) == "UIN"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_attributes().at(2) == "Name"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_attributes().at(3) == "UIN"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_attributes().at(4) == "Sex"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_attributes().at(5) == "major"));

		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(0)->get_entry(0) == "dank"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(0)->get_entry(1) == "000000000"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(0)->get_entry(2) == "James Aubin"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(0)->get_entry(3) == "999999999"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(0)->get_entry(4) == "male"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(0)->get_entry(5) == "Liberal Arts"));

		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(5)->get_entry(0) == "not dank"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(5)->get_entry(1) == "999999999"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(5)->get_entry(2) == "Matthew Broman"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(5)->get_entry(3) == "000000000"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(5)->get_entry(4) == "female"));
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_record(5)->get_entry(5) == "Dancing"));
		//check size 8
		assert(("Table.cross_join(Table* Table*) failed", crossTable->get_size() == 8));
	
	//natural join
	Table* naturalTable = memeTable->natural_join(memeTable, classTable1);
		//check if input tables are unaffected
		assert(("Table.natural_join(Table* Table*) failed", memeTable->get_attributes().at(0) == "Dank?"));
		assert(("Table.natural_join(Table* Table*) failed", memeTable->get_attributes().at(1) == "UIN"));

		assert(("Table.natural_join(Table* Table*) failed", classTable1->get_attributes().at(0) == "Name"));
		assert(("Table.natural_join(Table* Table*) failed", classTable1->get_attributes().at(1) == "UIN"));
		assert(("Table.natural_join(Table* Table*) failed", classTable1->get_attributes().at(2) == "Sex"));
		assert(("Table.natural_join(Table* Table*) failed", classTable1->get_attributes().at(3) == "major"));
		
		//Dank?, UIN, Name, Sex, major - check if natty joined table is 
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_attributes().at(0) == "Dank?"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_attributes().at(1) == "UIN"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_attributes().at(2) == "Name"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_attributes().at(3) == "Sex"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_attributes().at(4) == "major"));

		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(0)->get_entry(0) == "dank"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(0)->get_entry(1) == "000000000"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(0)->get_entry(2) == "Matthew Broman"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(0)->get_entry(3) == "female"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(0)->get_entry(4) == "Dancing"));

		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(1)->get_entry(0) == "not dank"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(1)->get_entry(1) == "999999999"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(1)->get_entry(2) == "James Aubin"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(1)->get_entry(3) == "male"));
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_record(1)->get_entry(4) == "Liberal Arts"));

		//check size 2
		assert(("Table.natural_join(Table* Table*) failed", naturalTable->get_size() == 2));
		
	//query tests
	Library->add_Table(memeTable, "meme");
	//test select *
	Table* queryTable = Library->Query("*", "meme", "");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "Dank?"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(1) == "UIN"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 2));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "dank"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(1) == "000000000"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(0) == "not dank"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(1) == "999999999"));
	//test selecting specific attributes
	queryTable = Library->Query("Name, Sex", "students", "");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "Name"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(1) == "Sex"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 2));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "James Aubin"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(1) == "male"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(0) == "Matthew Broman"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(1) == "female"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(2)->get_entry(0) == "MemeKing"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(2)->get_entry(1) == "otherKin"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(3)->get_entry(0) == "Bettati"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(3)->get_entry(1) == "15 min milestones"));
	//where checks
	// =
	queryTable = Library->Query("UIN", "students", "Name = Matthew Broman");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "UIN"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "000000000"));
	//<>
	queryTable = Library->Query("Dank?", "meme", "Dank <> not dank");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "Dank?"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "dank"));
	//we do not expect less thans and greater thans to work on non numeric values
	// > 
	queryTable = Library->Query("Name", "students", "UIN > 999999998");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "Name"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "James Aubin"));
	// <
	queryTable = Library->Query("Name", "students", "UIN < 000000001");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "Name"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "Matthew Broman"));
	// <= 
	queryTable = Library->Query("Name", "students", "UIN <= 123121234");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "Name"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "Matthew Broman"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(0) == "MemeKing"));
	// >=
	queryTable = Library->Query("Name", "students", "UIN >= 998090987");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "UIN"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "James Aubin"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(0) == "Bettati"));
	//AND
	queryTable = Library->Query("Name", "students", "UIN <= 1234121234 AND Sex = female");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "Name"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "Matthew Broman"));
	//OR
	queryTable = Library->Query("UIN", "students", "Name = Matthew Broman OR Name = James Aubin");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "UIN"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "999999999"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(0) == "000000000"));
	//NOT
	queryTable = Library->Query("UIN", "students", "NOT Name = Matthew Broman");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "UIN"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "999999999"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(1) == "123121234"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(2)->get_entry(2) == "998090987"));
	//() not nested
	queryTable = Library->Query("UIN", "students", "(Name = Matthew Broman) OR (Name = James Aubin)");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "UIN"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "999999999"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(0) == "000000000"));
	//() nested
	queryTable = Library->Query("UIN", "students", "NOT((Name = Matthew Broman) OR (Name = James Aubin))");
		//attribute check
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().at(0) == "UIN"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_attributes().size() == 1));
		//Record check
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(0)->get_entry(0) == "123121234"));
		assert(("Database.Query(string, string, string) failed", queryTable->get_record(1)->get_entry(0) == "998090987"));
}
