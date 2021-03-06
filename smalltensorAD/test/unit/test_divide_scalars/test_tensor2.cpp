#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor2<ad_dual<double>, 3,3> obj1(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj2(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj3(GRAPH,0.);
	obj1(2,2) = ad_dual<double>(GRAPH,3.);
	obj2(2,2) = ad_dual<double>(GRAPH,2.);
	Ident<'i'> _i;
	Ident<'j'> _j;
	obj3(_i,_j) = obj2(_i,_j) / 2;
	ASSERT_MSG(obj3(2,2)== 1,"tensor2(_i,_j) plus operator error");

	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}