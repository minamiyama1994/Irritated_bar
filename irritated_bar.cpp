#include<iostream>
#include<fstream>
#include"wx/dcbuffer.h"
#include"irritated_bar.hpp"
namespace ib
{
	auto app::OnInit ( ) -> bool
	{
		auto f = new frame { } ;
		f->Show ( true ) ;
		return true ;
	}
	frame::frame ( )
		: wxFrame { nullptr , - 1 , "イライラ棒" , wxDefaultPosition , wxSize { Width , Height } , wxDEFAULT_FRAME_STYLE & ~ ( wxRESIZE_BORDER | wxMAXIMIZE_BOX ) }
	{
		std::ifstream ifile { "irritated_bar.dat" , std::ios_base::in } ;
		if ( ! ifile )
		{
			throw std::runtime_error { "データが読み込めません" } ;
		}
		for ( ; ifile ; )
		{
			try
			{
				std::string mod_name ;
				std::getline ( ifile , mod_name ) ;
				creater_manager crearer_getter { mod_name } ;
				drawer_list.push_back ( crearer_getter.creater ( this ) ) ;
			}
			catch ( create_error & e )
			{
			}
		}
		SetClientSize ( wxSize { Width , Height } ) ;
		SetBackgroundColour ( wxColour { 1 , 1 , 1 } ) ;
		timer.Start ( 10 ) ;
	}
	auto frame::on_timer ( wxTimerEvent & ) -> void
	{
		auto shift = is_on_key [ 4 ] ? 4 : 2 ;
		if ( is_on_key [ 0 ] )
		{
			point += wxPoint { 0 , - shift } ;
		}
		if ( is_on_key [ 1 ] )
		{
			point += wxPoint { 0 , shift } ;
		}
		if ( is_on_key [ 2 ] )
		{
			point += wxPoint { - shift , 0 } ;
		}
		if ( is_on_key [ 3 ] )
		{
			point += wxPoint { shift , 0 } ;
		}
		if ( point.x < 0 )
		{
			point.x = 0 ;
		}
		else if ( point.x >= Width )
		{
			point.x = Width - 1 ;
		}
		if ( point.y < 0 )
		{
			point.y = 0 ;
		}
		else if ( point.y >= Height )
		{
			point.y = Height - 1 ;
		}
		Refresh ( false ) ;
	}
	auto frame::on_key_down ( wxKeyEvent & event ) -> void
	{
		switch ( event.GetKeyCode ( ) )
		{
			case WXK_UP :
			{
				is_on_key [ 0 ] = true ;
			}
			break ;
			case WXK_DOWN  :
			{
				is_on_key [ 1 ] = true ;
			}
			break ;
			case WXK_LEFT :
			{
				is_on_key [ 2 ] = true ;
			}
			break ;
			case WXK_RIGHT  :
			{
				is_on_key [ 3 ] = true ;
			}
			break ;
			case WXK_SHIFT  :
			{
				is_on_key [ 4 ] = true ;
			}
			break ;
		}
	}
	auto frame::on_key_up ( wxKeyEvent & event ) -> void
	{
		switch ( event.GetKeyCode ( ) )
		{
			case WXK_UP :
			{
				is_on_key [ 0 ] = false ;
			}
			break ;
			case WXK_DOWN  :
			{
				is_on_key [ 1 ] = false ;
			}
			break ;
			case WXK_LEFT :
			{
				is_on_key [ 2 ] = false ;
			}
			break ;
			case WXK_RIGHT  :
			{
				is_on_key [ 3 ] = false ;
			}
			break ;
			case WXK_SHIFT  :
			{
				is_on_key [ 4 ] = false ;
			}
			break ;
		}
	}
	auto frame::on_paint ( wxPaintEvent & ) -> void
	{
		wxBufferedPaintDC dc { this } ;
		dc.Clear ( ) ;
		dc.SetPen ( wxPen { wxColour { 0xFF , 0xFF , 0xFF } } ) ;
		dc.SetBrush ( wxBrush { wxColour { 0xFF , 0xFF , 0xFF } } ) ;
		dc.DrawCircle ( point , 5 ) ;
	}
}
wxIMPLEMENT_APP ( ib::app ) ;
wxBEGIN_EVENT_TABLE ( ib::frame , wxFrame )
	EVT_TIMER ( timer_id , ib::frame::on_timer )
	EVT_KEY_DOWN ( ib::frame::on_key_down )
	EVT_KEY_UP ( ib::frame::on_key_up )
	EVT_PAINT ( ib::frame::on_paint )
wxEND_EVENT_TABLE ( )
