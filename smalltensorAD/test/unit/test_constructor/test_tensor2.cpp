#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
	ad_graph<double> GRAPH;
	tensor2<ad_dual<double>, 3, 3> obj1;
	obj1(1,2) = ad_dual<double>(GRAPH,3) ;

	ASSERT_MSG(obj1(1,2).get_value()==3,"tensor2(n1,n2) assignment error");

	tensor2<ad_dual<double>, 3, 3> obj2(obj1) ;

	ASSERT_MSG(obj2(1,2).get_value()==3,"obj2(n1,n2) copy constructor error");
	tensor2<ad_dual<double>, 3, 3> obj3;
	obj3 = obj1;
	ASSERT_MSG(obj3(1,2).get_value()==3,"obj3(n1,n2) copy assignment operator error");

	tensor2<ad_dual<double>, 3, 3> obj4(std::move(obj1));
	ASSERT_MSG(obj4(1,2).get_value()==3,"obj4(n1,n2) move constructor error");

	tensor2<ad_dual<double>, 3, 3> obj5 ;
	obj5 = std::move(obj2);
	ASSERT_MSG(obj5(1,2).get_value()==3,"obj5(n1,n2) move assignment operator error");

	// Ident<'i'> i;
	// Ident<'j'> j;

	// tensor2<ad_dual<double>, 3, 3> L;
	// tensor2<ad_dual<double>, 3, 3> R;
	// L(0,0) = 9; R(0,0) = 2;
	// ad_dual<double> ret = L(i,j) * R(i,j);
	// ASSERT_MSG(ret==18,"expr2 tensor2 contraction error");


	return 0;
}