#include "demo.h"

void test_func(fstream & fstrm)
{
	Base_Class<int> x1;

	Bases_Class<int,int> x2;

	Base_Class<string> x3;

	Bases_Class<char*,char*> x4;

	Base_Class<double> x5;
	Derive_Class<Combine> x6(parse_combine);

	vector<Temp_Class*> vec = {
		&x1, &x2, &x3, &x4, &x5,&x6
	};


	string line;
	size_t line_no(0);
	
	while(getline(fstrm,line))
	{
		cout << "-----------------------------------line: " << ++line_no << endl;
		if(Parse_line(line,vec) < 0)
		{
			cout << "*****line-"	<< line_no << ": stream wrong, ignore" << endl;
			continue;
		}
		//x1
		cout << "int: " << x1.value << endl;

		//x2
		cout << "int[" << x2.N << "]: ";
		for(size_t i(0); i != x2.N ; ++i)
			cout << "int[" << i <<"] = " <<  x2.value[i] << " ";
		cout << endl;

		//3
		cout << "string: " << x3.value << endl;

		//4
		cout << "char*[" << x4.N << "]: ";
		for(size_t i(0); i!= x4.N; ++i)
			cout << "char*[" << i << "]= " << x4.value[i] << " ";
		cout << endl;

		//5
		cout << "double: " << x5.value << endl;
		
		//6
		cout << "Combine: " ;
		x6.value.output();
	}
	cout << "----------------------end data--------------------" << endl;
	cout << "----------------------end data--------------------" << endl;
	cout << "----------------------end data--------------------" << endl;
	cout << "----------------------end data--------------------" << endl;
}


void print_help()
{
	cout << "-------------------------------------------------" << endl;
	cout << "the data type in order is :" << endl;
	cout << "int, int[NUM], string, char*[NUM],\
 double, Self_define : Combine(int,char[2],double,string) " << endl;
	cout << "----------------input your choice---------------" << endl;
	cout << "case 1 : ALL_RIGHT        -> all right" << endl;
	cout << "case 2 : INT_WRONG        -> 2 " << endl;
	cout << "case 3 : INT[NUM]_WRONG   -> 3 " << endl;
	cout << "case 4 : CHAR*[NUM]_WRONG -> 2 " << endl;
	cout << "case 5 : DOUBLE_WRONG     -> 2,3 " << endl;
	cout << "case 6 : COMBINE_WRONG    -> 2 " << endl;
}

int main()
{
	fstream fstrm;
	int c;
	while(print_help(),cin >> c)
	{
		fstrm.close();
		fstrm.clear();
		switch(c)
		{
			case 1:
				fstrm.open("test_ar.txt");
				break;
			case 2:
				fstrm.open("test_int.txt");
				break;
			case 3:
				fstrm.open("test_int_num.txt");
				break;
			case 4:
				fstrm.open("test_char_num.txt");
				break;
			case 5:
				fstrm.open("test_double.txt");
				break;
			case 6:
				fstrm.open("test_combine.txt");
				break;
			default:
				cout << "wrong input" << endl;
				continue;
		}
		if(fstrm.fail())
		{
			cout << "open file error" << endl;
			continue;
		}
		test_func(fstrm);
	}
	return 0;
}
