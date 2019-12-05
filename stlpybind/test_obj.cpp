#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include <Eigen/Core>
#include <vector>

#include "myobj.h"

namespace py = pybind11;

using namespace test;

CModelData mytest()
{
	CModelData data;
	std::string name = "show me the money";
	data.setName(name);
	return data;
}

std::vector<double> modify()
{
	std::vector<double> input;
	input.reserve(10);
	//input.resize(10);
	for(int i = 0; i < 10; i++)
		input.push_back(i);
	
  std::vector<double> output;

  std::transform(
    input.begin(),
    input.end(),
    std::back_inserter(output),
    [](double x) -> double { return 2.*x; }
  );

  return input;
}

char *name_str_list[100] = {
	"show",
	"me",
	"the",
	"money",
	"test",
	"jjang"
};
std::vector<CModelData> readfile()
{
	std::vector<CModelData> input;
	input.reserve(5);
	for( int i = 0; i < 5; i++)
	{
		CModelData data;
		std::string insert_name = name_str_list[i];
		data.setName(insert_name);
		input.push_back(data);		
	}		
	return input;
}

PYBIND11_MODULE(MyData, m) {
	py::class_<CModelData>(m, "CModelData")
		.def(py::init<>())				
		.def("setName", &CModelData::setName)
		.def("getName", &CModelData::getName)
		;
		
	m.def("mytest", &mytest);
	m.def("modify", &modify, "Multiply all entries of a list by 2.0");
	m.def("readfile", &readfile, "Multisdfsdfdsfist by 2.0");
		// m.def("test", &test, "testsdfsdf");
		// m.def("append_1", &append_1, "sdfdsf");
		//m.def_readwrite("test_concat", &test_concat, "sdfsdf");
}
