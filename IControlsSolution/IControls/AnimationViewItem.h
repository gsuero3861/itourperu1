#include "pch.h"

namespace IControls
{
	public delegate void AnimationViewItemCompletedEventHandler(Platform::Object ^ sender  );

	public ref class AnimationViewItem sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		AnimationViewItem();
		event AnimationViewItemCompletedEventHandler ^ AnimationViewItemCompleted ;

#pragma region Properties

	public:
		property float64 ItemHeight
		{
			void set(float64 value){ this->Height =  value ; }
			float64 get(){return this->Height ;}
		}

		property float64 ItemWidth
		{
			void set(float64 value){ this->Width =  value ;}
			float64 get(){return this->Width ;}
		}

		property float64 ImageHeight
		{
			void set(float64 value){ this->_imageheight =  value ;}
			float64 get(){return this->_imageheight ;}
		}

		property float64 ImageWidth
		{
			void set(float64 value){ this->_imagewidht =  value ;}
			float64 get(){return this->_imagewidht ;}
		}


		property float64 InitialPosition
		{
			void set(float64 value)
			{
				this->_initialposition=  value ;
				this->_itemtransform->TranslateX = value ;
			}
			float64 get(){return this->_initialposition ;}
		}

		property Platform::String ^ ImageSource
		{
			void set(Platform::String ^ value)
			{
				this->_imageitem->Source =  ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri( value ));
			}
			Platform::String ^get(){ return nullptr ; }
		}

		property Windows::UI::Xaml::Media::CompositeTransform^ ItemTransform
		{
			void set(Windows::UI::Xaml::Media::CompositeTransform ^ value){ this->_itemtransform =  value  ;}
			Windows::UI::Xaml::Media::CompositeTransform^ get() {return this->_itemtransform ; }
		}



	private:
		float64 _itemheight,_itemwidth, _imagewidht , _imageheight , _initialposition;
		Platform::String ^ _imagesource ;
		

#pragma endregion

#pragma region Controls and Animations

	public:

		void AnimateTo(float64 _x , float64 _y);

	private:
		Windows::UI::Xaml::Controls::Image ^ _imageitem ;
		Windows::UI::Xaml::Media::CompositeTransform ^ _itemtransform ;

		Windows::UI::Xaml::Media::Animation::Storyboard ^ _translatestory ;
		Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ _translatexanimation;
		Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ _translateyanimation;

		void initanimations();
		void Storyboard_Completed_1(Platform::Object^ sender, Platform::Object^ e);
#pragma endregion

	}; 
}