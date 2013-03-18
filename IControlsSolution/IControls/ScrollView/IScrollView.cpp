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
	tempinit();
}


#pragma region Controls
 
void IScrollView::initIscrollcontrols()
{
	//this->_manipulationstate =  IScrollManipulationState::Dislable ;

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
	//this->_maxcumulative  = ( ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth ) / 2 ; 
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
				//_currentdelta = e->Delta.Translation.X /( ( x + 1 )  * 5);

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
			if(x < 100.0 ) // && this->_cumulative <=  this->_scrollwidth)
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
	/**
	if(_currentitem > 0)
		this->_maxptranslate = ( ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemWidth ) / 2 ; 
	else
		this->_maxptranslate =  10000.0 ;

	if(_currentitem < this->_numberofitems - 1 )
		this->_maxntranslate = -1 * (((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemWidth ) / 2 ; 
	else
		this->_maxntranslate =  -10000.0 ; 
	_temptranslate = this->_paneltransform->TranslateX ;
 */
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
	ts.Duration = 1500000 ;
	Windows::UI::Xaml::Duration duration(ts) ;

	this->_panelstory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_panelanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_panelanimation->Duration = duration ;
	this->_panelstory->Children->Append(this->_panelanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_panelanimation , "TranslateX");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_panelanimation , _paneltransform);
}

#pragma endregion


#pragma region  DataLoad Temp


void IScrollView::tempinit()
{
	this->_scrollheight = 900 ;
	this->_scrollwidth = 1600 ;
	this->_currentitem = 0 ;
	this->_numberofitems = 10 ;
	
	float64 ftranslate = 0.0 ;

	for (int i = 0; i < 10; i++)
	{
		IScrollViewItem ^ item1  = ref new IScrollViewItem();
		item1->Height = 900 ;
		if(i==1 || i==5 || i==9)
			item1->ItemWidth = 1600 ;
		else
			item1->ItemWidth = 1200 ;

		if(i%2 > 0)
			item1->Background = ref new SolidColorBrush(Windows::UI::Colors::Azure);
		else
			item1->Background = ref new SolidColorBrush(Windows::UI::Colors::GreenYellow);
		ftranslate += item1->ItemWidth ;
		this->_ipanel->Children->Append(item1);
	}

	this->_finaltranslate = -1 * ( ftranslate - 800 - ((IScrollViewItem^)_ipanel->Children->GetAt(9))->ItemWidth / 2  ) ;
	this->_initialtranslate = (1600 - ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth ) / 2 ;

	
	this->_paneltransform->TranslateX = (1600 - ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth ) / 2 ;


	if(_currentitem > 0)
		this->_maxptranslate = ( ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemWidth ) / 2 ; 
	else
		this->_maxptranslate =  10000.0 ;

	if(_currentitem < this->_numberofitems - 1 )
		this->_maxntranslate = -1 * (((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemWidth ) / 2 ; 
	else
		this->_maxntranslate =  -10000.0 ; 
	_temptranslate = this->_paneltransform->TranslateX ;
	 
	/*
	IScrollItem^ item1 =  ref new IScrollItem();
	item1->ItemsList =  this->_itemslist ;
	item1->ItemNumber = 0 ;
	item1->ItemHeight = 900 ;
	item1->ItemWidth = 1600;
	item1->Background =  ref new SolidColorBrush(Windows::UI::Colors::Azure);
	item1->IScrollItemLockParent +=  ref new IScrollItemLockParentEventHandler(this, &IControls::IScroll::IScroll_ItemLockParent);
	item1->IScrollItemUnlockParent +=  ref new IScrollItemUnlockParentEventHandler(this, &IControls::IScroll::IScroll_ItemUnlockParent);
	this->_ipanel->Children->Append(item1);


	IScrollItem^ item2 =  ref new IScrollItem();
	item2->ItemsList =  this->_itemslist ;
	item2->ItemNumber = 0 ;
	item2->ItemHeight = 900 ;
	item2->ItemWidth = 1600;
	item2->Background =  ref new SolidColorBrush(Windows::UI::Colors::GreenYellow);
	item2->IScrollItemLockParent +=  ref new IScrollItemLockParentEventHandler(this, &IControls::IScroll::IScroll_ItemLockParent);
	item2->IScrollItemUnlockParent +=  ref new IScrollItemUnlockParentEventHandler(this, &IControls::IScroll::IScroll_ItemUnlockParent);
	this->_ipanel->Children->Append(item2);

	IScrollItem^ item3 =  ref new IScrollItem();
	item3->ItemsList =  this->_itemslist ;
	item3->ItemNumber = 0 ;
	item3->ItemHeight = 900 ;
	item3->ItemWidth = 1600;
	item3->Background =  ref new SolidColorBrush(Windows::UI::Colors::Azure);
	item3->IScrollItemLockParent +=  ref new IScrollItemLockParentEventHandler(this, &IControls::IScroll::IScroll_ItemLockParent);
	item3->IScrollItemUnlockParent +=  ref new IScrollItemUnlockParentEventHandler(this, &IControls::IScroll::IScroll_ItemUnlockParent);
	this->_ipanel->Children->Append(item3);
 */ 

	//this->_finaltranslate = -1 * 1600 * 2 ;
	
}

#pragma endregion