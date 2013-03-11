#include "pch.h"

namespace IControls
{
	namespace StackView
	{
		public delegate void StackViewItemManipulationStartedEventHandler(Platform::Object ^ sender , int32 _currentitem);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class IStackView sealed : public Windows::UI::Xaml::Controls::Grid 
		{
		public:
			IStackView();
#pragma region Controls

		private:
			Windows::UI::Xaml::Controls::Grid ^ _itemsgrid ;

#pragma endregion

#pragma region Public Properties
		
		public:
			property float64 ItemHeight
			{
				void set(float64 value){ this->_itemheight =  value ; }
				float64 get(){ return this->_itemheight ;}
			}

			property float64 ItemWidth
			{
				void set(float64 value){ this->_itemwidth = value ; }
				float64 get(){ return this->_itemwidth; }
			}

			property float64 ItemContentHeight
			{
				void set(float64 value){ this->_itemcontentheight =  value ;}
				float64 get(){ return this->_itemcontentheight ; }
			}

			property float64 ItemContentWidth
			{
				void set(float64 value){ this->_itemcontentwidth = value ;}
				float64 get(){ return this->_itemcontentwidth ;}
			}

			property float64 FullXPosition
			{
				void set(float64 value){ this->_fullXposition =  value ;}
				float64 get(){ return this->_fullXposition ;}
			}

			property float64 FullYPosition
			{
				void set(float64 value){ this->_fullYposition ;}
				float64 get(){ return this->_fullYposition ; }
			}

			property int32 SelectedItem
			{
				void set(int32 value){this->_selecteditem = value ;}
				int32 get(){ return this->_selecteditem  ;}
			}

		private: 
			float64 _itemwidth, _itemheight ;
			float64 _itemcontentwidth , _itemcontentheight ;
			int32 _selecteditem ;
			float64 _fullXposition , _fullYposition ;


#pragma endregion

#pragma region Public Methods

		public:
			void SetToFullScreen();
			void SetToThumb();

			void AnimateToFullScreen();
			void AnimateToThumb();

#pragma endregion

#pragma region Private Methods

		private :
			void openstack();
			void closestack();
			void loaditems();
			void updatestackitems();

			void ItemsGrid_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
			void ItemsGrid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
			void ItemsGrid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
			void ItemsGrid_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void ItemsGrid_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
#pragma endregion

#pragma region Private Properties

		private:
			int32 _numberofitems, _numberoftouches ;
			float64 _currentscale ;
#pragma endregion
 
		};

	}
}