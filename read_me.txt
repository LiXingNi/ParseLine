/////////////////////////////////////////////////////////////////////
// FUNCTION: This function will parse txt line by line , and push 
//			 data in correspond type variable
//
// DIRECTION FOR USE : 
//		1)if you want to read Build-in type,such as int,double...
//		  except array;
//		  * define variable as "Base_Class<T> x",T is the type you
//			want read
//
//		2)if you want to read array, and the type of element in 
//		  array must be Build-in type,such as int[3],double[4]..
//		  * define variable as "Bases_Class<T,N> x", T is the 
//			type you want read, N is the length of the array
//		
//		3)if you want to read the type defined by yourself,
//		  you have to provide the function to initialize your
//		  class, which input a string and return the type you need
//		  * define varible as "Derive_Class<T> x(func)",
//			T is the type you have defined
//			func is the function which can initialize your own type
//			func should define as " T func(string&) "
//	NOTITION:
//		1) you should define every row class ,follow the rule in 
//		   <DIRECTION FOR USE>,and push them in vector<Temp_Class*>
//		   in ordered,which will initialize in queto
//		
//		2) you should call func " int Parse_line(string&,vector<Temp_Class*>)"
//		   string is the line you need parse now
//		   vector is the corresponding Class defined follow <DIRECTION FOR USE>
//
//		3) if Parse_line return -1,mines there is something wrong in this line parse
//		   else this is correct
//
//		4) after call Parse_line, you can use the data you get from txt. 
//		   the formal is "x.value", all type of value save as "***.value"
//
//	EXAMPLE:
//		"test.txt" :	1	2.2	3 4 5	4 hello
//						3	3.3	1 2 4	4 how
//						4	2.1	5 5 5	4 are
//						5	2.2	6 6 6	4 you
//	    * in fact it is : 1'\t'2.2'\t'3' '4' '5'\t'4' 'hello,
//		  corresponding type is: int,double,int[3],Own_type
//		  different type separate by '\t'
//		  the same type separate by ' '
//		
//		struct Own_type
//		{
//			int ival;
//			string sval;
//		};
//
//		Own_type parse_func(string & str)
//		{
//			stringstream strm(str);
//			string str_temp;
//			Own_type temp;
//
//			strm >> temp.ival;
//
//			while(strm >> str_temp)
//				temp.sval += " " + str_temp;
//				
//			return temp;
//		}
//
//
//		int main()
//		{
//			fstream fstrm("test.txt");
//			string line;
//
//			Base_Class<int> x1;							//for int
//			Base_Class<double> x2;						//for double
//			Bases_Class<int,3> x3;						//for int[3]
//			Derive_Class<Own_type> x4(parse_func);		//for Own_type 
//
//			vector<Temp_Class*> vec = {
//				&x1, &x2, &x3, &x4						//must correspond the txt type
//			};
//
//			while(getline(fstrm,line))
//			{
//				Parse_line(line,vec);
//
//				//now you can use the data you need 
//
//				cout << x1.value << endl;
//				cout << x2.value << endl;
//				cout << x3.value[1] << endl;
//				cout << x4.value.sval << endl;
//			}
//
//		}
//
//	DECLARE:
//		The function is writen by myself, I am not sure wether it is stable.
//																			by LXN ,2015/7/1
///////////////////////////////////////////////////////////////////////////////////////////////


/***************************************************************/



