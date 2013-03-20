#include "pch.h"

using namespace IControls::ScrollView ;

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

IScrollViewItem::IScrollViewItem()
{

}

#pragma region Private Methods
 
void IScrollViewItem::loadlargeimage()
{
	Windows::UI::Xaml::Controls::Image^ img = ref new Windows::UI::Xaml::Controls::Image();
	img->Source =  ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri(_datasource->FullSource));
	img->Width = _datasource->PageWidth ;
	img->Height = _datasource->PageHeight ;
	img->Stretch =  Windows::UI::Xaml::Media::Stretch::Fill ;
	this->Height =  this->Height ;
	this->Children->Append(img);
}

#pragma endregion