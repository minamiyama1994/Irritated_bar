#include"irritated_bar_interface.hpp"
#include"wx/dynlib.h"
#include"wx/dcbuffer.h"
extern "C"
{
	const int Width { 800 } ;
	const int Height { 600 } ;
}
namespace ib
{
	class irritated_bar_dc
		: public wxBufferedPaintDC
	{
		int offset_ ;
	public :
		irritated_bar_dc ( wxWindow * window , int offset ) ;
	} ;
	irritated_bar_dc::irritated_bar_dc ( wxWindow * window , int offset )
		: wxBufferedPaintDC { window }
		, offset_ { offset }
	{
		auto pos = GetDeviceOrigin ( ) ;
		SetDeviceOrigin ( pos.x + offset , pos.y ) ;
	}
	creater_base::creater_base ( wxWindow * window )
		: window_ { window }
	{
	}
	auto creater_base::draw ( int x ) -> void
	{
		irritated_bar_dc dc { window_ , Width - x - 1 } ;
	}
	creater_base::~ creater_base ( )
	{
	}
}
