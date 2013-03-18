#include "pch.h"
namespace IControls	
{

	namespace  ScrollView
	{

		public enum class IScrollManipulationState
		{  Enable, Dislable };

		public ref class IScrollView sealed : public Windows::UI::Xaml::Controls::Grid
		{
		public:
				IScrollView();

#pragma region Controls

		private :
			Windows::UI::Xaml::Controls::ScrollViewer^ _iscroll ;
			Windows::UI::Xaml::Controls::StackPanel^ _ipanel ;
			Windows::UI::Xaml::Media::CompositeTransform^ _paneltransform ;
			void initIscrollcontrols();

#pragma endregion

#pragma region Public Properties

		public:
			property float64 ScrollWidth
			{
				void set(float64 value){ this->_scrollwidth =  value ;}
				float64 get(){return this->_scrollwidth;}
			}

			property float64 ScrollHeight
			{
				void set(float64 value){ this->_scrollheight =  value ;}
				float64 get(){return this->_scrollheight ;}
			}

			property int32 CurrentItem
			{
				void set(int32 value){ this->_currentitem =  value ;}
				int32 get(){return this->_currentitem ;}
			}

			property int32 NumberofItems
			{
				void set(int32 value){ this->_numberofitems =  value ;}
				int32 get(){return this->_numberofitems ;}
			}

		private:
			float64 _scrollwidth, _scrollheight ;
			int32 _currentitem ,  _numberofitems ;

#pragma endregion

#pragma region Private Properties

		private:
			IScrollManipulationState _manipulationstate ; //State of manipualtion
			float64 _initialtranslate, _finaltranslate ;
			float64 _cumulative, _maxcumulative , _maxptranslate , _maxntranslate , _temptranslate ;

#pragma endregion

#pragma region Private Methods
		private:
		 
			void IScroll_ItemLockParent(Platform::Object^ sender,  int32 _item);
			void IScroll_ItemUnlockParent(Platform::Object^ sender,  int32 _item);

			void IPanel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void IPanel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
			void IPanel_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e);
			void IPanel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
			void IPanel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
			void IPanel_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e);

#pragma endregion

#pragma region Animation
		private:
			Windows::UI::Xaml::Media::Animation::Storyboard^ _panelstory;
			Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _panelanimation ;
			void initanimationproperties();

#pragma endregion

#pragma region DataLoad Temp
		public:
			property Windows::Foundation::Collections::IVector<Platform::String^>^ ItemsList
			{
				void set(Windows::Foundation::Collections::IVector<Platform::String^>^ value)
				{
					this->_itemslist = value ; 
					tempinit();
				}
				Windows::Foundation::Collections::IVector<Platform::String^>^ get(){ return this->_itemslist ; }
			}

		private :
			 Windows::Foundation::Collections::IVector<Platform::String^>^ _itemslist;
			void tempinit();

#pragma endregion

		};

	}
}