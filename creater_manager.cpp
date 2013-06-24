#include"creater_manager.hpp"
#include"irritated_bar_interface.hpp"
#include"wx/dynlib.h"
namespace ib
{
	create_error::create_error ( )
		: runtime_error { "" }
	{
	}
	class creater_manager::Impl
	{
		wxDynamicLibrary dll ;
	public :
		Impl ( ) = delete ;
		Impl ( const Impl & ) = delete ;
		Impl ( Impl && ) = delete ;
		auto operator = ( const Impl & ) -> Impl & = delete ;
		auto operator = ( Impl && ) -> Impl & = delete ;
		~ Impl ( ) = default ;
		Impl ( const std::string & dll_name ) ;
		auto creater ( wxWindow * window ) -> std::shared_ptr < creater_base > ;
	} ;
	creater_manager::Impl::Impl ( const std::string & dll_name )
		: dll { dll_name + ".mdl" , wxDL_QUIET }
	{
		static_assert ( sizeof ( std::size_t ) == sizeof ( creater_base * ( * ) ( ) ) , "sizeof ( std::size_t ) == sizeof ( creater_base * ( * ) ( ) )" ) ;
		if ( ! dll.IsLoaded ( ) )
		{
			throw create_error { } ;
		}
		if ( ! dll.HasSymbol ( "create" ) )
		{
			throw create_error { } ;
		}
	}
	auto creater_manager::Impl::creater ( wxWindow * window ) -> std::shared_ptr < creater_base >
	{
		std::size_t address_number = reinterpret_cast < std::size_t > ( dll.GetSymbol ( "create" ) ) ;
		auto address = reinterpret_cast < creater_base * ( * ) ( wxWindow * ) > ( address_number ) ;
		return std::shared_ptr < creater_base > { address ( window ) } ;
	}
	creater_manager::creater_manager ( const std::string & dll_name )
		: impl_ { new Impl { dll_name } }
	{
	}
	auto creater_manager::creater ( wxWindow * window ) -> std::shared_ptr < creater_base >
	{
		return impl_-> creater ( window ) ;
	}
	creater_manager::~ creater_manager ( )
	{
		delete impl_ ;
		impl_ = nullptr ;
	}
}
