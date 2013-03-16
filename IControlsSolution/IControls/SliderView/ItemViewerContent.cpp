#include "pch.h" 

using namespace IControls::SliderView;

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

ItemViewerContent::ItemViewerContent()
{

}


#pragma region ImageItem 
		
void ItemViewerContent::loaditem()
{
	this->_itemimage =  ref new Image();
	this->_itemimage->Source =  ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri(_itemdata));	
	this->Children->Append(_itemimage);
}

#pragma endregion