#include "parse.h"
#include "parse_d.h"


inline void Check_stream(stringstream & strm)
{
	if(strm.eof())
		throw runtime_error("stream terminate early");
	if(strm.fail())
		throw runtime_error("stream is break");
}


struct Combine
{
	int ival;
	char cval[2];
	double dval;
	string sval;

	void output();
};

void Combine::output()
{
	cout << "ival = " << ival << ","
		<< "cval[0] = " << cval[0] << ","
		<< "cval[1] = " << cval[1] << ","
		<< "sval = " << sval << endl;
}

Combine parse_combine(const string & str)
{
	Combine c_temp;
	string s_temp;
	stringstream strm(str);
	
	Check_stream(strm);
	strm >> c_temp.ival;
	Check_stream(strm);
	strm >> c_temp.cval[0];
	Check_stream(strm);
	strm >> c_temp.cval[1];
	Check_stream(strm);
	strm >> c_temp.dval;
	Check_stream(strm);
	
	while(strm >> s_temp,!strm.eof())
		c_temp.sval += " " + s_temp;
	c_temp.sval += " " + s_temp;

	return c_temp;
}
