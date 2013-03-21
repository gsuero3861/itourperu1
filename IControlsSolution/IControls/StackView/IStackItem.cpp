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
	this->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left ;
	//this->ManipulationMode = ManipulationModes::All;
	this->Background =  ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	Canvas::SetZIndex(this, 1);
	inititemcontent();
	initprivatemethodsandvariables();
	this->_itemtransform = ref new CompositeTransform();
	this->RenderTransform = this->_itemtransform ;
	initanimationproperties();
	inititemanimationstory();
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
	//this->_itemcontent->ManipulationMode = ManipulationModes::All;
	this->_itemcontent->Background =  ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	this->Children->Append(this->_itemcontent);
	
	this->_itemcontent->PointerPressed += ref new PointerEventHandler(this,&IControls::StackView::IStackItem::ItemContent_PointerPressed_1 );
	this->_itemcontent->PointerReleased += ref new PointerEventHandler(this,&IControls::StackView::IStackItem::ItemContent_PointerReleased_1 );
	this->_itemcontent->Tapped += ref new TappedEventHandler(this , &IControls::StackView::IStackItem::ItemContent_Tapped);
}

#pragma endregion



#pragma region Item Content Touch
 
void IControls::StackView::IStackItem::ItemContent_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_numberoftouches += 1 ;
	if(this->_numberoftouches >= 2)
		StackItemSelected(this , this->_itemnumber);
}
	
void IControls::StackView::IStackItem::ItemContent_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_numberoftouches -= 1 ;
}

void IControls::StackView::IStackItem::ItemContent_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	StackItemTapped(this, this->_itemnumber);
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
	ts.Duration = 3500000 ;
	Windows::UI::Xaml::Duration dur(ts) ;

	this->_translatestory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_translateXanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_translateXanimation->Duration = dur ;
	this->_translatestory->Children->Append(this->_translateXanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_translateXanimation, this->_itemtransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_translateXanimation , "TranslateX") ;
	Windows::UI::Xaml::Media::Animation::QuinticEase ^ ease1 =  ref new Windows::UI::Xaml::Media::Animation::QuinticEase();
	ease1->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut ;
	this->_translateXanimation->EasingFunction = ease1 ;

	this->_rotatestory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_rotateanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation(); ;	
	this->_rotateanimation->Duration = dur ;
	this->_rotatestory->Children->Append(_rotateanimation) ;	
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_rotateanimation, this->_itemtransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_rotateanimation , "Rotation") ; 
	this->_translatestory->Completed += ref new EventHandler<Platform::Object^>(this, &IControls::StackView::IStackItem::Storyboard_Completed_1);
}

#pragma endregion

#pragma region Animation

void IStackItem::RestoreItem()
{
	this->_translatexanimation1->To = this->_itemwidth * this->_itemnumber ;
	this->_translateyanimation1->To = 0.0 ;
	this->_rotateanimation1->To = 0.0 ;
	this->_scalexanimation1->To = 1.0 ;
	this->_scaleyanimation1->To = 1.0 ;
	this->_translatestory1->Begin();
	this->_rotatestory1->Begin();
	this->_scalestory1->Begin();
}

void IStackItem::AnimateTo(float64 _x, float64 _y ,float64 _scale)
{
	this->_translatexanimation1->To = _x - this->_itemwidth / 2 ;
	this->_translateyanimation1->To =  _y ;
	this->_rotateanimation1->To = 0.0 ;
	this->_scalexanimation1->To =_scale ;
	this->_scaleyanimation1->To =_scale ;
	this->_translatestory1->Begin();
	this->_rotatestory1->Begin();
	this->_scalestory1->Begin();
}

void IControls::StackView::IStackItem::Storyboard_Completed_1(Platform::Object^ sender, Platform::Object^ e)
{
	this->_numberoftouches = 0 ;
	if(this->_itemtransform->ScaleX > 1.5)
		StackItemFullScreenAnimationCompleted(this , this->_itemnumber);
	else
		ZIndex = 1 ;
		
}

void IStackItem::inititemanimationstory()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 1750000 ;
	Windows::UI::Xaml::Duration duration(ts) ;
	
	_translatestory1 = ref new Windows::UI::Xaml::Media::Animation::Storyboard() ;
	_translatexanimation1 = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation() ;
	this->_translatexanimation1->Duration = duration ; 
	this->_translatestory1->Children->Append(this->_translatexanimation1);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_translatexanimation1 , "TranslateX");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_translatexanimation1 , _itemtransform);

	_translateyanimation1 = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation() ;
	this->_translateyanimation1->Duration = duration ; 
	this->_translatestory1->Children->Append(this->_translateyanimation1);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_translateyanimation1 , "TranslateY");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_translateyanimation1 , _itemtransform);

	_scalestory1 = ref new Windows::UI::Xaml::Media::Animation::Storyboard() ;
	_scalexanimation1 = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_scalexanimation1->Duration = duration ; 
	this->_scalestory1->Children->Append(this->_scalexanimation1);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_scalexanimation1 , "ScaleX");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_scalexanimation1 , _itemtransform);

	_scaleyanimation1 = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_scaleyanimation1->Duration = duration ; 
	this->_scalestory1->Children->Append(this->_scaleyanimation1);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_scaleyanimation1 , "ScaleY");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_scaleyanimation1 , _itemtransform);
	
	_rotatestory1 = ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	_rotateanimation1 = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_rotateanimation1->Duration = duration ; 
	this->_rotatestory1->Children->Append(this->_rotateanimation1);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_rotateanimation1 , "Rotation");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_rotateanimation1 , _itemtransform);

	this->_scalestory1->Completed += ref new EventHandler<Platform::Object^>(this, &IControls::StackView::IStackItem::Storyboard_Completed_1);
}

#pragma endregion