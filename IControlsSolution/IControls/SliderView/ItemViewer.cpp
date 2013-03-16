#include "pch.h" 

using namespace IControls::SliderView ;

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

ItemViewer::ItemViewer()
{
	this->_itemcontainer =  ref new Grid();
	this->_itemcontainer->Background =  ref new SolidColorBrush(Windows::UI::Colors::Black);
	this->_itemtransform =  ref new CompositeTransform();
	this->_itemcontainer->RenderTransform = _itemtransform ;
	this->Children->Append(_itemcontainer);
	//load item content
	this->_itemcontent =  ref new ItemViewerContent();
	this->_itemcontainer->Children->Append(this->_itemcontent);
	initanimations();
}

void ItemViewer::AnimateToFull()
{
	this->_scaleanimationX->To = 1.0 ;
	this->_scaleanimationY->To = 1.0 ;
	this->_animation_story->Begin();
}
	
void ItemViewer::AnimateToMedium()
{
	this->_scaleanimationX->To = _minscale ;
	this->_scaleanimationY->To = _minscale ;
	this->_animation_story->Begin();
}

void ItemViewer::SetToLeft()
{
	this->_itemtransform->CenterX = this->Width ;
	this->_itemtransform->ScaleX = _minscale ;
	this->_itemtransform->ScaleY = _minscale ;
}
	
void ItemViewer::SetToRight()
{
	this->_itemtransform->CenterX = 0.0 ;
	this->_itemtransform->ScaleX = _minscale ;
	this->_itemtransform->ScaleY = _minscale ;
}

void ItemViewer::initanimations()
{
	this->_animation_story = ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 2000000 ;
	Windows::UI::Xaml::Duration dur(ts) ; 
	
	this->_scaleanimationX = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_scaleanimationX->Duration = dur ;
	this->_animation_story->Children->Append(_scaleanimationX);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_scaleanimationX, this->_itemtransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_scaleanimationX , "ScaleX") ;

	this->_scaleanimationY = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->_scaleanimationY->Duration = dur ;
	this->_animation_story->Children->Append(_scaleanimationY);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->_scaleanimationY, this->_itemtransform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->_scaleanimationY , "ScaleY") ;

}

#pragma region Manipulation Control

//transferimos el estado del item
void IControls::SliderView::ItemViewer::ItemViewerContentUpdateState_1(Platform::String^ sender, bool _value)
{
	//OnItemViewerUpdateState(this, (SliderManipulationState)value); // 0->enable : 1 ->dislable
	ItemViewerManipulationEnable(this, _value ) ;
	
}

#pragma endregion