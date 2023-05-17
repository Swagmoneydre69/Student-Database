#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
const std::string majors[31] = {
	"Accounting",
"Architecture",
"Art",
"Behavioral_Neuroscience",
"Biology",
"Business_Administration",
"Chemistry",
"Communications",
"Computer_Science",
"Criminal_Justice",
"Economics",
"Education", 
"Mechanical_Engineering",
"Electrical_Engineering",
"Chemical_Engineering",
"English",
"Environmental_Science",
"Environmental_Engineering",
"Game_Design",
"ITWS",
"Journalism",
"Spanish",
"Management",
"Marketing",
"Mathematics",
"Music",
"Nursing",
"Pharmacy",
"Philosophy",
"Physics",
"Psychology"};

std::string get_email(const std::string& first, const std::string& last){
	std::string result("");
	int limit = 5;
	for(int i = 0; i < limit && i < last.size(); ++i){
		if(last[i] == '\'' || last[i] =='\"'){ ++limit; continue;}
		result.push_back(tolower(last[i]));
	}
	result.push_back(tolower(first[0]));
	result += "@rpi.edu";
	return result;
}
int main(){
	std::ifstream names("names.txt");
	std::ofstream out("students_large.txt");
	std::string firstname, lastname;
	while(names >> firstname >> lastname){
		std::string n = firstname + "_" + lastname;
		//.srand(time(0));
		int major_index = rand()%31;
		float GPA = (float)(rand()%400)/100.0;
		int credits = rand() % 128;
		out << n << " " << majors[major_index] << " " << credits << " "<< std::fixed << std::setprecision(2) << GPA<< " " << get_email(firstname, lastname);
		out << "\n";
	}
}