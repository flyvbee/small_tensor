///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// LTensor                                                                   //
//                                                                           //
// A Tensor Library with full Indicial Notation                              //
//                                                                           //
// Version 0.1                                                               //
// December 1, 2008                                                          //
//                                                                           //
// Copyright (C) 2007-2009-...                                               //
// Alejandro Limache & Sebastian Rojas Fredini                               //
//                                                                           //
// International Center of Computational Methods in Engineering  (CIMEC)     //
// Santa Fe, Argentina                                                       //
// alejandrolimache@gmail.com                                                //
//                                                                           //
// LTensor is freely available through the websites:                         //
// http://www.cimec.org.ar/alimache/                                         //
// http://code.google.com/p/ltensor/                                         //
// It may be copied, modified, and redistributed for non-commercial use as   //
// long as the original authors and the Library get proper public credit     //
// for its use.                                                              //
// Please consult the file LICENSE for the detailed copyright notices.       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef Encapsulate_to_Expr2_H
#define Encapsulate_to_Expr2_H

///////////////////////////////////////////////////////////////
// ENCAPSULATE CLASS of general RANK to CLASS of RANK = 1
///////////////////////////////////////////////////////////////

/*! \brief A class used to encapsulate any object that can be indexed
	*
	*	This class is used as a common container to hold Marray Objects.
	*	It is responsible for permuting the indexes, applying constant indexes
	*	and indexed dimensions. This object can be indexed, and returns the correct
	*	data after, passing all the above described filters. This class is specialized
	*	for each possible combination in order to use expression templates.
	*	This class encapsulates all kind of Marray objects to rank 2 expressions, even if the Marray Object
	*	has a different rank(it must supply fixed indexes).
	*	\tparam	A The Object that can be indexed, usually an Marray
	*	\tparam T The type of the data this object will contain
	*	\tparam Rank The rank of the Marray Object it holds
	*	\tparam Permutation A number that indicates the order the indexes are permuted. If the index
	*	is repeated it means it is a contracting index. And this class is in charge of the operation.
	*	\tparam Indexed is a number similar to Permutation but it indicates which indexes use an
	*	extern index indicating the arbitrary positions to loop. 0 if no Indexing is made
	*	\tparam i A char used to instantiate the ArrayH objects. No really necesary, but useful for future improvementes.
	*	\tparam j A char used to instantiate the ArrayH objects. No really necesary, but useful for future improvementes.
	*	\tparam k A char used to instantiate the ArrayH objects. No really necesary, but useful for future improvementes.
	*	\tparam l A char used to instantiate the ArrayH objects. No really necesary, but useful for future improvementes.
	*	\remarks The Permutation and Indexed numbers are interpreted in a digit basis. Eg:1233 means 1 and 2 are free indexes
	*	and 3 and 4 are contracting indexes.
	*/

template<class A, class T, int Rank, int Permutation, class idxObject1=void, class idxObject2=void, class idxObject3=void, class idxObject4=void>
class Encapsulate_to_Expr2
{
	/*! \brief A reference to the encapsulated object */
	A & TA;

	public:

	/*! \brief Constructs a new encapsulation
	*
	*	Constructs a new encapsulation. No memory is allocated here. All the objects are passed by reference,
	*	this is important because is a time-critic method. The constructor always receives the object intencapsulates
	*	and depending on the indexing number, it can receive the IndexH objects, that contains the indexes to use.
	*
	*/

	Encapsulate_to_Expr2(A &a): TA(a){}


	/*! \brief Indexing operator
	*
	*	This method allows the treatment of this class generically, no matter what it encapsulates
	*	\param N1 the first index
	*	\param N2 the second index
	*	\returns The data at position (N1,N2)
	*/
	T operator()(const int N1,const int N2) const
	{
		return TA(N1,N2);
	}

	/*! \brief Indexing operator
	*
	*	This method allows the treatment of this class generically, no matter what it encapsulates
	*	\param N1 the first index
	*	\param N2 the second index
	*	\returns The data at position (N1,N2)
	*/
	T & operator()(const int N1,const int N2)
	{
		return TA(N1,N2);
	}

	/*! \brief Returns the first dimension of the object it encapsulates */
  	int get_dim1() const
	{
		return TA.get_dim1();
	}

	/*! \brief Returns the second dimension of the object it encapsulates */
	int get_dim2() const
	{
		return TA.get_dim2();
	}
};

///////////////////////////////////////////////////////////////
// ENCAPSULATE CLASS of RANK = 2 to CLASS of RANK = 2
///////////////////////////////////////////////////////////////

template<class A, class T>
class Encapsulate_to_Expr2<A,T,2,12>
{
	A & TA;
	public:

	Encapsulate_to_Expr2(A &a): TA(a){}

	T operator()(const int N1,const int N2) const
	{
		return TA(N1,N2);
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(N1,N2);
	}

  	int get_dim1() const
	{

		return TA.get_dim1();
	}

	int get_dim2() const
	{
		return TA.get_dim2();
	}
};


template<class A, class T,class idxObject1, class idxObject2>
class Encapsulate_to_Expr2<A,T,2,12,idxObject1, idxObject2>
{
	A & TA;

	const idxObject1 &index1;
	const idxObject2 &index2;


	public:

	Encapsulate_to_Expr2(A &a, const idxObject1 &i1, const idxObject2 &i2): TA(a),index1(i1),index2(i2){}

	T operator()(const int N1,const int N2) const
	{
		return TA(index1(N1),index2(N2));
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(index1(N1),index2(N2));
	}

  	int get_dim1() const
	{

		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index2.get_dim2(TA);
	}
};




//DONE DONE DONE DONE DONE

///////////////////////////////////////////////////////////////
// ENCAPSULATE CLASS of RANK = 3 to CLASS of RANK = 2
///////////////////////////////////////////////////////////////

template<class A, class T>
class Encapsulate_to_Expr2<A,T,3,12>
{
	A & TA;
	const int N3;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3): TA(a), N3(NN3){}

	T operator()(const int N1,const int N2) const
	{
		return TA(N1,N2,N3);
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(N1,N2,N3);
	}

  	int get_dim1() const
	{
		return TA.get_dim1();
	}

	int get_dim2() const
	{
		return TA.get_dim2();
	}
};


template<class A, class T,class idxObject1, class idxObject2>
class Encapsulate_to_Expr2<A,T,3,12,idxObject1,idxObject2>
{
	A & TA;
	const int N3;

	const idxObject1 &index1;
	const idxObject2 &index2;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3, const idxObject1 &i1, const idxObject2 &i2): TA(a), N3(NN3)
						,index1(i1),index2(i2){}

	T operator()(const int N1,const int N2) const
	{
		return TA(index1(N1),index2(N2),N3);
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(index1(N1),index2(N2),N3);
	}

  	int get_dim1() const
	{
		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index2.get_dim2(TA);
	}
};


//DONE DONE DONE DONE DONE DONE DONE
//Parn NO-TEMA


template<class A, class T>
class Encapsulate_to_Expr2<A,T,3,13>
{
	A & TA;
	const int N3;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3): TA(a), N3(NN3){}

	T operator()(const int N1,const int N2) const
	{
		return TA(N1,N3,N2);
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(N1,N3,N2);
	}

  	int get_dim1() const
	{
		return TA.get_dim1();
	}

	int get_dim2() const
	{
		return TA.get_dim3();
	}
};

template<class A, class T, class idxObject1, class idxObject3>
class Encapsulate_to_Expr2<A,T,3,13,idxObject1,idxObject3>
{
	A & TA;
	const int N3;
	const idxObject1 &index1;
	const idxObject3 &index3;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3,const idxObject1 &i1, const idxObject3 &i3): TA(a), N3(NN3),
						index1(i1),index3(i3){}

	T operator()(const int N1,const int N2) const
	{
		return TA(index1(N1),N3,index3(N2));
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(index1(N1),N3,index3(N2));
	}

  	int get_dim1() const
	{
		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index3.get_dim3(TA);
	}
};

//DONE DONE DONE DONEDONE DONE DONEDONE DONE DONE DONE DONE DONE

template<class A, class T, class idxObject2, class idxObject3>
class Encapsulate_to_Expr2<A,T,3,23,idxObject2,idxObject3>
{
	A & TA;
	const int N3;
	const idxObject2 &index2;
	const idxObject3 &index3;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3, const idxObject2 &i2, const idxObject3 &i3): TA(a), N3(NN3),
						index2(i2),index3(i3){}

	T operator()(const int N1,const int N2) const
	{
		return TA(N3,index2(N1),index3(N2));
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(N3,index2(N1),index3(N2));
	}

  	int get_dim1() const
	{
		return index2.get_dim2(TA);
	}

	int get_dim2() const
	{
		return index3.get_dim3(TA);
	}
};



//DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE
//kaze no fantasia


///////////////////////////////////////////////////////////////
// ENCAPSULATE CLASS of RANK = 4 to CLASS of RANK = 2
///////////////////////////////////////////////////////////////


template<class A, class T, class idxObject1, class idxObject2>
class Encapsulate_to_Expr2<A,T,4,12,idxObject1,idxObject2>
{
	A & TA;
	const int N3;
	const int N4;
	const idxObject1 &index1;
	const idxObject2 &index2;
	public:
	Encapsulate_to_Expr2(A &a, const int NN3, const int NN4,const idxObject1 &i1,const idxObject2 &i2):
						TA(a), N3(NN3), N4(NN4),index1(i1),index2(i2) {}

	T operator()(const int N1,const int N2) const
	{
		return TA(index1(N1),index2(N2),N3,N4);
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(index1(N1),index2(N2),N3,N4);
	}

  	int get_dim1() const
	{
		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index2.get_dim2(TA);
	}
};


//DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE



template<class A, class T ,class idxObject1, class idxObject3>
class Encapsulate_to_Expr2<A,T,4,13,idxObject1, idxObject3>
{
	A & TA;
	const int N3;
	const int N4;

	const idxObject1 &index1;
	const idxObject3 &index3;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3, const int NN4, const idxObject1 &i1,const idxObject3 &i3):
						TA(a), N3(NN3), N4(NN4),index1(i1),index3(i3) {}

	T operator()(const int N1,const int N2) const
	{
		return TA(index1(N1),N3,index3(N2),N4);
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(index1(N1),N3,index3(N2),N4);
	}

  	int get_dim1() const
	{
		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index3.get_dim3(TA);
	}
};


//DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE

template<class A, class T, class idxObject1, class idxObject4>
class Encapsulate_to_Expr2<A,T,4,14,idxObject1, idxObject4>
{
	A & TA;
	const int N3;
	const int N4;
	const idxObject1 &index1;
	const idxObject4 &index4;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3, const int NN4,const idxObject1 &i1,const idxObject4 &i4):
						TA(a), N3(NN3), N4(NN4),index1(i1),index4(i4) {}

	T operator()(const int N1,const int N2) const
	{
		return TA(index1(N1),N3,N4,index4(N2));
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(index1(N1),N3,N4,index4(N2));
	}

  	int get_dim1() const
	{
		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index4.get_dim4(TA);
	}
};



//DONE DONE DONE DONE DONE DONE



template<class A, class T, class idxObject2, class idxObject3>
class Encapsulate_to_Expr2<A,T,4,23,idxObject2, idxObject3>
{
	A & TA;
	const int N3;
	const int N4;
	const idxObject2 &index2;
	const idxObject3 &index3;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3, const int NN4,const idxObject2 &i2, const idxObject3 &i3):
						TA(a), N3(NN3), N4(NN4),index2(i2),index3(i3) {}

	T operator()(const int N1,const int N2) const
	{
		return TA(N3,index2(N1),index3(N2),N4);
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(N3,index2(N1),index3(N2),N4);
	}

  	int get_dim1() const
	{
		return index2.get_dim2(TA);
	}

	int get_dim2() const
	{
		return index3.get_dim3(TA);
	}
};

// DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE


template<class A, class T, class idxObject2, class idxObject4>
class Encapsulate_to_Expr2<A,T,4,24,idxObject2,idxObject4>
{
	A & TA;
	const int N3;
	const int N4;

	const idxObject2 &index2;
	const idxObject4 &index4;

	public:
	Encapsulate_to_Expr2(A &a, const int NN3, const int NN4, const idxObject2 &i2, const idxObject4 &i4):
						TA(a), N3(NN3), N4(NN4),index2(i2),index4(i4) {}

	T operator()(const int N1,const int N2) const
	{
		return TA(N3,index2(N1),N4,index4(N2));
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(N3,index2(N1),N4,index4(N2));
	}

  	int get_dim1() const
	{
		return index2.get_dim2(TA);
	}

	int get_dim2() const
	{
		return index4.get_dim4(TA);
	}
};

//DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE


template<class A, class T, class idxObject3, class idxObject4>
class Encapsulate_to_Expr2<A,T,4,34,idxObject3,idxObject4>
{
	A & TA;
	const int N3;
	const int N4;

	const idxObject3 &index3;
	const idxObject4 &index4;
	public:
	Encapsulate_to_Expr2(A &a, const int NN3, const int NN4,const idxObject3 &i3,const idxObject4 &i4):
						TA(a), N3(NN3), N4(NN4),index3(i3),index4(i4) {}

	T operator()(const int N1,const int N2) const
	{
		return TA(N3,N4,index3(N1),index4(N2));
	}

	T & operator()(const int N1,const int N2)
	{
		return TA(N3,N4,index3(N1),index4(N2));
	}

  	int get_dim1() const
	{
		return index3.get_dim3(TA);
	}

	int get_dim2() const
	{
		return index4.get_dim4(TA);
	}
};


//DONDE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE

///////////////////////////////////////////////////////////////////////
// ENCAPSULATE CLASS of RANK = 2 from CONTRACTIONS OF CLASS of RANK = 4
///////////////////////////////////////////////////////////////////////

// Case T(i,j,k,l) ===> C(i,j)= T(i,j,N3,N3)
// Permutation = i j N3 N3 ===> 1 2 3 3
//

template<class A, class T,class idxObject1,class idxObject2,class idxObject3,class idxObject4>
class Encapsulate_to_Expr2<A,T,4,1233,idxObject1,idxObject2,idxObject3,idxObject4>
{
	A & TA;

	const idxObject1 &index1;
	const idxObject2 &index2;
	const idxObject3 &index3;
	const idxObject4 &index4;

	public:
	Encapsulate_to_Expr2(A &a, const idxObject1 &i1, const idxObject2 &i2, const idxObject3 &i3, const idxObject4 &i4):
						TA(a),index1(i1),index2(i2),index3(i3),index4(i4)
	{
		#ifdef USE_ASSERT_Encapsulate
			assert (TA.get_dim3() == TA.get_dim4();
			assert (TA.get_dim1() != 0);
			assert (TA.get_dim2() != 0);
			assert (TA.get_dim3() != 0);
			assert (TA.get_dim4() != 0);
		#endif
	}

	T operator()(const int N1,const int N2) const
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim3();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(N1),index2(N2),index3(n1),index4(n1));
		}
		return res;
	}

	T & operator()(const int N1,const int N2)
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim3();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(N1),index2(N2),index3(n1),index4(n1));
		}
		return res;
	}

  	int get_dim1() const
	{
		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index2.get_dim2(TA);
	}
};

//DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE

// Case T(i,j,k,l) ===> C(i,j)= T(i,N3,j,N3)
// Permutation = i N3 j N3 ===> 1 3 2 3


template<class A, class T,class idxObject1,class idxObject2,class idxObject3,class idxObject4>
class Encapsulate_to_Expr2<A,T,4,1323,idxObject1,idxObject2,idxObject3,idxObject4>
{
	A & TA;

	const idxObject1 &index1;
	const idxObject2 &index2;
	const idxObject3 &index3;
	const idxObject4 &index4;

	public:
	Encapsulate_to_Expr2(A &a, const idxObject1 &i1, const idxObject2 &i2, const idxObject3 &i3, const idxObject4 &i4):
						TA(a),index1(i1),index2(i2),index3(i3),index4(i4)
	{
		#ifdef USE_ASSERT_Encapsulate
			assert (TA.get_dim2() == TA.get_dim4();
			assert (TA.get_dim1() != 0);
			assert (TA.get_dim2() != 0);
			assert (TA.get_dim3() != 0);
			assert (TA.get_dim4() != 0);
		#endif
	}

	T operator()(const int N1,const int N2) const
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim2();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(N1),index2(n1),index3(N2),index4(n1));
		}
		return res;
	}

	T & operator()(const int N1,const int N2)
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim2();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(N1),index2(n1),index3(N2),index4(n1));
		}
		return res;
	}

  	int get_dim1() const
	{
		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index3.get_dim3(TA);
	}
};

//done done done done done done done done done


// Case T(i,j,k,l) ===> C(i,j)= T(i,N3,j,N3)
// Permutation = i N3 j N3 ===> 1 3 3 2
//

template<class A, class T,class idxObject1,class idxObject2,class idxObject3,class idxObject4>
class Encapsulate_to_Expr2<A,T,4,1332,idxObject1, idxObject2,idxObject3,idxObject4>
{
	A & TA;

	const idxObject1 &index1;
	const idxObject2 &index2;
	const idxObject3 &index3;
	const idxObject4 &index4;

	public:
	Encapsulate_to_Expr2(A &a, const idxObject1 &i1, const idxObject2 &i2, const idxObject3 &i3, const idxObject4 &i4):
						TA(a),index1(i1),index2(i2),index3(i3),index4(i4)
	{
		#ifdef USE_ASSERT_Encapsulate
			assert (TA.get_dim2() == TA.get_dim3();
			assert (TA.get_dim1() != 0);
			assert (TA.get_dim2() != 0);
			assert (TA.get_dim3() != 0);
			assert (TA.get_dim4() != 0);
		#endif
	}

	T operator()(const int N1,const int N2) const
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim2();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(N1),index2(n1),index3(n1),index4(N2));
		}
		return res;
	}

	T & operator()(const int N1,const int N2)
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim2();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(N1),index2(n1),index3(n1),index4(N2));
		}
		return res;
	}

  	int get_dim1() const
	{
		return index1.get_dim1(TA);
	}

	int get_dim2() const
	{
		return index4.get_dim4(TA);
	}
};

//done

//DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE

// Case T(i,j,k,l) ===> C(i,j)= T(N3,i,j,N3)
// Permutation = N3 i j N3 ===> 3 1 2 3
//

template<class A, class T,class idxObject1,class idxObject2,class idxObject3,class idxObject4>
class Encapsulate_to_Expr2<A,T,4,3123,idxObject1,idxObject2,idxObject3,idxObject4>
{
	A & TA;

	const idxObject1 &index1;
	const idxObject2 &index2;
	const idxObject3 &index3;
	const idxObject4 &index4;

	public:
	Encapsulate_to_Expr2(A &a, const idxObject1 &i1, const idxObject2 &i2, const idxObject3 &i3, const idxObject4 &i4):
						TA(a),index1(i1),index2(i2),index3(i3),index4(i4)
	{
		#ifdef USE_ASSERT_Encapsulate
			assert (TA.get_dim1() == TA.get_dim4();
			assert (TA.get_dim1() != 0);
			assert (TA.get_dim2() != 0);
			assert (TA.get_dim3() != 0);
			assert (TA.get_dim4() != 0);
		#endif
	}

	T operator()(const int N1,const int N2) const
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim1();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(n1),index2(N1),index3(N2),index4(n1));
		}
		return res;
	}

	T & operator()(const int N1,const int N2)
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim1();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(n1),index2(N1),index3(N2),index4(n1));
		}
		return res;
	}

  	int get_dim1() const
	{
		return index2.get_dim2(TA);
	}

	int get_dim2() const
	{
		return index3.get_dim3(TA);
	}
};

//DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE


// Case T(i,j,k,l) ===> C(i,j)= T(N3,i,N3,j)
// Permutation = N3 i N3 j ===> 3 1 3 2
//

template<class A, class T,class idxObject1,class idxObject2,class idxObject3,class idxObject4>
class Encapsulate_to_Expr2<A,T,4,3132,idxObject1,idxObject2,idxObject3,idxObject4>
{
	A & TA;

	const idxObject1 &index1;
	const idxObject2 &index2;
	const idxObject3 &index3;
	const idxObject4 &index4;

	public:
	Encapsulate_to_Expr2(A &a, const idxObject1 &i1, const idxObject2 &i2, const idxObject3 &i3, const idxObject4 &i4):
						TA(a),index1(i1),index2(i2),index3(i3),index4(i4)
	{
		#ifdef USE_ASSERT_Encapsulate
			assert (TA.get_dim1() == TA.get_dim3();
			assert (TA.get_dim1() != 0);
			assert (TA.get_dim2() != 0);
			assert (TA.get_dim3() != 0);
			assert (TA.get_dim4() != 0);
		#endif
	}

	T operator()(const int N1,const int N2) const
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim1();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(n1),index2(N1),index3(n1),index4(N2));
		}
		return res;
	}

	T & operator()(const int N1,const int N2)
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim1();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(n1),index2(N1),index3(n1),index4(N2));
		}
		return res;
	}

  	int get_dim1() const
	{
		return index2.get_dim2(TA);
	}

	int get_dim2() const
	{
		return index4.get_dim4(TA);
	}
};


//DONE DONE DONE DONE DONE DONE DONE DONE DONE DONE ODNE DONE

// Case T(i,j,k,l) ===> C(i,j)= T(N3,N3,i,j)
// Permutation = N3 N3 i j ===> 3 3 1 2
//

template<class A, class T,class idxObject1,class idxObject2,class idxObject3,class idxObject4>
class Encapsulate_to_Expr2<A,T,4,3312,idxObject1,idxObject2,idxObject3,idxObject4>
{
	A & TA;

	const idxObject1 &index1;
	const idxObject2 &index2;
	const idxObject3 &index3;
	const idxObject4 &index4;

	public:
	Encapsulate_to_Expr2(A &a, const idxObject1 &i1, const idxObject2 &i2, const idxObject3 &i3, const idxObject4 &i4):
						TA(a),index1(i1),index2(i2),index3(i3),index4(i4)
	{
		#ifdef USE_ASSERT_Encapsulate
			assert (TA.get_dim1() == TA.get_dim2();
			assert (TA.get_dim1() != 0);
			assert (TA.get_dim2() != 0);
			assert (TA.get_dim3() != 0);
			assert (TA.get_dim4() != 0);
		#endif
	}

	T operator()(const int N1,const int N2) const
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim1();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(n1),index2(n1),index3(N1),index4(N2));
		}
		return res;
	}

	T & operator()(const int N1,const int N2)
	{
		T res = 0;
		int n1;
		int const dim1 = TA.get_dim1();
		for (n1 = 0; n1 < dim1; ++n1)
		{
			res += (TA)(index1(n1),index2(n1),index3(N1),index4(N2));
		}
		return res;
	}

  	int get_dim1() const
	{
		return index3.get_dim3(TA);
	}

	int get_dim2() const
	{
		return index4.get_dim4(TA);
	}
};

//DONE DONE DONE DONE DONE DONE DONE DONE DONE DOEN DOENDEODNEDE
#endif
