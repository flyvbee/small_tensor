#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
	ad_graph<double> GRAPH;
	tensor1<ad_dual<double>, 3> obj1(GRAPH,0.) ;

	obj1(2) = ad_dual<double>(GRAPH,3) ;
	ASSERT_MSG(obj1(2).get_value() == 3,"tensor1(n1) assignment error");

	tensor1<ad_dual<double>, 3> obj2(obj1) ;
	ASSERT_MSG(obj2(2).get_value() == 3,"obj2(n1) copy constructor error");

	tensor1<ad_dual<double>, 3> obj3(GRAPH,0.) ;
	obj3 = obj1;
	ASSERT_MSG(obj3(2).get_value() ==3,"obj3(n1) copy assignment operator error");

	tensor1<ad_dual<double>, 3> obj4(std::move(obj1));
	ASSERT_MSG(obj4(2).get_value() ==3,"obj4(n1) move constructor error");

	tensor1<ad_dual<double>, 3> obj5 ;
	obj5 = std::move(obj2);
	ASSERT_MSG(obj5(2).get_value() ==3,"obj5(n1) move assignment operator error");

	// Ident<'i'> i;
	// Ident<'j'> j;

	// tensor1<ad_dual<double>, 3> L;
	// tensor1<ad_dual<double>, 3> R;
	// L(0,0) = 9; R(0,0) = 2;
	// ad_dual<double> ret = L(i,j) * R(i,j);
	// ret = L(i,j) * R(j,i);
	// ASSERT_MSG(ret==18,"expr2 tensor2 contraction error");


	return 0;
}