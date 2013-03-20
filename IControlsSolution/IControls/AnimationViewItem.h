#include "pch.h"

namespace IControls
{
	public ref class AnimationViewItem sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		AnimationViewItem();

#pragma region Properties

	public:
		property float64 ItemHeight
		{
			void set(float64 value){ this->_itemheight =  value ; }
			float64 get(){return this->_itemheight ;}
		}

		property float64 ItemWidth
		{
			void set(float64 value){ this->_itemwidth =  value ;}
			float64 get(){return this->_itemwidth ;}
		}

	private:
		float64 _itemheight,_itemwidth ;
		

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

#pragma endregion

	}; 
}