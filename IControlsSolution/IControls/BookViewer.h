#include "pch.h"

namespace IControls
{
	public ref class BookViewer sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		BookViewer();

#pragma region Properties

	public:

		property float64 BookHeight
		{
			void set(float64 value)
			{
				this->_bookheight =  value ;
				this->_pagedchapters->ScrollHeight =  this->_bookheight ;
			}
			float64 get(){return this->_bookheight;}
		}

		property float64 BookWidth
		{
			void set(float64 value)
			{
				this->_bookwidth =  value ;
				this->_pagedchapters->ScrollWidth = this->_bookwidth ;
			}
			float64 get(){return this->_bookwidth;}
		}

		property int32 SelectedChapter
		{
			void set(int32 value){ this->_selectedchapter =  value ;}
			int32 get(){return this->_selectedchapter;}
		}

		property int32 SelectedSection
		{
			void set(int32 value){ this->_selectedsetion =  value; }
			int32 get(){return this->_selectedsetion ;}
		}
		
		property int32 SelectedPage
		{
			void set(int32 value){ this->_selectionpage =  value ; }
			int32 get(){return this->_selectionpage ;}
		}

		property DataSource::BookDataSource^ BookSource
		{
			void set(DataSource::BookDataSource^ value)
			{
				this->_datasource = value ;
				loaddata();
			}
			DataSource::BookDataSource^ get(){ return _datasource ; }
		}

	private:
		float64 _bookwidth, _bookheight ;
		int32 _selectedchapter , _selectedsetion, _selectionpage ;
		DataSource::BookDataSource^ _datasource ;
#pragma endregion

#pragma region Controls

	private: 
		Windows::UI::Xaml::Controls::Grid ^ _fullscrollgrid ;
		PagedScroll ^ _pagedchapters ; 
		AnimationView ^ _animationview ;
		ScrollView::IScrollView ^ _fullpagescroll ;
		
#pragma endregion
 

#pragma region Private Methods

	private:
		void setcurrentpage(int32 _chapter, int32 _section, int32 _page );
		void initcontrols();
		void loaddata();

		void setanimationview();

#pragma endregion
 

#pragma region Private Properties

	private:

		bool _manipulationfullgridenable ;

#pragma endregion

#pragma region Events Methods

	private:
		void PagedScroll_AnimationOutStarted(Platform::Object^ sender);
		void PagedScroll_AnimationOutCompleted(Platform::Object^ sender);

		void AnimationViewCompleted(Platform::Object ^ sender );

		void FullGrid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void FullGrid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
		void FullGrid_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e);
		
		void IScrollView_LockParent(Platform::Object^ sender, int32 item);
		void IScrollView_UnlockParent(Platform::Object^ sender, int32 item);
		void IScrollView_ItemChanged(Platform::Object^ sender, int32 item);

#pragma endregion

	};
}