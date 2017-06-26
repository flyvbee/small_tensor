#ifndef TENSOR4_HPP_
#define TENSOR4_HPP_
#include "../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;
template <typename __dat_t, std::size_t __d1, std::size_t __d2, std::size_t __d3, std::size_t __d4>
class tensor4
{
public:
	__dat_t* __restrict__ _data;

	tensor4(): _data{new __dat_t[__d1*__d2*__d3*__d4]}{}
	tensor4(tensor4 const& rhs_): _data{new __dat_t[__d1*__d2*__d3*__d4]}{
		std::memcpy(_data, rhs_._data, sizeof(_data));
	}
	tensor4& operator=(tensor4 const& rhs_){
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(_data));		
		}
		return *this;
	}
    tensor4(tensor4&& rhs_) noexcept: _data{std::move(rhs_._data)}{}
    tensor4& operator=(tensor4&& rhs_) noexcept{
    	if(this != &rhs_){
    		_data = std::move(rhs_._data);
    	}
    	return *this;
    }
	~tensor4(){
		if (_data!=nullptr){
		    delete[] _data;
		    _data=nullptr;
		}
	}

	inline __dat_t& operator()(std::size_t n1_, std::size_t n2_,  std::size_t n3_, std::size_t n4_){
		ASSERT_MSG(n1_< __d1 && n2_ < __d2 && n3_< __d3 && n4_ < __d4,"tensor4() index out of bounds in lvalue. ");
		return _data[ n1_ * __d2 * __d3 *__d4 + n2_ * __d3 * __d4 + n3_ * __d4 + n4_];
	}
	inline __dat_t operator()(std::size_t n1_, std::size_t n2_,  std::size_t n3_, std::size_t n4_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2 && n3_< __d3 && n4_ < __d4, "tensor4() index out of bounds in rvalue. ");
		return _data[ n1_ * __d2 * __d3 *__d4 + n2_ * __d3 * __d4 + n3_ * __d4 + n4_];
	}
	template <char i, char j, char k, char l>
	inline expr4<__dat_t, __d1, __d2, __d3, __d4, i, j, k, l>& operator()(Index<i> i_, Index<j> j_, Index<k> k_, Index<l> l_){
        return static_cast<expr4<__dat_t, __d1, __d2, __d3, __d4, i, j, k, l>&>(*this);
	}
};

#endif