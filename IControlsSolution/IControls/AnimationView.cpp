#include "pch.h"

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

AnimationView::AnimationView()
{

}


#pragma region Controls
 
void AnimationView::inititemsgrid()
{
	this->_itemspanel =  ref new Grid();
	this->_itemspanel->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left ;
	this->Children->Append(this->_itemspanel);
	this->_paneltransform = ref new CompositeTransform(); 
	this->_itemspanel->RenderTransform = this->_paneltransform ;

	float64 ctranslate  = 0.0;
	for (int i = 0; i < _datasource->Pages->Size; i++)
	{
		AnimationViewItem^ item = ref new AnimationViewItem();
		item->InitialPosition = ctranslate ;
		item->ItemWidth = _datasource->Pages->GetAt(i)->PageWidth;
		item->ItemHeight = _datasource->Pages->GetAt(i)->PageHeight;
		ctranslate += _datasource->Pages->GetAt(i)->PageWidth ;
		item->ImageWidth = _datasource->Pages->GetAt(i)->PageWidth;
		item->ImageHeight = _datasource->Pages->GetAt(i)->PageHeight;
		item->ImageSource = _datasource->Pages->GetAt(i)->FullSource ;
		item->AnimationViewItemCompleted +=  ref new AnimationViewItemCompletedEventHandler(this, &IControls::AnimationView::AnimationViewItem_Completed);
		this->_itemspanel->Children->Append(item);
	} 
	//this->_paneltransform->ScaleX = 0.2 ;
	//this->_paneltransform->ScaleY = 0.2 ;
}

#pragma endregion


#pragma region Methods

void AnimationView::SetOutAnimation(int32 _item)
{

	//this->_paneltransform->ScaleX = 0.2 ;
	//this->_paneltransform->ScaleY = 0.2 ;
	this->_initialitem = _item ; 
	for (int i = 0; i < this->_itemspanel->Children->Size; i++)
	{
		((AnimationViewItem^)this->_itemspanel->Children->GetAt(i))->ItemTransform->TranslateX  = 4 * this->_itemwidth;
	}
	((AnimationViewItem^)this->_itemspanel->Children->GetAt(_item))->ItemTransform->TranslateX = ( this->_itemwidth  - ( (AnimationViewItem^)this->_itemspanel->Children->GetAt(_item))->ItemWidth ) / 2 ; 
	((AnimationViewItem^)this->_itemspanel->Children->GetAt(_item + 1 ))->ItemTransform->TranslateX  = this->_itemwidth ;
	//AnimateOut();
}

void AnimationView::AnimateOut()
{
	((AnimationViewItem^)this->_itemspanel->Children->GetAt(_initialitem))->AnimateTo(0.0 , 0.0);
	((AnimationViewItem^)this->_itemspanel->Children->GetAt(_initialitem + 1 ))->AnimateTo( ((AnimationViewItem^)this->_itemspanel->Children->GetAt(_initialitem ))->ItemWidth  , 0.0); 
}

void IControls::AnimationView::AnimationViewItem_Completed(Platform::Object ^ sender  )
{
	AnimationViewCompleted(this) ;
}

#pragma endregion