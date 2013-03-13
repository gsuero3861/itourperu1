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
	inittapfunctions();
	initdoubletapfunctions();
	initproperties();
	initcontrols();
}

#pragma region Controls 
			
void IStackView::initcontrols()
{  
	this->_itemsgrid	= ref new Windows::UI::Xaml::Controls::Grid();
	this->_itemsgrid->ManipulationMode  = ManipulationModes::System ;
	this->_itemsgrid->Background	= ref new SolidColorBrush(Windows::UI::Colors::AliceBlue);

	this->_itemsgrid->PointerPressed += ref new PointerEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_PointerPressed_1);
	this->_itemsgrid->PointerReleased += ref new PointerEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_PointerReleased_1);
	this->_itemsgrid->Tapped += ref new TappedEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_Tapped_1 );
	this->_itemsgrid->DoubleTapped += ref new DoubleTappedEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_DoubleTapped_1 );
	this->_itemsgrid->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_ManipulationCompleted_1);
	this->_itemsgrid->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &IControls::StackView::IStackView::ItemsGrid_ManipulationDelta_1);
	
	this->Children->Append(this->_itemsgrid);
	initanimationproperties();
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
		titem->InitialAngle = this->_angles[i%3];
		titem->ItemContent = tgrid ;
	}
}

#pragma endregion

#pragma region Public Methods
 
void IStackView::SetToFullScreen()
{}

void IStackView::SetToThumb()
{}

void IStackView::AnimateToFullScreen()
{}

void IStackView::AnimateToThumb()
{}

#pragma endregion

#pragma region Private Methods

void IStackView::initproperties()
{
	_angles[0] = 0.0 ;
	_angles[1] = 8.0 ;
	_angles[2] = 15.0 ,

	this->_numberofitems = 0 ;
	this->_numberoftouches = 0 ;
	this->_currentscale =1.0 ;

	_stackviewstate = StackViewState::Close  ;
	_stackmanipulatiotype = StackManipulationType::StackManipulation ;
	_stacktouches = StackTouches::Zero ;
}
 
void IStackView::openstack()
{
	this->_itemgridanimation->To = this->_numberofitems * this->_itemwidth ;
	this->_itemsgridstory->Begin();
	for (int i = 0; i < this->_numberofitems; i++) 
		((IStackItem^)this->_itemsgrid->Children->GetAt(i))->OpenItem();
}

void IStackView::closestack()
{
	this->_itemgridanimation->To = this->_itemwidth ;
	this->_itemsgridstory->Begin();
	for (int i = 0; i < this->_numberofitems; i++) 
		((IStackItem^)this->_itemsgrid->Children->GetAt(i))->CloseItem();
}
 

void IStackView::updatestackitems()
{}

#pragma endregion

#pragma region Animation 
			
void IStackView::initanimationproperties()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 3000000 ;
	Windows::UI::Xaml::Duration duration(ts) ;

	this->_itemsgridstory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_itemgridanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_itemgridanimation->Duration = duration ;
	this->_itemsgridstory->Children->Append(this->_itemgridanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_itemgridanimation , "(Grid.Width)");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_itemgridanimation , _itemsgrid);
}

#pragma endregion


#pragma region Event Handlers Functions

void IControls::StackView::IStackView::ItemsGrid_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	(this->*_tapfunctions[(int32)this->_stackviewstate])();
}

void IControls::StackView::IStackView::ItemsGrid_DoubleTapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs^ e)
{
	(this->*_doubletapfunctions[(int32)this->_stackviewstate])();
}

void IControls::StackView::IStackView::ItemsGrid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{}

void IControls::StackView::IStackView::ItemsGrid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{}

void IControls::StackView::IStackView::ItemsGrid_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}

void IControls::StackView::IStackView::ItemsGrid_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}

#pragma endregion

#pragma region Tap Pointer Functions
 
  
void IStackView::inittapfunctions()
{
	_tapfunctions[0] = &IStackView::tapclosedstack;
	_tapfunctions[1] = &IStackView::tapopennedstack;
}

bool IStackView::tapclosedstack()
{
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
	_doubletapfunctions[0] = &IStackView::doubletapclosedstack ;
	_doubletapfunctions[1] = &IStackView::doubletapopennedstack ;
}

bool IStackView::doubletapclosedstack()
{
	return true ;
}

bool IStackView::doubletapopennedstack()
{
	closestack();
	return true ;
}
 			 
#pragma endregion