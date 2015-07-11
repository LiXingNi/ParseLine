#ifndef PARSE_H_
#define PARSE_H_

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

//*************************define some help check function
inline bool Check_eof(stringstream & strm)
{
	string str;
	string str_t;
	while(strm >> str_t)
		str += str_t;
	if(str.empty())
		return true;
	else 
		return false;
}

/**************************************************************/

////////////////////////////////////////////////////////////////
//function: define basic class for bind, and use as Temp_Class*
////////////////////////////////////////////////////////////////
class Temp_Class
{
	public:
		virtual void set_val(const string & str)
		{
			cout << "error in Temp_Class" << endl;
		}
};


/***************************************************************/

////////////////////////////////////////////////////////////////
//function: define it to deal with common type,such as int,float
//          and special it for special type,such as char*,string
////////////////////////////////////////////////////////////////
template <typename T>
class Base_Class : public Temp_Class
{
	public:
		void set_val(const string & str)
		{
			stringstream strm(str);
			strm >> value;
			if( strm.fail() || !Check_eof(strm))
			{
				throw runtime_error("<Base_Class>: the stream longer or fail");
			}
			return;
		}
		T value;		//Storage Analytic value
};

////////////////////////////////////////////////////////////////////
//function: define the special class for Base_Class,deal with char*
//			input char * ,and final get const char *
///////////////////////////////////////////////////////////////////
template <>
class Base_Class<char *> : public Temp_Class
{
	public:
		void set_val(const string & str)
		{
			str_temp = str;
			value = str_temp.c_str(); // the char * place is fixed size 
		}
		string str_temp;
		const char * value;
};

////////////////////////////////////////////////////////////////////
//function: define the special class for Base_Class,deal with string 
//			input string ,and not use stringstream 
///////////////////////////////////////////////////////////////////
template<>
class Base_Class<string> : public Temp_Class
{
	public:
		void set_val(const string & str)
		{
			value = str;
		}
		string value;
};


//function declare
int Parse_line(string& str_org,vector<Temp_Class *>& vec);
#endif
