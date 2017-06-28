#ifndef TENSOR2_HPP_
#define TENSOR2_HPP_
#include "../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;
template <typename __dat_t, std::size_t __d1, std::size_t __d2>
class tensor2
{
public:
	__dat_t* __restrict__ _data;

	tensor2(): _data{new __dat_t[__d1*__d2]}{}
	tensor2(tensor2 const& rhs_): _data{new __dat_t[__d1*__d2]}{
		DEBUG_MSG("tensor2 copy constructor is called");
		std::memcpy(_data, rhs_._data, sizeof(_data)*__d1*__d2);
	}
	tensor2& operator=(tensor2 const& rhs_){
		DEBUG_MSG("tensor2 copy assignment operator is called");
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(_data)*__d1*__d2);		
		}
		return *this;
	}

    tensor2(tensor2&& rhs_) noexcept
    : _data{new __dat_t[__d1*__d2]}
    {
    	std::swap(_data, rhs_._data);
    	DEBUG_MSG("tensor2 move constructor is called");
    }
    tensor2& operator=(tensor2&& rhs_) noexcept{
    	if(this != &rhs_){
    		std::swap(_data, rhs_._data);
    	}
    	DEBUG_MSG("tensor2 move assignment operator is called");
    	return *this;
    }
	~tensor2(){
		if (_data!=nullptr){
		    delete[] _data;
		    _data=nullptr;
		}
	}

	inline __dat_t& operator()(std::size_t n1_, std::size_t n2_){
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() index out of bounds in lvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	inline __dat_t operator()(std::size_t n1_, std::size_t n2_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() index out of bounds in rvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	template <char i, char j>
	inline expr2<__dat_t, __d1, __d2, i, j>& operator()(Index<i> i_, Index<j> j_){
        return static_cast<expr2<__dat_t, __d1, __d2, i, j>&>(*this);
	}

	template <char i>
	inline __dat_t operator()(Index<i> i_, Index<i> j_){
		ASSERT_MSG(__d1 == __d2, "Dimension size should be equal for dummy indices. ");
		__dat_t ret=0;
		for (int n1 = 0; n1 < __d1; ++n1){
			ret += (*this)(n1,n1);
		}
        return ret;
	}
};

#endif