#ifndef IRRITATED_BAR_INTERFACE_HPP
#define IRRITATED_BAR_INTERFACE_HPP
#include<memory>
#include"wx/dc.h"
extern "C"
{
	extern const int Width ;
	extern const int Height ;
}
namespace ib
{
	class creater_base
	{
		wxWindow * window_ ;
		virtual auto draw_impl ( wxWindow * window , wxDC & x ) -> void = 0 ;
	public :
		creater_base ( ) = delete ;
		creater_base ( const creater_base & ) = delete ;
		creater_base ( creater_base && ) = delete ;
		auto operator = ( const creater_base & ) -> creater_base & = delete ;
		auto operator = ( creater_base && ) -> creater_base & = delete ;
		virtual ~ creater_base ( ) ;
		creater_base ( wxWindow * window ) ;
		auto draw ( int x ) -> void ;
	} ;
}
#endif
