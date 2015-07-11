#ifndef PARSE_D_H_
#define PARSE_D_H_

#include "parse.h"

string get_all(stringstream & strm)
{
	string str("");
	string str_temp;
	while(strm >> str_temp)
		str += " " + str_temp;
	return str;
}

/***************************************************************/

////////////////////////////////////////////////////////////////
//function: define Derive_Class for the user define struct, 
//			User send the function Parse to deal with the struct
////////////////////////////////////////////////////////////////

template <typename T>
class Derive_Class : public Temp_Class
{
	public:
		typedef T Func(const string&);
		
		Derive_Class(Func * p):func_ptr(p){}
		Derive_Class():func_ptr(NULL){}
		
		void set_val(const string & str)
		{
			if(func_ptr == NULL)
				throw runtime_error("<Derive_Class>: func_ptr == NULL");
			value = func_ptr(str);
		}

		Func * func_ptr;
		T value;
};


////////////////////////////////////////////////////////////////
//function: define Bases_Class for A variety of arrays,
//			the element is Built In type
////////////////////////////////////////////////////////////////


template<typename T1,typename T>
class Bases_Class: public Temp_Class
{
	public:
		Bases_Class():value(NULL),N(0){}

		void set_val(const string & str)
		{
			stringstream strm(str);
			char c;
			strm >> N;
			if(strm.fail())
				throw runtime_error("<Bases_Class>: N read wrong");

			if(value != NULL)
				delete value;

			value = new T[N];

			strm >> c;	// delete ':'
			
			string strs = get_all(strm);

			for(size_t i(0); i != N; ++i)
			{
				if(strs.size() == 0)
					throw runtime_error("<Bases_Class>: strs is empty");
				string str_temp;
				size_t j = 0;
				while(strs[j] != ',' && j < strs.size()) ++j;
				str_temp = string(strs,0,j);
				if(j != strs.size())
					strs = string(strs, j + 1);
				Base_Class<T> a;
				a.set_val(str_temp);
				value[i] = a.value;
			}
			
		}

		T* value;
		size_t N;
};


//------------------------------------------------------------
// function: special for char*[]------------------------------
// -----------------------------------------------------------
template<typename T>
class Bases_Class<char*, T>: public Temp_Class
{
	public:
		Bases_Class():value(NULL),N(0),pre_N(0){}
		
		void set_val(const string & str)
		{
			stringstream strm(str);
			char c;
			strm >> N;
			if(strm.fail())
				throw runtime_error("<Bases_Class>: N read wrong");

			//释放空间，与空间处理--------------------------
			if(value != NULL)
			{
				for(size_t i(0); i != pre_N; ++i)
				{
					if(value[i] != NULL)
						delete value[i];
				}

				delete value;
			}
			pre_N = 0;

			value = new char*[N];

			for(size_t i(0); i != N; ++i )
				value[i] = NULL;

			//------------------------------------------

			strm >> c;	// delete ':'
			
			string strs = get_all(strm);

			for(size_t i(0); i != N; ++i)
			{
				if(strs.size() == 0)
					throw runtime_error("<Bases_Class> <char*>: strs is empty");
				string str_temp;
				size_t j = 0;
				while(strs[j] != ',' && j < strs.size()) ++j;
				str_temp = string(strs,0,j);
				if(j != strs.size())
					strs = string(strs, j + 1);
				Base_Class<char*> a;
				a.set_val(str_temp);
				
				size_t len = strlen(a.value);

				value[i] = new char(len + 1);
				++pre_N;

				strncpy(value[i],a.value,len);
				*(value[i] + len) = 0;
			}

		}

		char ** value;
		size_t N;
		size_t pre_N;
};

template <typename T>
class Bases_Class< Derive_Class<T> ,T > : public Temp_Class
{
	public:
	typedef T Func(const string &);

	Bases_Class(Func * p) : func_ptr(p),value(NULL),N(0){}

	void set_val(const string & str)
	{
			stringstream strm(str);
			char c;
			strm >> N;
			if(strm.fail())
				throw runtime_error("<Bases_Class>: N read wrong");
			if(value != NULL)
			{
				delete value;
			}

			value = new Derive_Class<T>[N];
			for(size_t i(0); i != N; ++i)
			{
				value[i] = NULL;
			}


			strm >> c;	// delete ':'
			
			string strs = get_all(strm);
			for(size_t i(0); i != N; ++i)
			{
				if(strs.size() == 0)
					throw runtime_error("<Bases_Class> <char*>: strs is empty");
				string str_temp;
				size_t j = 0;
				while(strs[j] != ',' && j < strs.size()) ++j;
				str_temp = string(strs,0,j);
				if(j != strs.size())
					strs = string(strs, j + 1);

				Derive_Class<T> a(func_ptr);
				a.set_val(str_temp);
				value[i] = a;
			}

	}

	Func * func_ptr;
	Derive_Class<T> * value;
	size_t N;
	
};


#endif
