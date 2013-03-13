#include "pch.h"

namespace IControls
{
	namespace StackView
	{
		public enum class StackViewState
		{
			Open,Close
		};

		public enum class StackManipulationType
		{
			StackManipulation,
			ItemManipulation,
			NoneManipulation
		};

		public enum class StackTouches
		{
			Zero,One,Two,Many
		};

		public delegate void StackViewItemManipulationStartedEventHandler(Platform::Object ^ sender , int32 _currentitem);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class IStackView sealed : public Windows::UI::Xaml::Controls::Grid 
		{
		public:
			IStackView();

#pragma region Controls

		private:
			Windows::UI::Xaml::Controls::Grid ^ _itemsgrid ;
			void initcontrols();
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

#pragma region Load of Data

		public:
			property Windows::Foundation::Collections::IVector<Platform::String^>^ ItemsList
			{
				void set(Windows::Foundation::Collections::IVector<Platform::String^>^ value)
				{
					this->_itemslist = value ;
					loaditems();
				}
				Windows::Foundation::Collections::IVector<Platform::String^>^ get(){ return this->_itemslist ; }
			}

		private: 
			void loaditems();//temp load of data 
			Windows::Foundation::Collections::IVector<Platform::String^>^ _itemslist ;

#pragma endregion
			
#pragma region Private Properties

		private:
			int32 _numberofitems, _numberoftouches ;
			float64 _currentscale ;
			float64 _angles[3] ;

			StackViewState _stackviewstate ;
			StackManipulationType _stackmanipulatiotype ;
			StackTouches _stacktouches ;
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
			void initproperties();

			void openstack();
			void closestack();
			void updatestackitems();

#pragma endregion
		
#pragma region Animation

		private:
			Windows::UI::Xaml::Media::Animation::Storyboard^ _itemsgridstory;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _itemgridanimation ;
			void initanimationproperties();

#pragma endregion

#pragma region Event Handlers Functions

			void ItemsGrid_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
			void ItemsGrid_DoubleTapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs^ e);
			void ItemsGrid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
			void ItemsGrid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
			void ItemsGrid_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void ItemsGrid_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);

#pragma endregion

#pragma region Tap Pointer Functions

		public:
			typedef bool (IStackView:: * TappedFunctions)();
			bool tapclosedstack();
			bool tapopennedstack(); 

		private:
			TappedFunctions _tapfunctions[2] ;
			void inittapfunctions();
			 
#pragma endregion

#pragma region DoubleTap Pointer Functions

		public:
			typedef bool (IStackView:: * DoubleTappedFunctions)();
			bool doubletapclosedstack();
			bool doubletapopennedstack(); 

		private:
			DoubleTappedFunctions _doubletapfunctions[2] ;
			void initdoubletapfunctions();
			 
#pragma endregion
 
		};

	}
}