#include  "pch.h"

using namespace IControls;

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

PagedScrollItem::PagedScrollItem()
{
	this->initcontrols();
}

#pragma region Controls 
		
void PagedScrollItem::initcontrols()
{
	this->_stackscrollgrid = ref new Grid();
	this->Children->Append(this->_stackscrollgrid);
	this->_stackscrollgrid->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom ;	
}

#pragma endregion

#pragma region StackScroll Private Methods
 
void IControls::PagedScrollItem::StackScroll_LockParent(Platform::Object^ sender,  int32 _item)
{
	this->PagedScrollItemLockParent(this, _item);
}

void IControls::PagedScrollItem::StackScroll_UnlockParent(Platform::Object^ sender,  int32 _item)
{
	this->PagedScrollItemUnlockParent(this, _item);
}


void IControls::PagedScrollItem::StackScroll_OutAnimationStarted(Platform::Object^ sender,  int32 _section, int32 _page)
{
	PagedScrollItemAnimationOutStarted( this , _section , _page ) ;
}
	
void IControls::PagedScrollItem::StackScroll_OutAnimationCompleted(Platform::Object^ sender,  int32 _section, int32 _page)
{
	PagedScrollItemAnimationOutCompleted( this , _section , _page ) ;
}

#pragma endregion


#pragma region Stack Scroll Temporal Data Load

void PagedScrollItem::loadchapter()
{
	_stackscroll  = ref new IStackScroll(); 
	_stackscroll->ChapterSource = _datasource ;
	_stackscroll->ScrollHeight = 900 ;
	_stackscroll->ScrollWidth = 1600 ;
	_stackscroll->StackScrollLockParent +=  ref new StackScrollLockParentEventHandler(this, &IControls::PagedScrollItem::StackScroll_LockParent);
	_stackscroll->StackScrollUnlockParent +=  ref new StackScrollUnlockParentEventHandler(this, &IControls::PagedScrollItem::StackScroll_UnlockParent);
	_stackscroll->StackScrollOutAnimationStarted += ref new StackScrollOutAnimationStartedEventHandler(this, &IControls::PagedScrollItem::StackScroll_OutAnimationStarted);
	_stackscroll->StackScrollOutAnimationCompleted += ref new StackScrollOutAnimationCompletedEventHandler(this, &IControls::PagedScrollItem::StackScroll_OutAnimationCompleted);
	this->_stackscrollgrid->Children->Append(_stackscroll);
	 
}
 
void PagedScrollItem::loaditems()
{
	_stackscroll  = ref new IStackScroll();
	_stackscroll->ItemsList =  this->_itemslist ;
	_stackscroll->ScrollHeight = 900 ;
	_stackscroll->ScrollWidth = 1600 ;
	_stackscroll->StackScrollLockParent +=  ref new StackScrollLockParentEventHandler(this, &IControls::PagedScrollItem::StackScroll_LockParent);
	_stackscroll->StackScrollUnlockParent +=  ref new StackScrollUnlockParentEventHandler(this, &IControls::PagedScrollItem::StackScroll_UnlockParent);
	this->_stackscrollgrid->Children->Append(_stackscroll);

}

#pragma endregion