#ifndef IRRITATED_BAR_HPP
#define IRRITATED_BAR_HPP
#include<array>
#include<vector>
#include"wx/app.h"
#include"wx/frame.h"
#include"wx/timer.h"
#include"creater_manager.hpp"
namespace ib
{
	class app
		: public wxApp
	{
	public :
		auto OnInit ( ) -> bool ;
	} ;
	enum
	{
		timer_id
	} ;
	class frame
		: public wxFrame
	{
		wxTimer timer { this , timer_id } ;
		std::array < bool , 5 > is_on_key { { false , false , false , false , false } } ;
		wxPoint point { Width / 2 , Height / 2 } ;
		std::vector < std::shared_ptr < creater_base > > drawer_list ;
		wxDECLARE_EVENT_TABLE ( ) ;
	public :
		frame ( ) ;
		auto on_timer ( wxTimerEvent & ) -> void ;
		auto on_key_down ( wxKeyEvent & event ) -> void ;
		auto on_key_up ( wxKeyEvent & event ) -> void ;
		auto on_paint ( wxPaintEvent & ) -> void ;
	} ;
}
#endif
