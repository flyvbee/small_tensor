#pragma once

template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
inline val_type operator* (
       expr2<val_type,d1,d2,i,j> const& Lij_,  
       expr2<val_type,d1,d2,i,j> const& Rij_){
    val_type ret(*(Lij_(0,0).get_graph()), 0.) ;
    for (std::size_t n1 = 0; n1 < d1; ++n1){
      for (std::size_t n2 = 0; n2 < d2; ++n2){
        ret = ret + Lij_(n1,n2) * Rij_(n1,n2);
      }
    }
    return ret;
}


template <typename val_type, std::size_t d1, std::size_t d2, std::size_t d3,
          char i, char j, char k>
inline expr1<val_type,d1,i> operator* (
       expr3<val_type,d1,d2,d3,i,j,k> const& Lijk_,  
       expr2<val_type,d2,d3,j,k>      const& Rjk_){
    typedef expr1<val_type,d1,i> ret_type;
    ret_type ret_i(*(Rjk_(0,0).get_graph()), 0.) ;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      // ret_i(N1)=0;
      for (std::size_t n2 = 0; n2 < d2; ++n2){
        for (std::size_t n3 = 0; n3 < d3; ++n3){
          ret_i(N1) = ret_i(N1) + Lijk_(N1,n2,n3) * Rjk_(n2,n3);
        }
      }
    }
    return ret_i;
}


template <typename val_type, std::size_t d1, std::size_t d2, std::size_t d3,
          char i, char j, char k>
inline expr1<val_type,d1,i> operator* (
       expr2<val_type,d2,d3,j,k>      const& Ljk_,  
       expr3<val_type,d2,d3,d1,j,k,i> const& Rjki_){
    typedef expr1<val_type,d1,i> ret_type;
    ret_type ret_i(*(Ljk_(0,0).get_graph()), 0.) ;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      // ret_i(N1)=0;
      for (std::size_t n2 = 0; n2 < d2; ++n2){
        for (std::size_t n3 = 0; n3 < d3; ++n3){
          ret_i(N1) = ret_i(N1) + Ljk_(n2,n3) * Rjki_(n2,n3,N1);
        }
      }
    }
    return ret_i;
}




