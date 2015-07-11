#include "parse.h"
#include "parse_d.h"

class A
{
	public:
		int ival;
		double dval;
		void output()
		{
			cout << "ival = " << ival << " , dval = " << dval << " &&&& " ;
		}
};

A parse_A(const string & str)
{
	A a;
	stringstream strm(str);
	strm >> a.ival;
	strm >> a.dval;
	return a;
}


int main()
{
	ifstream fstrm("test_sn.txt");
	string line;
	Bases_Class<Derive_Class<A>,A> b(parse_A);
	vector<Temp_Class *> vec = {
		&b
	};

	while(getline(fstrm,line))
	{
		if(Parse_line(line,vec) < 0)
		{
			cout << "error in line " << endl;
			continue;
		}

		size_t N = b.N;
		for(size_t i(0); i != N; ++i)
			b.value[i].value.output();
		cout << endl;
	}
}

