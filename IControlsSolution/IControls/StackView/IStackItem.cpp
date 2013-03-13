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

IStackItem::IStackItem()
{
	Canvas::SetZIndex(this, 1);
	inititemcontent();
	initprivatemethodsandvariables();
}

			
#pragma region Item
 
void IStackItem::OpenItem()
{
	this->_translateXanimation->To = this->_itemwidth * this->_itemnumber ;
	this->_rotateanimation->To = 0.0 ;
	this->_rotatestory->Begin();
	this->_translatestory->Begin();
}

void IStackItem::CloseItem()
{
	this->_translateXanimation->To = 0.0 ;
	this->_rotateanimation->To = this->_initialangle ;
	this->_rotatestory->Begin();
	this->_translatestory->Begin();
} 

#pragma endregion


#pragma region Item Content


void IStackItem::inititemcontent()
{
	this->_itemcontent = ref new Grid();
	this->Children->Append(this->_itemcontent);
	
	this->_itemcontent->PointerPressed += ref new PointerEventHandler(this,&IControls::StackView::IStackItem::ItemContent_PointerPressed_1 );
	this->_itemcontent->PointerReleased += ref new PointerEventHandler(this,&IControls::StackView::IStackItem::ItemContent_PointerReleased_1 );
}

#pragma endregion



#pragma region Item Content Touch
 
void IControls::StackView::IStackItem::ItemContent_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_numberoftouches += 1 ;
	if(this->_numberoftouches == 2)
		StackItemSelected(this , this->_itemnumber);
}
	
void IControls::StackView::IStackItem::ItemContent_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_numberoftouches -= 1 ;
}

#pragma endregion


#pragma region Private Methods and Variables 
			
void IStackItem::initprivatemethodsandvariables()
{
	_numberoftouches = 0 ; 
}

void IStackItem::initanimationproperties()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 3000000 ;
	Windows::UI::Xaml::Duration dur(ts) ;

	this->_translatestory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_translateXanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_translateXanimation->Duration = dur ;
	this->_translatestory->Children->Append(this->_translateXanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_translateXanimation, this->_itemtransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_translateXanimation , "TranslateX") ;
	
	this->_rotatestory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_rotateanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation(); ;	
	this->_rotateanimation->Duration = dur ;
	this->_rotatestory->Children->Append(_rotateanimation) ;	
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_rotateanimation, this->_itemtransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_rotateanimation , "Rotation") ; 
}

#pragma endregion