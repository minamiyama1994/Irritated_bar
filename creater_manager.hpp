#ifndef CREATER_CREATER_HPP
#define CREATER_CREATER_HPP
#include<string>
#include<stdexcept>
#include"irritated_bar_interface.hpp"
namespace ib
{
	class create_error
		: public std::runtime_error
	{
	public :
		create_error ( ) ;
	} ;
	class creater_manager
	{
		class Impl ;
		Impl * impl_ ;
	public :
		creater_manager ( ) = delete ;
		creater_manager ( const creater_manager & ) = delete ;
		creater_manager ( creater_manager && ) = delete ;
		auto operator = ( const creater_manager & ) -> creater_manager & = delete ;
		auto operator = ( creater_manager && ) -> creater_manager & = delete ;
		~ creater_manager ( ) ;
		creater_manager ( const std::string & dll_name ) ;
		auto creater ( wxWindow * window ) -> std::shared_ptr < creater_base > ;
	} ;
}
#endif
