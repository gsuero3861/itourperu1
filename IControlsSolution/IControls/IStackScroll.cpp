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
	_ismanipulating = false ;
}

void IStackScroll::additem(Grid^ item)
{
	this->_panelstacks->Children->Append(item);
}

#pragma region Stack Scroll 

void IStackScroll::initscrollcontrols()
{
	this->_scrollgrid = ref new Windows::UI::Xaml::Controls::Grid();
	
	//this->_scrollgrid->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	//this->_scrollgrid->ManipulationMode = ManipulationModes::All ;

	this->Children->Append(this->_scrollgrid);
	this->_panelstacks = ref new Windows::UI::Xaml::Controls::StackPanel();
	this->_panelstacks->Orientation = Windows::UI::Xaml::Controls::Orientation::Horizontal ;
	this->_panelstacks->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
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
	ts.Duration = 4500000 ;
	Windows::UI::Xaml::Duration duration(ts) ;

	this->_panelstory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_panelanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_panelanimation->Duration = duration ;

	Windows::UI::Xaml::Media::Animation::CubicEase ^ ease1 =  ref new Windows::UI::Xaml::Media::Animation::CubicEase();
	ease1->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut ; 
	this->_panelanimation->EasingFunction = ease1 ;
	this->_panelstory->Children->Append(this->_panelanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_panelanimation , "TranslateX");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_panelanimation , _paneltransform);
}

#pragma endregion


#pragma region Stack Scroll Private Methods

 
void IControls::IStackScroll::StackView_TranformChanged(Platform::Object^ sender)
{
	float64 _cumulativepos = 0.0 ;

	///set the X and Y position to every stack
	for (int i = 0 ; i < this->_numberofstacks ; i++)
	{
		((IStackView^)this->_panelstacks->Children->GetAt(i))->FullXPosition = abs(this->_paneltransform->TranslateX) - _cumulativepos + 800.0 ;
		((IStackView^)this->_panelstacks->Children->GetAt(i))->FullYPosition = 0.0 ;
		_cumulativepos += ((IStackView^)this->_panelstacks->Children->GetAt(i))->CurrentWidth ;
	}
}

void IControls::IStackScroll::StackViewScrollTo(Platform::Object^ sender, float64 delta)
{
	float64 _delta = this->_paneltransform->TranslateX + delta  ;
	
	if(_delta < this->_scrollgrid->Width - this->_panelstacks->ActualWidth) //this->_finaltranslate + (((IStackView^)sender)->CurrentScale -1)*((IStackView^)sender)->ItemWidth )
		_delta = this->_scrollgrid->Width - this->_panelstacks->ActualWidth ;
	if(_delta > 0.0)
		_delta = 0.0 ;
	this->_paneltransform->TranslateX = _delta ;
}

void IControls::IStackScroll::StackViewManipulationStarted_1(Platform::Object ^ sender , int32 _type)
{
	_scrollmanipulationstate = ScrollManipulationState::Dislable ; 
	StackScrollLockParent(this, _selectedstack); ///Lock MainScroll
}

void IControls::IStackScroll::StackViewManipulationFinished(Platform::Object ^ sender , int32 _type)
{
	_scrollmanipulationstate = ScrollManipulationState::Enable ; 
	//StackScrollUnlockParent(this, _selectedstack);
}

//when an stack is openned
void IControls::IStackScroll::StackViewOpen_1(Platform::Object^ sender, int32 _stacknumber )
{ 
	float64 _citemposition = 0.0;
	float64 _newfinalpos =  this->_scrollgrid->Width -  this->_panelstacks->ActualWidth  ; 
	for (int i = 0; i < _stacknumber; i++)
	{
		_citemposition += ((IStackView^)this->_panelstacks->Children->GetAt(i))->CurrentWidth;
	}
	if( _citemposition * -1  < _newfinalpos )
		this->_panelanimation->To = _newfinalpos ;
	else
		this->_panelanimation->To = _citemposition * -1 ;

	this->_panelanimation->To = _citemposition * -1 ;
	this->_panelstory->Begin();
	float64 delta = (((IStackView^)sender)->StackSize - 1) * ((IStackView^)sender)->ItemWidth ; 
	this->_finaltranslate = _newfinalpos ;

	StackScrollLockParent(this, _selectedstack);
	//this->_finaltranslate -= delta ;
	//this->_panelstacks->Width += delta ; 
}

//when an stack is closed
void IControls::IStackScroll::StackViewClose_1(Platform::Object^ sender, int32 _stacknumber , float64 _scroll)
{ 
	float64 _citemposition = 0.0;
	float64 _newfinalpos =  this->_scrollgrid->Width -  this->_panelstacks->ActualWidth + (((IStackView^)sender)->CurrentScale - 1) * ((IStackView^)sender)->ItemWidth   ; 
	float64 _newctranslate = this->_paneltransform->TranslateX + _scroll ;
	
	if(_newctranslate > 0.0 )
		_newctranslate = 0.0 ;
	if(_newctranslate < _newfinalpos )
		_newctranslate = _newfinalpos ;	
	this->_panelanimation->To  =  _newctranslate ;
	this->_panelstory->Begin();
	float64 delta = (((IStackView^)sender)->StackSize - 1) * ((IStackView^)sender)->ItemWidth ;
	this->_finaltranslate = _newfinalpos ;

	//this->_finaltranslate += delta ;
	//this->_panelstacks->Width -= delta ; 
}


void IControls::IStackScroll::Panel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	float64 x ;
	
	//if(_scrolltouches == ScrollStackTouches::One &&  _scrollmanipulationstate == ScrollManipulationState::Enable) this->_numberoftouches <= 1 &&
	if(  _scrollmanipulationstate == ScrollManipulationState::Enable)
	{
		
		if(this->_paneltransform->TranslateX > this->_initialtranslate || this->_paneltransform->TranslateX < this->_finaltranslate )//|| abs(this->_finaltranslate) < this->_scrollgrid->Width)
		{ 
			x = fmod( abs(this->_finaltranslate - this->_currenttrnaslate), abs(this->_finaltranslate)) ;
			if(x > 0)
				this->_currentdelta = e->Delta.Translation.X / ( x + 1 ) * 5 ; 
		}else
		{
			this->_currentdelta = e->Delta.Translation.X ;
			x=1.0 ;
		}

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
		_ismanipulating = true ;
		
		if(this->_paneltransform->TranslateX > this->_initialtranslate + 70.0 || this->_paneltransform->TranslateX < this->_finaltranslate - 70.0)//this->_paneltransform->TranslateX > 100.0)
		{
			StackScrollUnlockParent(this, _selectedstack);
			_scrollmanipulationstate == ScrollManipulationState::Dislable ;
		}
	}
	else
	{
		int a = 0 ;
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
	_ismanipulating = false ;
	//this->_scrolltouches = ScrollStackTouches::Zero ;
	//this->_numberoftouches = 0 ;
	 _scrollmanipulationstate = ScrollManipulationState::Enable ;
	 StackScrollLockParent(this, _selectedstack); //lock
	 
}
	

void IControls::IStackScroll::Panel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	StackScrollUnlockParent(this, _selectedstack);
	//(this->*_pointerreleasedfunctions[(int32)this->_scrolltouches - 1 ])();
	//this->_numberoftouches -= 1 ;
}
	
void IControls::IStackScroll::Panel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	//(this->*_pointerpressedfunctions[(int32)this->_scrolltouches])();
	//this->_numberoftouches += 1 ;
	float64 a = this->_scrollgrid->Width ;
	float64 b= this->_panelstacks->ActualWidth ;
	this->_finaltranslate = this->_scrollgrid->Width - this->_panelstacks->ActualWidth  ;
}		

void IControls::IStackScroll::Panel_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{
	//e->Handled = true ;
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

void IStackScroll::loadchapter()
{
	_numberofstacks =  this->_datasource->Sections->Size;
	for (int i = 0; i < _numberofstacks; i++)
	{
		IStackView^ tmpstack = ref new IStackView();
		tmpstack->ItemContentHeight = 180 ;
		tmpstack->ItemContentWidth = 240 ;
		tmpstack->ItemHeight = 180 ;
		tmpstack->ItemWidth = 320 ;
		tmpstack->StackWidth = 500 ;
		//tmpstack->ItemsList = _itemslist ;	
		tmpstack->StackDataSource = this->_datasource->Sections->GetAt(i);
		tmpstack->StackNumber = i ;
		tmpstack->OnStackViewOpen += ref new StackViewOpenEventHandler(this, &IControls::IStackScroll::StackViewOpen_1);
		tmpstack->OnStackViewClose += ref new StackViewCloseEventHandler(this, &IControls::IStackScroll::StackViewClose_1);
		tmpstack->StackViewManipulationStarted += ref new StackViewManipulationStartedEventHandler(this, &IControls::IStackScroll::StackViewManipulationStarted_1);
		tmpstack->StackViewManipulationFinished += ref new StackViewManipulationFinishedEventHandler(this, &IControls::IStackScroll::StackViewManipulationFinished);
		tmpstack->StackViewScrollTo += ref new StackViewScrollToEventHandler(this,&IControls::IStackScroll::StackViewScrollTo );
		tmpstack->StackViewTranformChanged += ref new StackViewTranformChangedEventHandler(this, &IControls::IStackScroll::StackView_TranformChanged);
		tmpstack->StackViewFullScreenAnimationStarted += ref new StackViewFullScreenAnimationStartedEventHandler(this, &IControls::IStackScroll::StackView_FullScreenAnimationStarted);
		tmpstack->StackViewFullScreenAnimationCompleted += ref new StackViewFullScreenAnimationCompletedEventHandler(this, &IControls::IStackScroll::StackView_FullScreenAnimationCompleted);
		tmpstack->Background = ref new SolidColorBrush(Windows::UI::Colors::GreenYellow);
		this->_panelstacks->Children->Append(tmpstack);
	}
}
 
void IStackScroll::loaditems()
{  
	_numberofstacks = 5 ;
	for (int i = 0; i < _numberofstacks; i++)
	{
		IStackView^ tmpstack = ref new IStackView();
		tmpstack->ItemContentHeight = 180 ;
		tmpstack->ItemContentWidth = 240 ;
		tmpstack->ItemHeight = 180 ;
		tmpstack->ItemWidth = 320 ;
		tmpstack->StackWidth = 500 ;
		tmpstack->ItemsList = _itemslist ;	
		tmpstack->StackNumber = i ;
		tmpstack->OnStackViewOpen += ref new StackViewOpenEventHandler(this, &IControls::IStackScroll::StackViewOpen_1);
		tmpstack->OnStackViewClose += ref new StackViewCloseEventHandler(this, &IControls::IStackScroll::StackViewClose_1);
		tmpstack->StackViewManipulationStarted += ref new StackViewManipulationStartedEventHandler(this, &IControls::IStackScroll::StackViewManipulationStarted_1);
		tmpstack->StackViewManipulationFinished += ref new StackViewManipulationFinishedEventHandler(this, &IControls::IStackScroll::StackViewManipulationFinished);
		tmpstack->StackViewScrollTo += ref new StackViewScrollToEventHandler(this,&IControls::IStackScroll::StackViewScrollTo );
		tmpstack->StackViewTranformChanged += ref new StackViewTranformChangedEventHandler(this, &IControls::IStackScroll::StackView_TranformChanged);
		tmpstack->StackViewFullScreenAnimationStarted += ref new StackViewFullScreenAnimationStartedEventHandler(this, &IControls::IStackScroll::StackView_FullScreenAnimationStarted);
		tmpstack->StackViewFullScreenAnimationCompleted += ref new StackViewFullScreenAnimationCompletedEventHandler(this, &IControls::IStackScroll::StackView_FullScreenAnimationCompleted);
		tmpstack->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
		this->_panelstacks->Children->Append(tmpstack);
	}
	
	//this->_panelstacks->Width = numberofstacks * 600 ;
	this->_finaltranslate = -1* _numberofstacks * 500  + 1600;
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


#pragma region Interaction 

///Stackanimation Started
void IControls::IStackScroll::StackView_FullScreenAnimationStarted(Platform::Object^ sender, int32 _stacknumber,int32 _itemnumber)
{
}
	
//Stackanimation Completed
void IControls::IStackScroll::StackView_FullScreenAnimationCompleted(Platform::Object^ sender, int32 _stacknumber,int32 _itemnumber)
{
}

#pragma endregion

 