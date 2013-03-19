#include "pch.h" 

using namespace IControls::ScrollView ;

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


IScrollView::IScrollView()
{
	initIscrollcontrols();
	initanimationproperties();
	//tempinit();
}


#pragma region Controls
 
void IScrollView::initIscrollcontrols()
{  
	this->_ipanel =  ref new StackPanel();
	this->_ipanel->Orientation = Orientation::Horizontal ;
	this->_ipanel->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	this->_ipanel->ManipulationMode  = ManipulationModes::All ;
	this->_iscroll =  ref new ScrollViewer();
	this->Children->Append(this->_iscroll);
	this->_iscroll->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Enabled ;
	this->_iscroll->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
	this->_iscroll->VerticalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled ; 
	this->_iscroll->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Disabled;
	this->_iscroll->Content =  this->_ipanel ;

	this->_paneltransform = ref new CompositeTransform();
	this->_ipanel->RenderTransform = this->_paneltransform ;

	this->_ipanel->ManipulationStarted += ref new ManipulationStartedEventHandler(this, & IControls::ScrollView::IScrollView::IPanel_ManipulationStarted_1);
	this->_ipanel->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, & IControls::ScrollView::IScrollView::IPanel_ManipulationDelta_1);
	this->_ipanel->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, & IControls::ScrollView::IScrollView::IPanel_ManipulationCompleted_1);
	this->_ipanel->ManipulationInertiaStarting += ref new ManipulationInertiaStartingEventHandler(this, & IControls::ScrollView::IScrollView::IPanel_ManipulationInertiaStarting_1);
}

#pragma endregion

#pragma region Private Methods


void IControls::ScrollView::IScrollView::IScroll_ItemLockParent(Platform::Object^ sender,  int32 _item)
{
	this->_manipulationstate =  IScrollManipulationState::Dislable ;
}

void IControls::ScrollView::IScrollView::IScroll_ItemUnlockParent(Platform::Object^ sender,  int32 _item)
{
	this->_manipulationstate =  IScrollManipulationState::Enable ;
}

void  IControls::ScrollView::IScrollView::IPanel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}
	
void IControls::ScrollView::IScrollView::IPanel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}
	
void  IControls::ScrollView::IScrollView::IPanel_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e)
{ 
	if(_currentitem > 0)
		this->_maxptranslate = ( ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemWidth ) / 2 ; 
	else
		this->_maxptranslate =  10000.0 ;

	if(_currentitem < this->_numberofitems - 1 )
		this->_maxntranslate = -1 * (((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemWidth ) / 2 ; 
	else
		this->_maxntranslate =  -10000.0 ; 
	_temptranslate = this->_paneltransform->TranslateX ; 
}
	
void  IControls::ScrollView::IScrollView::IPanel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	float64  x , x_factor = 1.0 , _currentdelta, _currenttranslate  =  this->_paneltransform->TranslateX;
	
	if(this->_manipulationstate == IScrollManipulationState::Enable)
	{
		if(this->_paneltransform->TranslateX > this->_initialtranslate + 1 || this->_paneltransform->TranslateX < this->_finaltranslate - 1)
		{ 
			x = fmod( abs(this->_finaltranslate -  _currenttranslate), abs(this->_finaltranslate)) ;
			if(x > 0)
				x_factor = 5.0 / x ; 

		}else
		{
			x_factor = 1.0 ;
			_currentdelta = e->Delta.Translation.X ;
			x=1.0 ;

		} 

		this->_cumulative += e->Delta.Translation.X ;

		if(!e->IsInertial)
		{
			this->_paneltransform->TranslateX += (e->Delta.Translation.X * x_factor); ///_currentdelta ; 
		}
		else
		{
			if(x < 100.0 ) 
			{
				this->_paneltransform->TranslateX += (e->Delta.Translation.X * x_factor); ///_currentdelta ; 
			}
			else
				e->Complete(); 
		} 
		_currenttranslate = this->_paneltransform->TranslateX ;
	}
	else
	{
		int aaa =  0  ;
	}

	if(_cumulative < this->_maxntranslate || _cumulative > this->_maxptranslate )
	{
		e->Complete();
		e->Handled = true ;
		return ;
	}
}
	
void  IControls::ScrollView::IScrollView::IPanel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	if(_cumulative > _maxptranslate / 2)
	{
		 float64 a0 = _temptranslate  + ( ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemWidth )/2; 
		this->_panelanimation->To = a0;
		this->_panelstory->Begin();
		_currentitem -= 1 ;
	}
	else
	{
		if(_cumulative < _maxntranslate / 2)
		{
			this->_panelanimation->To = _temptranslate - ( ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemWidth )/2 ;
			this->_panelstory->Begin();
			_currentitem += 1 ;
		}
		else
		{
			this->_panelanimation->To = _temptranslate  ;
			this->_panelstory->Begin();
		}
	}
	 
	_cumulative = 0.0; 
}
	
void  IControls::ScrollView::IScrollView::IPanel_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{ 
	//if(this->_manipulationstate == IScrollManipulationState::Enable)
		//e->TranslationBehavior->DesiredDeceleration = 10.0 * 96.0 / (1000.0 * 1000.0);
}
 
#pragma endregion


#pragma region  Animations
 
void IScrollView::initanimationproperties()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 2500000 ;
	Windows::UI::Xaml::Duration duration(ts) ;

	this->_panelstory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_panelanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_panelanimation->Duration = duration ;
	this->_panelstory->Children->Append(this->_panelanimation);
	Windows::UI::Xaml::Media::Animation::CubicEase ^ ease1 = ref new Windows::UI::Xaml::Media::Animation::CubicEase();
	ease1->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut ;
	//this->_panelanimation->EasingFunction = ref new Windows
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_panelanimation , "TranslateX");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_panelanimation , _paneltransform);
}

#pragma endregion


#pragma region  DataLoad Temp


void IScrollView::tempinit()
{
	float64 _h = 900 ;
	float64 _w = 1600 ;
	this->_scrollheight = _h ;
	this->_scrollwidth = _w ;
	this->_currentitem = 0 ;
	this->_numberofitems = _itemslist->Size ;
	
	float64 ftranslate = 0.0 ;

	for (int i = 0; i < _itemslist->Size; i++)
	{
		IScrollViewItem ^ item1  = ref new IScrollViewItem();
		item1->Height = _h ;
		item1->ItemWidth = 1200 ;
		/**if(i==1 || i==5 || i==9)
			item1->ItemWidth = 1600 ;
		else
			item1->ItemWidth = 1200 ;

		if(i%2 > 0)
			item1->Background = ref new SolidColorBrush(Windows::UI::Colors::Azure);
		else
			item1->Background = ref new SolidColorBrush(Windows::UI::Colors::GreenYellow);*/
		ftranslate += item1->ItemWidth ;

		item1->Source = _itemslist->GetAt(i);
		this->_ipanel->Children->Append(item1);
	}

	this->_finaltranslate = -1 * ( ftranslate - _w/2 - ((IScrollViewItem^)_ipanel->Children->GetAt(9))->ItemWidth / 2  ) ;
	this->_initialtranslate = (_w - ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth ) / 2 ;

	
	this->_paneltransform->TranslateX = (_w - ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth ) / 2 ;


	if(_currentitem > 0)
		this->_maxptranslate = ( ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemWidth ) / 2 ; 
	else
		this->_maxptranslate =  10000.0 ;

	if(_currentitem < this->_numberofitems - 1 )
		this->_maxntranslate = -1 * (((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemWidth ) / 2 ; 
	else
		this->_maxntranslate =  -10000.0 ; 
	_temptranslate = this->_paneltransform->TranslateX ;
	 
 
}

#pragma endregion