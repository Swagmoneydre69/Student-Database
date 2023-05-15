#include "HashMap.h"
#include <fstream>
#include <string>

class String_Hash{
public:
	unsigned int operator() ( const std::string& key ) const {
    //  This implementation comes from 
    //  http://www.partow.net/programming/hashfunctions/
    //
    //  This is a general-purpose, very good hash function for strings.
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
  }   
};

struct student_info{
	std::string major;
	int credits;
	float GPA;
	std::string email;
};
std::ostream& operator<<(std::ostream& o, const student_info& s){
  o << "[ " << s.major <<", "<<s.credits <<", " << s.GPA << ", " << s.email <<" ]";
  return o;
}

int main(int argc, char** argv){
  HashMap<std::string, student_info, String_Hash> data_map(20);
	std::ifstream input(argv[1]);
  std::string _name, _major, _email;
  int _credits;
  float _GPA;
  while(input >> _name >> _major >> _credits >> _GPA >> _email){
    student_info s;
    s.major = _major; s.credits = _credits; s.GPA = _GPA; s.email = _email;
    data_map[_name] = s;
  }
  data_map.print_table();
}