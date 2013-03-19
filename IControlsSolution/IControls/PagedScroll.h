#include  "pch.h"

namespace IControls
{

	public enum class PagedScrollManipulationState
	{  Enable, Dislable };

	public ref class PagedScroll sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
			PagedScroll();

#pragma region Controls

	private :
		Windows::UI::Xaml::Controls::ScrollViewer^ _pagedscroll ;
		Windows::UI::Xaml::Controls::StackPanel^ _pagedpanel ;
		Windows::UI::Xaml::Media::CompositeTransform^ _paneltransform ;
		void initpagedscrollcontrols();

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
		
		property Windows::Foundation::Collections::IVector<DataSource::ChapterDataSource^>^ ChaptersList
		{
			void set( Windows::Foundation::Collections::IVector<DataSource::ChapterDataSource^>^ value)
			{
				this->_datasource = value ; 
				temploaddata();
			}
			Windows::Foundation::Collections::IVector<DataSource::ChapterDataSource^>^ get(){ return this->_datasource ; }
		}

	private:
		Windows::Foundation::Collections::IVector<DataSource::ChapterDataSource^>^ _datasource ;
		float64 _scrollwidth, _scrollheight ;
		int32 _currentitem ;

#pragma endregion

#pragma region Private Properties

	private:
		PagedScrollManipulationState _manipulationstate ; //State of manipualtion
		float64 _initialtranslate, _finaltranslate ;
		float64 _cumulative ;

#pragma endregion

#pragma region Private Methods
	private:
		 
		void PagedScroll_ItemLockParent(Platform::Object^ sender,  int32 _item);
		void PagedScroll_ItemUnlockParent(Platform::Object^ sender,  int32 _item);

		void PagedPanel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void PagedPanel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void PagedPanel_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e);
		void PagedPanel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void PagedPanel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
		void PagedPanel_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e);

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
		void tempinit() ;
		void temploaddata();

#pragma endregion

	};
}