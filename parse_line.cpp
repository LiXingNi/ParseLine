#include "parse.h"
/*********************************************************************/
////////////////////////////////////////////////////////////////
//function: define the function to deal every line  
////////////////////////////////////////////////////////////////

int Parse_line(string& str_org,vector<Temp_Class *>& vec)
{
	string str_temp;
	for(vector<Temp_Class*>::iterator it = vec.begin();it != vec.end();++it)
	{
		size_t i(0);
		while(str_org[i] != '\t' && i < str_org.size()) ++i;
		str_temp = string(str_org,0,i);
		if(i != str_org.size())
			str_org = string(str_org,i + 1);

		try
		{
			(*it)->set_val(str_temp);
		}
		catch (runtime_error err )
		{
			cout << err.what() << endl;
			return -1;
		}
	}
	return 0;
}

