#include "pch.h"

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

IStackView::IStackView()
{
	_constantdelta = 1.0 ;
	_ismanipulating = false ;
	inittapfunctions();
	initdoubletapfunctions();
	initproperties();
	initcontrols();
	 
}

#pragma region Controls 
			
void IStackView::initcontrols()
{  
	this->_itemsgrid	= ref new Windows::UI::Xaml::Controls::Grid();
	this->_itemsgrid->ManipulationMode  = ManipulationModes::All ;
	this->_itemsgrid->Background	= ref new SolidColorBrush(Windows::UI::Colors::Transparent);

	this->_itemsgrid->PointerPressed += ref new PointerEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_PointerPressed_1);
	this->_itemsgrid->PointerReleased += ref new PointerEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_PointerReleased_1);
	this->_itemsgrid->Tapped += ref new TappedEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_Tapped_1 );
	//this->_itemsgrid->DoubleTapped += ref new DoubleTappedEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_DoubleTapped_1 );
	this->_itemsgrid->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_ManipulationCompleted_1);
	this->_itemsgrid->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_ManipulationDelta_1);
	this->_itemsgrid->ManipulationInertiaStarting += ref new ManipulationInertiaStartingEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_ManipulationInertiaStarting);
	this->_itemsgrid->ManipulationStarted +=  ref new ManipulationStartedEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_ManipulationStarted);
	
	this->_itemspanel =  ref new StackPanel();
	this->_itemspanel->Orientation = Orientation::Horizontal ;

	this->_begingrid = ref new Grid();
	this->_endgrid = ref new Grid();
	this->_itemspanel->Children->Append(this->_begingrid);
	this->_itemspanel->Children->Append(this->_itemsgrid);
	this->_itemspanel->Children->Append(this->_endgrid);

	this->Children->Append(this->_itemspanel);
	initanimationproperties();
}


void IStackView::loadatsource()
{
	this->_numberofitems = this->_datasource->Pages->Size ;
	for (int i = 0; i < this->_numberofitems ; i++)
	{
		Image^ timage = ref new Image();
		timage->Source =  ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri( this->_datasource->Pages->GetAt(i)->ThumbSource ));
		//timage->Width =  this->_itemcontentwidth ;
		timage->Height = this->_itemcontentheight  ;
		//timage->Stretch =  Windows::UI::Xaml::Media::Stretch:: ;
		Grid^ tgrid =  ref new Grid();
		tgrid->Children->Append(timage);
		IStackItem^ titem = ref new IStackItem();
		titem->ZIndex = 1 ;
		titem->ItemWidth = this->_itemwidth ;
		titem->ItemHeight =  this->_itemheight ;
		titem->ItemContentWidth = this->_itemcontentwidth ;
		titem->ItemContentHeight =  this->_itemcontentheight ;
		titem->ItemNumber = i ;
		float64 angle = this->_angles[i%3];
		titem->InitialAngle = angle ;
		titem->ItemContent = tgrid ;
		titem->StackItemSelected += ref new StackItemSelectedEventHandler(this, &IControls::StackView::IStackView::StackItemSelected_1);
		titem->StackItemTapped +=  ref new StackItemTappedEventHandler(this, &IControls::StackView::IStackView::StackItem_Tapped);
		this->_itemsgrid->Children->Append(titem);
	}
}
#pragma endregion


#pragma region Load of Data

//temp load of data
void IStackView::loaditems()
{
	this->_numberofitems = this->_itemslist->Size ;
	for (int i = 0; i < this->_numberofitems; i++)
	{
		Image^ timage = ref new Image();
		timage->Source =  ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri(this->_itemslist->GetAt(i)));
		timage->Width =  this->_itemcontentwidth ;
		timage->Height = this->_itemcontentheight  ;
		Grid^ tgrid =  ref new Grid();
		tgrid->Children->Append(timage);
		IStackItem^ titem = ref new IStackItem();
		titem->ZIndex = 1 ;
		titem->ItemWidth = this->_itemwidth ;
		titem->ItemHeight =  this->_itemheight ;
		titem->ItemContentWidth = this->_itemcontentwidth ;
		titem->ItemContentHeight =  this->_itemcontentheight ;
		titem->ItemNumber = i ;
		float64 angle = this->_angles[i%3];
		titem->InitialAngle = angle ;
		titem->ItemContent = tgrid ;
		titem->StackItemSelected += ref new StackItemSelectedEventHandler(this, &IControls::StackView::IStackView::StackItemSelected_1);
		titem->StackItemTapped +=  ref new StackItemTappedEventHandler(this, &IControls::StackView::IStackView::StackItem_Tapped);
		this->_itemsgrid->Children->Append(titem);
	}
}

#pragma endregion

#pragma region Public Methods
 
void IStackView::SetToFullScreen()
{
	//this->_currenttransform ->TranslateX  = _fullXposition ;
	//this->_currenttransform ->TranslateY  = _fullYposition ; 
}

void IStackView::SetToThumb()
{
	//this->_currenttransform ->TranslateX = _selecteditem * _itemwidth ;
	//this->_currenttransform ->TranslateY = 0.0 ;
}

void IStackView::AnimateToFullScreen()
{
	((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->AnimateTo( this->_fullXposition - this->_begingrid->Width , this->FullYPosition ,  5.0 ) ;
	//this->_translatexanimation->To = _fullXposition ;
	//this->_translateyanimation->To = _fullYposition ;
	//this->_translatestory->Begin();
}

void IStackView::AnimateToThumb()
{}

#pragma endregion

#pragma region Private Methods

void IStackView::initproperties()
{
	this->_itemwidth = 100 ;
	this->_itemcontentwidth = 100 ;
	this->_itemheight = 100 ;
	this->_itemcontentheight = 100 ;
	this->_stackwidth = 100 ;

	_angles[0] = 0.0 ;
	_angles[1] = 8.0 ;
	_angles[2] = 15.0 ,

	this->_numberofitems = 0 ;
	this->_numberoftouches = 0 ;
	this->_currentscale =1.0 ;
	this->_cananimate = false ;

	_stackviewstate = StackViewState::Close  ;
	_stackmanipulatiotype = StackManipulationType::StackManipulation ;
	_stacktouches = StackTouches::Zero ;
}
 
void IStackView::openstack()
{
	if( this->_stackviewstate == StackViewState::Close)
	{
		
		this->_itemgridanimation->To = this->_numberofitems * this->_itemwidth ;
		this->_itemgridanimation->From =  this->_itemwidth  ;
		this->_itemsgridstory->Begin();
		for (int i = 0; i < this->_numberofitems; i++) 
			((IStackItem^)this->_itemsgrid->Children->GetAt(i))->OpenItem();
		if(this->_currentscale < this->_numberofitems )
			OnStackViewOpen(this , this->_stacknumber);
		this->_stackviewstate = StackViewState::Open ;
		this->_currentscale = (float64)this->_numberofitems ;
		this->_numberoftouches =0 ;
	}
}

void IStackView::closestack()
{
	if( this->_stackviewstate == StackViewState::Open)
	{
		
		this->_itemgridanimation->To = this->_itemwidth ;
		this->_itemgridanimation->From = this->_currentscale * this->_itemwidth ;
		this->_itemsgridstory->Begin();
		for (int i = 0; i < this->_numberofitems; i++) 
			((IStackItem^)this->_itemsgrid->Children->GetAt(i))->CloseItem();
		if(this->_currentscale > 1.0)
			OnStackViewClose(this, this->_stacknumber, _constantdelta * this->_currentscale * this->_itemwidth);
		this->_currentscale = 1.0 ;
		this->_stackviewstate = StackViewState::Close ;
		this->_numberoftouches =0 ;
	}
}
 

void IStackView::updatestackitems()
{
	for (int i = 0; i < _numberofitems; i++)
	{
		((IStackItem^)this->_itemsgrid->Children->GetAt(i))->ItemTransform->TranslateX =   i * ((_itemsgrid->ActualWidth  - _itemwidth ) / (_numberofitems	 - 1 )) ; 
		((IStackItem^)this->_itemsgrid->Children->GetAt(i))->ItemTransform->Rotation = (1.0 - this->_currentscale / this->_numberofitems) * ((IStackItem^)this->_itemsgrid->Children->GetAt(i))->InitialAngle  ;
	}
}

#pragma endregion

#pragma region Animation 
			
void IStackView::initanimationproperties()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 3500000 ;
	Windows::UI::Xaml::Duration duration(ts) ;

	this->_itemsgridstory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_itemgridanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_itemgridanimation->Duration = duration ;
	this->_itemgridanimation->EnableDependentAnimation = true ;
	Windows::UI::Xaml::Media::Animation::QuinticEase ^ ease1 =  ref new Windows::UI::Xaml::Media::Animation::QuinticEase();
	ease1->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut ;
	this->_itemgridanimation->EasingFunction = ease1 ;
	this->_itemsgridstory->Children->Append(this->_itemgridanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_itemgridanimation , "(Grid.Width)");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_itemgridanimation , _itemsgrid);

	this->_itemsgridstory->Completed += ref new EventHandler<Platform::Object^>(this, &IControls::StackView::IStackView::Storyboard_Completed_1);
}


#pragma endregion


#pragma region Event Handlers Functions

void IControls::StackView::IStackView::StackItem_FullScreenAnimationCompleted(Platform::Object ^ sender )
{
	///Animation completed event
	StackViewFullScreenAnimationCompleted(this, this->_stacknumber, this->_selecteditem);
}

void  IControls::StackView::IStackView::Storyboard_Completed_1(Platform::Object^ sender, Platform::Object^ e)
{
	StackViewTranformChanged(this);
	this->_numberoftouches = 0 ;
	_ismanipulating = false ;
}

void IControls::StackView::IStackView::StackItem_Tapped(Platform::Object ^ sender , int32 _currentitem)
{
	if(this->_stackviewstate == StackViewState::Open && !_ismanipulating)//and i f is not being manipulated->FALTA
	{
		this->_selecteditem = _currentitem ;
		//this->_currenttransform = ((IStackItem^)sender)->ItemTransform ;
		//Animate to full
		((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->ZIndex = 100 ;
		AnimateToFullScreen();
		StackViewFullScreenAnimationStarted(this, this->_stacknumber, this->_selecteditem);///full scren  animation started
	}
}

void IControls::StackView::IStackView::StackItemSelected_1(Platform::Object ^ sender , int32 _currentitem)
{
	//_currenttransform = ((IStackItem^)sender)->ItemTransform ;
	if(_stackviewstate == StackViewState::Open)
	{
		this->_selecteditem = _currentitem ;
		this->_stackmanipulatiotype = StackManipulationType::ItemManipulation ;
		StackViewManipulationStarted(this, 1) ;
		((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->ZIndex = 100 ;
	}
}

void IControls::StackView::IStackView::ItemsGrid_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	//this->_itemsgrid->Width = this->_currentscale * ( this->_itemwidth ) ;
	StackViewManipulationFinished(this,0);
	(this->*_tapfunctions[(int32)this->_stackviewstate])();
	StackViewTranformChanged(this);
	Canvas::SetZIndex(this , 100);
	//_numberoftouches = 0 ;
}

void IControls::StackView::IStackView::ItemsGrid_DoubleTapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs^ e)
{
	_constantdelta = e->GetPosition(this->_itemsgrid).X / (this->_numberofitems* this->_itemwidth);
	(this->*_doubletapfunctions[(int32)this->_stackviewstate])();
	StackViewTranformChanged(this);
}

void IControls::StackView::IStackView::ItemsGrid_ManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e)
{
	if(this->_numberoftouches >= 2)
		StackViewManipulationStarted(this, 0); //0 type
	else
		StackViewManipulationFinished(this, 0);

	_tempwidth = this->_currentscale * this->_itemwidth ;
	Canvas::SetZIndex(this , 100);
	_isinertia =false ;
	_ismanipulating = true ;
}

void IControls::StackView::IStackView::ItemsGrid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{   
	if(this->_numberoftouches >= 2 || _isinertia)
	{
		 
		_isinertia = true ;
		if(_stackmanipulatiotype == StackManipulationType::StackManipulation)
		{ 
			StackViewManipulationStarted(this, 0 ); //type stackmanipulation
			this->_currentscale *= e->Delta.Scale ;
			if (this->_currentscale > (float64)this->_numberofitems - 0.01)
				this->_currentscale = (float64)this->_numberofitems - 0.01;

			if ( this->_currentscale < 1.01)
				this->_currentscale =  1.01 ;

			this->_itemsgrid->Width = this->_currentscale * this->_itemwidth ;
			//set all the properties
			updatestackitems();
			if(this->_stackviewstate == StackViewState::Open)
			{ 
				float _scrollto =(_tempwidth -  this->_currentscale * this->_itemwidth ) / ((1-_constantdelta ) * this->ItemWidth );
				StackViewScrollTo(this, _scrollto);
			}
			this->_cananimate = true ;
		}

		if(_stackmanipulatiotype == StackManipulationType::ItemManipulation ) 
		{
			((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->ItemTransform->TranslateX += e->Delta.Translation.X;
			((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->ItemTransform->TranslateY += e->Delta.Translation.Y;
			((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->ItemTransform->ScaleX *= e->Delta.Scale ;
			((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->ItemTransform->ScaleY *= e->Delta.Scale ;
			((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->ItemTransform->Rotation +=e->Delta.Rotation ;
			this->_cananimate =false ;
		}
		
	}
	 
}

void IControls::StackView::IStackView::ItemsGrid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{ 
	//_stackmanipulatiotype == StackManipulationType::StackManipulation &&
	if( this->_cananimate )
	{
		if (this->_stackviewstate == StackViewState::Close )
			if(this->_currentscale > 1.5)
			{
				this->_stackviewstate = StackViewState::Close ;
				openstack();
			}
			else
			{
				this->_stackviewstate = StackViewState::Open;
				closestack();			
			}
		else
		{
			if(this->_currentscale > 8.5)
			{
				this->_stackviewstate = StackViewState::Close ;
				openstack();
			}
			else
			{
				this->_stackviewstate = StackViewState::Open;
				closestack();			
			}
		}
	}

	if(_stackmanipulatiotype == StackManipulationType::ItemManipulation)
	{
		if(((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->ItemTransform->ScaleX <= 2.5 )
			((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->RestoreItem() ;
		else ///HERE THROW THE ANIMATION STARTED
		{
			((IStackItem^)this->_itemsgrid->Children->GetAt(this->_selecteditem))->AnimateTo( this->_fullXposition - this->_begingrid->Width , this->FullYPosition ,  5.0 )  ; //this->_itemwidth , this->FullYPosition ,  5.0 ) ;
			StackViewFullScreenAnimationStarted(this, this->_stacknumber, this->_selecteditem);
		}
	}
	StackViewManipulationFinished(this,0);
	_stackmanipulatiotype = StackManipulationType::StackManipulation ;
	this->_cananimate = false ;
	_isinertia = false ;
	_ismanipulating = false ;
	this->_numberoftouches = 0 ;
	StackViewTranformChanged(this);
	Canvas::SetZIndex(this , 1);
}

void IControls::StackView::IStackView::ItemsGrid_ManipulationInertiaStarting(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{
	if(_isinertia)
	{
		e->TranslationBehavior->DesiredDeceleration = 300.0 * 96.0 / (1000.0 * 1000.0);
		e->ExpansionBehavior->DesiredDeceleration = 300.0 * 96.0 / (1000.0 * 1000.0); 
		e->RotationBehavior->DesiredDeceleration = 300.0 * 96.0 / (1000.0 * 1000.0); 
	}
	 
}

void IControls::StackView::IStackView::ItemsGrid_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_numberoftouches -= 1 ;
	/**if(this->_numberoftouches < 0)
		this->_numberoftouches == 0 ;*/
}

void IControls::StackView::IStackView::ItemsGrid_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_numberoftouches += 1 ;
	_constantdelta = e->GetCurrentPoint( this->_itemsgrid)->Position.X / (this->_numberofitems* this->_itemwidth);
}

void IControls::StackView::IStackView::ItemsGrid_PointerExited_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_numberoftouches -= 1 ;
}


#pragma endregion

#pragma region Tap Pointer Functions
 
  
void IStackView::inittapfunctions()
{
	_tapfunctions[1] = &IStackView::tapclosedstack;
	_tapfunctions[0] = &IStackView::tapopennedstack;
}

bool IStackView::tapclosedstack()
{
	//OnStackViewOpen(this, this->_stacknumber);
	this->_currentscale += 0.01 ;
	openstack();
	return true ;
}

bool IStackView::tapopennedstack()
{ 
	return true ;
}

#pragma endregion

#pragma region DoubleTap Pointer Functions

void IStackView::initdoubletapfunctions()
{
	_doubletapfunctions[1] = &IStackView::doubletapclosedstack ;
	_doubletapfunctions[0] = &IStackView::doubletapopennedstack ;
}

bool IStackView::doubletapclosedstack()
{
	return true ;
}

bool IStackView::doubletapopennedstack()
{
	this->_itemgridanimation->From = this->_numberofitems * this->_itemwidth ;
	//OnStackViewClose(this, this->_stacknumber);
	this->_currentscale -= 0.01 ;
	closestack();
	return true ;
}
 			 
#pragma endregion