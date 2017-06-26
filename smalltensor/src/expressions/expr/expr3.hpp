#ifndef EXPR3_HPP_
#define EXPR3_HPP_

template <typename __dat_t, std::size_t __d1, std::size_t __d2, std::size_t __d3> class tensor3;
template<typename __dat_t, std::size_t __d1, std::size_t __d2, std::size_t __d3, char __i, char __j, char __k>
class expr3: public tensor3<__dat_t, __d1, __d2, __d3>
{
public:
    typedef tensor3<__dat_t, __d1, __d2, __d3> _tensor3;
    expr3()=delete;
    expr3(expr3 const& rhs_)=delete;
    expr3& operator=(expr3 const& rhs_){
    	memcpy(_tensor3::_data, rhs_._tensor3::_data, __d1*__d2*__d3);
    	return (*this);
    }
    expr3 operator=(expr3&& rhs_) noexcept{
    	_tensor3::_data = std::move(rhs_._tensor3::_data);
    	return (*this);
    }
};





#endif