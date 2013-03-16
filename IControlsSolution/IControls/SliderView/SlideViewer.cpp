#include "pch.h" 

using namespace IControls::SliderView;

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


SlideViewer::SlideViewer()
{
	this->_controlwidth =0 ;
	this->_itemwidth = 0 ;
	initcontrols() ;
	initstoryboard();
}

void SlideViewer::initcontrols()
{
	this->_scrollviewer =  ref new ScrollViewer();
	this->_scrollviewer->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Enabled ;
	this->_scrollviewer->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
	this->_scrollviewer->VerticalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled ; 
	this->_scrollviewer->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Disabled;
	
	this->_scrollpanel = ref new StackPanel() ;
	this->_scrollpanel->Orientation = Orientation::Horizontal;
	this->_scrollpanel->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	this->_scrollpanel->ManipulationMode = ManipulationModes::All;
	this->_itemspanel = ref new StackPanel() ;
	this->_itemspanel->Orientation = Orientation::Horizontal; 	
	this->_virtualitem_1 = ref  new Grid();
	this->_virtualitem_2 = ref  new Grid();
	this->Children->Append(this->_scrollviewer);
	this->_scrollviewer->Content = _scrollpanel ;
	this->_scrollpanel->Children->Append(this->_virtualitem_1);
	this->_scrollpanel->Children->Append(this->_itemspanel);
	this->_scrollpanel->Children->Append(this->_virtualitem_2);

	this->_paneltransform = ref new CompositeTransform();
	this->_scrollpanel->RenderTransform = this->_paneltransform ;

	this->_scrollpanel->PointerPressed += ref new PointerEventHandler(this, &IControls::SliderView::SlideViewer::Slider_PointerPressed_1);
	this->_scrollpanel->PointerReleased += ref new PointerEventHandler(this, &IControls::SliderView::SlideViewer::Slider_PointerReleased_1);
	this->_scrollpanel->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &IControls::SliderView::SlideViewer::Slider_ManipulationDelta_1);
	this->_scrollpanel->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &IControls::SliderView::SlideViewer::Slider_ManipulationCompleted_1);
	this->_scrollpanel->ManipulationInertiaStarting += ref new ManipulationInertiaStartingEventHandler(this, &IControls::SliderView::SlideViewer::Slider_ManipulationInertiaStarting_1);
}

void SlideViewer::initstoryboard()
{
	this->_translatestory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 2400000 ;
	Windows::UI::Xaml::Duration dur(ts) ;
	this->_translateanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_translateanimation->Duration = dur ;
	this->_translatestory->Children->Append(_translateanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_translateanimation, this->_paneltransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_translateanimation , "TranslateX") ;
}

void SlideViewer::loaditems()
{
	this->_numberofitems = this->_mediumpaths->Size ;
	for (int i = 0; i < this->_numberofitems; i++)
	{
		ItemViewer^ _tmpitem = ref new ItemViewer();
		_tmpitem->ItemWidth = _itemwidth ;
		_tmpitem->ItemHeight= _itemheight ;
		_tmpitem->MinScale = _minscale ;
		_tmpitem->ItemData = _mediumpaths->GetAt(i); 
		this->_itemspanel->Children->Append(_tmpitem);
		if(i<this->_currentitem)
			_tmpitem->SetToLeft();
		if(i > this->_currentitem)
			_tmpitem->SetToRight(); 
	}
	this->_initialtranslate = 0.0 ;
	this->_finaltranslate = (-1) * (_numberofitems - 1)* _itemwidth  ;
	this->_mintranslate = 100 ;
	this->_maxtranslate = this->_finaltranslate - 100;
	 
}

void IControls::SliderView::SlideViewer::Slider_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_numberofpointers += 1 ;
	if(_numberofpointers == 1)
		_manipulationstate = SliderManipulationState::Enable;
	else
		_manipulationstate =SliderManipulationState::Dislable;
}
	
void IControls::SliderView::SlideViewer::Slider_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}
	
void IControls::SliderView::SlideViewer::Slider_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	if(e->Cumulative.Translation.X > this->_itemwidth)
	{
		e->Complete();
		return ;
	}
	float64 x , _currentdelta , _currenttrnaslate = this->_paneltransform->TranslateX ;
	if( _manipulationstate == SliderManipulationState::Enable)
	{
		if(this->_paneltransform->TranslateX > this->_initialtranslate || this->_paneltransform->TranslateX < this->_finaltranslate)
		{ 
			x = fmod( abs(this->_finaltranslate - _currenttrnaslate), abs(this->_finaltranslate)) ;
			if(x > 0)
				_currentdelta = e->Delta.Translation.X / ( x + 1 ) * 5 ;

		}else
		{
			_currentdelta = e->Delta.Translation.X ;
			x=1.0 ;
		}

		if(!e->IsInertial)
		{
			this->_paneltransform->TranslateX += _currentdelta ;
		}
		else
		{
			if(x < 100.0)
				this->_paneltransform->TranslateX += _currentdelta ;
			else
				e->Complete(); 
		} 

		if(this->_paneltransform->TranslateX < _initialtranslate && this->_paneltransform->TranslateX > _finaltranslate)
		{
			this->_currentitem = (int32)(( -1 ) * this->_paneltransform->TranslateX / this->_itemwidth); 
			float64 _cdelta = fmod ((-1)*this->_paneltransform->TranslateX  ,this->_itemwidth );
			if(_cdelta <= _itemwidth/2)
				((ItemViewer ^)this->_itemspanel->Children->GetAt(this->_currentitem+1))->DeltaTranslation = _cdelta ;
			else
				((ItemViewer ^)this->_itemspanel->Children->GetAt(this->_currentitem))->DeltaTranslation = _cdelta ;				 
		}
		//_currenttrnaslate = this->_paneltransform->TranslateX ;

		/**
		if(_paneltransform->TranslateX <= _mintranslate && _paneltransform->TranslateX >= _maxtranslate)
		{ 		
			this->_paneltransform->TranslateX += e->Delta.Translation.X ;
			if(this->_paneltransform->TranslateX < _initialtranslate && this->_paneltransform->TranslateX > _finaltranslate)
			{
				this->_currentitem = (int32)(( -1 ) * this->_paneltransform->TranslateX / this->_itemwidth); 
				float64 _cdelta = fmod ((-1)*this->_paneltransform->TranslateX  ,this->_itemwidth );
				if(_cdelta <= _itemwidth/2)
					((ItemViewer ^)this->_itemspanel->Children->GetAt(this->_currentitem+1))->DeltaTranslation = _cdelta ;
				else
					((ItemViewer ^)this->_itemspanel->Children->GetAt(this->_currentitem))->DeltaTranslation = _cdelta ;				 
			}
		}
		else
		{
			if(this->_paneltransform->TranslateX < 0)
				this->_paneltransform->TranslateX += 0.1 ;
			else
				this->_paneltransform->TranslateX  -= 0.1 ;
		}*/
	}

}
	
void IControls::SliderView::SlideViewer::Slider_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	
	if( _manipulationstate == SliderManipulationState::Enable)
	{
		this->_currentitem = (int32)(( -1 ) * this->_paneltransform->TranslateX / this->_itemwidth + 0.5);
		this->_translateanimation->To =  (-1)* _currentitem * _itemwidth ;
		
		if(fmod ((-1)*this->_paneltransform->TranslateX  ,this->_itemwidth) < this->_itemwidth/2)
		{
			((ItemViewer ^)this->_itemspanel->Children->GetAt(this->_currentitem))->AnimateToFull();
			if(_currentitem < _numberofitems -1 )
				((ItemViewer ^)this->_itemspanel->Children->GetAt(this->_currentitem+1))->AnimateToMedium();
		}else
		{
			((ItemViewer ^)this->_itemspanel->Children->GetAt(this->_currentitem))->AnimateToFull();
			if(_currentitem > 0)
				((ItemViewer ^)this->_itemspanel->Children->GetAt(this->_currentitem-1))->AnimateToMedium();
		}
		this->_translatestory->Begin();
	}
	///throw when change the current item
	if(_currentitem != _currentitemduplicate)
	{
		_currentitemduplicate = _currentitem ;
		SlideViewerItemChanged(this, _currentitem);
	}

	this->_manipulationstate = SliderManipulationState::Dislable ;
	this->_numberofpointers = 0 ;
}
	
void IControls::SliderView::SlideViewer::Slider_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{
	/**double _velocidad =abs( e->Velocities.Linear.X );
	if( _manipulationstate == SliderManipulationState::Enable)
	{
		if(_velocidad > 3.5)
			e->TranslationBehavior->DesiredDisplacement = 300 ; 
		else
			e->TranslationBehavior->DesiredDisplacement = 10 ; 
		e->TranslationBehavior->DesiredDeceleration = 100.0 * 96.0 / (1000.0*1000.0) ; 
	}*/

	e->TranslationBehavior->DesiredDeceleration = 250.0 * 96.0 / (1000.0 * 1000.0);
}

#pragma region Item Manipulation

void IControls::SliderView::SlideViewer::ItemViewerUpdateState_1(Platform::Object^ sender , bool _value)
{
	//_manipulationstate  = state ;
	if(_value)
		this->_manipulationstate = SliderManipulationState::Dislable ;
	else
		this->_manipulationstate = SliderManipulationState::Enable ;
}

#pragma endregion