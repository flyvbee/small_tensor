#pragma once



template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
inline expr2<val_type,d1,d2,i,j> operator*(
	   expr1<val_type,d1,i> const& Li_, 
	   expr1<val_type,d2,j> const& Rj_){
	typedef expr2<val_type,d1,d2,i,j> ret_type;
	ret_type ret_ij(*(Li_(0).get_graph()), 0.) ;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2)
		{
    		ret_ij(n1,n2) = Li_(n1) * Rj_(n2) ;
		}
	}
	return ret_ij;
}



