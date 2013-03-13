#include "pch.h"

using namespace IControls;
using namespace IControls::StackView;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

IStackScroll::IStackScroll()
{
	initscrollcontrols();
	initpointerfunctions();
	initanimationproperties();
}

void IStackScroll::additem(Grid^ item)
{
	this->_panelstacks->Children->Append(item);
}

#pragma region Stack Scroll 

void IStackScroll::initscrollcontrols()
{
	this->_scrollgrid = ref new Windows::UI::Xaml::Controls::Grid();
	this->Children->Append(this->_scrollgrid);
	this->_panelstacks = ref new Windows::UI::Xaml::Controls::StackPanel();
	this->_panelstacks->Orientation = Windows::UI::Xaml::Controls::Orientation::Horizontal ;
	this->_panelstacks->Background = ref new SolidColorBrush(Windows::UI::Colors::Blue);
	this->_panelstacks->ManipulationMode = ManipulationModes::All ;
	this->_scrollviewer = ref new Windows::UI::Xaml::Controls::ScrollViewer() ; 
	this->_scrollviewer->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Enabled;
	this->_scrollviewer->VerticalScrollMode =  Windows::UI::Xaml::Controls::ScrollMode::Disabled;
	this->_scrollviewer->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Visible ;
	this->_scrollviewer->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden ;
	this->_scrollviewer->ZoomMode = ZoomMode::Disabled ;
	this->_scrollviewer->IsHorizontalRailEnabled  = false ;
	this->_scrollgrid->Children->Append(this->_scrollviewer);
	this->_scrollviewer->Content = this->_panelstacks ;

	this->_paneltransform = ref new CompositeTransform();
	this->_panelstacks->RenderTransform = this->_paneltransform ;

	this->_panelstacks->PointerPressed += ref new PointerEventHandler(this, &IControls::IStackScroll::Panel_PointerPressed_1);
	this->_panelstacks->PointerReleased += ref new PointerEventHandler(this, &IControls::IStackScroll::Panel_PointerReleased_1);
	this->_panelstacks->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &IControls::IStackScroll::Panel_ManipulationCompleted_1);
	this->_panelstacks->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &IControls::IStackScroll::Panel_ManipulationDelta_1);
	this->_panelstacks->ManipulationInertiaStarting += ref new ManipulationInertiaStartingEventHandler(this, &IControls::IStackScroll::Panel_ManipulationInertiaStarting_1);
	
}
			

#pragma endregion

#pragma region Stack Scroll Animations
 
void IStackScroll::initanimationproperties()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 3000000 ;
	Windows::UI::Xaml::Duration duration(ts) ;

	this->_panelstory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_panelanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_panelanimation->Duration = duration ;
	this->_panelstory->Children->Append(this->_panelanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_panelanimation , "TranslateX");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_panelanimation , _paneltransform);
}

#pragma endregion


#pragma region Stack Scroll Private Methods

void IControls::IStackScroll::Panel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	//if(_scrolltouches == ScrollStackTouches::One &&  _scrollmanipulationstate == ScrollManipulationState::Enable)
	if(this->_numberoftouches <= 1 &&  _scrollmanipulationstate == ScrollManipulationState::Enable)
	{
		float64 x = fmod( abs(this->_finaltranslate - this->_currenttrnaslate), abs(this->_finaltranslate)) ;
		if(this->_paneltransform->TranslateX > this->_initialtranslate || this->_paneltransform->TranslateX < this->_finaltranslate)
		{ 
			this->_currentdelta = e->Delta.Translation.X / ( x+1 ) * 5 ;
		}else
		{
			this->_currentdelta = e->Delta.Translation.X ;
			x=0.0 ;
		}

		//this->_paneltransform->TranslateX += this->_currentdelta ;

		if(!e->IsInertial)
		{
			this->_paneltransform->TranslateX += this->_currentdelta ;
		}
		else
		{
			if(x < 100.0)
				this->_paneltransform->TranslateX += this->_currentdelta ;
			else
				e->Complete(); 
		} 
		this->_currenttrnaslate = this->_paneltransform->TranslateX ;

	}
}
	
 
void IControls::IStackScroll::Panel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	if(this->_paneltransform->TranslateX > this->_initialtranslate )
	{
		this->_panelanimation->To = this->_initialtranslate;
		this->_panelstory->Begin();
	}
		
	if(this->_paneltransform->TranslateX < this->_finaltranslate)
	{
		this->_panelanimation->To = this->_finaltranslate ;
		this->_panelstory->Begin();
	}

	this->_scrolltouches = ScrollStackTouches::Zero ;
}
	

void IControls::IStackScroll::Panel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	(this->*_pointerreleasedfunctions[(int32)this->_scrolltouches - 1 ])();
	this->_numberoftouches -= 1 ;
}
	
void IControls::IStackScroll::Panel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	(this->*_pointerpressedfunctions[(int32)this->_scrolltouches])();
	this->_numberoftouches += 1 ;
}		

void IControls::IStackScroll::Panel_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{

}


void IStackScroll::initprivateproperties()
{
	this->_scrollmanipulationside = ScrollManipulationSide::Inside ;
	this->_scrollmanipulationstate = ScrollManipulationState::Enable ;
	this->_scrolldeltatype = ScrollDeltaType::Normal ;
	 
	this->_numberoftouches = 0 ;
	this->_initialtranslate = 0.0 ;
	this->_finaltranslate = 0.0 ;
	this->_currenttrnaslate  = 0.0 ;
}

#pragma endregion

#pragma region Stack Scroll Temporal Data Load
 
void IStackScroll::loaditems()
{
	for (int i = 0; i < 5; i++)
	{
		IStackView^ tmpstack = ref new IStackView();
		tmpstack->ItemContentHeight = 300 ;
		tmpstack->ItemContentWidth = 400 ;
		tmpstack->ItemHeight = 300 ;
		tmpstack->ItemWidth = 460 ;
		tmpstack->StackWidth = 800 ;
		tmpstack->ItemsList = _itemslist ;	
		this->_panelstacks->Children->Append(tmpstack);
	}
	
}

#pragma endregion


#pragma region Pointer Pressed Functions
 
bool IStackScroll::zeropressed()
{
	this->_scrolltouches = ScrollStackTouches::One;
	return true ;
}

bool IStackScroll::onepressed()
{
	this->_scrolltouches = ScrollStackTouches::Many;
	return true ;
}

bool IStackScroll::manypressed()
{
	this->_scrolltouches = ScrollStackTouches::Many;
	return true ;
}
 
bool IStackScroll::onereleased()
{
	this->_scrolltouches = ScrollStackTouches::Zero ;
	return true ;
}
	
bool IStackScroll::manyreleased()
{
	if(this->_numberoftouches == 2)
		this->_scrolltouches = ScrollStackTouches::One ;
	return true ;
}

void IStackScroll::initpointerfunctions()
{
	_pointerpressedfunctions[0] =  &IStackScroll::zeropressed ;
	_pointerpressedfunctions[1] =  &IStackScroll::onepressed ;
	_pointerpressedfunctions[2] =  &IStackScroll::manypressed ;
	
	_pointerreleasedfunctions[0] = &IStackScroll::onereleased;
	_pointerreleasedfunctions[1] = &IStackScroll::manyreleased;	
}

#pragma endregion
