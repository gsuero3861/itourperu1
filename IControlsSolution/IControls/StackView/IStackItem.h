#include "pch.h"

namespace IControls
{
	namespace StackView
	{
		public delegate void StackItemSelectedEventHandler(Platform::Object ^ sender , int32 _currentitem);
		public delegate void StackItemTappedEventHandler(Platform::Object ^ sender , int32 _currentitem);
		public delegate void StackItemFullScreenAnimationCompletedEventHandler(Platform::Object ^ sender );

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class IStackItem sealed : public Windows::UI::Xaml::Controls::Grid 
		{
		public:
			IStackItem();
			event StackItemSelectedEventHandler ^ StackItemSelected ;
			event StackItemTappedEventHandler^ StackItemTapped ;
			event StackItemFullScreenAnimationCompletedEventHandler^ StackItemFullScreenAnimationCompleted ;


#pragma region Properties

		public:
			property float64 ItemWidth
			{
				void set(float64 value)
				{ 
					this->_itemwidth =  value ; 
					this->Width = value ;
					this->_itemtransform->CenterX = value / 2 ;
				}
				float64 get(){ return this->_itemwidth ;}
			}

			property float64 ItemHeight
			{
				void set(float64 value)
				{ 
					this->_itemheight =  value ; 
					this->Height = value ;
					this->_itemtransform->CenterY = value / 2 ;
				}
				float64 get(){ return this->_itemheight ;}
			}

			property int32 ItemNumber
			{
				void set(int32 value)
				{ 
					this->_itemnumber =  value ;  
				}
				int32 get(){ return this->_itemnumber ;}
			}

			property float64 InitialAngle
			{
				void set(float64 value)
				{ 
					this->_initialangle =  value ;  
					this->_itemtransform->Rotation = value ; 
				}
				float64 get(){ return this->_initialangle ;}
			}

			property int32 ZIndex
			{
				void set(int32 value){ Windows::UI::Xaml::Controls::Canvas::SetZIndex(this , value ); }
				int32 get(){ return 0 ; }
			}


		private:
			float64 _itemwidth, _itemheight ;
			int32 _itemnumber ;
			float64 _initialangle ;

#pragma endregion

			
#pragma region Item

		public:

			void OpenItem();
			void CloseItem();

			property Windows::UI::Xaml::Media::CompositeTransform ^ ItemTransform
			{
				void set(Windows::UI::Xaml::Media::CompositeTransform ^ value){}
				Windows::UI::Xaml::Media::CompositeTransform^ get(){return this->_itemtransform ;}
			}

		private:
			Windows::UI::Xaml::Media::CompositeTransform ^  _itemtransform ;


#pragma endregion

#pragma region Private Methods and Variables

		private:
			int32 _numberoftouches ;
			void initprivatemethodsandvariables();
			 
			//_itemtransform
			Windows::UI::Xaml::Media::Animation::Storyboard ^ _translatestory ;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ _translateXanimation;
			Windows::UI::Xaml::Media::Animation::Storyboard ^ _rotatestory ;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ _rotateanimation;
			 
			void initanimationproperties();
#pragma endregion



#pragma region Item Content
		public:
			property Windows::UI::Xaml::Controls::Grid^ ItemContent
			{
				void set(Windows::UI::Xaml::Controls::Grid ^ value){ this->_itemcontent->Children->Append(value); }
				Windows::UI::Xaml::Controls::Grid^ get(){return this->_itemcontent;}
			}

			property float64 ItemContentWidth
			{
				void set(float64 value)
				{ 
					this->_itemcontentwidth =  value ; 
					//_itemcontent->Width = value ;
				}
				float64 get(){ return this->_itemcontentwidth ;}
			}

			property float64 ItemContentHeight
			{
				void set(float64 value) 
				{
					this->_itemcontentheight =  value ; 
					_itemcontent->Height = value ;
				}
				float64 get(){ return this->_itemcontentheight ;}
			}

		private :
			Windows::UI::Xaml::Controls::Grid ^ _itemcontent ;
			float64 _itemcontentwidth, _itemcontentheight ;
			void inititemcontent();

#pragma endregion


#pragma region Item Content Touch

		private:
			void ItemContent_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void ItemContent_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void ItemContent_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
			
#pragma endregion
			
#pragma region Item Content Animation
		public :
			void RestoreItem();
			void AnimateTo(float64 _x, float64 _y ,float64 _scale);

		private :
			//Animations for the selected item
			//Windows::UI::Xaml::Media::CompositeTransform ^ _currenttransform ;

			Windows::UI::Xaml::Media::Animation::Storyboard^ _translatestory1 ;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _translatexanimation1 ;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _translateyanimation1 ;

			Windows::UI::Xaml::Media::Animation::Storyboard^ _scalestory1 ;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _scalexanimation1 ;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _scaleyanimation1 ;

			Windows::UI::Xaml::Media::Animation::Storyboard^ _rotatestory1;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _rotateanimation1 ;
			void inititemanimationstory();
			void Storyboard_Completed_1(Platform::Object^ sender, Platform::Object^ e);

#pragma endregion

		};

	}
}