#include "pch.h"

using namespace IControls ;

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

AnimationViewItem::AnimationViewItem()
{
	this->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left ;
	this->_imageitem =  ref new Image();
	this->_imageitem->Stretch = Stretch::Fill ;
	this->_itemtransform = ref new CompositeTransform();
	//this->_itemtransform->CenterX = 0.0 ;
	this->RenderTransform =  this->_itemtransform ;
	this->Children->Append(this->_imageitem);
	this->_imageitem->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center ;
	initanimations();
}

void AnimationViewItem::initanimations()
{
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 4500000 ;
	Windows::UI::Xaml::Duration dur(ts) ;

	this->_translatestory =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->_translatexanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_translatexanimation->Duration = dur ;
	this->_translatestory->Children->Append(this->_translatexanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_translatexanimation, this->_itemtransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_translatexanimation , "TranslateX") ;
	Windows::UI::Xaml::Media::Animation::CubicEase ^ ease1 =  ref new Windows::UI::Xaml::Media::Animation::CubicEase();
	ease1->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut ;
	this->_translatexanimation->EasingFunction = ease1 ;

	this->_translateyanimation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_translateyanimation->Duration = dur ;
	this->_translatestory->Children->Append(this->_translateyanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_translateyanimation, this->_itemtransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_translateyanimation , "TranslateY") ;
	Windows::UI::Xaml::Media::Animation::CubicEase ^ ease2 =  ref new Windows::UI::Xaml::Media::Animation::CubicEase();
	ease2->EasingMode = Windows::UI::Xaml::Media::Animation::EasingMode::EaseOut ;
	this->_translateyanimation->EasingFunction = ease2 ;
	this->_translatestory->Completed += ref new EventHandler<Platform::Object^>(this, &IControls::AnimationViewItem::Storyboard_Completed_1);

}

void AnimationViewItem::AnimateTo(float64 _x , float64 _y)
{
	this->_translatexanimation->To =  _x ;
	this->_translateyanimation->To =  _y ;
	this->_translatestory->Begin();
}

void IControls::AnimationViewItem::Storyboard_Completed_1(Platform::Object^ sender, Platform::Object^ e)
{
	AnimationViewItemCompleted(this);
}