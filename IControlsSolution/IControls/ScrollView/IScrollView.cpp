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
	this->_currentchapter = 0 ;
	this->_currentitem = 0 ;
	this->_currentpage = 0 ;
	this->_currentsection = 0 ;
	initIscrollcontrols();
	initanimationproperties(); 
	_counter = 0  ;
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

void IScrollView::setpage()
{
	int32 tmpcounter = 0 ;
	bool flag = false ;
	for (int i = 0; i < this->_chapterslist->Size ; i++)
	{
		for (int j = 0; j < this->_chapterslist->GetAt(i)->Sections->Size ; j++)
		{
			if(this->_currentitem + 1 > tmpcounter + this->_chapterslist->GetAt(i)->Sections->GetAt(j)->Pages->Size )
			{
				tmpcounter += this->_chapterslist->GetAt(i)->Sections->GetAt(j)->Pages->Size ;
			}
			else
			{
				this->_currentchapter = i ;
				this->_currentsection = j ;
				this->_currentpage = this->_currentitem - tmpcounter ;
				flag = true ;
				break ;
			}
		}
		if(flag) break ;
	}
}
 
void IScrollView::setscroll()
{
	int32 _citem = 0 ;
	for (int i = 0; i < _currentchapter; i++) 
		for (int j = 0; j < _chapterslist->GetAt(i)->Sections->Size ; j++)
		{
			_citem += _chapterslist->GetAt(i)->Sections->GetAt(j)->Pages->Size ;
		} 

	for (int i = 0; i < _currentsection; i++)
	{
		_citem += _chapterslist->GetAt(_currentchapter)->Sections->GetAt(i)->Pages->Size ;
	}

	_citem += _currentpage  ;
	_currentitem = _citem ;
	this->_paneltransform->TranslateX = -1 * ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemPosition ;
	
}

void IControls::ScrollView::IScrollView::IScrollItem_LockParent(Platform::Object^ sender,  int32 _item)
{
	this->_manipulationstate =  IScrollManipulationState::Dislable ;
	IScrollViewLockParent(this, _currentitem ) ;
}

void IControls::ScrollView::IScrollView::IScrollItem_UnlockParent(Platform::Object^ sender,  int32 _item)
{
	if(this->_pointerscounter < 2)
		this->_manipulationstate =  IScrollManipulationState::Enable ;
}

void  IControls::ScrollView::IScrollView::IPanel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	_pointerscounter += 1 ;
	if(this->_pointerscounter > 1 )
	{ 
		IScrollViewUnlockParent(this, _currentitem ) ;
	}
}
	
void IControls::ScrollView::IScrollView::IPanel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	_pointerscounter -= 1 ;
}
	
void  IControls::ScrollView::IScrollView::IPanel_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e)
{ 
	//_cumulative = 0.0; 
	_counter++ ;
	if(_counter > 1)	
	{
		e->Complete();
		e->Handled =  true ;
		return ;
	} 
	if(_currentitem > 0 )
	{
		this->_maxtranslate = -1 * ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemPosition ;
		this->_maxthreshold = _paneltransform->TranslateX + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemWidth / 3 ; 
	}
	else
	{
		this->_maxtranslate = this->_scrollwidth / 2 ;
		this->_maxthreshold = this->_scrollwidth ;
	}
	if(_currentitem < this->_numberofitems - 1)
	{
		this->_mintranslate = -1 * ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemPosition ;
		this->_minthreshold = _paneltransform->TranslateX - ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemWidth / 3 ;
	}
	else
	{
		this->_mintranslate = -1 * ((IScrollViewItem^)_ipanel->Children->GetAt(_numberofitems - 1 ))->ItemPosition - this->_scrollwidth / 2 ;
		this->_minthreshold = this->_finaltranslate - this->_scrollwidth ; 
	}
	 
	/*
	if(_currentitem > 0)//( ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemWidth ) / 2 ; 
		this->_maxptranslate = ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemWidth  ;
	else
		this->_maxptranslate =  10000.0 ;

	if(_currentitem < this->_numberofitems - 1 ) // (((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth + ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemWidth ) / 2 ; 
		this->_maxntranslate = -1 * (((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ItemWidth);
	else
		this->_maxntranslate =  -10000.0 ; */
	_temptranslate = this->_paneltransform->TranslateX ; 
}
	
void  IControls::ScrollView::IScrollView::IPanel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	float64  x , x_factor = 1.0 , _currentdelta, _currenttranslate  =  this->_paneltransform->TranslateX; 
	if(this->_manipulationstate == IScrollManipulationState::Enable && _pointerscounter < 2	 )
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

	if(this->_paneltransform->TranslateX > this->_maxtranslate || this->_paneltransform->TranslateX < this->_mintranslate )
	{
		e->Complete();
		e->Handled = true ;
		return ;
	}
}
	
void  IControls::ScrollView::IScrollView::IPanel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	if(this->_paneltransform->TranslateX > this->_maxthreshold)
	{
		this->_panelanimation->To = -1 * ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem - 1 ))->ItemPosition  ;
		this->_panelstory->Begin();
		this->_currentitem -= 1 ;
		IScrollViewItemChanged(this, this->_currentitem);
		setpage();
	}
	else
	{
		if(this->_paneltransform->TranslateX < this->_minthreshold)
		{
			this->_panelanimation->To = -1 * ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem + 1 ))->ItemPosition  ;
			this->_panelstory->Begin();
			this->_currentitem += 1 ;
			IScrollViewItemChanged(this, this->_currentitem);
			setpage();
		}
		else
		{
			this->_panelanimation->To = -1 * ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem ))->ItemPosition  ;
			this->_panelstory->Begin();
		}
	}
}
	
void  IControls::ScrollView::IScrollView::IPanel_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{ 
	 //if(this->_manipulationstate == IScrollManipulationState::Enable)
		// e->TranslationBehavior->DesiredDeceleration = 5.0 * 96.0 / (1000.0 * 1000.0);
}
 
#pragma endregion


#pragma region  Animations
 
void IScrollView::initanimationproperties()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 3000000 ;
	Windows::UI::Xaml::Duration duration(ts) ;

	this->_panelstory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_panelanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_panelanimation->Duration = duration ;
	this->_panelstory->Children->Append(this->_panelanimation);
	Windows::UI::Xaml::Media::Animation::CubicEase ^ ease1 = ref new Windows::UI::Xaml::Media::Animation::CubicEase();
	ease1->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseInOut ;
	//this->_panelanimation->EasingFunction = ref new Windows
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_panelanimation , "TranslateX");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_panelanimation , _paneltransform);

	this->_panelstory->Completed += ref new EventHandler<Platform::Object^>(this, &IControls::ScrollView::IScrollView::Storyboard_Completed_1);
}

void IControls::ScrollView::IScrollView::Storyboard_Completed_1(Platform::Object^ sender, Platform::Object^ e)
{
	_cumulative = 0.0 ;
	_counter = 0 ;
	this->_currentchapter = ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->ChapterNumber ;
	this->_currentsection = ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->SectionNumber ;
	this->_currentpage = ((IScrollViewItem^)_ipanel->Children->GetAt(_currentitem))->PageNumber ;
}

#pragma endregion


#pragma region Scroll Load & Update
 
void IScrollView::loadchapters()
{
	this->_numberofitems = 0 ;
	int32 _numberofchapters = this->_chapterslist->Size ;
	float64 _twidth = 0.0 , _cw  ;
	for (int i = 0; i < _numberofchapters; i++)
	{
		for (int j = 0; j <  this->_chapterslist->GetAt(i)->Sections->Size ; j++)
		{
			for (int k = 0; k < this->_chapterslist->GetAt(i)->Sections->GetAt(j)->Pages->Size ; k++)
			{
				this->_numberofitems += 1 ;
				IScrollViewItem ^ scrollitem  = ref new IScrollViewItem();
				scrollitem->IScrollViewItemLockParent += ref new IScrollViewItemLockParentEventHandler(this, &IControls::ScrollView::IScrollView::IScrollItem_LockParent);
				scrollitem->IScrollViewItemUnlockParent += ref new IScrollViewItemUnlockParentEventHandler(this, &IControls::ScrollView::IScrollView::IScrollItem_UnlockParent);
				scrollitem->ItemPosition = _twidth ;
				scrollitem->ChapterNumber =  i ;
				scrollitem->SectionNumber = j ;
				scrollitem->PageNumber = k ;
				_cw = this->_chapterslist->GetAt(i)->Sections->GetAt(j)->Pages->GetAt(k)->PageWidth ;
				scrollitem->ItemWidth = _cw ;
				scrollitem->ItemDataSource = this->_chapterslist->GetAt(i)->Sections->GetAt(j)->Pages->GetAt(k); // set de pagedatasource
				_twidth += _cw ;
				this->_ipanel->Children->Append(scrollitem);
			}
		}
	}

	this->_initialtranslate = 0.0 ;
	this->_finaltranslate = -1 * ( _twidth - _cw ) ;
}



#pragma endregion


 