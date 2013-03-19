#include "pch.h" 

namespace IControls
{
	namespace ScrollView
	{
		public ref class IScrollViewItem sealed : public Windows::UI::Xaml::Controls::Grid
		{
		public:
			IScrollViewItem();

#pragma region Public Properties

		public:
			property float64 ItemWidth
			{
				void set(float64 value){this->Width = value;}
				float64 get(){return this->Width;}
			}

			property Platform::String^ Source
			{
				void set(Platform::String^ value)
				{
					Windows::UI::Xaml::Controls::Image^ img = ref new Windows::UI::Xaml::Controls::Image();
					img->Source =  ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri(value));
					img->Width = this->ItemWidth;
					img->Stretch =  Windows::UI::Xaml::Media::Stretch::Fill ;
					this->Height =  this->Height ;
					this->Children->Append(img);
				}
				Platform::String^ get(){return nullptr ;}
			}

#pragma endregion
		};
	}
}