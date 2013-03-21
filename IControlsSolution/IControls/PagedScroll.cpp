#include  "pch.h"

using namespace IControls ;

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


PagedScroll::PagedScroll()
{
	initpagedscrollcontrols();
	initanimationproperties();
	//tempinit();
}


#pragma region Controls
 
void PagedScroll::initpagedscrollcontrols()
{
	this->_manipulationstate =  PagedScrollManipulationState::Dislable ;

	this->_pagedpanel =  ref new StackPanel();
	this->_pagedpanel->Orientation = Orientation::Horizontal ;
	this->_pagedpanel->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	this->_pagedpanel->ManipulationMode  = ManipulationModes::All ;
	this->_pagedscroll =  ref new ScrollViewer();
	this->Children->Append(this->_pagedscroll);
	this->_pagedscroll->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Enabled ;
	this->_pagedscroll->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
	this->_pagedscroll->VerticalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled ; 
	this->_pagedscroll->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Disabled;
	this->_pagedscroll->Content =  this->_pagedpanel ;

	this->_paneltransform = ref new CompositeTransform();
	this->_pagedpanel->RenderTransform = this->_paneltransform ;

	this->_pagedpanel->ManipulationStarted += ref new ManipulationStartedEventHandler(this, & IControls::PagedScroll::PagedPanel_ManipulationStarted_1);
	this->_pagedpanel->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, & IControls::PagedScroll::PagedPanel_ManipulationDelta_1);
	this->_pagedpanel->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, & IControls::PagedScroll::PagedPanel_ManipulationCompleted_1);
	this->_pagedpanel->ManipulationInertiaStarting += ref new ManipulationInertiaStartingEventHandler(this, & IControls::PagedScroll::PagedPanel_ManipulationInertiaStarting_1);
}

#pragma endregion

#pragma region Private Methods


void IControls::PagedScroll::PagedScroll_ItemLockParent(Platform::Object^ sender,  int32 _item)
{
	this->_manipulationstate =  PagedScrollManipulationState::Dislable ;
}

void IControls::PagedScroll::PagedScroll_ItemUnlockParent(Platform::Object^ sender,  int32 _item)
{
	this->_manipulationstate =  PagedScrollManipulationState::Enable ;
}

void IControls::PagedScroll::PagedScrollItem_AnimationOutStarted(Platform::Object^ sender,  int32 _section, int32 _page)
{
	this->_currentpage = _page ;
	this->_currentsection = _section ;
	PagedScrollAnimationOutStarted(this);
}
	
void IControls::PagedScroll::PagedScrollItem_AnimationOutCompleted(Platform::Object^ sender,  int32 _section, int32 _page)
{
	this->_currentpage = _page ;
	this->_currentsection = _section ;
	PagedScrollAnimationOutCompleted(this);
}



void  IControls::PagedScroll::PagedPanel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}
	
void IControls::PagedScroll::PagedPanel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}
	
void  IControls::PagedScroll::PagedPanel_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e)
{
}
	
void  IControls::PagedScroll::PagedPanel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	float64  x , x_factor = 1.0 ,  _currentdelta = 1.0 , _currenttranslate  =  this->_paneltransform->TranslateX;
	if(abs(_cumulative) > this->_scrollwidth )
	{
		e->Complete();
		e->Handled = true ;
		return ;
	}
	if(this->_manipulationstate == PagedScrollManipulationState::Enable)
	{
		if(this->_paneltransform->TranslateX > this->_initialtranslate || this->_paneltransform->TranslateX < this->_finaltranslate)
		{ 
			x = fmod( abs(this->_finaltranslate -  _currenttranslate), abs(this->_finaltranslate)) ;
			if(x > 0)
				x_factor = 5.0 /(x + 1)	;
				//_currentdelta = e->Delta.Translation.X / ( x + 1 ) * 5 ; 
		}
		else
		{
			x_factor = 1.0 ;	;
			//_currentdelta = e->Delta.Translation.X ;
			x=1.0 ;
		} 

		this->_cumulative += e->Delta.Translation.X ;

		if(!e->IsInertial)
		{
			this->_paneltransform->TranslateX += (e->Delta.Translation.X * x_factor);  //+= _currentdelta ; 
		}
		else
		{
			if(x < 100.0 && abs(this->_cumulative) <=  this->_scrollwidth)
			{
				this->_paneltransform->TranslateX += (e->Delta.Translation.X * x_factor) ; // += _currentdelta ; 
			}
			else
				e->Complete(); 
		} 
		_currenttranslate = this->_paneltransform->TranslateX ;
	}
}
	
void  IControls::PagedScroll::PagedPanel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	//if(this->_manipulationstate == PagedScrollManipulationState::Enable)
	//{
		//int32 a =(int)(this->_cumulative / this->_scrollwidth +1 ) ;
		this->_currentitem = (int32)floor((abs(this->_paneltransform->TranslateX) + this->_scrollwidth / 2 ) / this->_scrollwidth ) ;
		this->_panelanimation->To = -1 * this->_scrollwidth * this->_currentitem ;
		this->_panelstory->Begin();
		this->_currentchapter = this->_currentitem ;
	///}
	 
	this->_manipulationstate = PagedScrollManipulationState::Dislable ;
	_cumulative = 0.0;
 
}
	
void  IControls::PagedScroll::PagedPanel_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{ 
	//if(this->_manipulationstate == PagedScrollManipulationState::Enable)
		//e->TranslationBehavior->DesiredDeceleration = 10.0 * 96.0 / (1000.0 * 1000.0);
}


#pragma endregion

#pragma region  Animations
 
void PagedScroll::initanimationproperties()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 2500000 ;
	Windows::UI::Xaml::Duration duration(ts) ;

	this->_panelstory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_panelanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_panelanimation->Duration = duration ;
	Windows::UI::Xaml::Media::Animation::CubicEase ^ cease = ref new Windows::UI::Xaml::Media::Animation::CubicEase();
	cease->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut ;
	this->_panelstory->Children->Append(this->_panelanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_panelanimation , "TranslateX");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_panelanimation , _paneltransform);
}

#pragma endregion


#pragma region  DataLoad Temp

void PagedScroll::temploaddata()
{
	this->_scrollheight = 900 ;
	this->_scrollwidth = 1600 ;
	this->_currentitem = 0 ;

	for (int i = 0; i < _datasource->Size; i++)
	{
		PagedScrollItem^ item1 =  ref new PagedScrollItem();
		//item1->ItemsList =  this->_itemslist ;
		item1->ChapterSource = this->_datasource->GetAt(i);
		item1->ItemNumber = 0 ;
		item1->ItemHeight = 900 ;
		item1->ItemWidth = 1600;
		item1->Background =  ref new SolidColorBrush(Windows::UI::Colors::Azure);
		item1->PagedScrollItemLockParent +=  ref new PagedScrollItemLockParentEventHandler(this, &IControls::PagedScroll::PagedScroll_ItemLockParent);
		item1->PagedScrollItemUnlockParent +=  ref new PagedScrollItemUnlockParentEventHandler(this, &IControls::PagedScroll::PagedScroll_ItemUnlockParent);
		item1->PagedScrollItemAnimationOutStarted +=  ref new PagedScrollItemAnimationOutStartedEventHandler(this, &IControls::PagedScroll::PagedScrollItem_AnimationOutStarted);
		item1->PagedScrollItemAnimationOutCompleted +=  ref new PagedScrollItemAnimationOutCompletedEventHandler(this, &IControls::PagedScroll::PagedScrollItem_AnimationOutCompleted);
		this->_pagedpanel->Children->Append(item1);
	}

	this->_finaltranslate = -1 * _scrollwidth * (_datasource->Size - 1 ) ;
	this->_initialtranslate = 0.0 ;
}

void PagedScroll::tempinit()
{
	this->_scrollheight = 900 ;
	this->_scrollwidth = 1600 ;
	this->_currentitem = 0 ;
	PagedScrollItem^ item1 =  ref new PagedScrollItem();
	item1->ItemsList =  this->_itemslist ;
	item1->ItemNumber = 0 ;
	item1->ItemHeight = 900 ;
	item1->ItemWidth = 1600;
	item1->Background =  ref new SolidColorBrush(Windows::UI::Colors::Azure);
	item1->PagedScrollItemLockParent +=  ref new PagedScrollItemLockParentEventHandler(this, &IControls::PagedScroll::PagedScroll_ItemLockParent);
	item1->PagedScrollItemUnlockParent +=  ref new PagedScrollItemUnlockParentEventHandler(this, &IControls::PagedScroll::PagedScroll_ItemUnlockParent);
	this->_pagedpanel->Children->Append(item1);


	PagedScrollItem^ item2 =  ref new PagedScrollItem();
	item2->ItemsList =  this->_itemslist ;
	item2->ItemNumber = 0 ;
	item2->ItemHeight = 900 ;
	item2->ItemWidth = 1600;
	item2->Background =  ref new SolidColorBrush(Windows::UI::Colors::GreenYellow);
	item2->PagedScrollItemLockParent +=  ref new PagedScrollItemLockParentEventHandler(this, &IControls::PagedScroll::PagedScroll_ItemLockParent);
	item2->PagedScrollItemUnlockParent +=  ref new PagedScrollItemUnlockParentEventHandler(this, &IControls::PagedScroll::PagedScroll_ItemUnlockParent);
	this->_pagedpanel->Children->Append(item2);

	PagedScrollItem^ item3 =  ref new PagedScrollItem();
	item3->ItemsList =  this->_itemslist ;
	item3->ItemNumber = 0 ;
	item3->ItemHeight = 900 ;
	item3->ItemWidth = 1600;
	item3->Background =  ref new SolidColorBrush(Windows::UI::Colors::Azure);
	item3->PagedScrollItemLockParent +=  ref new PagedScrollItemLockParentEventHandler(this, &IControls::PagedScroll::PagedScroll_ItemLockParent);
	item3->PagedScrollItemUnlockParent +=  ref new PagedScrollItemUnlockParentEventHandler(this, &IControls::PagedScroll::PagedScroll_ItemUnlockParent);
	this->_pagedpanel->Children->Append(item3);
 
	 

	this->_finaltranslate = -1 * 1600 * 2 ;
	this->_initialtranslate = 0.0 ;
}

#pragma endregion