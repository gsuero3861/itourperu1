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

		public delegate void StackViewManipulationStartedEventHandler(Platform::Object ^ sender , int32 _type);
		public delegate void StackViewManipulationFinishedEventHandler(Platform::Object ^ sender , int32 _type);
		public delegate void StackViewOpenEventHandler(Platform::Object^ sender, int32 _stacknumber );
		public delegate void StackViewCloseEventHandler(Platform::Object^ sender, int32 _stacknumber , float64 _scroll  );
		public delegate void StackViewScrollToEventHandler(Platform::Object^ sender, float64 delta);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class IStackView sealed : public Windows::UI::Xaml::Controls::Grid 
		{
		public:
			IStackView();
			event StackViewOpenEventHandler ^ OnStackViewOpen ;
			event StackViewCloseEventHandler ^ OnStackViewClose ;
			event StackViewManipulationStartedEventHandler ^ StackViewManipulationStarted ;
			event StackViewManipulationFinishedEventHandler^ StackViewManipulationFinished ;
			event StackViewScrollToEventHandler^ StackViewScrollTo ;
#pragma region Controls

		private:
			Windows::UI::Xaml::Controls::Grid ^ _itemsgrid ;
			Windows::UI::Xaml::Controls::StackPanel^ _itemspanel ;
			Windows::UI::Xaml::Controls::Grid^ _begingrid ;
			Windows::UI::Xaml::Controls::Grid^ _endgrid ;
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
				void set(float64 value)
				{
					this->_itemwidth = value ; 
					this->_itemsgrid->Width = value ;
					//this->_begingrid->Width = (_stackwidth - this->_itemwidth) / 2 ;
					//this->_endgrid->Width = (_stackwidth - this->_itemwidth) / 2 ;
				}
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

			property float64 StackWidth
			{
				void set(float64 value)
				{
					this->_stackwidth = value ;
					this->_begingrid->Width = (_stackwidth - this->_itemwidth) / 2 ;
					this->_endgrid->Width = (_stackwidth - this->_itemwidth) / 2 ;
				}
				float64 get(){return this->_stackwidth;}
			}

			property float64 CurrentWidth
			{
				void set(float64 value){ this->_currentwidth = value ;}
				float64 get()
				{
					if(this->_stackviewstate == StackViewState::Open)
						return  this->StackWidth+ this->_itemwidth * (this->_numberofitems - 1 );
					else
						return  this->_stackwidth ;
				}
			}

			property int32 StackNumber
			{
				void set(int32 value){ this->_stacknumber =  value ;}
				int32 get(){ return this->_stacknumber ;}
			}
			
			property int32 StackSize
			{
				void set(int32 value){ this->_numberofitems =  value ;}
				int32 get(){ return this->_numberofitems ;}
			}

			property float64 CurrentScale
			{
				void set(float64 value){ this->_currentscale =  value ;}
				float64 get(){ return this->_currentscale ;}
			}

		private: 
			float64 _stackwidth, _currentwidth ;
			float64 _itemwidth, _itemheight ;
			float64 _itemcontentwidth , _itemcontentheight ;
			int32 _selecteditem, _stacknumber ;
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
			bool _cananimate  ;
			float64 _constantdelta ; //to scroll 
			float64 _tempwidth ;

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
			void ItemsGrid_ManipulationInertiaStarting(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e);
			void ItemsGrid_PointerExited_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void ItemsGrid_ManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e);

			void StackItemSelected_1(Platform::Object ^ sender , int32 _currentitem);

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