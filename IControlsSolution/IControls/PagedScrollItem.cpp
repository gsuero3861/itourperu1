#include  "pch.h"

using namespace IControls;

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

#pragma endregion


#pragma region Stack Scroll Temporal Data Load
 
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