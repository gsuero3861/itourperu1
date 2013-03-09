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
	inititemcontent();
	initprivatemethodsandvariables();
}


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

#pragma endregion