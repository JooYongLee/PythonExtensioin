#ifndef MYOBJ_H_
#define MYOBJ_H_
#include <iostream>
#include <fstream>
#define EYE_DATA {1, 0, 0, 0,\
				0, 1, 0, 0,\
				0, 0, 1, 0,\
				0, 0, 0, 1}
namespace test { ;
class CModelData
{
public:
	CModelData()
		:name(""),
		mat EYE_DATA
	{
	//	double dd[16] = EYE_DATA;
	}
	char name[100];
	double mat[16];

	void setName(std::string &_name)
	{
		strcpy_s(name, _name.c_str());
	}
	std::string getName()
	{
		std::string outname = name;
		return outname;
	}
	friend std::ostream& operator<<(std::ostream &out, CModelData &rhs)
	{
		for (int i = 0; i < 16; i++)
		{
			out << rhs.mat[i];
			if (i % 4 == 3 && i > 0)
			{
				out << std::endl;
			}
			else
			{
				out << ",";
			}
		}
		return out;
	}
};

class CTest
{
public:
	CTest() = default;
	~CTest() = default;

	bool addInput();

	std::string myname;
	std::fstream file;
};
}
#endif//MYOBJ_H_
